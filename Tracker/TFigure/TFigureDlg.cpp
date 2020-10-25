
// TFigureDlg.cpp : 实现文件
//


#include "stdafx.h"
#include "TFigure.h"
#include "TFigureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CTFigureDlg 对话框




CTFigureDlg::CTFigureDlg(CWnd* pParent /*=NULL*/)  //初始化成员列表
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
	for(int j=0;j<1024;j++)   //初始化点位
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

BEGIN_MESSAGE_MAP(CTFigureDlg, CDialogEx)  //消息映射 注册
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


// CTFigureDlg 消息处理程序

BOOL CTFigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->SetDlgItemTextW(IDC_COMBOX1,_T("四线三行"));//初始为四线三行

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTFigureDlg::OnPaint()
{	

	//TODO : test:  绘制箭头
#if 0:
	CClientDC dcTest(this);
	dcTest.DrawTextW(CString("test"),CRect(450,180,480,210),DT_CENTER);
	CPoint p1(40,40),p2(60,60);
	DrawArrow( p1, p2,45.0,10);
#endif

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

	//TODO : test:  绘制箭头
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
	//this->SetDlgItemTextW(IDC_COMBOX1,_T("四线三行"));//初始为四线三行

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
	//绘制箭头
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTFigureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTFigureDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd::MessageBoxW(_T("确定"));
	CDialogEx::OnOK();
}


void CTFigureDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTFigureDlg::OnBnClickedStartbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	//this->SetDlgItemTextW(IDC_COMBOX1,_T("四线三行"));//初始为四线三行
	CString strCurrent;
	CString strCurrent1("四线三行");
	CString strCurrent2("六线五行");
	CString strCurrent3("八线七行");
	this->GetDlgItemTextW(IDC_COMBOX1,strCurrent);
	if(strCurrent == strCurrent1)
	{
		//dc.TextOutW(300,300,strCurrent);
		//开始绘制四线三行  //标志位开启
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
	// TODO: 在此添加控件通知处理程序代码
}


void CTFigureDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
}


// 划线
void CTFigureDlg::DrawLine(CPoint left, CPoint right)
{
	CClientDC dc(this);
	dc.MoveTo(left);
	dc.LineTo(right);
	return ;
}

//初始化划线区域
void CTFigureDlg::InitArea(CPoint left, CPoint right)
{	
	CClientDC dc(this);
	//CBrush brush((248,248,255));
	CRect rect(left,right);
	dc.SelectStockObject(LTGRAY_BRUSH); //灰色
	dc.Rectangle(&rect);
}

void CTFigureDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
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


void CTFigureDlg::OnMouseMove(UINT nFlags, CPoint point)  //鼠标移动消息响应
{
	if(m_bDrawLine == TRUE)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertCircle(&dc,this->m_headPoint1[i],this->m_tailPoint1[i]);  //绘制反转圆
			InvertCircle(&dc,this->m_headPoint1[i],point);
			m_tailPoint1[i] = point;
		}
	}
	/***********************/ 
	if(m_bDrawArrow == TRUE)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint2[i],this->m_tailPoint2[i]);  //绘制反转线
			InvertLine(&dc,this->m_headPoint2[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint2[i] = point;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CTFigureDlg::OnLButtonDown(UINT nFlags, CPoint point) //鼠标左键按下
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//AfxMessageBox(_T("测试"));
	if(m_bDrawLine == TRUE)                   //选择直线
	{
		if(m_bDrawLine == TRUE)
		{
			m_bTracking = TRUE;              //点位追踪

			char *p = "test";                                      //文字输出转换
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
			//记录左键位置
			m_headPoint[i] = point;
			m_tailPoint[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}

	/****************************/
	if(m_bDrawCircle == TRUE)  //选择了实心圆
	{
		if(m_bDrawCircle == TRUE)
		{
			m_bTracking = TRUE;  

			char *p = "test";                                      //文字输出转换
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
			//记录左键位置
			m_headPoint1[i] = point;
			m_tailPoint1[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}

    //选择了箭头  /***********************/
	if(m_bDrawArrow == TRUE)  //选择了箭头
	{
		if(m_bDrawArrow == TRUE)
		{
			m_bTracking = TRUE;  

			char *p = "test";                                      //文字输出转换
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
			//记录左键位置
			m_headPoint2[i] = point;
			m_tailPoint2[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}
}


void CTFigureDlg::OnLButtonUp(UINT nFlags, CPoint point)   //左键松开
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bDrawLine == TRUE)
	{
		m_bTracking = FALSE;              //停止追踪
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


void CTFigureDlg::OnBnClickedButton3()    //回退
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_bDrawLine == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("不能再退了"));
			this->Invalidate(1);    //参数设置为1，全屏刷新
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
	/*******************/  //实心圆
	if(m_bDrawCircle == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("不能再退了"));
			this->Invalidate(1);    //参数设置为1，全屏刷新
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

	/*********************************/  //箭头
	if(m_bDrawArrow == TRUE)
	{
		if(i==0)
		{
			AfxMessageBox(_T("不能再退了"));
			this->Invalidate(1);    //参数设置为1，全屏刷新
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


void CTFigureDlg::OnBnClickedLinebutton() //选择了直线
{
	// TODO: 在此添加控件通知处理程序代码

	m_bDrawLine = !m_bDrawLine;   //直线绘制标记
	if(m_bDrawLine == TRUE)
	{	
		m_bDrawCircle = FALSE;
		m_bDrawArrow = FALSE;
		AfxMessageBox(_T("你选择了直线"));
	}

}




void CTFigureDlg::OnBnClickedCirclebutton() //实心圆
{
	// TODO: 在此添加控件通知处理程序代码
	m_bDrawCircle = !m_bDrawCircle ;  //曲线绘制标记
	if(m_bDrawCircle == TRUE)
	{
		m_bDrawLine = FALSE;
		m_bDrawArrow = FALSE;
		AfxMessageBox(_T("你选择了实心圆"));
	}	// TODO: 在此添加控件通知处理程序代码
}

//void CTFigureDlg::OnBnClickedArrow()  //选择了箭头
//{
//
//
//}

void CTFigureDlg::OnBnClickedArrowbutton() //选择了箭头
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	m_bDrawArrow = !m_bDrawArrow;
	if(m_bDrawArrow == TRUE)
	{
		m_bDrawLine = FALSE;
		m_bDrawCircle = FALSE;
		AfxMessageBox(_T("你选择了箭头"));
	}	// TODO: 在此添加控件通知处理程序代码
}

void CTFigureDlg::OnBnClickedCurvebutton() //选择了曲线
{

}
void CTFigureDlg::DrawArrow(CPoint p1,CPoint p2,double theta,int length)
{
	theta=3.1415926*theta/180;
	//转换为弧度
	double Px,Py,P1x,P1y,P2x,P2y;
	//以P2为原点得到向量P2P1（P）
	Px=p1.x-p2.x;
	Py=p1.y-p2.y;
	//向量P旋转theta角得到向量P1
	P1x=Px*
		cos(theta)-Py*
		sin(theta);
	P1y=Px*sin(theta)+Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x=Px*cos(-theta)-Py*sin(-theta);
	P2y=Px*sin(-theta)+Py*cos(-theta);
	//伸缩向量至制定长度
	double x1,x2;
	x1=sqrt(P1x*P1x+P1y*P1y);
	P1x=P1x*length/x1;
	P1y=P1y*length/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	P2y=P2y*length/x2;

	//平移变量到直线的末端
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	CClientDC dc(this);
	//获取客户窗口DC
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

//TODO: 重载 CTFigureDlg::DrawArrow

//void CTFigureDlg::DrawArrow(CPoint p1,CPoint p2,double theta,int length)

//{
//	theta=3.1415926*theta/180;
//	//转换为弧度
//	double Px,Py,P1x,P1y,P2x,P2y;
//	//以P2为原点得到向量P2P1（P）
//	Px=p1.x-p2.x;
//	Py=p1.y-p2.y;
//	//向量P旋转theta角得到向量P1
//	P1x=Px*
//		cos(theta)-Py*
//		sin(theta);
//	P1y=Px*sin(theta)+Py*cos(theta);
//	//向量P旋转-theta角得到向量P2
//	P2x=Px*cos(-theta)-Py*sin(-theta);
//	P2y=Px*sin(-theta)+Py*cos(-theta);
//	//伸缩向量至制定长度
//	double x1,x2;
//	x1=sqrt(P1x*P1x+P1y*P1y);
//	P1x=P1x*length/x1;
//	P1y=P1y*length/x1;
//	x2=sqrt(P2x*P2x+P2y*P2y);
//	P2x=P2x*length/x2;
//	P2y=P2y*length/x2;
//
//	//平移变量到直线的末端
//	P1x=P1x+p2.x;
//	P1y=P1y+p2.y;
//	P2x=P2x+p2.x;
//	P2y=P2y+p2.y;
//	CClientDC dc(this);
//	//获取客户窗口DC
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



