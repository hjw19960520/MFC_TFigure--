
// TFigureDlg.cpp : ʵ���ļ�
//


#include "stdafx.h"
#include "TFigure.h"
#include "TFigureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTFigureDlg �Ի���




CTFigureDlg::CTFigureDlg(CWnd* pParent /*=NULL*/)  //��ʼ����Ա�б�
	: CDialogEx(CTFigureDlg::IDD, pParent)
	, bFourThree(FALSE)
	, bSixFive(false)
	, m_flagTracking(false)

	, m_bTracking(false)
	, m_bDrawLine(false)
	, m_bDrawCircle(false)
	, b_DrawArrow(false)
	, m_bDrawArrow(false)
	, m_bDrawTen(false)
	, m_bDrawWavy(false)
	, m_bSizeAll(false)
	, m_dragPoint(0)
	, m_bDragFlag(false)
	, m_iDragFlag(0)
	, m_bForbidSizeAll(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	for(int j=0;j<1024;j++)   //��ʼ����λ
	{	
		CPoint point(0,0);
		m_headPoint1[j] = point;
	}
	this->i = 0;

}

void CTFigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINEBUTTON, buttonLine);
	DDX_Control(pDX, IDC_BUTTONTEN, m_buttonTen);
	DDX_Control(pDX, IDC_ARROWBUTTON, m_buttonArrow);
	DDX_Control(pDX, IDC_BWAVY, m_buttonWavy);
}

BEGIN_MESSAGE_MAP(CTFigureDlg, CDialogEx)  //��Ϣӳ�� ע��
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTFigureDlg::OnBnClickedOk)
	//	ON_BN_CLICKED(IDC_BUTTON1, &CTFigureDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_STARTBUTTON, &CTFigureDlg::OnBnClickedStartbutton)
	//	ON_LBN_SELCHANGE(IDC_LIST1, &CTFigureDlg::OnLbnSelchangeList1)
	//ON_BN_CLICKED(IDC_CHECK1, &CTFigureDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDCANCEL, &CTFigureDlg::OnBnClickedCancel)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON3, &CTFigureDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_LINEBUTTON, &CTFigureDlg::OnBnClickedLinebutton)
	ON_BN_CLICKED(IDC_CURVEBUTTON, &CTFigureDlg::OnBnClickedCurvebutton)
	ON_BN_CLICKED(ID_CIRCLEBUTTON, &CTFigureDlg::OnBnClickedCirclebutton)
	//ON_BN_CLICKED(IDC_ARROW, &CTFigureDlg::OnBnClickedArrow)
	ON_BN_CLICKED(IDC_ARROWBUTTON, &CTFigureDlg::OnBnClickedArrowbutton)
	ON_BN_CLICKED(IDC_OPENFILEBUTTON, &CTFigureDlg::OnBnClickedOpenfilebutton)
	ON_BN_CLICKED(IDC_BUTTON2, &CTFigureDlg::OnBnClickedButton2)
	//ON_STN_CLICKED(IDC_PICTEN, &CTFigureDlg::OnStnClickedPicten)
	//	ON_BN_CLICKED(IDC_MFCBUTTON1, &CTFigureDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_BUTTONTEN, &CTFigureDlg::OnBnClickedButtonten)
	//ON_BN_CLICKED(IDC_BUTTON4, &CTFigureDlg::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTONWAVY, &CTFigureDlg::OnBnClickedButtonwavy)
	ON_BN_CLICKED(IDC_BWAVY, &CTFigureDlg::OnBnClickedBwavy)
END_MESSAGE_MAP()


// CTFigureDlg ��Ϣ�������

BOOL CTFigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	ShowWindow(SW_SHOWMAXIMIZED);//���
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->SetDlgItemTextW(IDC_COMBOX1,_T("��������"));//��ʼΪ��������
	//����buttonλͼ
	HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPTEN));   
	m_buttonTen.SetBitmap(hBmp);
	HBITMAP hBmp1=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPARROW));   
	m_buttonArrow.SetBitmap(hBmp1);
	HBITMAP hBmp2=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPWAVY));   
	m_buttonWavy.SetBitmap(hBmp2);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTFigureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTFigureDlg::OnPaint()
{	

	//TODO : test:  ���Ƽ�ͷ
#if 0:
	CClientDC dcTest(this);
	dcTest.DrawTextW(CString("test"),CRect(450,180,480,210),DT_CENTER);
	CPoint p1(40,40),p2(60,60);
	DrawArrow( p1, p2,45.0,10);
#endif

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
		//		if(m_flagTracking == TRUE)
		//{	
		//	//CPaintDC dc(this);
		//	char p1[10];
		//	sprintf(p1,"%d,%d",m_headPoint);
		//	CString str(p1);
		//	//AfxMessageBox(str);
		//	dc.MoveTo(m_headPoint);
		//	dc.LineTo(m_tailPoint);
		//}
	}
	else
	{
		CDialogEx::OnPaint();

	}

	//TODO : test:  ���Ƽ�ͷ  //����ʮ��
#if 0:
	CPaintDC dcTest(this);
	dcTest.DrawTextW(CString("test"),CRect(450,180,480,210),DT_CENTER);
	CPoint p1(40,40),p2(220,90);
	DrawTen( p1, p2,8.0,30);
#endif

	/*********************************/
	if(bFourThree == TRUE)
	{	
		//bSixFive = FALSE;
		CPoint left1(15,300),right1(1850,850);  //��������
		InitArea(left1,right1);
		CPoint left(20,340),right(1800,340);  //ģ�屳���߶�
		CString str[5];
		str[0]="A";
		str[1]="A-V";
		str[2]="V";
		CClientDC dc(this);
		for(int i=0;i<4;i++)
		{
			DrawLine(left, right);
			if(i<3)
			{
				dc.TextOutW(left.x,left.y,str[i]);
			}
			left.y+=60;
			right.y+=60;		
		}
	}
	if(bSixFive == TRUE)
	{	
		//this->bFourThree = FALSE;
		CPoint left1(0,250),right1(650,650);
		InitArea(left1,right1);

		CPoint left(20,280),right(600,280);
		CString str[6];
		str[0]="S";
		str[1]="S-A";
		str[2]="A";
		str[3]="A-V";
		str[4]="V";
		CClientDC dc(this);//
		for(int i=0;i<6;i++)
		{
			DrawLine(left, right);
			if(i<5)
			{
				dc.TextOutW(left.x,left.y,str[i]);
			}
			left.y+=40;
			right.y+=40;		
		}

	}
	//this->SetDlgItemTextW(IDC_COMBOX1,_T("��������"));//��ʼΪ��������

	/*******************************************/
	if(m_flagTracking == TRUE)
	{	
		CClientDC dc(this);
		CPen pen(PS_SOLID,2,RGB(255,0,0));
		dc.SelectObject(&pen);
		//char p1[10];
		//sprintf(p1,"%d,%d",m_headPoint);
		//CString str(p1);
		//AfxMessageBox(str);
		for(int j=0;j<i;j++)
		{
			dc.MoveTo(m_headPoint[j]);
			dc.LineTo(m_tailPoint[j]);
		}
	}
	if(m_flagTracking == TRUE)
	{	
		CClientDC dc(this);
		CPen pen(PS_SOLID,1,RGB(0,0,0));
		dc.SelectObject(&pen);
		dc.SelectStockObject(BLACK_BRUSH);

		//char p1[10];
		//sprintf(p1,"%d,%d",m_headPoint);
		//CString str(p1);
		//AfxMessageBox(str);
		for(int j=0;j<i;j++)
		{	
			/*dc.MoveTo(m_headPoint1[j]);
			dc.LineTo(m_tailPoint1[j]);*/
			//
			//DrawArrow( m_headPoint1[j], m_tailPoint1[j],45.0,10);
			dc.Ellipse(m_headPoint1[j].x,m_headPoint1[j].y,m_tailPoint1[j].x,m_tailPoint1[j].y);
		}
	}
	//���Ƽ�ͷ
	if(m_flagTracking == TRUE)
	{	
		//CClientDC dc(this);
		//CPen pen(PS_SOLID,1,RGB(0,0,0));
		//dc.SelectObject(&pen);
		//dc.SelectStockObject(BLACK_BRUSH);

		//char p1[10];
		//sprintf(p1,"%d,%d",m_headPoint);
		//CString str(p1);
		//AfxMessageBox(str);
		for(int j=0;j<i;j++)
		{	
			/*		dc.MoveTo(m_headPoint1[j]);
			dc.LineTo(m_tailPoint1[j]);*/
			//
			DrawArrow(m_headPoint2[j], m_tailPoint2[j],45.0,10);
			//dc.Ellipse(m_headPoint1[j].x,m_headPoint1[j].y,m_tailPoint1[j].x,m_tailPoint1[j].y);
		}

		//����Ten
		for(int j=0;j<i;j++) 
		{	
			//if(m_headPoint3[j] ==m_tailPoint3[j]) continue;
			DrawTen(m_headPoint3[j], m_tailPoint3[j],15.0,10);
		}
		//����Wavy

		for(int j=0;j<i;j++) 
		{	
			//if(m_headPoint4[j] ==m_tailPoint4[j]) continue;
			DrawWavy(m_headPoint4[j], m_tailPoint4[j],5);
		}
		//Sleep(2);
	}


	//�����ĵ�ͼ���
	DrawGrid(CPoint(10,150),CPoint(1850,290));
	//CClientDC dc(this);
	//int i=0;
	//for(std::vector<CPoint>::iterator iter = m_vecPoint.begin();iter !=m_vecPoint.end();iter++)
	//{
	//	point[i].x = iter->x;
	//	point[i].y = iter->y;
	//	i++;
	//}
	//dc.PolyBezier(point,10002);
	//���Ʋ���
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	dc.SelectObject(&pen);
	//dc.Rectangle(0,0,10,10);
	int i=0;
//TODO: vector ������Ҫ���
	//for (int i=0;i<10000;i++)
	//{
	//	point[i] = m_vecPoint[i];
	//}
	
	for(std::vector<CPoint>::iterator iter = m_vecPoint.begin();iter !=m_vecPoint.end();iter++)
	{
		point[i] = *iter;	
		i++;
	}
	dc.Polyline(point,10000);
	//dc.Rectangle(0,0,40,40);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTFigureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTFigureDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd::MessageBoxW(_T("ȷ��"));
	return ;
	CDialogEx::OnOK();
}


void CTFigureDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTFigureDlg::OnBnClickedStartbutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//this->SetDlgItemTextW(IDC_COMBOX1,_T("��������"));//��ʼΪ��������
	CString strCurrent;
	CString strCurrent1("��������");
	CString strCurrent2("��������");
	CString strCurrent3("��������");
	this->GetDlgItemTextW(IDC_COMBOX1,strCurrent);
	if(strCurrent == strCurrent1)
	{
		//dc.TextOutW(300,300,strCurrent);
		//��ʼ������������  //��־λ����
		bFourThree = TRUE;
		bSixFive = FALSE;
		this->Invalidate(0);
	}
	if(strCurrent == strCurrent2)
	{
		bSixFive = TRUE;
		bFourThree = FALSE;
		this->Invalidate(0);
	}

}


void CTFigureDlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTFigureDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


// ����
void CTFigureDlg::DrawLine(CPoint left, CPoint right)
{
	CClientDC dc(this);
	dc.MoveTo(left);
	dc.LineTo(right);
	return ;
}

//��ʼ����������
void CTFigureDlg::InitArea(CPoint left, CPoint right)
{	
	CClientDC dc(this);
	//CBrush brush((248,248,255));
	CRect rect(left,right);
	dc.SelectStockObject(LTGRAY_BRUSH); //��ɫ
	dc.Rectangle(&rect);
}

void CTFigureDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CTFigureDlg::InvertLine(CDC* pDC,CPoint x,CPoint y)
{
	int nOldMode = pDC->SetROP2(R2_NOT);
	pDC->MoveTo(x);
	pDC->LineTo(y);
	pDC->SetROP2(nOldMode);	 
}

void CTFigureDlg::InvertCircle(CDC* pDC,CPoint x,CPoint y)
{
	int nOldMode = pDC->SetROP2(R2_NOT);
	//pDC->MoveTo(x);
	//pDC->LineTo(y);
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->SelectStockObject(BLACK_PEN);
	pDC->Ellipse(x.x,x.y,y.x,y.y);
	pDC->SetROP2(nOldMode);	 
}

//void CTFigureDlg::InvertArrow(CDC* pDC,CPoint x,CPoint y)
//{
//	int nOldMode = pDC->SetROP2(R2_NOT);
//	//pDC->MoveTo(x);
//	//pDC->LineTo(y);
//
//	pDC->SelectStockObject(BLACK_BRUSH);
//	pDC->SelectStockObject(BLACK_PEN);
//	pDC->Ellipse(x.x,x.y,y.x,y.y);
//
//	pDC->SetROP2(nOldMode);	 
//}


void CTFigureDlg::OnMouseMove(UINT nFlags, CPoint point)  //����ƶ���Ϣ��Ӧ
{
	if(m_bDrawLine == TRUE) 
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) //����Ԥ��  ǰ�����ʼ�հ���
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint[i],this->m_tailPoint[i]);
			InvertLine(&dc,this->m_headPoint[i],point);
			m_tailPoint[i] = point;
		}
	}

	/***************/
	else if(m_bDrawCircle == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertCircle(&dc,this->m_headPoint1[i],this->m_tailPoint1[i]);  //���Ʒ�תԲ
			InvertCircle(&dc,this->m_headPoint1[i],point);
			m_tailPoint1[i] = point;
		}
	}
	/***********************/ 
	else if(m_bDrawArrow == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint2[i],this->m_tailPoint2[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint2[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint2[i] = point;
		}
	}
	else if(m_bDrawTen == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint3[i],this->m_tailPoint3[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint3[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint3[i] = point;
		}
	}
	else if(m_bDrawWavy == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint4[i],this->m_tailPoint4[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint4[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint4[i] = point;
		}
	}
	
	//�ж�����Ƿ�������ͼ����
	//if(m_bForbidSizeAll == TRUE)
	//{
	for(int j=0;j<i;j++)
	{	 
		if(m_bTracking == FALSE)  //��������ƶ�ʱ��,�ǰ���״̬
		{
			if((m_headPoint4[j].x-10 < point.x && m_headPoint4[j].x+10 > point.x)
				&&(m_headPoint4[j].y-10 < point.y && m_headPoint4[j].y+10 > point.y
				/*&&m_bForbidSizeAll == FALSE*/))
			{
				//�������
				SetClassLong(this->GetSafeHwnd(),
					GCL_HCURSOR , 
					(LONG)LoadCursor(NULL , IDC_SIZEALL));
				//���ҵ�������� m_bSizeAll
				m_bSizeAll = TRUE;
				/*m_bForbidSizeAll = TRUE;*/
				m_iDragFlag = j;//��¼�±�

				break;     //���j++,��ʱ�Ѿ���λ��m_headpoint[j]
			}
			else
			{
				//�������
				SetClassLong(this->GetSafeHwnd(),
					GCL_HCURSOR , 
					(LONG)LoadCursor(NULL , IDC_ARROW));
				m_bSizeAll = FALSE;
				//m_bForbidSizeAll == FALSE;
			}
		}
	}
	//}
	//else
	//{
	//	m_bForbidSizeAll = TRUE;
	//}
	//CDialogEx::OnMouseMove(nFlags, point);
}


void CTFigureDlg::OnLButtonDown(UINT nFlags, CPoint point) //����������
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���������ʽ
	SetClassLong(this->GetSafeHwnd(),
		GCL_HCURSOR , 
		(LONG)LoadCursor(NULL , IDC_CROSS));

	//AfxMessageBox(_T("����"));
	//ѡ��ֱ��
	if(m_bDrawLine == TRUE&&m_bSizeAll == FALSE)
	{
		m_bTracking = TRUE;              //��λ׷��
		drawCordinate(point);
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint[i] = point;
		m_tailPoint[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}


	/****************************/
	if(m_bDrawCircle == TRUE&&m_bSizeAll == FALSE)  //ѡ����ʵ��Բ
	{
		if(m_bDrawCircle == TRUE)
		{
			m_bTracking = TRUE;  
			drawCordinate(point);
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint1[i] = point;
			m_tailPoint1[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}

	//ѡ���˼�ͷ  /***********************/
	if(m_bDrawArrow == TRUE&&m_bSizeAll == FALSE)  //ѡ���˼�ͷ
	{
		if(m_bDrawArrow == TRUE)
		{
			m_bTracking = TRUE;  
			drawCordinate(point);
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint2[i] = point;
			m_tailPoint2[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}
	if(m_bDrawTen == TRUE &&m_bSizeAll == FALSE)  //m_bDrawTen
	{
		m_bTracking = TRUE;  
		drawCordinate(point);
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint3[i] = point;
		m_tailPoint3[i] = point;
		this->Invalidate(0);
		CDialogEx::OnLButtonDown(nFlags, point);
	}

	///////////////////////////TODO:DOWNʱ �����m_tailPoint4[i]���λ�ã�
	////�����ʱ�������ͷ״̬�����ܸı���λ��
	if(m_bDrawWavy == TRUE && m_bSizeAll == FALSE)  //m_bDrawWavy
	{
		m_bTracking = TRUE;  
		drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint4[i] = point;
		m_tailPoint4[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}


	/////////////////
	if(m_bSizeAll == TRUE)
	{	
		m_bTracking = FALSE; 
		m_flagTracking = FALSE;
		//AfxMessageBox(_T("test"));
		//��¼�˴���ʼ��� �϶��ĵ�λ 
		m_dragPoint = point;
		m_bDragFlag = TRUE;
	}

}

void CTFigureDlg::drawCordinate(CPoint point)
{
	char *p = "test";                                      //�������ת��
	char p1[10];
	sprintf(p1,"%d,%d",point.x,point.y);
	CString str(p1);
	CClientDC dc(this);
	//CBrush brush((255,255,255));
	//dc.FillRect(CRect(2,86,64,106),&brush);
	dc.SelectStockObject(WHITE_BRUSH );
	dc.Rectangle(CRect(2,86,70,106));
	dc.DrawText(str,CRect(2,86,70,106),DT_CENTER);   //2,86  64,106
}

void CTFigureDlg::OnLButtonUp(UINT nFlags, CPoint point)   //����ɿ�
{	

	//���������ʽ
	SetClassLong(this->GetSafeHwnd(),
		GCL_HCURSOR , 
		(LONG)LoadCursor(NULL , IDC_ARROW));
	//TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bDrawLine == TRUE)
	{
		m_bTracking = FALSE;              //ֹͣ׷��
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint[i] = point;
			++i;
			//CClientDC dc(this);
			//char p1[10];
			//sprintf(p1,"%d,%d",m_headPoint);
			//CString str(p1);
			//AfxMessageBox(str);
			//dc.MoveTo(m_headPoint);
			//dc.LineTo(m_tailPoint);
			this->Invalidate(1);
		}
	}

	else if(m_bDrawCircle == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint1[i] = point;
			++i;
			this->Invalidate(0);
		}
	}

	else if(m_bDrawArrow == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint2[i] = point;
			++i;
			this->Invalidate(0);
		}
	}

	else if(m_bDrawTen == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint3[i] = point;
			++i;
			this->Invalidate(0);
		}
	}
	////////////////////
	else if(m_bDrawWavy == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint4[i] = point;
			++i;
			this->Invalidate(0);
		}
	}



	///////////////////////////////
	//���ڰ����϶�ͼ��
	if((m_bDragFlag == TRUE))
	{	
		m_bDragFlag = FALSE;
		m_flagTracking = TRUE;
		int nDx = point.x - m_dragPoint.x;
		int nDy = point.y - m_dragPoint.y;
		m_headPoint4[m_iDragFlag].x = m_headPoint4[m_iDragFlag].x + nDx;
		m_headPoint4[m_iDragFlag].y = m_headPoint4[m_iDragFlag].y + nDy;
		m_tailPoint4[m_iDragFlag].x = m_tailPoint4[m_iDragFlag].x + nDx;
		m_tailPoint4[m_iDragFlag].y = m_tailPoint4[m_iDragFlag].y + nDy;

		//if(m_headPoint4[m_iDragFlag+1]==m_tailPoint4[m_iDragFlag+1])
		//{m_headPoint4[m_iDragFlag+1].x = 0;
		//m_headPoint4[m_iDragFlag+1].y = 0;
		//m_tailPoint4[m_iDragFlag+1].x = 0;
		//m_tailPoint4[m_iDragFlag+1].y = 0;
		//}
		this->Invalidate(1);  //ȫ��ˢ�£���������
		//AfxMessageBox(_T("test"));
	}
}

//���ˣ�ɾ����λ
void CTFigureDlg::DeleteDataPoint()
{	
	this->m_headPoint4[i].x = 0;
	this->m_headPoint4[i].y = 0;
	this->m_tailPoint4[i].x = 0;
	this->m_tailPoint4[i].y = 0;
	this->m_headPoint3[i].x = 0;
	this->m_headPoint3[i].y = 0;
	this->m_tailPoint3[i].x = 0;
	this->m_tailPoint3[i].y = 0;
	this->m_headPoint2[i].x = 0;
	this->m_headPoint2[i].y = 0;
	this->m_tailPoint2[i].x = 0;
	this->m_tailPoint2[i].y = 0;

	this->m_headPoint1[i].x = 0;
	this->m_headPoint1[i].y = 0;
	this->m_tailPoint1[i].x = 0;
	this->m_tailPoint1[i].y = 0;

	this->m_headPoint[i].x = 0;
	this->m_headPoint[i].y = 0;
	this->m_tailPoint[i].x = 0;
	this->m_tailPoint[i].y = 0;
}	
void CTFigureDlg::OnBnClickedButton3()    //����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bDrawLine == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("����������"));
			this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
		}
		else
		{
			i--;
			DeleteDataPoint();
			this->Invalidate(1);

		}
	}
	/*******************/  //ʵ��Բ
	if(m_bDrawCircle == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("����������"));
			this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
		}
		else
		{
			i--;
			DeleteDataPoint();
			this->Invalidate(1);

		}
	}

	/*********************************/  //��ͷ
	if(m_bDrawArrow == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("����������"));
			this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
		}
		else
		{
			i--;
			DeleteDataPoint();
			this->Invalidate(1);

		}
	}

	if(m_bDrawTen == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("����������"));
			this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
		}
		else
		{
			i--;
			DeleteDataPoint();
			this->Invalidate(1);

		}
	}
	//////////////////
	if(m_bDrawWavy == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("����������"));
			this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
		}
		else
		{
			i--;
			DeleteDataPoint();
			this->Invalidate(1);

		}
	}
}


void CTFigureDlg::OnBnClickedLinebutton() //ѡ����ֱ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_bDrawLine = !m_bDrawLine;   //ֱ�߻��Ʊ��
	if(m_bDrawLine == TRUE)
	{	
		ChangeFlag(&m_bDrawLine);
		AfxMessageBox(_T("��ѡ����ֱ��"));
	}

}


void CTFigureDlg::OnBnClickedCirclebutton() //ʵ��Բ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawCircle = !m_bDrawCircle ;  //���߻��Ʊ��
	if(m_bDrawCircle == TRUE)
	{
		ChangeFlag(&m_bDrawCircle);
		AfxMessageBox(_T("��ѡ����ʵ��Բ"));
	}	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//void CTFigureDlg::OnBnClickedArrow()  //ѡ���˼�ͷ
//{
//
//
//}

void CTFigureDlg::OnBnClickedArrowbutton() //ѡ���˼�ͷ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawArrow = !m_bDrawArrow;
	if(m_bDrawArrow == TRUE)
	{
		ChangeFlag(&m_bDrawArrow);
		AfxMessageBox(_T("��ѡ���˼�ͷ"));
	}	
}

//�ı��ͼ���״̬
void CTFigureDlg::ChangeFlag(bool* b)
{
	m_bDrawLine = FALSE;
	m_bDrawCircle = FALSE;
	m_bDrawArrow = FALSE;
	m_bDrawTen = FALSE;
	m_bDrawWavy = FALSE;
	*b = TRUE;		
}
void CTFigureDlg::OnBnClickedButtonten()  //ѡ����TEN
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawTen = !m_bDrawTen;
	if(m_bDrawTen == TRUE) 
	{
		//��������ͼ�������Ϊfalse
		ChangeFlag(&m_bDrawTen);
		AfxMessageBox(_T("��ѡ����TEN"));
	}

}


void CTFigureDlg::OnBnClickedBwavy()  //ѡ���˲�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawWavy = !m_bDrawWavy;
	if(m_bDrawWavy == TRUE) 
	{
		//��������ͼ�������Ϊfalse
		ChangeFlag(&m_bDrawWavy);
		AfxMessageBox(_T("��ѡ����WAVY"));
	}
}

void CTFigureDlg::OnBnClickedCurvebutton() //ѡ��������
{

}

//���Ʋ�����
void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length)
{
	CClientDC dc(this);
	CPen pen,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen = dc.SelectObject(&pen);
	CPoint arrPoint[8];
	int d = (p2.y-p1.y)/7;
	arrPoint[0] = p1;
	arrPoint[7] = p2;
	for(int i = 1;i<7;i++)
	{
		arrPoint[i].y = arrPoint[0].y + i*d;
		if(i%2==0)
		{
			arrPoint[i].x = arrPoint[0].x - (int)length;
		}
		else
		{
			arrPoint[i].x = arrPoint[0].x + (int)length;
		}
	}
	dc.Polyline(arrPoint,8);

}

//����ʮ��
void CTFigureDlg::DrawTen(CPoint p1,CPoint p2,double theta,int length) 
{
	//CPoint p3;
	//p3.x = (p1.x + p2.x)/2;
	//p3.y = (p2.y + p1.y)/2;
	length =(int)sqrt((double)(p2.x*p2.x+p1.x*p1.x-2*p2.x*p1.x
		+p2.y*p2.y+p1.y*p1.y-2*p1.y*p2.y))/2;
	theta=3.1415926*theta/180;
	//ת��Ϊ����
	double Px,Py,P1x,P1y,P2x,P2y;
	//��P2Ϊԭ��õ�����P2P1��P��
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	//����P��תtheta�ǵõ�����P1
	P1x=Px*
		cos(theta)-Py*
		sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//�����������ƶ�����
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;

	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	CClientDC dc(this);
	//��ȡ�ͻ�����DC
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(p1.x,p1.y);
	dc.LineTo(p2.x,p2.y);
	dc.SelectObject(&pen1);
	dc.MoveTo(P1x,P1y);
	dc.LineTo(P2x,P2y);
	dc.SelectObject(oldpen);
}

void CTFigureDlg::DrawArrow(CPoint p1,CPoint p2,double theta,int length)
{
	theta=3.1415926*theta/180;
	//ת��Ϊ����
	double Px,Py,P1x,P1y,P2x,P2y;
	//��P2Ϊԭ��õ�����P2P1��P��
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	//����P��תtheta�ǵõ�����P1
	P1x=Px*
		cos(theta)-Py*
		sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//�����������ƶ�����
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;

	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	CClientDC dc(this);
	//��ȡ�ͻ�����DC
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(p1.x,p1.y);
	dc.LineTo(p2.x,p2.y);
	dc.SelectObject(&pen1);
	dc.MoveTo(p2.x,p2.y);
	dc.LineTo(P1x,P1y);
	dc.MoveTo(p2.x,p2.y);
	dc.LineTo(P2x,P2y);
	dc.SelectObject(oldpen);
}

//TODO: ���� CTFigureDlg::DrawArrow

//void CTFigureDlg::DrawArrow(CPoint p1,CPoint p2,double theta,int length)

//{
//	theta=3.1415926*theta/180;
//	//ת��Ϊ����
//	double Px,Py,P1x,P1y,P2x,P2y;
//	//��P2Ϊԭ��õ�����P2P1��P��
//	Px=p1.x-p2.x;
//	Py=p1.y-p2.y;
//	//����P��תtheta�ǵõ�����P1
//	P1x=Px*
//		cos(theta)-Py*
//		sin(theta);
//	P1y=Px*sin(theta)+Py*cos(theta);
//	//����P��ת-theta�ǵõ�����P2
//	P2x=Px*cos(-theta)-Py*sin(-theta);
//	P2y=Px*sin(-theta)+Py*cos(-theta);
//	//�����������ƶ�����
//	double x1,x2;
//	x1=sqrt(P1x*P1x+P1y*P1y);
//	P1x=P1x*length/x1;
//	P1y=P1y*length/x1;
//	x2=sqrt(P2x*P2x+P2y*P2y);
//	P2x=P2x*length/x2;
//	P2y=P2y*length/x2;
//
//	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
//	P1x=P1x+p2.x;
//	P1y=P1y+p2.y;
//	P2x=P2x+p2.x;
//	P2y=P2y+p2.y;
//	CClientDC dc(this);
//	//��ȡ�ͻ�����DC
//	CPen pen,pen1,*oldpen;
//	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
//	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
//	oldpen=dc.SelectObject(&pen);
//	dc.MoveTo(p1.x,p1.y);
//	dc.LineTo(p2.x,p2.y);
//	dc.SelectObject(&pen1);
//	dc.MoveTo(p2.x,p2.y);
//	dc.LineTo(P1x,P1y);
//	dc.MoveTo(p2.x,p2.y);
//	dc.LineTo(P2x,P2y);
//	dc.SelectObject(oldpen);
//}

//�ݹ��ȡԪ��
TiXmlElement* ReadElememt(TiXmlElement* InputElement, char* pName)
{
	TiXmlElement* ptemp = NULL;

	if(InputElement == NULL || pName == NULL)
		return ptemp;

	if (InputElement && 0 == strcmp(pName,InputElement->Value()))
	{
		printf("Find the element :%s \n", InputElement->Value());
		ptemp = InputElement;
		return ptemp;
	}
	else
	{
		printf("%s \n", InputElement->Value());
	}

	TiXmlElement* tmpElement = InputElement;
	if (tmpElement->FirstChildElement())
	{
		ptemp = ReadElememt(tmpElement->FirstChildElement(), pName);
	}
	if (!ptemp)
	{
		tmpElement = tmpElement->NextSiblingElement();
		if (tmpElement)
		{
			ptemp = ReadElememt(tmpElement ,  pName);
		}
	}
	return ptemp;
}

TiXmlElement SelectElementByName(char* InputInfo, char* pName, int iXMLType)
{
	//ע��XMLTYPE Ϊ1ʱ��InputInfoΪXML·������Ϊ2ʱ,InputInfoΪ�������ļ�����
	TiXmlDocument cXmlDoc;
	TiXmlElement* pRootElement = NULL;
	if (iXMLType == 1)
	{
		if (!cXmlDoc.LoadFile(InputInfo))
		{
			printf("parse XML file failed \n");
			return TiXmlElement("");
		}
	}
	else if (iXMLType == 2)
	{
		if (!cXmlDoc.Parse(InputInfo))
		{
			printf("parse XML failed \n");
			return TiXmlElement("");
		}
	}

	pRootElement = cXmlDoc.RootElement();
	if (NULL == pRootElement)
	{
		printf("no have root Element\n");
		return TiXmlElement("");
	}
	else
	{
		TiXmlElement* pTempElement = NULL;
		pTempElement = ReadElememt(pRootElement, pName);
		if (pTempElement)
		{
			printf("find the Name : %s, Text = %s\n", pTempElement->Value(), pTempElement->GetText());
		}
		return *pTempElement;
	}	
}

//��vector���ֵ
int FindMax(std::vector<int> vecNum )
{
	int max = 0;
	for(std::vector<int>::iterator iter = vecNum.begin();iter !=vecNum.end();iter++)
	{
		if(*iter > max)
		{
			max = *iter;
		}
	}
	return max;
}

//��vector��Сֵ
int FindMin(std::vector<int> vecNum )
{
	int min = 0;
	for(std::vector<int>::iterator iter = vecNum.begin();iter !=vecNum.end();iter++)
	{
		if(*iter < min)
		{
			min = *iter;
		}
	}
	return min;
}

void CTFigureDlg::OnBnClickedOpenfilebutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,NULL,NULL,
		OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,
		_T("DATA�ļ�(*.xml)|*.xml|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*))|*.*||"),this);
	if(dlg.DoModal() == IDOK)
	{
		AfxMessageBox(dlg.GetPathName());
		USES_CONVERSION;
		char* pathName = T2A(dlg.GetPathName().GetBuffer(0));
		dlg.GetPathName().ReleaseBuffer();
		Sleep(2);
		TiXmlElement pTempEle = SelectElementByName(pathName,"digits", 1);
		Sleep(2);
		//printf("find the Name : %s, Text = %s\n", pTempEle.Value(), pTempEle.GetText());
		Sleep(2);
		const char* str = pTempEle.GetText();
		std::vector<CString> vecString;
		std::vector<int> vecNum;
		m_vecPoint.resize(0);
		char tempstr[8];
		char* p = tempstr;
		memset(tempstr,0,8);
		//������
		//std::vector<CPoint>  vecPoint;
		//���±�
		double nPointX = 20 ;
		Sleep(2);
		for (unsigned int i=0;i<strlen(str)+1;i++)
		{	

			if((*(str+i) != ' ')&&(*(str+i) != '\0') )
			{	
				*p++ = *(str+i);
			}
			else
			{
				*p++ ='\0';
				vecString.push_back(CString(tempstr));
				//MessageBox(vecString.back());
				m_vecPoint.push_back(CPoint((int)nPointX,(4200-(atoi(tempstr)+610))*0.03+150)); //��ŵ�λ
				nPointX = nPointX + 0.18 ;
				vecNum.push_back(atoi(tempstr));
				memset(tempstr,0,8);
				p = tempstr;
			}
		}
		Sleep(3);
		char nnn[10];
		memset(nnn,0,10);
		//sprintf(nnn,"min:%d",FindMin(vecNum));
		sprintf(nnn,"min:%d",m_vecPoint.size());
		AfxMessageBox(CString(nnn));
		this->Invalidate(0);
		//CClientDC dc(this);
		//for (int i=0;i<1000;i++)
		//{
		//	//point[i] = m_vecPoint[i];
		//}

		//for(std::vector<int>::iterator iter = vecNum.begin();iter !=vecNum.end();iter++)
		//{
		//	std::cout<<*iter;
		//	std::cout<<" ";
		//}
		//CString cstr(pathName);
		//MessageBox(cstr);
	}

}


void CTFigureDlg::OnBnClickedButton2()  //����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(FALSE,NULL,NULL,
		OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,
		_T("DATA�ļ�(*.dat)|*.dat|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*))|*.*||"),this);
	if(dlg.DoModal() == IDOK)
	{
		//AfxMessageBox(dlg.GetPathName());
		CStdioFile file(dlg.GetPathName(),CFile::modeWrite);
		char temp[50];
		CString strTemp;
		CString str[1024];
		for(int i=0;i<1024;i++)
		{	
			memset(temp,0,50);
			sprintf(temp,"x:%d,y:%d\r\n",m_headPoint[i].x,m_headPoint[i].y);
			str[i] =temp;
			strTemp.Append(str[i]);
		}
		file.Seek(0, CFile::end);
		file.WriteString(strTemp);
		file.Close();

	}
}

//�����ĵ�ͼ���
void CTFigureDlg::DrawGrid(CPoint lP,CPoint rP)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID ,1,RGB(255,0,0));
	dc.SelectStockObject(WHITE_BRUSH); //��ɫ
	dc.SelectObject(&pen);
	dc.Rectangle(lP.x,lP.y,rP.x,rP.y);
	CPoint lPoint(lP.x,lP.y);
	CPoint rPoint(rP.x,lP.y);
	CPoint uPoint(lP.x,lP.y);
	CPoint dPoint(lP.x,rP.y);
	for(int i=0;i<6;i++)
	{
		lPoint.y +=20;
		rPoint.y +=20;
		dc.MoveTo(lPoint);
		dc.LineTo(rPoint);
	}
	for(int i=0;i<(rP.x-lP.x)/20-1;i++)
	{
		uPoint.x += 20;
		dPoint.x += 20;
		dc.MoveTo(uPoint);
		dc.LineTo(dPoint);
	}
}
//void CTFigureDlg::OnStnClickedPicten()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	AfxMessageBox(_T("��ѡ����TEN"));
//}


////void CTFigureDlg::OnBnClickedMfcbutton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
//


//
//
//void CTFigureDlg::OnBnClickedButton4()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}

//void CTFigureDlg::OnBnClickedButtonwavy()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	AfxMessageBox(_T("��ѡ����TEN"));
//	AfxMessageBox(_T("��ѡ����WAVY"));
//}

