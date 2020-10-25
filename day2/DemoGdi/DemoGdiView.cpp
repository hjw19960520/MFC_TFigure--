
// DemoGdiView.cpp : CDemoGdiView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DemoGdi.h"
#endif

#include "DemoGdiDoc.h"
#include "DemoGdiView.h"

#include <math.h>

#define SEGMENT 500
#define PI 3.1415926

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPoint startPt,endPt;
bool LButtonDown;

// CDemoGdiView

IMPLEMENT_DYNCREATE(CDemoGdiView, CView)

BEGIN_MESSAGE_MAP(CDemoGdiView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDemoGdiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CDemoGdiView 构造/析构

CDemoGdiView::CDemoGdiView()
{
	// TODO: 在此处添加构造代码

}

CDemoGdiView::~CDemoGdiView()
{
}

BOOL CDemoGdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDemoGdiView 绘制

void CDemoGdiView::OnDraw(CDC* /*pDC*/)
{
	CDemoGdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDemoGdiView 打印


void CDemoGdiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDemoGdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDemoGdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDemoGdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CDemoGdiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDemoGdiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDemoGdiView 诊断

#ifdef _DEBUG
void CDemoGdiView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoGdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoGdiDoc* CDemoGdiView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoGdiDoc)));
	return (CDemoGdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CDemoGdiView 消息处理程序



void CDemoGdiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting，CPaintDC是OnPaint消息专用的
	// TODO: 在此处添加消息处理程序代码

	//绘制图形测试案例
#if 1:
	// 不为绘图消息调用 CView::OnPaint()
	int nSize=10;
	CRect rect(50,50,200,200);
	//画笔
	CPen pen(PS_SOLID,2,RGB(255,0,0));
	dc.SelectObject(&pen); //选择笔
	//画刷
	CRect rect1(200,200,250,250);
	CBrush brush(RGB(0,0,225));
	CBrush brush1(HS_CROSS,RGB(0,255,0));
	dc.SelectObject(&brush); //选择画刷
	dc.Rectangle(rect1);
	//绘制圆
	dc.SelectObject(&brush1); 
	dc.Ellipse(5*nSize,5*nSize,10*nSize,10*nSize);
	dc.DrawText(TEXT("CDC"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);//位于正中间
	//绘制直线
	dc.MoveTo(100,100);
	dc.LineTo(200,200);
	//绘制连接线
	POINT aPoint[5] = {10,10,10,400,400,400,400,10,10,10};
	dc.Polyline(aPoint,5);
	//曲线绘制
	POINT aPoint1[4] = {10,10,10,400,400,400,400,10};
	dc.PolyBezier(aPoint1,4);
	//sin cos曲线

	int nWidth = rect.Width();
	int nHeight = rect.Height();
	CPoint aPoint3[SEGMENT];

	for(int i=0;i<SEGMENT;i++)
	{
		aPoint3[i].x = (i*nWidth)/SEGMENT;
		aPoint3[i].y = (int)((1-sin((2*PI*i)/SEGMENT))*(nHeight/2));
	}

	dc.Polyline(aPoint3,SEGMENT);//绘制
#endif
}


void CDemoGdiView::OnLButtonDown(UINT nFlags, CPoint point)//点击放大图像
{
	//绘制图形的测试案例
	#if 0：
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int nSize=10; 
	CView::OnLButtonDown(nFlags, point);
	MessageBox(TEXT("test"));
	//CClientDC dc(this);
	CWindowDC dc(this);
	CClientDC dc1(this);
	CPoint p1(0,0);
	CPoint p2(300,300);
	//圆的绘制
	dc.Ellipse(5*nSize,5*nSize,10*nSize,10*nSize);
	nSize++;

	//第二种方法 利用rect绘制方框和圆形/圆弧
	CRect rect(200,200,300,400);
	dc.Rectangle(rect);
	//dc.Ellipse(rect); //圆形
	//dc.Arc(200,200,300,400,0,0,300,300); //圆弧
	dc1.Pie(rect,p1,p2); //饼
	//字体风格设置
	CFont font;
	font.CreatePointFont(110,TEXT("Arial"));//设置字体，字体大小
	dc1.SelectObject(&font);
	dc1.TextOut(400,200,TEXT("Location"));
	#endif
	LButtonDown=true;
    startPt=point;

	//TODO:更多字体风格

	//TODO:映射模式，直尺案例，控制精度
	
}

void CDemoGdiView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnRButtonDblClk(nFlags, point);

}


void CDemoGdiView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDblClk(nFlags, point);

}


void CDemoGdiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//消息点击提示弹出
	#if 0:   
	CView::OnLButtonUp(nFlags, point);
	int nResult = this->MessageBox(_T("消息内容"),_T("标题"),MB_YESNOCANCEL | MB_ICONINFORMATION);

	if(nResult == IDYES)
	{
		this->MessageBox(_T("你选择了YES"));
	}
	else if(nResult == IDNO)
	{
		this->MessageBox(_T("你选择了NO"));
	}
	else if(nResult == IDCANCEL)
	{
		this->MessageBox(_T("你选择了取消"));
	}

	#endif
	LButtonDown = false;
    endPt = point;
}

//鼠标移动消息
void CDemoGdiView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (LButtonDown == true)
	{
		CDC *pDC = GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		CRect rect(startPt,endPt);
		pDC->Rectangle(rect);
		CRect rect2(startPt,point);
		pDC->Rectangle(rect2);
		endPt = point;
		ReleaseDC(pDC);
	}
	CView::OnMouseMove(nFlags, point);
}
