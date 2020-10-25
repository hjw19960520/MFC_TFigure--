
// DemoMouseMoveView.h : CDemoMouseMoveView ��Ľӿ�
//

#pragma once


class CDemoMouseMoveView : public CView
{
private:
	BOOL m_startRect;   //���ƾ��ο��־
	BOOL m_endFirstRect;
	CPoint m_startPoint; //���ο�ʼ��
	CPoint m_OldPoint;   //���ο��յ㣨����������һ�εĵ㣬������������Old��ʶ
protected: // �������л�����2
	CDemoMouseMoveView();
	DECLARE_DYNCREATE(CDemoMouseMoveView)

// ����
public:
	CDemoMouseMoveDoc* GetDocument() const;

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
	virtual ~CDemoMouseMoveView();
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
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // DemoMouseMoveView.cpp �еĵ��԰汾
inline CDemoMouseMoveDoc* CDemoMouseMoveView::GetDocument() const
   { return reinterpret_cast<CDemoMouseMoveDoc*>(m_pDocument); }
#endif

