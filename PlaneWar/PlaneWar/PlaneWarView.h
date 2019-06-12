
// PlaneWarView.h : CPlaneWarView ��Ľӿ�
//

#pragma once
#include"Bullet.h"
#include"MyPlane.h"

class CPlaneWarView : public CView
{
protected: // �������л�����
	CPlaneWarView();
	DECLARE_DYNCREATE(CPlaneWarView)

	// ����
public:
	CPlaneWarDoc* GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CPlaneWarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void ResizeWindow(); //��������
	void DrawMyPlane(const MyPlane &player, CDC *pDC);
	void DrawBullet(const Bullet &bts, CDC *pDC);
	void DrawEnemy(const Enemy &enemys, CDC *pDC);

 // ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // PlaneWarView.cpp �еĵ��԰汾
inline CPlaneWarDoc* CPlaneWarView::GetDocument() const
{
	return reinterpret_cast<CPlaneWarDoc*>(m_pDocument);
}
#endif

