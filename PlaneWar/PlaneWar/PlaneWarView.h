
// PlaneWarView.h : CPlaneWarView 类的接口
//

#pragma once
#include"Bullet.h"
#include"MyPlane.h"

class CPlaneWarView : public CView
{
protected: // 仅从序列化创建
	CPlaneWarView();
	DECLARE_DYNCREATE(CPlaneWarView)

	// 特性
public:
	CPlaneWarDoc* GetDocument() const;

	// 操作
public:

	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPlaneWarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void ResizeWindow(); //调整窗口
	void DrawMyPlane(const MyPlane &player, CDC *pDC);
	void DrawBullet(const Bullet &bts, CDC *pDC);
	void DrawEnemy(const Enemy &enemys, CDC *pDC);

 // 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGameStart();
	afx_msg void OnGameExit();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHelpGuide();
};

#ifndef _DEBUG  // PlaneWarView.cpp 中的调试版本
inline CPlaneWarDoc* CPlaneWarView::GetDocument() const
{
	return reinterpret_cast<CPlaneWarDoc*>(m_pDocument);
}
#endif

