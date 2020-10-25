
// DemoTrackerView.h : CDemoTrackerView ��Ľӿ�
//

#pragma once

class CMyRectTracker : public CRectTracker
{
public:
	void CMyRectTracker::Draw(CDC * pDC, CPen * pen);
};

class CDemoTrackerView : public CView
{
public:
	HCURSOR m_hCursorHit;
	CMyRectTracker m_RectTracker; 
	CPoint m_ptStart;  //���ο����ʼ��
	BOOL m_bDrawing;   //��ͼ״̬
protected: // �������л�����
	CDemoTrackerView();
	DECLARE_DYNCREATE(CDemoTrackerView)

// ����
public:
	CDemoTrackerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CDemoTrackerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // DemoTrackerView.cpp �еĵ��԰汾
inline CDemoTrackerDoc* CDemoTrackerView::GetDocument() const
   { return reinterpret_cast<CDemoTrackerDoc*>(m_pDocument); }
#endif

