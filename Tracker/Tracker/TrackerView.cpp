
// TrackerView.cpp : CTrackerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Tracker.h"
#endif

#include "TrackerDoc.h"
#include "TrackerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrackerView

IMPLEMENT_DYNCREATE(CTrackerView, CView)

	BEGIN_MESSAGE_MAP(CTrackerView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTrackerView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_SETCURSOR()
		ON_WM_LBUTTONDOWN()
		ON_WM_CREATE()
		ON_BN_CLICKED(IDB_DRAW_START,OnPushButtonClicked)  
		ON_BN_CLICKED(IDB_SAVE,OnPushButtonClicked1)
		ON_BN_CLICKED(IDB_BACK,OnPushButtonClicked2)
		//		ON_WM_PAINT()
//		ON_WM_PAINT()
	END_MESSAGE_MAP()

	void CTrackerView::OnDraw(CDC* pDC)
	{
		CTrackerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		CBrush brush(RGB(0,0,255));
		CBrush * oldBrush = pDC->SelectObject(&brush);
		CRect rect;

		pDoc->m_RectTracker.GetTrueRect(&rect); //得到CRectTracker中的m_rect的大小，将其传递给rect；

		//pDC->Ellipse(&rect);
		if(bDraw == TRUE) 
		{    
			pDC->Ellipse(&rect);
		}

		pDoc->m_RectTracker.Draw(pDC);            //这句画才真正的将这个四边形画出来；
		//绘制直线
			//画笔
		CPen pen(PS_SOLID,2,RGB(255,0,0));          //颜色红色 实线 2粗度
		pDC->SelectObject(&pen);                    //选择笔
		pDC->MoveTo(10,400);
		pDC->LineTo(800,400);//
		pDC->MoveTo(10,450);
		pDC->LineTo(800,450);//
		pDC->MoveTo(10,500);
		pDC->LineTo(800,500);//

		//文字绘制
		CString str("brillian");
		COLORREF oldColor = pDC->SetTextColor((55,233,33));
		pDC->TextOut(400,400,str);
		pDC->SetTextColor(oldColor);
	    pDC->DrawText(TEXT("CDC"),-1,CRect(100,100,200,200),DT_SINGLELINE|DT_CENTER|DT_VCENTER);//位于正中间

		pDC->SelectObject(oldBrush);
		if(m_bFlagDraw == TRUE)
		{
			CClientDC dc(this);
			dc.SelectStockObject(BLACK_BRUSH);
			dc.Rectangle(30,10,200,60);
		}

	    
		// TODO: add draw code for native data here
	}
	// CTrackerView 构造/析构

	CTrackerView::CTrackerView()
	{
		// TODO: 在此处添加构造代码
		bDraw = FALSE;
		m_bFlagDraw = FALSE;
	}

	CTrackerView::~CTrackerView()
	{
	}

	BOOL CTrackerView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}


	// CTrackerView 绘制

	//void CTrackerView::OnDraw(CDC* /*pDC*/)
	//{
	//	CTrackerDoc* pDoc = GetDocument();
	//	ASSERT_VALID(pDoc);
	//	if (!pDoc)
	//		return;
	//
	//	// TODO: 在此处为本机数据添加绘制代码
	//}


	// CTrackerView 打印


	void CTrackerView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CTrackerView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CTrackerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CTrackerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CTrackerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CTrackerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CTrackerView 诊断

#ifdef _DEBUG
	void CTrackerView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CTrackerView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CTrackerDoc* CTrackerView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrackerDoc)));
		return (CTrackerDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CTrackerView 消息处理程序


	BOOL CTrackerView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CTrackerDoc* pDoc = GetDocument();

		if((pWnd == this) && (pDoc->m_RectTracker.SetCursor(this,nHitTest)))
		{
			return TRUE;
		}
		return CView::OnSetCursor(pWnd, nHitTest, message);
	}


	void CTrackerView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		//判断鼠标点击的区域是在哪里，在在矩形区域内，还是区域外
		int nRetCode = GetDocument()->m_RectTracker.HitTest(point);

		if(nRetCode < 0)            //不在矩形区域
		{
			//给temp变量初始化
			CRectTracker  temp;
			temp.m_rect.SetRect(0,0,0,0);
			temp.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;

			//TrackRubberBand函数直到鼠标左键提起的时候才会返回，并把左键提起的位置也记录了下来
			//该函数过程中，不会产生鼠标移动消息
			temp.TrackRubberBand(this,point,TRUE);
			//使得矩形为正确的坐标，不会出现负的坐标
			temp.m_rect.NormalizeRect();
			//此时把bDraw设为false
			//bDraw = FALSE;
			CClientDC dc(this);

			CBrush brush(RGB(0,0,255));
			CBrush * oldBrush = dc.SelectObject(&brush);
			//把新的矩形区域绘制出来
			//temp.Track(this,point,TRUE);
			temp.Draw(&dc);
			CRect rect;
			temp.GetTrueRect(&rect); //得到CRectTracker中的m_rect的大小，将其传递给rect；
			dc.Ellipse(&rect);
		}
		else                        //在矩形区域内
		{
			//Track和TrackRubberBand类似，直到鼠标左键提起的时候才会返回，并把左键提起的位置也记录了下来
			//该函数过程中，不会产生鼠标移动消息
			GetDocument()->m_RectTracker.Track(this,point,TRUE);
			//设置为true,则需要在矩形内绘制椭圆
			bDraw = TRUE;
			//this->m_bFlagDraw = TRUE;

			//窗口无效，调用Onpaint函数
			Invalidate(TRUE);
		}
		CView::OnLButtonDown(nFlags, point);
	}


	int CTrackerView::OnCreate(LPCREATESTRUCT lpCreateStruct) //创建窗口
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		// TODO:  在此添加您专用的创建代码
		this->m_DrawButton.Create(_T("开始绘制"),      //按钮标题
			WS_CHILD | WS_VISIBLE | WS_BORDER,         //按钮风格
			CRect(40,10,200,60),					 //按钮大小
			this,									 //按钮父指针
			IDB_DRAW_START);							//该按钮对应的ID号
		this->m_SaveButton.Create(_T("保存"),      //按钮标题
			WS_CHILD | WS_VISIBLE | WS_BORDER,         //按钮风格
			CRect(220,10,380,60),					 //按钮大小
			this,									 //按钮父指针
			IDB_SAVE);							//该按钮对应的ID号
		this->m_BackButton.Create(_T("回退"),      //按钮标题
			WS_CHILD | WS_VISIBLE | WS_BORDER,         //按钮风格
			CRect(400,10,560,60),					 //按钮大小
			this,									 //按钮父指针
			IDB_BACK);							//该按钮对应的ID号
		return 0;
	}
	void CTrackerView::OnPushButtonClicked()
	{
		this->MessageBox(_T("开始绘图"),
			_T("tips:"));
		m_bFlagDraw = TRUE; //黑色标记
		Invalidate(TRUE);

	}
	void CTrackerView::OnPushButtonClicked1()
	{
		this->MessageBox(_T("保存成功"),
			_T("tips:"));
		m_bFlagDraw = FALSE; //黑色标记
		Invalidate(TRUE);

	}

	void CTrackerView::OnPushButtonClicked2()
	{
		this->MessageBox(_T("回退成功"),
			_T("tips:"));
		m_bFlagDraw = FALSE; //黑色标记
		Invalidate(TRUE);
	}

	//文字绘制
	//dc.DrawText(TEXT("CDC"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);//位于正中间

	//	void CTrackerView::OnPaint()
	//	{
	//		CPaintDC dc(this); // device context for painting
	//		// TODO: 在此处添加消息处理程序代码
	//		if(m_bFlagDraw) ;  //标记信号
	//		// 不为绘图消息调用 CView::OnPaint()
	//	}


//	void CTrackerView::OnPaint()
//	{
//		CPaintDC dc(this); // device context for painting
//		// TODO: 在此处添加消息处理程序代码
//		// 不为绘图消息调用 CView::OnPaint()
//	}
