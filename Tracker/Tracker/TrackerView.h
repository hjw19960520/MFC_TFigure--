
// TrackerView.h : CTrackerView ��Ľӿ�
//

#pragma once

#define IDB_DRAW_START 19990201
#define IDB_SAVE 19990202
#define IDB_BACK 19990203


class CTrackerView : public CView
{
protected: // �������л�����
	CTrackerView();  //����
	DECLARE_DYNCREATE(CTrackerView)

// ����
public:
	CTrackerDoc* GetDocument() const;
	void CTrackerView::WordDraw();
	BOOL bDraw;

	CButton m_DrawButton; //��ʼ��ͼ
	CButton m_SettingsButton;//����
	CButton m_SaveButton; //����
	CButton m_BackButton; //����
// ����
public:
	BOOL m_bFlagDraw;  //��ʼ��ͼǰ��С��Ǿ��ο�
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
	virtual ~CTrackerView();
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
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPushButtonClicked();
	afx_msg void OnPushButtonClicked1();
	afx_msg void OnPushButtonClicked2();
//	afx_msg void OnPaint();
//	afx_msg void OnPaint();
};

#ifndef _DEBUG  // TrackerView.cpp �еĵ��԰汾
inline CTrackerDoc* CTrackerView::GetDocument() const
   { return reinterpret_cast<CTrackerDoc*>(m_pDocument); }
#endif

