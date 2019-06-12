
// PlaneWarView.cpp : CPlaneWarView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PlaneWar.h"
#endif

#include "PlaneWarDoc.h"
#include "PlaneWarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneWarView

IMPLEMENT_DYNCREATE(CPlaneWarView, CView)

BEGIN_MESSAGE_MAP(CPlaneWarView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_START, &CPlaneWarView::OnGameStart)
	ON_COMMAND(ID_GAME_EXIT, &CPlaneWarView::OnGameExit)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_HELP_GUIDE, &CPlaneWarView::OnHelpGuide)
END_MESSAGE_MAP()

// CPlaneWarView 构造/析构

CPlaneWarView::CPlaneWarView()
{
	// TODO: 在此处添加构造代码

}

CPlaneWarView::~CPlaneWarView()
{
}

BOOL CPlaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneWarView 绘制

void CPlaneWarView::OnDraw(CDC* pDC)
{
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 绘制背景
	const CImage &bk = pDoc->getBackground();
	if (!bk.IsNull())
	{
		bk.Draw(pDC->GetSafeHdc(), 0, 0,
			pDoc->getWidth(), pDoc->getHeight());
	}


	// 绘制玩家飞机
	DrawMyPlane(pDoc->getPlanePlayer(), pDC);

	// 绘制子弹
	for (const auto &b : pDoc->getBullet())
	{
		DrawBullet(b, pDC);
	}

	// 绘制敌机
	for (const auto pe : pDoc->getEnemy())
	{
		DrawEnemy(pe, pDC);
	}

	// 打印成绩
	CString str;
	str.Format(_T("%.4d"), pDoc->getScore());

	pDC->SetBkMode(TRANSPARENT);

	CFont font;
	font.CreatePointFont(300, _T("微软雅黑"));
	CFont *oldFont = pDC->SelectObject(&font);

	pDC->TextOut(0, 0, str);

	pDC->SelectObject(oldFont);
}


// CPlaneWarView 诊断

#ifdef _DEBUG
void CPlaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneWarDoc* CPlaneWarView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneWarDoc)));
	return (CPlaneWarDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneWarView 消息处理程序
void CPlaneWarView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	switch (nChar)
	{
	case VK_LEFT: case 'A':
		pDoc->playerMove(3);
		break;
	case VK_RIGHT: case 'D':
		pDoc->playerMove(4);
		break;
	case VK_UP: case 'W':
		pDoc->playerMove(1);
		break;
	case VK_DOWN: case 'S':
		pDoc->playerMove(2);
		break;
	case VK_SPACE:
		pDoc->launchBullet();
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPlaneWarView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	ResizeWindow();

}

void CPlaneWarView::ResizeWindow()
{
	//  First get a pointer to the document
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->getWidth() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->getHeight() + nHeightDiff;
	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CPlaneWarView::DrawMyPlane(const MyPlane &player, CDC *pDC)
{
	const CImage &img = player.getImage();
	if (!img.IsNull())
	{
		img.Draw(pDC->GetSafeHdc(), player.getX(), player.getY(),
			player.getWidth(), player.getHeight());
	}
}
void CPlaneWarView::DrawEnemy(const Enemy &enemys, CDC *pDC)
{
	/*CImage image;
	image.Load(_T("..\\Image\\Enemy.png"));
	transparent(image);
	image.Draw(pDC->GetSafeHdc(), enemys.getX(), enemys.getY(),
		enemys.getWidth(), enemys.getHeight());*/
	const CImage &img = enemys.getImage();
	if (!img.IsNull())
	{
		img.Draw(pDC->GetSafeHdc(), enemys.getX(), enemys.getY(),
			enemys.getWidth(), enemys.getHeight());
	}
}
void CPlaneWarView::DrawBullet(const Bullet &bts, CDC *pDC)
{
	/*CImage image;
	image.Load(_T("..\\Image\\Bullet.png"));
	transparent(image);
	image.Draw(pDC->GetSafeHdc(), bts.getX(), bts.getY(),
		bts.getWidth(), bts.getHeight());*/
	const CImage &img = bts.getImage();
	if (!img.IsNull())
	{
		img.Draw(pDC->GetSafeHdc(), bts.getX(), bts.getY(),
			10, 25);
	}
}


void CPlaneWarView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//  First get a pointer to the document
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	switch (nIDEvent)
	{
	case 1:
		pDoc->updateBullets();
		pDoc->updateEnemies();

		if (pDoc->isGameOver())
		{
			KillTimer(1);
			KillTimer(2);
			MessageBox(_T("GameOver"), 0, MB_ICONWARNING);
		}

		break;
	case 2:
		break;
	default:
		break;
	}

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CPlaneWarView::OnGameStart()
{
	// TODO: 在此添加命令处理程序代码
	//  First get a pointer to the document
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->init();

	SetTimer(1, 40, 0);
	SetTimer(2, 500, 0);
}


void CPlaneWarView::OnGameExit()
{
	// TODO: 在此添加命令处理程序代码
	AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
}


BOOL CPlaneWarView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CPlaneWarView::OnHelpGuide()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("方向键或ADWS键控制飞机移动\n空格键发射子弹\n初始生命值为20\n中弹-1，被撞-2\n生命值≤0游戏结束"),
		_T("PlaneWar(飞机大战)-玩法规则"), MB_ICONINFORMATION);
}
