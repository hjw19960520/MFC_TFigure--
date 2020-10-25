
// DemoGdiView.cpp : CDemoGdiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CDemoGdiView ����/����

CDemoGdiView::CDemoGdiView()
{
	// TODO: �ڴ˴���ӹ������

}

CDemoGdiView::~CDemoGdiView()
{
}

BOOL CDemoGdiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDemoGdiView ����

void CDemoGdiView::OnDraw(CDC* /*pDC*/)
{
	CDemoGdiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDemoGdiView ��ӡ


void CDemoGdiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDemoGdiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDemoGdiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDemoGdiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CDemoGdiView ���

#ifdef _DEBUG
void CDemoGdiView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoGdiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoGdiDoc* CDemoGdiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoGdiDoc)));
	return (CDemoGdiDoc*)m_pDocument;
}
#endif //_DEBUG


// CDemoGdiView ��Ϣ�������



void CDemoGdiView::OnPaint()
{
	CPaintDC dc(this); // device context for painting��CPaintDC��OnPaint��Ϣר�õ�
	// TODO: �ڴ˴������Ϣ����������

	//����ͼ�β��԰���
#if 1:
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
	int nSize=10;
	CRect rect(50,50,200,200);
	//����
	CPen pen(PS_SOLID,2,RGB(255,0,0));
	dc.SelectObject(&pen); //ѡ���
	//��ˢ
	CRect rect1(200,200,250,250);
	CBrush brush(RGB(0,0,225));
	CBrush brush1(HS_CROSS,RGB(0,255,0));
	dc.SelectObject(&brush); //ѡ��ˢ
	dc.Rectangle(rect1);
	//����Բ
	dc.SelectObject(&brush1); 
	dc.Ellipse(5*nSize,5*nSize,10*nSize,10*nSize);
	dc.DrawText(TEXT("CDC"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);//λ�����м�
	//����ֱ��
	dc.MoveTo(100,100);
	dc.LineTo(200,200);
	//����������
	POINT aPoint[5] = {10,10,10,400,400,400,400,10,10,10};
	dc.Polyline(aPoint,5);
	//���߻���
	POINT aPoint1[4] = {10,10,10,400,400,400,400,10};
	dc.PolyBezier(aPoint1,4);
	//sin cos����

	int nWidth = rect.Width();
	int nHeight = rect.Height();
	CPoint aPoint3[SEGMENT];

	for(int i=0;i<SEGMENT;i++)
	{
		aPoint3[i].x = (i*nWidth)/SEGMENT;
		aPoint3[i].y = (int)((1-sin((2*PI*i)/SEGMENT))*(nHeight/2));
	}

	dc.Polyline(aPoint3,SEGMENT);//����
#endif
}


void CDemoGdiView::OnLButtonDown(UINT nFlags, CPoint point)//����Ŵ�ͼ��
{
	//����ͼ�εĲ��԰���
	#if 0��
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static int nSize=10; 
	CView::OnLButtonDown(nFlags, point);
	MessageBox(TEXT("test"));
	//CClientDC dc(this);
	CWindowDC dc(this);
	CClientDC dc1(this);
	CPoint p1(0,0);
	CPoint p2(300,300);
	//Բ�Ļ���
	dc.Ellipse(5*nSize,5*nSize,10*nSize,10*nSize);
	nSize++;

	//�ڶ��ַ��� ����rect���Ʒ����Բ��/Բ��
	CRect rect(200,200,300,400);
	dc.Rectangle(rect);
	//dc.Ellipse(rect); //Բ��
	//dc.Arc(200,200,300,400,0,0,300,300); //Բ��
	dc1.Pie(rect,p1,p2); //��
	//����������
	CFont font;
	font.CreatePointFont(110,TEXT("Arial"));//�������壬�����С
	dc1.SelectObject(&font);
	dc1.TextOut(400,200,TEXT("Location"));
	#endif
	LButtonDown=true;
    startPt=point;

	//TODO:����������

	//TODO:ӳ��ģʽ��ֱ�߰��������ƾ���
	
}

void CDemoGdiView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnRButtonDblClk(nFlags, point);

}


void CDemoGdiView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonDblClk(nFlags, point);

}


void CDemoGdiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//��Ϣ�����ʾ����
	#if 0:   
	CView::OnLButtonUp(nFlags, point);
	int nResult = this->MessageBox(_T("��Ϣ����"),_T("����"),MB_YESNOCANCEL | MB_ICONINFORMATION);

	if(nResult == IDYES)
	{
		this->MessageBox(_T("��ѡ����YES"));
	}
	else if(nResult == IDNO)
	{
		this->MessageBox(_T("��ѡ����NO"));
	}
	else if(nResult == IDCANCEL)
	{
		this->MessageBox(_T("��ѡ����ȡ��"));
	}

	#endif
	LButtonDown = false;
    endPt = point;
}

//����ƶ���Ϣ
void CDemoGdiView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
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
