
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->SetDlgItemTextW(IDC_COMBOX1,_T("��������"));//��ʼΪ��������

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

	//TODO : test:  ���Ƽ�ͷ
#if 0:
	CPaintDC dcTest(this);
	dcTest.DrawTextW(CString("test"),CRect(450,180,480,210),DT_CENTER);
	CPoint p1(40,40),p2(220,90);
	DrawArrow( p1, p2,45.0,10);
#endif

	/*********************************/
	if(bFourThree == TRUE)
	{	
		//bSixFive = FALSE;
		CPoint left1(0,250),right1(650,650);
		InitArea(left1,right1);
		CPoint left(20,280),right(600,280);
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
			left.y+=40;
			right.y+=40;		
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
	/*		dc.MoveTo(m_headPoint1[j]);
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
			DrawArrow( m_headPoint2[j], m_tailPoint2[j],45.0,10);
			//dc.Ellipse(m_headPoint1[j].x,m_headPoint1[j].y,m_tailPoint1[j].x,m_tailPoint1[j].y);
		}
	}
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
		this->Invalidate(1);
	}
	if(strCurrent == strCurrent2)
	{
		bSixFive = TRUE;
		bFourThree = FALSE;
		this->Invalidate(1);
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
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint[i],this->m_tailPoint[i]);
			InvertLine(&dc,this->m_headPoint[i],point);
			m_tailPoint[i] = point;
		}
	}

	/***************/
	if(m_bDrawCircle == TRUE)
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
	if(m_bDrawArrow == TRUE)
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

	CDialogEx::OnMouseMove(nFlags, point);
}


void CTFigureDlg::OnLButtonDown(UINT nFlags, CPoint point) //����������
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//AfxMessageBox(_T("����"));
	if(m_bDrawLine == TRUE)                   //ѡ��ֱ��
	{
		if(m_bDrawLine == TRUE)
		{
			m_bTracking = TRUE;              //��λ׷��

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
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint[i] = point;
			m_tailPoint[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}

	/****************************/
	if(m_bDrawCircle == TRUE)  //ѡ����ʵ��Բ
	{
		if(m_bDrawCircle == TRUE)
		{
			m_bTracking = TRUE;  

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
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint1[i] = point;
			m_tailPoint1[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}

    //ѡ���˼�ͷ  /***********************/
	if(m_bDrawArrow == TRUE)  //ѡ���˼�ͷ
	{
		if(m_bDrawArrow == TRUE)
		{
			m_bTracking = TRUE;  

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
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint2[i] = point;
			m_tailPoint2[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}
}


void CTFigureDlg::OnLButtonUp(UINT nFlags, CPoint point)   //����ɿ�
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bDrawLine == TRUE)
	{
		m_bTracking = FALSE;              //ֹͣ׷��
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint[i] = point;
			i++;
			//CClientDC dc(this);
			//char p1[10];
			//sprintf(p1,"%d,%d",m_headPoint);
			//CString str(p1);
			//AfxMessageBox(str);
			//dc.MoveTo(m_headPoint);
			//dc.LineTo(m_tailPoint);
			this->Invalidate(0);
		}
	}

	if(m_bDrawCircle == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint1[i] = point;
			i++;
			this->Invalidate(0);
		}
	}

	if(m_bDrawArrow == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint2[i] = point;
			i++;
			this->Invalidate(0);
		}
	}

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
		m_bDrawCircle = FALSE;
		m_bDrawArrow = FALSE;
		AfxMessageBox(_T("��ѡ����ֱ��"));
	}

}




void CTFigureDlg::OnBnClickedCirclebutton() //ʵ��Բ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawCircle = !m_bDrawCircle ;  //���߻��Ʊ��
	if(m_bDrawCircle == TRUE)
	{
		m_bDrawLine = FALSE;
		m_bDrawArrow = FALSE;
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
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawArrow = !m_bDrawArrow;
	if(m_bDrawArrow == TRUE)
	{
		m_bDrawLine = FALSE;
		m_bDrawCircle = FALSE;
		AfxMessageBox(_T("��ѡ���˼�ͷ"));
	}	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTFigureDlg::OnBnClickedCurvebutton() //ѡ��������
{

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



