
// DemoTrackerView.cpp : CDemoTrackerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
		// ��׼��ӡ����
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

	// CDemoTrackerView ����/����

	CDemoTrackerView::CDemoTrackerView()
	{
		// TODO: �ڴ˴���ӹ������
		m_RectTracker.m_nStyle = CRectTracker::solidLine|CRectTracker::resizeOutside;
		m_RectTracker.m_rect.SetRect(-3,-3,-3,-3);
		m_RectTracker.m_nHandleSize = 5;

	}

	CDemoTrackerView::~CDemoTrackerView()
	{
	}

	BOOL CDemoTrackerView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// CDemoTrackerView ����

	void CDemoTrackerView::OnDraw(CDC* /*pDC*/)
	{
		CDemoTrackerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	}


	// CDemoTrackerView ��ӡ


	void CDemoTrackerView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CDemoTrackerView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CDemoTrackerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CDemoTrackerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
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


	// CDemoTrackerView ���

#ifdef _DEBUG
	void CDemoTrackerView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CDemoTrackerView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CDemoTrackerDoc* CDemoTrackerView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoTrackerDoc)));
		return (CDemoTrackerDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CDemoTrackerView ��Ϣ�������

	void CDemoTrackerView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		int nHitTest = m_RectTracker.HitTest(point);

		if (nHitTest < 0)//����������ڿ�������棬��ʼ�����壬��¼��ʼ�㣬�������ʶ��TRUE
		{
			m_ptStart = point;
			m_bDrawing = TRUE;
		} 
		else//���򣬸��ݵ��λ���϶��������ſ���
		{
			m_RectTracker.Track(this,point,TRUE);
		}

		CView::OnLButtonDown(nFlags, point);
	}


	void CDemoTrackerView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		m_bDrawing = FALSE;

		CView::OnLButtonUp(nFlags, point);

	}


	void CDemoTrackerView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if (m_bDrawing)
		{
			m_RectTracker.m_rect.SetRect(m_ptStart.x-1,m_ptStart.y-1,point.x,point.y);
		}
		else
		{
			int nHitTest = m_RectTracker.HitTest(point);
			switch (nHitTest)//���ݹ��Ϳ�������λ�ã�����������״
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
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		m_RectTracker.m_rect.SetRect(-3,-3,-3,-3);

		CView::OnRButtonDown(nFlags, point);
	}


	void CMyRectTracker::Draw(CDC * pDC, CPen * pen)
	{
		if((m_nStyle & dottedLine) != 0 || (m_nStyle & solidLine) != 0 )
		{
			VERIFY(pDC->SaveDC() != 0);//�����豸�����ĵĵ�ǰ״̬

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

			rect.InflateRect(+1,+1);//������εĿ�͸�
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
		// TODO: �ڴ˴������Ϣ����������
		//����
		CPen pen(PS_SOLID,6,RGB(0,0,255));
		//dc.SelectObject(&pen); //ѡ���
		m_RectTracker.Draw(&dc,&pen);
		// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
	}
