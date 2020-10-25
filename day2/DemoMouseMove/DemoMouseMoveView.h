
// DemoMouseMoveView.h : CDemoMouseMoveView 类的接口
//

#pragma once


class CDemoMouseMoveView : public CView
{
private:
	BOOL m_startRect;   //绘制矩形框标志
	BOOL m_endFirstRect;
	CPoint m_startPoint; //矩形框开始点
	CPoint m_OldPoint;   //矩形框终点（但是它是上一次的点，所以这里用了Old标识
protected: // 仅从序列化创建2
	CDemoMouseMoveView();
	DECLARE_DYNCREATE(CDemoMouseMoveView)

// 特性
public:
	CDemoMouseMoveDoc* GetDocument() const;

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
	virtual ~CDemoMouseMoveView();
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
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // DemoMouseMoveView.cpp 中的调试版本
inline CDemoMouseMoveDoc* CDemoMouseMoveView::GetDocument() const
   { return reinterpret_cast<CDemoMouseMoveDoc*>(m_pDocument); }
#endif

