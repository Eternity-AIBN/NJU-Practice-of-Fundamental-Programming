
// PlaneWarView.cpp : CPlaneWarView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CPlaneWarView ����/����

CPlaneWarView::CPlaneWarView()
{
	// TODO: �ڴ˴���ӹ������

}

CPlaneWarView::~CPlaneWarView()
{
}

BOOL CPlaneWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneWarView ����

void CPlaneWarView::OnDraw(CDC* pDC)
{
	CPlaneWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// ���Ʊ���
	const CImage &bk = pDoc->getBackground();
	if (!bk.IsNull())
	{
		bk.Draw(pDC->GetSafeHdc(), 0, 0,
			pDoc->getWidth(), pDoc->getHeight());
	}


	// ������ҷɻ�
	DrawMyPlane(pDoc->getPlanePlayer(), pDC);

	// �����ӵ�
	for (const auto &b : pDoc->getBullet())
	{
		DrawBullet(b, pDC);
	}

	// ���Ƶл�
	for (const auto pe : pDoc->getEnemy())
	{
		DrawEnemy(pe, pDC);
	}

	// ��ӡ�ɼ�
	CString str;
	str.Format(_T("%.4d"), pDoc->getScore());

	pDC->SetBkMode(TRANSPARENT);

	CFont font;
	font.CreatePointFont(300, _T("΢���ź�"));
	CFont *oldFont = pDC->SelectObject(&font);

	pDC->TextOut(0, 0, str);

	pDC->SelectObject(oldFont);
}


// CPlaneWarView ���

#ifdef _DEBUG
void CPlaneWarView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneWarDoc* CPlaneWarView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneWarDoc)));
	return (CPlaneWarDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneWarView ��Ϣ�������
void CPlaneWarView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
}


BOOL CPlaneWarView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CPlaneWarView::OnHelpGuide()
{
	// TODO: �ڴ���������������
	MessageBox(_T("�������ADWS�����Ʒɻ��ƶ�\n�ո�������ӵ�\n��ʼ����ֵΪ20\n�е�-1����ײ-2\n����ֵ��0��Ϸ����"),
		_T("PlaneWar(�ɻ���ս)-�淨����"), MB_ICONINFORMATION);
}
