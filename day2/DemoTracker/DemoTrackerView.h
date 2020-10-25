
// DemoTrackerView.h : CDemoTrackerView 类的接口
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
	CPoint m_ptStart;  //矩形框的起始点
	BOOL m_bDrawing;   //截图状态
protected: // 仅从序列化创建
	CDemoTrackerView();
	DECLARE_DYNCREATE(CDemoTrackerView)

// 特性
public:
	CDemoTrackerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDemoTrackerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // DemoTrackerView.cpp 中的调试版本
inline CDemoTrackerDoc* CDemoTrackerView::GetDocument() const
   { return reinterpret_cast<CDemoTrackerDoc*>(m_pDocument); }
#endif

