
// DemoMouseMoveView.cpp : CDemoMouseMoveView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DemoMouseMove.h"
#endif

#include "DemoMouseMoveDoc.h"
#include "DemoMouseMoveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDemoMouseMoveView

IMPLEMENT_DYNCREATE(CDemoMouseMoveView, CView)

	BEGIN_MESSAGE_MAP(CDemoMouseMoveView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDemoMouseMoveView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		//	ON_WM_LBUTTONDBLCLK()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_PAINT()
	END_MESSAGE_MAP()

	// CDemoMouseMoveView 构造/析构

	CDemoMouseMoveView::CDemoMouseMoveView()
	{
		// TODO: 在此处添加构造代码
		m_startRect = FALSE;
		m_startRect = 0;
		m_OldPoint = 0;

	}

	CDemoMouseMoveView::~CDemoMouseMoveView()
	{
	}

	BOOL CDemoMouseMoveView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// CDemoMouseMoveView 绘制

	void CDemoMouseMoveView::OnDraw(CDC* /*pDC*/)
	{
		CDemoMouseMoveDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
	}


	// CDemoMouseMoveView 打印


	void CDemoMouseMoveView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CDemoMouseMoveView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CDemoMouseMoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CDemoMouseMoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CDemoMouseMoveView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		//ClientToScreen(&point);
		//OnContextMenu(this, point);
		CClientDC dc(this);
		//dc.SetROP2(R2_NOT);
		//dc.SelectStockObject(NULL_BRUSH);
		//dc.Rectangle(CRect(m_startPoint,m_OldPoint));

		dc.SetROP2(R2_NOT);   //此为关键!!!
		dc.SelectStockObject(NULL_BRUSH); //不使用画刷
		dc.Rectangle(CRect(100,100,200,200));

	}

	void CDemoMouseMoveView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CDemoMouseMoveView 诊断

#ifdef _DEBUG
	void CDemoMouseMoveView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CDemoMouseMoveView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CDemoMouseMoveDoc* CDemoMouseMoveView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoMouseMoveDoc)));
		return (CDemoMouseMoveDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CDemoMouseMoveView 消息处理程序


	//void CDemoMouseMoveView::OnLButtonDblClk(UINT nFlags, CPoint point)
	//{
	//	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//
	//	CView::OnLButtonDblClk(nFlags, point);
	//}


	void CDemoMouseMoveView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		// TODO: Add your message handler code here and/or call default
		m_startRect = TRUE;   //鼠标左键单击，设置可以开始绘制矩形框
		m_startPoint = point; //记录开始点
		m_OldPoint = point;   //设置老点也为开始点

		CView::OnLButtonDown(nFlags, point);
	}


	void CDemoMouseMoveView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		m_startRect = FALSE; //重置绘制矩形框标志  暂停鼠标移动绘制

		//消隐最后的一个矩形（其原理跟拖动时矩形框绘制原理相同）
		CClientDC dc(this);
		//dc.SetROP2(R2_NOT);
		//dc.SelectStockObject(NULL_BRUSH);
		//dc.Rectangle(CRect(m_startPoint,m_OldPoint));

		//dc.SetROP2(R2_NOT);   //此为关键!!!
		//dc.SelectStockObject(NULL_BRUSH); //不使用画刷
		//dc.Rectangle(CRect(100,100,200,200));
		this->MessageBox(_T("test"));

		CView::OnLButtonUp(nFlags, point);
	}


	void CDemoMouseMoveView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CClientDC dc(this);   //获取设备句柄

		//SetRop2 Specifies the new drawing mode.(MSDN)
		//R2_NOT   Pixel is the inverse of the screen color.(MSDN)
		//即：该函数用来定义绘制的颜色，而该参数则将颜色设置为原屏幕颜色的反色
		//这样，如果连续绘制两次的话，就可以恢复原来屏幕的颜色了（如下）
		//但是，这里的连续两次绘制却不是在一次消息响应中完成的
		//而是在第一次拖动响应的绘制可以显示（也就是看到的），第二次拖动绘制实现擦出（也就看不到了）
		dc.SetROP2(R2_NOT);   //此为关键!!!
		dc.SelectStockObject(NULL_BRUSH); //不使用画刷
		if (TRUE == m_startRect)   //根据是否有单击判断是否可以画矩形
		{
			dc.Rectangle(CRect(m_startPoint,m_OldPoint));
			dc.Rectangle(CRect(m_startPoint,point));
			m_OldPoint = point;
			m_endFirstRect = FALSE;
		}
		else
		{
			m_endFirstRect = TRUE;
		}
		CView::OnMouseMove(nFlags, point);

	}


	void CDemoMouseMoveView::OnPaint() //只是页面刷新时会重绘
	{
		CPaintDC dc(this); // device context for painting
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CView::OnPaint()
		dc.SetROP2(R2_NOT);   //此为关键!!!
		dc.SelectStockObject(NULL_BRUSH); //不使用画刷

		dc.Rectangle(CRect(100,100,200,200));//示例方形
		//dc.Rectangle(CRect(100,100,200,200));
		//if(m_startRect == TRUE)
		//{
		//	dc.SetROP2(R2_NOT);   //此为关键!!!
		//	dc.SelectStockObject(NULL_BRUSH); //不使用画刷
		//	dc.Rectangle(CRect(100,100,200,200));
		//}


	}
