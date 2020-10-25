
// TrackerView.cpp : CTrackerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
		// ��׼��ӡ����
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

		pDoc->m_RectTracker.GetTrueRect(&rect); //�õ�CRectTracker�е�m_rect�Ĵ�С�����䴫�ݸ�rect��

		//pDC->Ellipse(&rect);
		if(bDraw == TRUE) 
		{    
			pDC->Ellipse(&rect);
		}

		pDoc->m_RectTracker.Draw(pDC);            //��仭�������Ľ�����ı��λ�������
		//����ֱ��
			//����
		CPen pen(PS_SOLID,2,RGB(255,0,0));          //��ɫ��ɫ ʵ�� 2�ֶ�
		pDC->SelectObject(&pen);                    //ѡ���
		pDC->MoveTo(10,400);
		pDC->LineTo(800,400);//
		pDC->MoveTo(10,450);
		pDC->LineTo(800,450);//
		pDC->MoveTo(10,500);
		pDC->LineTo(800,500);//

		//���ֻ���
		CString str("brillian");
		COLORREF oldColor = pDC->SetTextColor((55,233,33));
		pDC->TextOut(400,400,str);
		pDC->SetTextColor(oldColor);
	    pDC->DrawText(TEXT("CDC"),-1,CRect(100,100,200,200),DT_SINGLELINE|DT_CENTER|DT_VCENTER);//λ�����м�

		pDC->SelectObject(oldBrush);
		if(m_bFlagDraw == TRUE)
		{
			CClientDC dc(this);
			dc.SelectStockObject(BLACK_BRUSH);
			dc.Rectangle(30,10,200,60);
		}

	    
		// TODO: add draw code for native data here
	}
	// CTrackerView ����/����

	CTrackerView::CTrackerView()
	{
		// TODO: �ڴ˴���ӹ������
		bDraw = FALSE;
		m_bFlagDraw = FALSE;
	}

	CTrackerView::~CTrackerView()
	{
	}

	BOOL CTrackerView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}


	// CTrackerView ����

	//void CTrackerView::OnDraw(CDC* /*pDC*/)
	//{
	//	CTrackerDoc* pDoc = GetDocument();
	//	ASSERT_VALID(pDoc);
	//	if (!pDoc)
	//		return;
	//
	//	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//}


	// CTrackerView ��ӡ


	void CTrackerView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CTrackerView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CTrackerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CTrackerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
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


	// CTrackerView ���

#ifdef _DEBUG
	void CTrackerView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CTrackerView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CTrackerDoc* CTrackerView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrackerDoc)));
		return (CTrackerDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CTrackerView ��Ϣ�������


	BOOL CTrackerView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		CTrackerDoc* pDoc = GetDocument();

		if((pWnd == this) && (pDoc->m_RectTracker.SetCursor(this,nHitTest)))
		{
			return TRUE;
		}
		return CView::OnSetCursor(pWnd, nHitTest, message);
	}


	void CTrackerView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		//�ж����������������������ھ��������ڣ�����������
		int nRetCode = GetDocument()->m_RectTracker.HitTest(point);

		if(nRetCode < 0)            //���ھ�������
		{
			//��temp������ʼ��
			CRectTracker  temp;
			temp.m_rect.SetRect(0,0,0,0);
			temp.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;

			//TrackRubberBand����ֱ�������������ʱ��Ż᷵�أ�������������λ��Ҳ��¼������
			//�ú��������У������������ƶ���Ϣ
			temp.TrackRubberBand(this,point,TRUE);
			//ʹ�þ���Ϊ��ȷ�����꣬������ָ�������
			temp.m_rect.NormalizeRect();
			//��ʱ��bDraw��Ϊfalse
			//bDraw = FALSE;
			CClientDC dc(this);

			CBrush brush(RGB(0,0,255));
			CBrush * oldBrush = dc.SelectObject(&brush);
			//���µľ���������Ƴ���
			//temp.Track(this,point,TRUE);
			temp.Draw(&dc);
			CRect rect;
			temp.GetTrueRect(&rect); //�õ�CRectTracker�е�m_rect�Ĵ�С�����䴫�ݸ�rect��
			dc.Ellipse(&rect);
		}
		else                        //�ھ���������
		{
			//Track��TrackRubberBand���ƣ�ֱ�������������ʱ��Ż᷵�أ�������������λ��Ҳ��¼������
			//�ú��������У������������ƶ���Ϣ
			GetDocument()->m_RectTracker.Track(this,point,TRUE);
			//����Ϊtrue,����Ҫ�ھ����ڻ�����Բ
			bDraw = TRUE;
			//this->m_bFlagDraw = TRUE;

			//������Ч������Onpaint����
			Invalidate(TRUE);
		}
		CView::OnLButtonDown(nFlags, point);
	}


	int CTrackerView::OnCreate(LPCREATESTRUCT lpCreateStruct) //��������
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		// TODO:  �ڴ������ר�õĴ�������
		this->m_DrawButton.Create(_T("��ʼ����"),      //��ť����
			WS_CHILD | WS_VISIBLE | WS_BORDER,         //��ť���
			CRect(40,10,200,60),					 //��ť��С
			this,									 //��ť��ָ��
			IDB_DRAW_START);							//�ð�ť��Ӧ��ID��
		this->m_SaveButton.Create(_T("����"),      //��ť����
			WS_CHILD | WS_VISIBLE | WS_BORDER,         //��ť���
			CRect(220,10,380,60),					 //��ť��С
			this,									 //��ť��ָ��
			IDB_SAVE);							//�ð�ť��Ӧ��ID��
		this->m_BackButton.Create(_T("����"),      //��ť����
			WS_CHILD | WS_VISIBLE | WS_BORDER,         //��ť���
			CRect(400,10,560,60),					 //��ť��С
			this,									 //��ť��ָ��
			IDB_BACK);							//�ð�ť��Ӧ��ID��
		return 0;
	}
	void CTrackerView::OnPushButtonClicked()
	{
		this->MessageBox(_T("��ʼ��ͼ"),
			_T("tips:"));
		m_bFlagDraw = TRUE; //��ɫ���
		Invalidate(TRUE);

	}
	void CTrackerView::OnPushButtonClicked1()
	{
		this->MessageBox(_T("����ɹ�"),
			_T("tips:"));
		m_bFlagDraw = FALSE; //��ɫ���
		Invalidate(TRUE);

	}

	void CTrackerView::OnPushButtonClicked2()
	{
		this->MessageBox(_T("���˳ɹ�"),
			_T("tips:"));
		m_bFlagDraw = FALSE; //��ɫ���
		Invalidate(TRUE);
	}

	//���ֻ���
	//dc.DrawText(TEXT("CDC"),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);//λ�����м�

	//	void CTrackerView::OnPaint()
	//	{
	//		CPaintDC dc(this); // device context for painting
	//		// TODO: �ڴ˴������Ϣ����������
	//		if(m_bFlagDraw) ;  //����ź�
	//		// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
	//	}


//	void CTrackerView::OnPaint()
//	{
//		CPaintDC dc(this); // device context for painting
//		// TODO: �ڴ˴������Ϣ����������
//		// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
//	}
