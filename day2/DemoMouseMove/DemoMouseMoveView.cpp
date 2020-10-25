
// DemoMouseMoveView.cpp : CDemoMouseMoveView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
		// ��׼��ӡ����
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

	// CDemoMouseMoveView ����/����

	CDemoMouseMoveView::CDemoMouseMoveView()
	{
		// TODO: �ڴ˴���ӹ������
		m_startRect = FALSE;
		m_startRect = 0;
		m_OldPoint = 0;

	}

	CDemoMouseMoveView::~CDemoMouseMoveView()
	{
	}

	BOOL CDemoMouseMoveView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// CDemoMouseMoveView ����

	void CDemoMouseMoveView::OnDraw(CDC* /*pDC*/)
	{
		CDemoMouseMoveDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	}


	// CDemoMouseMoveView ��ӡ


	void CDemoMouseMoveView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CDemoMouseMoveView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CDemoMouseMoveView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CDemoMouseMoveView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
	}

	void CDemoMouseMoveView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		//ClientToScreen(&point);
		//OnContextMenu(this, point);
		CClientDC dc(this);
		//dc.SetROP2(R2_NOT);
		//dc.SelectStockObject(NULL_BRUSH);
		//dc.Rectangle(CRect(m_startPoint,m_OldPoint));

		dc.SetROP2(R2_NOT);   //��Ϊ�ؼ�!!!
		dc.SelectStockObject(NULL_BRUSH); //��ʹ�û�ˢ
		dc.Rectangle(CRect(100,100,200,200));

	}

	void CDemoMouseMoveView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CDemoMouseMoveView ���

#ifdef _DEBUG
	void CDemoMouseMoveView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CDemoMouseMoveView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CDemoMouseMoveDoc* CDemoMouseMoveView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoMouseMoveDoc)));
		return (CDemoMouseMoveDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CDemoMouseMoveView ��Ϣ�������


	//void CDemoMouseMoveView::OnLButtonDblClk(UINT nFlags, CPoint point)
	//{
	//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//
	//	CView::OnLButtonDblClk(nFlags, point);
	//}


	void CDemoMouseMoveView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		// TODO: Add your message handler code here and/or call default
		m_startRect = TRUE;   //���������������ÿ��Կ�ʼ���ƾ��ο�
		m_startPoint = point; //��¼��ʼ��
		m_OldPoint = point;   //�����ϵ�ҲΪ��ʼ��

		CView::OnLButtonDown(nFlags, point);
	}


	void CDemoMouseMoveView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		m_startRect = FALSE; //���û��ƾ��ο��־  ��ͣ����ƶ�����

		//��������һ�����Σ���ԭ����϶�ʱ���ο����ԭ����ͬ��
		CClientDC dc(this);
		//dc.SetROP2(R2_NOT);
		//dc.SelectStockObject(NULL_BRUSH);
		//dc.Rectangle(CRect(m_startPoint,m_OldPoint));

		//dc.SetROP2(R2_NOT);   //��Ϊ�ؼ�!!!
		//dc.SelectStockObject(NULL_BRUSH); //��ʹ�û�ˢ
		//dc.Rectangle(CRect(100,100,200,200));
		this->MessageBox(_T("test"));

		CView::OnLButtonUp(nFlags, point);
	}


	void CDemoMouseMoveView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		CClientDC dc(this);   //��ȡ�豸���

		//SetRop2 Specifies the new drawing mode.(MSDN)
		//R2_NOT   Pixel is the inverse of the screen color.(MSDN)
		//�����ú�������������Ƶ���ɫ�����ò�������ɫ����Ϊԭ��Ļ��ɫ�ķ�ɫ
		//��������������������εĻ����Ϳ��Իָ�ԭ����Ļ����ɫ�ˣ����£�
		//���ǣ�������������λ���ȴ������һ����Ϣ��Ӧ����ɵ�
		//�����ڵ�һ���϶���Ӧ�Ļ��ƿ�����ʾ��Ҳ���ǿ����ģ����ڶ����϶�����ʵ�ֲ�����Ҳ�Ϳ������ˣ�
		dc.SetROP2(R2_NOT);   //��Ϊ�ؼ�!!!
		dc.SelectStockObject(NULL_BRUSH); //��ʹ�û�ˢ
		if (TRUE == m_startRect)   //�����Ƿ��е����ж��Ƿ���Ի�����
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


	void CDemoMouseMoveView::OnPaint() //ֻ��ҳ��ˢ��ʱ���ػ�
	{
		CPaintDC dc(this); // device context for painting
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
		dc.SetROP2(R2_NOT);   //��Ϊ�ؼ�!!!
		dc.SelectStockObject(NULL_BRUSH); //��ʹ�û�ˢ

		dc.Rectangle(CRect(100,100,200,200));//ʾ������
		//dc.Rectangle(CRect(100,100,200,200));
		//if(m_startRect == TRUE)
		//{
		//	dc.SetROP2(R2_NOT);   //��Ϊ�ؼ�!!!
		//	dc.SelectStockObject(NULL_BRUSH); //��ʹ�û�ˢ
		//	dc.Rectangle(CRect(100,100,200,200));
		//}


	}
