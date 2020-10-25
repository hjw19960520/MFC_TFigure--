
// DemoTrackerView.cpp : CDemoTrackerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DemoTracker.h"
#endif

#include "DemoTrackerDoc.h"
#include "DemoTrackerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDemoTrackerView

IMPLEMENT_DYNCREATE(CDemoTrackerView, CView)

	BEGIN_MESSAGE_MAP(CDemoTrackerView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDemoTrackerView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_SETCURSOR()
		ON_WM_RBUTTONDOWN()
		ON_WM_PAINT()
	END_MESSAGE_MAP()

	// CDemoTrackerView 构造/析构

	CDemoTrackerView::CDemoTrackerView()
	{
		// TODO: 在此处添加构造代码
		m_RectTracker.m_nStyle = CRectTracker::solidLine|CRectTracker::resizeOutside;
		m_RectTracker.m_rect.SetRect(-3,-3,-3,-3);
		m_RectTracker.m_nHandleSize = 5;

	}

	CDemoTrackerView::~CDemoTrackerView()
	{
	}

	BOOL CDemoTrackerView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// CDemoTrackerView 绘制

	void CDemoTrackerView::OnDraw(CDC* /*pDC*/)
	{
		CDemoTrackerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
	}


	// CDemoTrackerView 打印


	void CDemoTrackerView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CDemoTrackerView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CDemoTrackerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CDemoTrackerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CDemoTrackerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CDemoTrackerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CDemoTrackerView 诊断

#ifdef _DEBUG
	void CDemoTrackerView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CDemoTrackerView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CDemoTrackerDoc* CDemoTrackerView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoTrackerDoc)));
		return (CDemoTrackerDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CDemoTrackerView 消息处理程序

	void CDemoTrackerView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		int nHitTest = m_RectTracker.HitTest(point);

		if (nHitTest < 0)//鼠标左键点击在框体的外面，开始画框体，记录起始点，将画框标识置TRUE
		{
			m_ptStart = point;
			m_bDrawing = TRUE;
		} 
		else//否则，根据点击位置拖动或是缩放框体
		{
			m_RectTracker.Track(this,point,TRUE);
		}

		CView::OnLButtonDown(nFlags, point);
	}


	void CDemoTrackerView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		m_bDrawing = FALSE;

		CView::OnLButtonUp(nFlags, point);

	}


	void CDemoTrackerView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if (m_bDrawing)
		{
			m_RectTracker.m_rect.SetRect(m_ptStart.x-1,m_ptStart.y-1,point.x,point.y);
		}
		else
		{
			int nHitTest = m_RectTracker.HitTest(point);
			switch (nHitTest)//根据光标和框体的相对位置，加载鼠标的形状
			{
			case -1:
				//m_hCursorHit = theApp.LoadCursor(IDC_SIZENWSE);
				break;
			case 0:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZENWSE);
				break;
			case 1:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZENESW);
				break;
			case 2:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZENWSE);
				break;
			case 3:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZENESW);
				break;
			case 4:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZENS);
				break;
			case 5:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZEWE );
				break;
			case 6:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZENS);
				break;
			case 7:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZEWE );
				break;
			case 8:
				m_hCursorHit = theApp.LoadStandardCursor(IDC_SIZEALL);
				break;
			}
		}

		CView::OnMouseMove(nFlags, point);
	}


	BOOL CDemoTrackerView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if(pWnd == this && m_RectTracker.SetCursor(this,nHitTest))
		{
			SetCursor(m_hCursorHit);
			return TRUE;
		}
		else
		{
			SetCursor(m_hCursorHit);
			return TRUE;
		}

		return CView::OnSetCursor(pWnd, nHitTest, message);
	}


	void CDemoTrackerView::OnRButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		m_RectTracker.m_rect.SetRect(-3,-3,-3,-3);

		CView::OnRButtonDown(nFlags, point);
	}


	void CMyRectTracker::Draw(CDC * pDC, CPen * pen)
	{
		if((m_nStyle & dottedLine) != 0 || (m_nStyle & solidLine) != 0 )
		{
			VERIFY(pDC->SaveDC() != 0);//保存设备上下文的当前状态

			pDC->SetMapMode(MM_TEXT);
			pDC->SetViewportOrg(0,0);
			pDC->SetWindowOrg(0,0);

			CRect rect = m_rect;
			rect.NormalizeRect();

			CPen *pOldPen = NULL;
			CBrush *pOldBrush = NULL;
			int nOldROP;

			pOldPen   = (CPen*)pDC->SelectObject(pen);
			pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
			nOldROP   = pDC->SetROP2(R2_COPYPEN);

			rect.InflateRect(+1,+1);//增大矩形的宽和高
			pDC->Rectangle(rect.left,rect.top,rect.right,rect.bottom);
			pDC->SetROP2(nOldROP); 

			if ((m_nStyle & (resizeInside|resizeOutside)) != 0)
			{
				UINT mask = GetHandleMask();
				for (int i = 0; i < 8; ++i)
				{
					if (mask & (1<<i))
					{
						GetHandleRect((TrackerHit)i,&rect);
						LOGPEN logpen;
						pen->GetLogPen(&logpen);
						pDC->FillSolidRect(rect,RGB(0,0,255));
					}
				}
			}
		} 
		else
		{
			CRectTracker::Draw(pDC);
		}
	}

	void CDemoTrackerView::OnPaint()
	{
		CPaintDC dc(this); 
		// device context for painting
		// TODO: 在此处添加消息处理程序代码
		//画笔
		CPen pen(PS_SOLID,6,RGB(0,0,255));
		//dc.SelectObject(&pen); //选择笔
		m_RectTracker.Draw(&dc,&pen);
		// 不为绘图消息调用 CView::OnPaint()
	}
