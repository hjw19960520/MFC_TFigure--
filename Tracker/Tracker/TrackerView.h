
// TrackerView.h : CTrackerView 类的接口
//

#pragma once

#define IDB_DRAW_START 19990201
#define IDB_SAVE 19990202
#define IDB_BACK 19990203


class CTrackerView : public CView
{
protected: // 仅从序列化创建
	CTrackerView();  //构造
	DECLARE_DYNCREATE(CTrackerView)

// 特性
public:
	CTrackerDoc* GetDocument() const;
	void CTrackerView::WordDraw();
	BOOL bDraw;

	CButton m_DrawButton; //开始绘图
	CButton m_SettingsButton;//设置
	CButton m_SaveButton; //保存
	CButton m_BackButton; //回退
// 操作
public:
	BOOL m_bFlagDraw;  //开始绘图前的小标记矩形块
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
	virtual ~CTrackerView();
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
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPushButtonClicked();
	afx_msg void OnPushButtonClicked1();
	afx_msg void OnPushButtonClicked2();
//	afx_msg void OnPaint();
//	afx_msg void OnPaint();
};

#ifndef _DEBUG  // TrackerView.cpp 中的调试版本
inline CTrackerDoc* CTrackerView::GetDocument() const
   { return reinterpret_cast<CTrackerDoc*>(m_pDocument); }
#endif

