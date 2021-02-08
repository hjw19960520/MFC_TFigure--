
// TFigureDlg.cpp : ʵ���ļ�
//
/**  @file        TFigureDlg.cpp
*   @note  XXX Technology Co., Ltd. All Right Reserved.
*   @brief   Breif
*
*   @author  Author
*   @date    2020/12/10
*
*  
*	@note   detailed functional description of this document and comments
*   @note   History
*
*   @warning warning message related to this document 
*/
#include "stdafx.h"
#include "TFigure.h"
#include "TFigureDlg.h"
#include "afxdialogex.h"
#include <fstream>
#define ROUND(a) (int)(a+0.5)
#define PI 3.14
#define DEBUGS 0;
#define ID_EDIT1 109876
#define ID_EDIT2 209876
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using std::vector;
using std::string;

const int iRange = 5;
char* cLead[12];

HBITMAP CaptureScreen(LPRECT lpRect);//lpRectΪNULLʱ��ʾȫ��Ļ��ͼ
TiXmlElement SelectElementByName(char* InputInfo, char* pName, int iXMLType,int nLead);
//����ͼƬ
BOOL SaveBmp(HBITMAP hBitmap,CString FileName);
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
// template<typename T>
// inline T labs( const T & x ){return x<0?-x:x;} 
//    
// template<typename T>
//  int sgn( const T & x ){return x<0?-1:(x?1:0);}
// 
// int d_round( const double & x ){return (int)(sgn(x)*(labs(x)+0.50001));}
std::string GbkToUtf8(const char *src_str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}
inline bool cmp(const CPoint& a, const CPoint& b)
{
	return a.x < b.x; //�Ӵ�С����
}

inline int d_round(double a)
{
	int b;
	if(a > 0){
		b = (a*2+1)/2;
	}else{
		b = (a*2-1)/2;  
	}
	return b;
}
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    //DDX/DDV ֧��

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
	,m_flagSublineTracking(FALSE)
	, bSixFive(false)
	,bEightSeven(false)
	, m_flagTracking(false)
	,m_cstrFileLocation(_T(""))
	, m_bTracking(false)
	,m_bChangeLead(FALSE)
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
	, m_iFallinWhere(0)
	, m_bDrawDash(false)
	,m_bChangeFlag(false)
	,m_bDrawCircleLine(false)
	,m_bDrawText (FALSE)
	,m_DragGraphics(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAIN);
	for(int j=0;j<1024;j++)   //��ʼ����λ
	{	
		CPoint point(0,0);
		m_headPoint1[j] = point;
	}
	m_pPointFourLeft = new CPoint[4];
	m_pPointFourRight = new CPoint[4];
	m_pPointSixLeft=  new CPoint[6];
	m_pPointSixRight =new CPoint[6];
	m_pPointEightLeft =new CPoint[8];
	m_pPointEightRight=new CPoint[8];
	m_nWord = 0;
	// 	 std::shared_ptr<CPoint> PP(m_pPointFourLeft);
	// 	 std::shared_ptr<CPoint> PP1(m_pPointFourRight);
	// 	 std::shared_ptr<CPoint> PP2(m_pPointSixLeft);
	// 	 std::shared_ptr<CPoint> PP3(m_pPointSixRight);
	// 	 std::shared_ptr<CPoint> PP4(m_pPointEightLeft);
	// 	 std::shared_ptr<CPoint> PP5(m_pPointEightRight);

	//ָ�븳ֵ
	m_arrHeadPoint[0] = m_headPoint;
	m_arrHeadPoint[1] = m_headPoint1;
	m_arrHeadPoint[2] = m_headPoint2;
	m_arrHeadPoint[3] = m_headPoint3;
	m_arrHeadPoint[4] = m_headPoint4;
	m_arrHeadPoint[5] = m_headPoint5;
	m_arrHeadPoint[6] = m_headPoint6;
	m_arrHeadPoint[7] = m_headPoint7;
	m_arrHeadPoint[8] = m_headPoint8;
	m_arrHeadPoint[9] = m_headPoint9;
	m_arrHeadPoint[10] = m_headPoint10;
	m_arrHeadPoint[11] = m_headPoint11;
	m_arrHeadPoint[12] = m_headPoint12;
	m_arrHeadPoint[13] = m_headPoint13;
	m_arrHeadPoint[14] = m_headPoint14;
	m_arrHeadPoint[15] = m_headPoint15;
	m_arrHeadPoint[16] = m_headPoint16;
	m_arrTailPoint[0] = m_tailPoint ;
	m_arrTailPoint[1] = m_tailPoint1 ;
	m_arrTailPoint[2] = m_tailPoint2 ;
	m_arrTailPoint[3] = m_tailPoint3 ;
	m_arrTailPoint[4] = m_tailPoint4 ;
	m_arrTailPoint[5] = m_tailPoint5 ;
	m_arrTailPoint[6] = m_tailPoint6 ;
	m_arrTailPoint[7] = m_tailPoint7 ;
	m_arrTailPoint[8] = m_tailPoint8 ;
	m_arrTailPoint[9] = m_tailPoint9 ;
	m_arrTailPoint[10] = m_tailPoint10 ;
	m_arrTailPoint[11] = m_tailPoint11 ;
	m_arrTailPoint[12] = m_tailPoint12 ;
	m_arrTailPoint[13] = m_tailPoint13 ;
	m_arrTailPoint[14] = m_tailPoint14 ;
	m_arrTailPoint[15] = m_tailPoint15 ;
	m_arrTailPoint[16] = m_tailPoint16 ;


	m_bDrawT= FALSE;
	m_bDraw3arrow= FALSE;
	m_bDraw2arrow= FALSE;
	m_bDrawO= FALSE;
	m_bDrawTupdown= FALSE;
	m_bDrawtenten= FALSE;
	m_bDrawtententen= FALSE;
	m_bDraw3arrow = FALSE;
	m_bDrawTT= FALSE;//
	m_bDraw3T= FALSE;
	m_bdrawNline = FALSE;
	m_nMmmV = 10;
	m_nMmS = 25; 
	m_strCurrentLead = CString("1");

	//m_vecPoint.resize(0);
	this->i = 0;

}

CTFigureDlg::~CTFigureDlg()
{
	// 	delete[] m_pPointFourLeft;
	// 	delete[] m_pPointFourRight;
	// 	delete[] m_pPointSixLeft;
	// 	delete[] m_pPointSixRight; 
	// 	delete[] m_pPointEightLeft; 
	// 	delete[] m_pPointEightRight;
}
//�������еĽ���
BOOL CTFigureDlg::AnalysisCommandLine()
{
	CString strCMD = GetCommandLineW();
	USES_CONVERSION;
    char* strbuf = T2A(strCMD.GetBuffer(0));
	strCMD.ReleaseBuffer();

	char* strBuf = new char[strlen(strbuf)+1];
	strcpy(strBuf,strbuf);
	//AfxMessageBox(CString(strBuf));
	char * cFileName = strtok(strBuf,"@");
	//AfxMessageBox(CString(cFileName)+CString("|")); 
	cFileName = strtok(NULL,"@");
	//AfxMessageBox(CString("|")+CString((char*)nullptr)+CString("|"));
	if (cFileName)
	{
		m_cstrFileLocation = CString(cFileName);
		delete[] strBuf;
		//delete[] strbuf;
		//AfxMessageBox(m_cstrFileLocation);
		return TRUE;
	} 
	else
	{
		delete[] strBuf;
	}
	//delete[] strbuf;
	return FALSE ;
}
void CTFigureDlg::DoDataExchange(CDataExchange* pDX)
{
	//����ť�Ͷ��������
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINEBUTTON, m_buttonLine);
	DDX_Control(pDX, IDC_BUTTONTEN, m_buttonTen);
	DDX_Control(pDX, IDC_DRAWTENTEN, m_buttonTenten);
	DDX_Control(pDX, IDC_DRAWTENTENTEN, m_buttonTententen);
	DDX_Control(pDX, IDC_ARROWBUTTON, m_buttonArrow);
	DDX_Control(pDX, IDC_2ARROW, m_button2Arrow);
	DDX_Control(pDX, IDC_3ARROW, m_button3Arrow);
	DDX_Control(pDX, IDC_BWAVY, m_buttonWavy);
	DDX_Control(pDX, IDC_DASHBUTTON, m_buttonDash);
	DDX_Control(pDX, ID_CIRCLEBUTTON, m_buttonCircle);
	DDX_Control(pDX, IDC_DRAWT, m_buttonT);
	DDX_Control(pDX, IDC_BUTTONTT, m_buttonTT);
	DDX_Control(pDX, IDC_BUTTON3T, m_button3T);
	DDX_Control(pDX, IDC_BUTTONOO, m_buttonCircleO);
	DDX_Control(pDX, IDC_BUTTONTTUPDOWN, m_buttonTTUpDown);
	DDX_Control(pDX, IDC_BUTTONNLINE, m_buttonNline);
	DDX_Control(pDX, IDC_CIRCLELINE, m_buttonCircleLine);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_scroChange);
	DDX_Control(pDX, IDC_COMBOXCHANGELEAD, m_LeadCombox);
	DDX_Control(pDX, IDC_COMBOMMS, m_CombommS);
	DDX_Control(pDX, IDC_COMBOMMMV, m_Combomm_mV);
	DDX_Control(pDX, IDC_COMBOX1, m_comboPattern);
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
	ON_BN_CLICKED(IDC_DASHBUTTON, &CTFigureDlg::OnBnClickedDashbutton)
	//ON_BN_CLICKED(IDC_BUTTON4, &CTFigureDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_REMAKE, &CTFigureDlg::OnBnClickedRemake)
	ON_CBN_SELCHANGE(IDC_COMBOXCHANGELEAD, &CTFigureDlg::OnCbnSelchangeComboxchangelead)
	ON_BN_CLICKED(IDC_3ARROW, &CTFigureDlg::OnBnClicked3arrow)
	ON_BN_CLICKED(IDC_DRAWT, &CTFigureDlg::OnBnClickedDrawt)
	ON_BN_CLICKED(IDC_2ARROW, &CTFigureDlg::OnBnClicked2arrow)
	ON_BN_CLICKED(IDC_BUTTONOO, &CTFigureDlg::OnBnClickedButtonoo)
	ON_BN_CLICKED(IDC_BUTTONTTUPDOWN, &CTFigureDlg::OnBnClickedButtonttupdown)
	ON_BN_CLICKED(IDC_DRAWTENTEN, &CTFigureDlg::OnBnClickedDrawtenten)
	ON_BN_CLICKED(IDC_DRAWTENTENTEN, &CTFigureDlg::OnBnClickedDrawtententen)
	ON_BN_CLICKED(IDC_BUTTONWORD, &CTFigureDlg::OnBnClickedButtonword)
	ON_BN_CLICKED(IDC_BUTTON3T, &CTFigureDlg::OnBnClickedButton3t)
	ON_BN_CLICKED(IDC_BUTTONTT, &CTFigureDlg::OnBnClickedButtontt)
	ON_BN_CLICKED(IDC_BUTTONSAVE, &CTFigureDlg::OnBnClickedButtonsave)
	ON_BN_CLICKED(IDC_BUTTONNLINE, &CTFigureDlg::OnBnClickedButtonnline)
	ON_WM_RBUTTONDOWN()
	ON_WM_XBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
	//ON_EN_CHANGE(IDC_EDIT1, &CTFigureDlg::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBOX1, &CTFigureDlg::OnCbnSelchangeCombox1)
	//ON_EN_CHANGE(IDC_EDITA_V, &CTFigureDlg::OnEnChangeEditaV)
	ON_EN_CHANGE(IDC_EDITAVS, &CTFigureDlg::OnEnChangeEditavs)
	//	ON_WM_VSCROLL()
	ON_WM_MBUTTONDOWN()
	ON_BN_CLICKED(IDC_CIRCLELINE, &CTFigureDlg::OnBnClickedCircleline)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	//ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR1, &CTFigureDlg::OnNMThemeChangedScrollbar1)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR2, &CTFigureDlg::OnNMThemeChangedScrollbar2)
	ON_WM_VSCROLL()
	ON_CBN_EDITCHANGE(IDC_COMBOXCHANGELEAD, &CTFigureDlg::OnCbnEditchangeComboxchangelead)
	ON_CBN_CLOSEUP(IDC_COMBOXCHANGELEAD, &CTFigureDlg::OnCbnCloseupComboxchangelead)
	ON_CBN_SELCHANGE(IDC_COMBOMMS, &CTFigureDlg::OnCbnSelchangeCombomms)
	ON_CBN_SELCHANGE(IDC_COMBOMMMV, &CTFigureDlg::OnCbnSelchangeCombommmv)
	// 	ON_NOTIFY(NM_OUTOFMEMORY, IDC_HOTKEY1, &CTFigureDlg::OnNMOutofmemoryHotkey1)
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
// 	this->SetDlgItemTextW(IDC_COMBOX1,_T("��������"));//��ʼΪ��������
// 	this->SetDlgItemTextW(IDC_COMBOXCHANGELEAD,_T("1"));//��ʼΪ��������
// 	this->SetDlgItemTextW(IDC_EDITAVS,_T("A;A-V;V")); 
// 	this->SetDlgItemTextW(IDC_COMBOMMS,_T("25"));
// 	this->SetDlgItemTextW(IDC_COMBOMMMV,_T("10"));
	//��ʼ��ѡ���
	m_LeadCombox.SetCurSel(0);
	m_comboPattern.SetCurSel(2);
	m_Combomm_mV.SetCurSel(1);
	m_CombommS.SetCurSel(0);
	

	//���ð�ť��С
	int x = 75;
	GetDlgItem(IDC_LINEBUTTON)->SetWindowPos(NULL, 70, 110, 73,33,SWP_NOZORDER);
	GetDlgItem(IDC_DASHBUTTON)->SetWindowPos(NULL, 70+x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_BWAVY)->SetWindowPos(NULL, 70+2*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(ID_CIRCLEBUTTON)->SetWindowPos(NULL, 70+3*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_BUTTONOO)->SetWindowPos(NULL, 70+4*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_BUTTONTEN)->SetWindowPos(NULL, 70+5*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_DRAWTENTEN)->SetWindowPos(NULL, 70+6*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_DRAWTENTENTEN)->SetWindowPos(NULL, 70+7*x, 110, 73,33,SWP_NOZORDER);
	GetDlgItem(IDC_ARROWBUTTON)->SetWindowPos(NULL, 70+8*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_2ARROW)->SetWindowPos(NULL, 70+9*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_3ARROW)->SetWindowPos(NULL, 70+10*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_DRAWT)->SetWindowPos(NULL, 70+11*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_BUTTONTT)->SetWindowPos(NULL, 70+12*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_BUTTON3T)->SetWindowPos(NULL, 70+13*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_BUTTONTTUPDOWN)->SetWindowPos(NULL, 70+14*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_BUTTONNLINE)->SetWindowPos(NULL, 70+15*x, 110, 73,33,SWP_NOZORDER );
	GetDlgItem(IDC_CIRCLELINE)->SetWindowPos(NULL, 70+16*x, 110, 73,33,SWP_NOZORDER );

	/*	((CBitmapButton *)GetDlgItem(IDC_3ARROW))->LoadBitmaps(IDB_BITMAPTEN);*/
	//����buttonλͼ
	HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPTEN));   
	m_buttonTen.SetBitmap(hBmp);
	HBITMAP hBmp1=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPARROW));   
	m_buttonArrow.SetBitmap(hBmp1);
	HBITMAP hBmp2=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPWAVY));   
	m_buttonWavy.SetBitmap(hBmp2);
	HBITMAP hBmp3=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAP2ARROW));   
	m_button2Arrow.SetBitmap(hBmp3);
	HBITMAP hBmp4=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAP3ARROW));   
	m_button3Arrow.SetBitmap(hBmp4);
	HBITMAP hBmp5=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPLINE));   
	m_buttonLine.SetBitmap(hBmp5);
	HBITMAP hBmp6=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPDASH));   
	m_buttonDash.SetBitmap(hBmp6);
	HBITMAP hBmp7=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPCIRCLE));   
	m_buttonCircle.SetBitmap(hBmp7);
	HBITMAP hBmp8=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPTENTEN));   
	m_buttonTenten.SetBitmap(hBmp8);
	HBITMAP hBmp9=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPTENTENTEN));   
	m_buttonTententen.SetBitmap(hBmp9);
	HBITMAP hBmp10=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPT));   
	m_buttonT.SetBitmap(hBmp10);
	HBITMAP hBmp11=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPTT));   
	m_buttonTT.SetBitmap(hBmp11);
	HBITMAP hBmp12=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAP3T));   
	m_button3T.SetBitmap(hBmp12);
	HBITMAP hBmp13=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPNLINE));   
	m_buttonNline.SetBitmap(hBmp13);
	HBITMAP hBmp14=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPCIRCLEO));   
	m_buttonCircleO.SetBitmap(hBmp14);
	HBITMAP hBmp15=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPTTUPDOWN));   
	m_buttonTTUpDown.SetBitmap(hBmp15);
	HBITMAP hBmp16=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPCIRCLELINE));   
	m_buttonCircleLine.SetBitmap(hBmp16);
	cLead[0] = "I";
	cLead[1] = "II";
	cLead[2] = "III";
	cLead[3] = "AVR";
	cLead[4] = "AVL";
	cLead[5] = "AVF";
	cLead[6] = "V1";
	cLead[7] = "V2";
	cLead[8] = "V3";
	cLead[9] = "V4";
	cLead[10] = "V5";
	cLead[11] = "V6";

	m_scroChange.SetScrollRange(1, 200);   
	m_scroChange.SetScrollPos(100); 
	//���ù�����λ��     
	GetDlgItem(IDC_SCROLLBAR2)->SetWindowPos(NULL, 1850, 150, 20,150,SWP_NOZORDER);
	

	//Ĭ�Ͽ�ʼ������������  //��־λ����
	bFourThree = TRUE;
	bSixFive = FALSE; 
	bEightSeven = FALSE;
	this->SetDlgItemTextW(IDC_EDITAVS,CString("A;A-V;V"));
	//this->Invalidate(0);
	//m_nMmmV = 10;
	//m_nMmS = 25; 
	//DrawGrid(CPoint(15+25+5,150),CPoint(1850-5,290));
	// 	ppDC = NULL;
	// 	ppDC = GetDC();
	//CRect rect(20,20,80,50);
	//ShortTextInput(rect);
	ShowWindow(SW_SHOWMAXIMIZED);//���


	//ͨ�������д�XML����json�ļ�
	using namespace  std;
	//static int nForbid = 0;
	//int a =1 ;
	if(AnalysisCommandLine() == TRUE/* && nForbid==0*/)
		//������ͨ���˷�ʽ��һ�Σ������򿪷�ʽ�����Ի���
	{
		//m_cstrFileLocation = dlg.GetPathName();
		//AnalysisCommandLine();
		//nForbid++;
		USES_CONVERSION;
		char* pathName = T2A(m_cstrFileLocation.GetBuffer(0)); 
		//std::unique_ptr<char> pathName(new char[strlen(pathNameTmp)]);
		m_cstrFileLocation.ReleaseBuffer();
		std::string strFilename = pathName;
		//�õ��ļ���׺
		std::string suffixStr = strFilename.substr(strFilename.find_last_of('.') + 1);
		//�����xml�ļ�
		if(suffixStr == "xml")
		{
			//�ݴ�XML�ļ�·��
			//std::unique_ptr<string> pPathName(new string(pathName));

			//string* pPathName = new string(pathName);
			//std::shared_ptr<string> pp(pPathName) ;
			m_cXmlFilePath = pathName;
			//m_cXmlFilePath = pathName;
#if DEBUGS:
			AfxMessageBox(CString(suffixStr.c_str()));Sleep(1);
#endif
			TiXmlElement pTempEle = SelectElementByName(pathName,"digits", 1,0);
			m_bChangeLead = FALSE;
			//Sleep(1);
			//printf("find the Name : %s, Text = %s\n", pTempEle.Value(), pTempEle.GetText());
			//Sleep(2);
			const char* str = pTempEle.GetText();
			std::vector<CString> vecString;
			std::vector<int> vecNum;
			m_vecPoint.resize(0);
			char tempstr[8];
			char* p = tempstr;
			memset(tempstr,0,8);
			//������
			//std::vector<CPoint>  vecPoint;
			//���±��X
			double nPointX = 20+150 ;
			//Sleep(2);
			if(CString(str)!=CString(""))
			{
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
						m_vecPoint.push_back(CPoint(d_round(nPointX),d_round(( 4200-(atoi(tempstr)+4200))*0.009*m_nMmmV/10+250) ));   //��ŵ�λ
						nPointX = nPointX + 0.1554*m_nMmS/25;/*0.18 ;*//*1554/10000*/ /*0.0250.16098*/
						vecNum.push_back(atoi(tempstr));
						memset(tempstr,0,8);
						p = tempstr;
					}
				}
			}
			//Sleep(3);
			char nnn[10];
			memset(nnn,0,10);
			//sprintf(nnn,"min:%d",FindMin(vecNum));
			sprintf(nnn,"min:%d",m_vecPoint.size());
#if DEBUGS:
			AfxMessageBox(CString(nnn));
#endif
			this->Invalidate(1);
		}

		//�����json�ļ�
		else if(suffixStr == "json")
		{
			//this->i = 0;
			ClearPoint(); //��յ�λ
			this->i = 0;
			CTFigureDlg::readfireadFileJson(m_cstrFileLocation);
		}
		else
		{
			AfxMessageBox(_T("��֧���������,\n\r.xml�ĵ�ͼ�����ļ���.json����ͼ��ͼ�����ļ�"));
		}
		//		return ; //������������������򷵻� ������ִ�н���

	}
	//Ĭ����������
	//OnBnClickedStartbutton();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CTFigureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	//�����϶�
	if (nID == SC_MOVE || nID == 0xF012)
		return;
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
//��ȡ�Ի������ݲ�չʾ��

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
/*int n=7;*/
void CTFigureDlg::OnPaint()
{	

	//TODO : test:  ���Ƽ�ͷ
#if 0: \
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
#if 0: \
	CPaintDC dcTest(this);
	dcTest.DrawTextW(CString("test"),CRect(450,180,480,210),DT_CENTER);
	CPoint p1(40,40),p2(220,90);
	DrawTen( p1, p2,8.0,30);
#endif	
	//��ӡ�ļ�λ��
	drawDispalyFilePath(m_cstrFileLocation);
	CPoint left1(15+25,300),right1(1850,850);  //��������
	InitArea(left1,right1);
	//˫��������ĵ�ͼ���
	/*********************************/
	// 	{
	// 		CClientDC pDC(this);
	// // 		pDC.SetBkMode(TRANSPARENT);
	// 		//pDC.SelectStockObject(NULL_BRUSH);
	//  		//pDC.Rectangle(0,0,1900,120);
	// 		CPoint ptCenter;
	// 		CRect rect(0,0,200,200),ellipseRect;
	// 		//GetClientRect(&rect);
	// 		ptCenter = rect.CenterPoint();
	// 		CDC dcMem;                                   //���ڻ�����ͼ���ڴ�DC
	// 		CBitmap bmp;                                 //�ڴ��г�����ʱͼ���λͼ
	// 		bmp.CreateCompatibleBitmap(&dcMem,rect.Width(),rect.Height());//��������λͼ
	// 		dcMem.CreateCompatibleDC(&pDC);               //��������DC���������ڴ�DC
	// 		dcMem.SelectObject(&bmp);                    //��λͼѡ����ڴ�DC
	// 		//dcMem.FillSolidRect(rect,pDC.GetBkColor()); //��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
	// 		for(int i=20;i>0;i--)                        //���ڴ�DC����ͬ����ͬ��Բͼ��
	// 		{
	// 			ellipseRect.SetRect(ptCenter,ptCenter);
	// 			ellipseRect.InflateRect(i*10,i*10);
	// 			dcMem.Ellipse(ellipseRect);
	// 		}
	// 		pDC.BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
	// 		dcMem.DeleteDC();                            //ɾ��DC
	// 		bmp.DeleteObject();                           //ɾ��λͼ
	// 	}
	//���߳�ʼ��
	if(bEightSeven == TRUE)
	{	
		//�������
		for(int i=0;i<6;i++)
		{
			m_pPointSixLeft[i].y =0;
			m_pPointSixLeft[i].x =0;
			m_pPointSixRight[i].y =0;
			m_pPointSixRight[i].x =0;
		}
		//�������
		for(int i=0;i<4;i++)
		{
			m_pPointFourLeft[i].y =0;
			m_pPointFourLeft[i].x =0;
			m_pPointFourRight[i].y =0;
			m_pPointFourRight[i].x =0;
		}
		//bSixFive = FALSE;
		//CPoint left1(15,300),right1(1850,850);  //��������
		InitArea(left1,right1);
		CPoint left(20+25,340),right(1800+25,340);  //ģ���߶�
		m_pPointEightLeft[0] = left;
		m_pPointEightRight[0] = right;
		CString str[9];
		m_strAVS[0]="S";
		m_strAVS[1]="S-A";
		m_strAVS[2]="A";
		m_strAVS[3]="A-V";
		m_strAVS[4]="BB";
		m_strAVS[5]="V";
		m_strAVS[6]="St";
		CClientDC dc(this);
		//AfxMessageBox(_T("333"));
		for(int i=0;i<8;i++)
		{
			DrawLine(m_pPointEightLeft[i], m_pPointEightRight[i]);
			if(i<7)
			{
				//dc.TextOutW(m_pPointEightLeft[i].x,(m_pPointEightLeft[i].y+m_pPointEightLeft[i+1].y)/2-9,m_strAVS[i]);
			} 
			left.y+=60;
			m_pPointEightLeft[i+1].y = left.y;
			m_pPointEightLeft[i+1].x = left.x;
			right.y+=60;
			m_pPointEightRight[i+1].y = right.y;
			m_pPointEightRight[i+1].x = right.x;
		}
		bEightSeven = FALSE;
	}
	//���ư���
	CClientDC dc(this);
	CString str[9];
	// 	m_strAVS[0]="A";
	// 	m_strAVS[1]="A-V";
	// 	m_strAVS[2]="V";
	// 	m_strAVS[3]="V-S";
	// 	m_strAVS[4]="S";
	// 	m_strAVS[5]="S-A";
	// 	m_strAVS[6]="A";
	//ShortTextInput(CRect(20,20,40,40));
	//CPoint left1(15,300),right1(1850,850);  //��������
	//InitArea(left1,right1);
	for(int i=0;i<8;i++)
	{

		DrawLine(m_pPointEightLeft[i], m_pPointEightRight[i]);
		if(i<7 && m_pPointEightLeft[i] != CPoint(0,0))
		{
			dc.TextOutW(m_pPointEightLeft[i].x,(m_pPointEightLeft[i].y+m_pPointEightLeft[i+1].y)/2-9,m_strAVS[i]);
		} 
	}

	//���߳�ʼ��
	if(bFourThree == TRUE)
	{	
		//�������
		for(int i=0;i<6;i++)
		{
			m_pPointSixLeft[i].y =0;
			m_pPointSixLeft[i].x =0;
			m_pPointSixRight[i].y =0;
			m_pPointSixRight[i].x =0;
		}
		//��հ���
		for(int i=0;i<8;i++)
		{
			m_pPointEightLeft[i].y =0;
			m_pPointEightLeft[i].x =0;
			m_pPointEightRight[i].y =0;
			m_pPointEightRight[i].x =0;
		}
		//bSixFive = FALSE;
		//CPoint left1(15,300),right1(1850,850);  //��������
		InitArea(left1,right1);

		CPoint left(20+25,340),right(1800+25,340);  //ģ���߶�
		m_pPointFourLeft[0] = left;
		m_pPointFourRight[0] = right;
		CString str[5];
		m_strAVS[0]="A";
		m_strAVS[1]="A-V";
		m_strAVS[2]="V";
		CClientDC dc(this);
		for(int i=0;i<4;i++)
		{
			DrawLine(m_pPointFourLeft[i], m_pPointFourRight[i]);

			if(i<3)
			{
				//dc.TextOutW(m_pPointFourLeft[i].x,(m_pPointFourLeft[i].y+m_pPointFourLeft[i+1].y)/2-9,m_strAVS[i]);
			} 
			left.y+=60;
			m_pPointFourLeft[i+1].y = left.y;
			m_pPointFourLeft[i+1].x = left.x;
			right.y+=60;
			m_pPointFourRight[i+1].y = right.y;
			m_pPointFourRight[i+1].x = right.x;
		}
		bFourThree = FALSE;
	}
	//��������
	//	CClientDC dc(this);
	// 	CString str4[5];
	// 	m_strAVS[0]="A";
	// 	m_strAVS[1]="A-V";
	// 	m_strAVS[2]="V";
	//ShortTextInput(CRect(20,20,40,40));
	//CPoint left1(15,300),right1(1850,850);  //��������
	//InitArea(left1,right1);
	for(int i=0;i<4;i++)
	{

		DrawLine(m_pPointFourLeft[i], m_pPointFourRight[i]);

		if(i<3 && m_pPointFourLeft[i] != CPoint(0,0))
		{
			dc.TextOutW(m_pPointFourLeft[i].x,(m_pPointFourLeft[i].y+m_pPointFourLeft[i+1].y)/2-9,m_strAVS[i]);
		} 
	}

	if(bSixFive == TRUE)

	{	
		//�������
		for(int i=0;i<4;i++)
		{
			m_pPointFourLeft[i].y =0;
			m_pPointFourLeft[i].x =0;
			m_pPointFourRight[i].y =0;
			m_pPointFourRight[i].x =0;
		}
		//��հ���
		for(int i=0;i<8;i++)
		{
			m_pPointEightLeft[i].y =0;
			m_pPointEightLeft[i].x =0;
			m_pPointEightRight[i].y =0;
			m_pPointEightRight[i].x =0;
		}
		//this->bFourThree = FALSE;
		//CPoint left1(15,300),right1(1850,850);
		InitArea(left1,right1);
		CPoint left(20+25,340),right(1800+25,340);
		m_pPointSixLeft[0] = left;
		m_pPointSixRight[0] = right;
		CString str[6];
		m_strAVS[0]="S";
		m_strAVS[1]="S-A";
		m_strAVS[2]="A";
		m_strAVS[3]="A-V";
		m_strAVS[4]="V";
		CClientDC dc(this);//
		for(int i=0;i<6;i++)
		{
			DrawLine(m_pPointSixLeft[i], m_pPointSixRight[i]);
			if(i<5 && m_pPointSixLeft[i]!=CPoint(0,0))
			{
				//������ʾ
				//dc.TextOutW(m_pPointSixLeft[i].x,(m_pPointSixLeft[i].y+m_pPointSixLeft[i+1].y)/2-9,m_strAVS[i]);
			}
			left.y+=60;
			m_pPointSixLeft[i+1].y = left.y;
			m_pPointSixLeft[i+1].x = left.x;
			right.y+=60;	
			m_pPointSixRight[i+1].y = right.y;
			m_pPointSixRight[i+1].x = right.x;
		}
		bSixFive = FALSE ;
	}

	CString str1[6];
	// 	m_strAVS[0]="S";
	// 	m_strAVS[1]="S-A";
	// 	m_strAVS[2]="A";
	// 	m_strAVS[3]="A-V";
	// 	m_strAVS[4]="V";
	for(int i=0;i<6;i++)
	{
		DrawLine(m_pPointSixLeft[i], m_pPointSixRight[i]);
		if(i<5 && m_pPointSixLeft[i]!=CPoint(0,0))
		{
			dc.TextOutW(m_pPointSixLeft[i].x,(m_pPointSixLeft[i].y+m_pPointSixLeft[i+1].y)/2-9,m_strAVS[i]);
		}
	}

	//this->SetDlgItemTextW(IDC_COMBOX1,_T("��������"));//��ʼΪ��������

	/*******************************************/
	if(m_flagTracking == TRUE)
	{	
		CClientDC dc(this);
		CPen pen(PS_SOLID,2,RGB(0,0,0));
		dc.SelectObject(&pen);
		//char p1[10];
		//sprintf(p1,"%d,%d",m_headPoint);
		//CString str(p1);
		//AfxMessageBox(str);
		for(int j=0;j<i;j++)
		{
			if((m_headPoint[j] != m_tailPoint[j])&&(m_headPoint[j])!= CPoint(0,0))
			{
				dc.MoveTo(m_headPoint[j]);
				dc.LineTo(m_tailPoint[j]);
			}
		}


	}
	if(m_flagTracking == TRUE)
	{	
		CClientDC dc(this);
		CPen pen(PS_SOLID,1,RGB(0,0,0));
		dc.SelectObject(&pen);
		dc.SelectStockObject(WHITE_BRUSH);

		//char p1[10];
		//sprintf(p1,"%d,%d",m_headPoint);
		//CString str(p1);
		//AfxMessageBox(str);
		//����Բ
		for(int j=0;j<i;j++)
		{	
			/*dc.MoveTo(m_headPoint1[j]);
			dc.LineTo(m_tailPoint1[j]);*/
			//
			//DrawArrow( m_headPoint1[j], m_tailPoint1[j],45.0,10);
			if(m_headPoint1[j] == m_tailPoint1[j])
			{
				//����Բ�Ĵ�С
				int dist= 5 ;
				dc.SelectStockObject(BLACK_BRUSH);
				dc.Ellipse(m_headPoint1[j].x - dist,m_headPoint1[j].y - dist,m_tailPoint1[j].x+dist,m_tailPoint1[j].y+dist);
			}
			else
			{
				dc.SelectStockObject(BLACK_BRUSH);
				dc.Ellipse(m_headPoint1[j].x,m_headPoint1[j].y,m_tailPoint1[j].x,m_tailPoint1[j].y);
			}

			if(m_headPoint15[j] == m_tailPoint15[j])
			{
				//����Բ�Ĵ�С
				int dist= 5 ;
				dc.SelectStockObject(WHITE_BRUSH);
				dc.Ellipse(m_headPoint15[j].x - dist,m_headPoint15[j].y - dist,m_tailPoint15[j].x+dist,m_tailPoint15[j].y+dist);
			}
			else
			{
				dc.SelectStockObject(WHITE_BRUSH);
				dc.Ellipse(m_headPoint15[j].x,m_headPoint15[j].y,m_tailPoint15[j].x,m_tailPoint15[j].y);
			}

		}
	}
	//����Dash
	if(m_flagTracking == TRUE)
	{	
		CClientDC dc(this);
		CPen pen(PS_DASH,1,RGB(0,0,0));
		dc.SelectObject(&pen);
		//char p1[10];
		//sprintf(p1,"%d,%d",m_headPoint);
		//CString str(p1);
		//AfxMessageBox(str);7 
		for(int j=0;j<i;j++)
		{
			//dc.MoveTo(m_headPoint5[j]);
			//dc.LineTo(m_tailPoint5[j]);
			if((m_headPoint5[j] != m_tailPoint5[j])&&(m_headPoint5[j])!= CPoint(0,0))
			{
				DrawDash(m_headPoint5[j],m_tailPoint5[j],7);
			}
			if((m_headPoint16[j] != m_tailPoint16[j])&&(m_headPoint16[j])!= CPoint(0,0))
			{
				DrawCircleLine(m_headPoint16[j],m_tailPoint16[j],7);
			}
			//Draw2Arrow(m_headPoint5[j],m_tailPoint5[j],7);
			if((m_headPoint14[j] != m_tailPoint14[j])&&(m_headPoint14[j])!= CPoint(0,0))
			{
				DrawNLine(m_headPoint14[j],m_tailPoint14[j],7);
			}
			if((m_headPoint13[j] != m_tailPoint13[j])&&(m_headPoint13[j])!= CPoint(0,0))
			{
				DrawTTUpDown(m_headPoint13[j],m_tailPoint13[j],7);
			}

			//DrawCircleLine(m_headPoint5[j],m_tailPoint5[j],7);
		}
	}
	//����T

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
			if((m_headPoint2[j] != m_tailPoint2[j])&&(m_headPoint2[j])!= CPoint(0,0))
			{
				DrawArrow(m_headPoint2[j], m_tailPoint2[j],45.0,10);
			}

			if((m_headPoint6[j] != m_tailPoint6[j])&&(m_headPoint6[j])!= CPoint(0,0))
			{
				DrawArrow(m_headPoint6[j], m_tailPoint6[j],90.0,10);
			}
			if((m_headPoint11[j] != m_tailPoint11[j])&&(m_headPoint11[j])!= CPoint(0,0))
			{
				DrawTT(m_headPoint11[j], m_tailPoint11[j],10);
			}
			if((m_headPoint12[j] != m_tailPoint12[j])&&(m_headPoint12[j])!= CPoint(0,0))
			{
				Draw3T(m_headPoint12[j], m_tailPoint12[j],10);
			}
			//dc.Ellipse(m_headPoint1[j].x,m_headPoint1[j].y,m_tailPoint1[j].x,m_tailPoint1[j].y);
		}
		//2 arrow && 3arrow
		for(int j=0;j<i;j++)
		{	
			/*		dc.MoveTo(m_headPoint1[j]);
			dc.LineTo(m_tailPoint1[j]);*/
			//
			if((m_headPoint9[j] != m_tailPoint9[j])&&(m_headPoint9[j])!= CPoint(0,0))
			{
				Draw2Arrow(m_headPoint9[j], m_tailPoint9[j],10);
			}
			if((m_headPoint10[j] != m_tailPoint10[j])&&(m_headPoint10[j])!= CPoint(0,0))
			{

				Draw3Arrow(m_headPoint10[j], m_tailPoint10[j],10);
			}
			//dc.Ellipse(m_headPoint1[j].x,m_headPoint1[j].y,m_tailPoint1[j].x,m_tailPoint1[j].y);
		}


		//����Ten  ����tenten
		for(int j=0;j<i;j++) 
		{	
			//if(m_headPoint3[j] ==m_tailPoint3[j]) continue;
			if((m_headPoint3[j] != m_tailPoint3[j])&&(m_headPoint3[j])!= CPoint(0,0))
			{
				DrawTen(m_headPoint3[j], m_tailPoint3[j],15.0,10);
			}
			//tenten
			if((m_headPoint7[j] != m_tailPoint7[j])&&(m_headPoint7[j])!= CPoint(0,0))
			{
				DrawTentenB(m_headPoint7[j], m_tailPoint7[j],5);
			}
			// 			DrawTenten(m_headPoint7[j], m_tailPoint7[j],15.0,10);
			// 			CPoint tempPoint(0,0);
			// 			tempPoint.x = abs(m_headPoint7[j].x + m_tailPoint7[j].x)/2;
			// 			tempPoint.y = abs(m_headPoint7[j].y + m_tailPoint7[j].y)/2;
			// 			for(int i=0;i<1;i++)
			// 			{
			// 				tempPoint.x = abs(m_headPoint7[j].x + tempPoint.x)/2;
			// 				tempPoint.y = abs(m_headPoint7[j].y + tempPoint.y)/2;
			// 			}
			// 			DrawTenten(tempPoint, m_tailPoint7[j],15.0,10);

			//tententen
			if((m_headPoint8[j] != m_tailPoint8[j])&&(m_headPoint8[j])!= CPoint(0,0))
			{
				DrawTententenB(m_headPoint8[j], m_tailPoint8[j],5);
			}
			//CPoint tempPoint(0,0);
			// 			tempPoint.x = abs(m_headPoint8[j].x + m_tailPoint8[j].x)/2;
			// 			tempPoint.y = abs(m_headPoint8[j].y + m_tailPoint8[j].y)/2;
			// 			for(int i=0;i<1;i++)
			// 			{
			// 				tempPoint.x = abs(m_headPoint8[j].x + tempPoint.x)/2;
			// 				tempPoint.y = abs(m_headPoint8[j].y + tempPoint.y)/2;
			// 			}
			// 			DrawTenten(tempPoint, m_tailPoint8[j],15.0,10);
			// 
			// 			tempPoint.x = abs(m_headPoint8[j].x + m_tailPoint8[j].x)/2;
			// 			tempPoint.y = abs(m_headPoint8[j].y + m_tailPoint8[j].y)/2;
			// 			for(int i=0;i<1;i++)
			// 			{
			// 				tempPoint.x = abs(tempPoint.x + m_tailPoint8[j].x)/2;
			// 				tempPoint.y = abs(tempPoint.y + m_tailPoint8[j].y)/2;
			// 			}
			// 			DrawTenten(m_headPoint8[j], tempPoint,15.0,10);
			//if(m_tailPoint7[j].x-m_headPoint7[j].x != 0)
			//DrawTenten(CPoint(m_headPoint7[j].x,m_headPoint7[j].y), \
			//CPoint(m_tailPoint7[j].x-6,\
			//m_tailPoint7[j].y-6*((m_tailPoint7[j].y-m_headPoint7[j].y)/(m_tailPoint7[j].x-m_headPoint7[j].x))),15.0,10);

			//DrawTen(m_headPoint7[j], m_tailPoint7[j],15.0,10);

		}
		//����Wavy

		for(int j=0;j<i;j++) 
		{	
			//if(m_headPoint4[j] ==m_tailPoint4[j]) continue;
			if((m_headPoint4[j] != m_tailPoint4[j])&&(m_headPoint4[j])!= CPoint(0,0))
			{
				DrawWavy(m_headPoint4[j], m_tailPoint4[j],5);
			}
		}
		//Sleep(2);
	}
	// 	int flag[1024];
	// 	int k = 0 ;
	// 	bool bFlag = true;
	// 	//ΪԲ�����
	// 	vector<CPoint*> vecPPoint;
	// 	int m=0;
	// 	for (int n = 0;n<this->i;n++)
	// 	{
	// 		for (int nn=0;nn<n;nn++)
	// 		{
	// 			if(m_headPoint1[n].y == m_headPoint1[nn].y)
	// 				bFlag = false;
	// 			else 
	// 				bFlag = true;
	// 		}
	// 		if(bFlag == true)
	// 		{
	// 			flag[k] = m_headPoint1[n].y;
	// 			k++;
	// 			CPoint* temp = new CPoint[i];
	// 			temp[m] = m_headPoint1[n];
	// 			m++;
	// 			vecPPoint.push_back(temp);
	// 		}
	// 		else
	// 		{
	// 			for (int nnn = 0;nnn<sizeof(flag)/sizeof(int);nnn++)
	// 			{
	// 				if (flag[nnn] == m_headPoint1[n].y)
	// 				{
	// 					vecPPoint[nnn][m] = m_headPoint1[n].y;
	// 				}
	// 			}	
	// 		}
	// 	}
	// 	for (vector<CPoint*>::iterator it = vecPPoint.begin();it != vecPPoint.end();it++ )
	// 	{
	// 		DrawDistenceText(*it);
	// 	}
	//��ʾ����
	if(m_vecEdit.size()>0)
	{
		CString strText;
		int n;
		for( n = 0 ;n<m_vecEdit.size();n++)
		{
			this->GetDlgItemTextW(ID_EDIT1+n,strText);
			if(m_bDrawText == false)
			{
				this->GetDlgItem((ID_EDIT1+n))->ShowWindow(false);
				CClientDC dc(this);
				dc.SetBkMode(TRANSPARENT);//����
				LOGFONT lf; //�߼���
				::ZeroMemory(&lf, sizeof(lf));//���ڴ棬::���Ե���API����
				lf.lfHeight = 90;//8����
				lf.lfWeight =  FW_HEAVY;//
				lf.lfItalic = FALSE;//��б��
				::lstrcpy(lf.lfFaceName, TEXT("Times New Roman"));
				CFont font2;
				font2.CreatePointFontIndirect(&lf);
				dc.SelectObject(&font2);
				dc.TextOutW(m_headPointText[n].x,m_headPointText[n].y,strText);
			}
			else
			{
				CString str;
				if (this->GetDlgItemTextW(ID_EDIT1+n,str))
				{
					this->GetDlgItem((ID_EDIT1+n))->ShowWindow(TRUE);
				}
			}

		}
	}
	DrawDistenceText(m_headPoint1);
	DrawDistenceText(m_headPoint15);
	//�����ĵ�ͼ���
	DrawGrid(CPoint(15+25+5,145),CPoint(1850-5,295));

	// 	double nDistance;
	// 	char tem[10];
	// 	//���ƾ����ı�
	// 	vector<CPoint> vecPointTemp;
	// 	for (int n=0;n<this->i;n++)
	// 	{
	// 		vecPointTemp.push_back(m_headPoint1[n]);
	// 	}
	// 	//����
	// 	std::sort(vecPointTemp.begin(),vecPointTemp.end(),cmp);
	// 	for (int n=0;n<this->i-1;n++)
	// 	{
	// 		nDistance = (vecPointTemp[n+1].x - vecPointTemp[n].x)*0.1609;
	// 		memset(tem,0,10);
	// 		sprintf(tem,"%d",d_round(nDistance));
	// 		CString strDistance(tem);
	// 		dc.TextOutW( (vecPointTemp[n].x+vecPointTemp[n+1].x)/2 - 10,vecPointTemp[n].y - 10,strDistance);
	// 	}



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
	//	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(&pen);
	//dc.Rectangle(0,0,10,10);
	int i=0;
	//TODO: vector ������Ҫ���
	//for (int i=0;i<10000;i++)
	//{
	//	point[i] = m_vecPoint[i];
	//}
	for (int n=0;n<10002;n++)
	{
		point[n] = CPoint(0,0);
	}

	for(std::vector<CPoint>::iterator iter = m_vecPoint.begin();iter !=m_vecPoint.end();iter++)
	{
		point[i] = *iter;	
		i++;
	}
	//dc.PolyBezier(point,10000);
	if (m_CombommS.GetCurSel() == 1)  //�����50mm_s ���β���ʾ
	{
		dc.Polyline(point,5000);
	}
	else
	{
		dc.Polyline(point,10000);
	}
	//�ڵ�������

	//dc.SetBkMode(TRANSPARENT);
	// 	dc.SelectStockObject(NULL_PEN);
	// 	//dc.SelectStockObject(LTGRAY_BRUSH);
	// 	dc.Rectangle(1850,150,1920,280);


	//��ָ��λ����ʾ����
	// 	CDC* dc_T = GetDC();
	// 
	// 	// ����Ϊ����͸��
	// 	dc_T->SetBkMode(TRANSPARENT);
	// 	// ����������ɫ
	// 	dc_T->SetTextColor(RGB(255, 0, 0));
	// 
	// 	dc_T->DrawText(_T("�����ʾ"), &CRect(10,10,40,40), DT_LEFT);

	//�ı������Բ�ļ����С
	// 	CPoint temp[1024];
	// 	for(int n = 0;n<this->i;n++)
	// 	{
	// 		temp[n] = m_headPoint1[n];
	// 	}
	// 
	// 	for(int m = 0;m<this->i;m++)
	// 	{
	// 		for(int j=0;j<=this->i-m-1;j++)
	// 		{
	// 			if(temp[j].x>temp[j+1].x)
	// 			{
	// 				temp[1023]=temp[j];
	// 				temp[j]=temp[j+1];
	// 				temp[j+1]=temp[1023];
	// 			}
	// 		}
	// 	}
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
	if(this->m_bChangeFlag == TRUE)
	{
		int ret = AfxMessageBox(_T("����δ���棿ȷ���˳���") ,MB_OKCANCEL);
		if(ret == IDCANCEL)
		{
			return ;
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
	else
	{

		int ret = AfxMessageBox(_T("ȷ���˳���") ,MB_OKCANCEL);
		if(ret == IDCANCEL)
		{
			return ;
		}
		else
		{
			CDialogEx::OnOK();
		}
	}

}


void CTFigureDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTFigureDlg::OnBnClickedStartbutton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 	if(m_bChangeLead == TRUE)
	// 	{
	// 		LeadPaint();
	// 		m_bChangeLead = FALSE;
	// 	}
	//this->SetDlgItemTextW(IDC_COMBOX1,_T("��������"));//��ʼΪ��������
	CString strCurrent;
	CString strCurrent1("��������");
	CString strCurrent2("��������");
	CString strCurrent3("��������");
	//this->GetDlgItemTextW(IDC_COMBOX1,strCurrent);
	//CString strChoosed;
	m_comboPattern.GetLBText(m_comboPattern.GetCurSel(),strCurrent);
	if(strCurrent == strCurrent1)
	{
		//dc.TextOutW(300,300,strCurrent);
		//��ʼ������������  //��־λ����
		bFourThree = TRUE;
		bSixFive = FALSE; 
		bEightSeven = FALSE;
		this->SetDlgItemTextW(IDC_EDITAVS,CString("A;A-V;V"));
		this->Invalidate(0);
	}
	if(strCurrent == strCurrent2)
	{
		bSixFive = TRUE;
		bFourThree = FALSE;
		bEightSeven = FALSE;
		this->SetDlgItemTextW(IDC_EDITAVS,CString("S;S-A;A;A-V;V"));
		this->Invalidate(0);
	}
	if(strCurrent == strCurrent3)
	{
		bEightSeven = TRUE;
		bSixFive = FALSE;
		bFourThree = FALSE;
		this->SetDlgItemTextW(IDC_EDITAVS,CString("S;S-A;A;A-V;V;BB;V;St"));
		this->Invalidate(0);
	}
	//Sleep(100);
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
void CTFigureDlg::DrawLine(CPoint left, CPoint right,CDC* dc)
{
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	int nOldMode = dc->SetROP2(R2_NOT);
	dc->SelectObject(&pen);
	dc->MoveTo(left);
	dc->LineTo(right);
	dc->SetROP2(nOldMode);
	return ;
}
void CTFigureDlg::DrawLine(CPoint left, CPoint right)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	//int nOldMode = dc->SetROP2(R2_NOT);
	dc.SelectObject(&pen);
	dc.MoveTo(left);
	dc.LineTo(right);
	//dc->SetROP2(nOldMode);
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
	if(this->m_bChangeFlag == TRUE)
	{
		int ret = AfxMessageBox(_T("����δ���棿ȷ���˳���") ,MB_OKCANCEL);
		if(ret == IDCANCEL)
		{
			return ;
		}
		else
		{

			CDialogEx::OnOK();
		}
	}
	else
	{
		int ret = AfxMessageBox(_T("ȷ���˳���") ,MB_OKCANCEL);
		if(ret == IDCANCEL)
		{
			return ;
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
}

void CTFigureDlg::InvertLine(CDC* pDC,CPoint x,CPoint y)
{
	//��	 ��				//�� //��
	int nOldMode = pDC->SetROP2(R2_NOT);
	pDC->MoveTo(x);//�� //��
	pDC->LineTo(y); 
	pDC->SetROP2(nOldMode);	 //�� //�� 
}

void CTFigureDlg::InvertCircle(CDC* pDC,CPoint x,CPoint y)
{
	int nOldMode = pDC->SetROP2(R2_NOT);
	//pDC->MoveTo(x);
	//pDC->LineTo(y);
	pDC->SelectStockObject(BLACK_BRUSH);
	//pDC->SelectStockObject(BLACK_PEN);
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

//�ƶ�ʱ������Ƥ����

// if(m_flagTracking == TRUE && m_bTracking == TRUE) 
// {
// 	CClientDC dc(this);
// 	InvertLine(&dc,this->m_headPoint4[i],this->m_tailPoint4[i]);  //���Ʒ�ת��
// 	InvertLine(&dc,this->m_headPoint4[i],point);
// 	//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
// 	m_tailPoint4[i] = point;
// }
void CTFigureDlg::OnMouseMoveDrawLine(CPoint point,CPoint headPoint, CPoint tailPoint)
{
	if(m_flagTracking == TRUE && m_bTracking == TRUE) 
	{
		CClientDC dc(this);
		InvertLine(&dc,headPoint,tailPoint);  //���Ʒ�ת��
		InvertLine(&dc,headPoint,point);
		//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
		tailPoint = point;
	}
}
CPoint Temp;
CPoint Temp2;
void CTFigureDlg::DrawGhost(CPoint* headPoint4,CPoint* tailPoint4,int nDx,int nDy)
{
	CClientDC dcDc(this);
	IsDrawWhatAdd(headPoint4,tailPoint4,nDx,nDy);
	if(m_iFallinWhere == WAVY)
	{	
		DrawWavy(Temp,Temp2,5,&dcDc);
		//Sleep(2);
		DrawWavy(m_FlagPointL,m_FlagPointR,5,&dcDc);
		//Sleep(1);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
		// 			if (x>10000)
		// 			{
		// 				for (int n=1 ;n<10001;n++)
		// 				{
		// 					Temp[n] = CPoint(0,0);
		// 					Temp2[n] = CPoint(0,0);
		// 				}
		// 				x=0;
		// 				Temp[0] = Temp[10001]; 
		// 				Temp2[0]= Temp2[10001]; 
		// 			}
	}
	if(m_iFallinWhere == ARROW)
	{
		DrawArrow(Temp,Temp2,45,10,&dcDc);
		DrawArrow(m_FlagPointL,m_FlagPointR,45,10,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == TWOARROW)
	{
		Draw2Arrow(Temp,Temp2,10,&dcDc);
		Draw2Arrow(m_FlagPointL,m_FlagPointR,10,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == THREEARROW)
	{
		Draw3Arrow(Temp,Temp2,10,&dcDc);
		Draw3Arrow(m_FlagPointL,m_FlagPointR,10,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if (m_iFallinWhere == TEN )
	{
		DrawTen(Temp,Temp2,15.0,10,&dcDc);
		DrawTen(m_FlagPointL,m_FlagPointR,15.0,10,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if (m_iFallinWhere == TENTEN )
	{
		DrawTentenB(Temp,Temp2,5,&dcDc);
		DrawTentenB(m_FlagPointL,m_FlagPointR,5,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if (m_iFallinWhere == TENTENTEN )
	{
		DrawTententenB(Temp,Temp2,8,&dcDc);
		DrawTententenB(m_FlagPointL,m_FlagPointR,8,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == T)
	{
		DrawArrow(Temp,Temp2,90,10,&dcDc);
		DrawArrow(m_FlagPointL,m_FlagPointR,90,10,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == TT)
	{
		DrawTT(Temp,Temp2,3,&dcDc);
		DrawTT(m_FlagPointL,m_FlagPointR,3,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == TTT)
	{
		Draw3T(Temp,Temp2,3,&dcDc);
		Draw3T(m_FlagPointL,m_FlagPointR,3,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == TTUPDOWN)
	{
		DrawTTUpDown(Temp,Temp2,3,&dcDc);
		DrawTTUpDown(m_FlagPointL,m_FlagPointR,3,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == NLINE)
	{
		DrawNLine(Temp,Temp2,3,&dcDc);
		DrawNLine(m_FlagPointL,m_FlagPointR,3,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == DASH)
	{
		DrawDash(Temp,Temp2,7,&dcDc);
		DrawDash(m_FlagPointL,m_FlagPointR,7,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == LINE)
	{
		DrawLine(Temp,Temp2,&dcDc);
		DrawLine(m_FlagPointL,m_FlagPointR,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	if(m_iFallinWhere == CIRCLELINE)
	{
		DrawCircleLine(Temp,Temp2,5,&dcDc);
		DrawCircleLine(m_FlagPointL,m_FlagPointR,5,&dcDc);
		Temp = m_FlagPointL;
		Temp2 = m_FlagPointR;
	}
	IsDrawWhatSub(headPoint4,tailPoint4,nDx,nDy);
}
void CTFigureDlg::OnMouseMove(UINT nFlags, CPoint point)  //����ƶ���Ϣ��Ӧ
{

	if (m_bNoDraw == TRUE)
	{
		//m_bNoDraw = FALSE;
		return;
	}
// 	if (point.x >1850 ||point.y>850 || point.x <40 || point.y<145) //���Ʋ���λ��
// 	{
// 		//this->Invalidate();
// 		m_bNoDraw = TRUE;		
// 		SetClassLong(this->GetSafeHwnd(),
// 			GCL_HCURSOR , 
// 			(LONG)LoadCursor(NULL , IDC_ARROW));
// 		this->Invalidate(1);
// 		return ;
// 	}
	else
	{
		m_bNoDraw = FALSE;
	}


	m_bNoDraw = FALSE;
	//Sm_DragGraphics = false; //�����϶�
	//�������λ��
#if DEBUGS:
	drawCordinate(point);
#endif

	if(m_flagSublineTracking == TRUE)
	{	
		//LONG temp = point.y;
		CClientDC dcSubline(this);
		int nOldMode= 0;
		//CPen pen(PS_DASH,1,RGB(0,0,0));
		//int nOldMode = dc->SetROP2(R2_NOT);
		//dcSubline.SelectObject(&pen);
		//DrawSubline(m_downPoint,&dcSubline,nOldMode);

		////Sleep(50);
		////nOldMode = dcSubline.SetROP2(R2_NOT);
		//DrawSubline(CPoint(point.x,point.y),&dcSubline,nOldMode);
		DrawSubline(m_downPoint,&dcSubline,nOldMode);
		DrawSubline(CPoint(point.x,point.y),&dcSubline,nOldMode);
		m_downPoint = point;
		//temp = point.y;
		//this->Invalidate(-1);
		//DrawSubline(point,&dcSubline);
		//DrawSubline(point,&dcSubline);
		//DrawSubline(point,&dcSubline);
	}
	/*******************/
	//�����϶�ͼ�εĲ�Ӱ
	if((m_bDragFlag == TRUE/* && / *m_bSizeAll ==true* /*/ ))
	{	
		//m_bDragFlag = FALSE; 
		// m_dragPoint
		//m_flagTracking = TRUE;
		int nDx = point.x - m_dragPoint.x;
		int nDy = point.y - m_dragPoint.y;
		//m_dragPointMove = point;
		//IsDrawWhat(m_headPoint4,m_tailPoint4 ,nDx ,nDy);
		//DrawWavy(m_FlagPointL,m_FlagPointR,5,&dcDc);
		/*	DrawWavy(m_tempPoint,m_FlagPointR,5,&dcDc);*/

		// 		m_FlagPointL.x = nDx + m_FlagPointL.x; 
		// 		m_FlagPointL.y = nDy + m_FlagPointL.y;
		// 		m_FlagPointR.x = nDx + m_FlagPointR.x;
		// 		m_FlagPointR.y = nDy + m_FlagPointR.y;     
		//m_tempPoint = m_FlagPointL;	
		if( m_iFallinWhere == WAVY )
		{

			DrawGhost(m_headPoint4,m_tailPoint4,nDx,nDy);
			// 			CClientDC dcDc(this);
			// 			IsDrawWhatAdd(m_headPoint4,m_tailPoint4,nDx,nDy);
			// 			for(int i=0 ;i<10;i++)
			// 			{
			// 				DrawWavy(m_FlagPointL,m_FlagPointR,5,&dcDc);
			// 				Sleep(2);
			// 				DrawWavy(m_FlagPointL,m_FlagPointR,5,&dcDc);
			// 				Sleep(1);
			// 			}
			// 			IsDrawWhatSub(m_headPoint4,m_tailPoint4,nDx,nDy);
		}
		if( m_iFallinWhere == LINE )
		{
			DrawGhost(m_headPoint,m_tailPoint,nDx,nDy);
		}
		if( m_iFallinWhere == ARROW )
		{
			DrawGhost(m_headPoint2,m_tailPoint2,nDx,nDy);
		}	
		if( m_iFallinWhere == TWOARROW )
		{
			DrawGhost(m_headPoint9,m_tailPoint9,nDx,nDy);
		}
		if( m_iFallinWhere == THREEARROW )
		{
			DrawGhost(m_headPoint10,m_tailPoint10,nDx,nDy);
		}
		if (m_iFallinWhere == TEN )
		{
			DrawGhost(m_headPoint3,m_tailPoint3,nDx,nDy);
		}
		if (m_iFallinWhere == TENTEN )
		{
			DrawGhost(m_headPoint7,m_tailPoint7,nDx,nDy);
		}
		if (m_iFallinWhere == TENTENTEN )
		{
			DrawGhost(m_headPoint8,m_tailPoint8,nDx,nDy);
		}
		if (m_iFallinWhere == T )
		{
			DrawGhost(m_headPoint6,m_tailPoint6,nDx,nDy);
		}
		if (m_iFallinWhere == TT )
		{
			DrawGhost(m_headPoint11,m_tailPoint11,nDx,nDy);
		}
		if (m_iFallinWhere == TTT )
		{
			DrawGhost(m_headPoint12,m_tailPoint12,nDx,nDy);
		}
		if (m_iFallinWhere == TTUPDOWN )
		{
			DrawGhost(m_headPoint13,m_tailPoint13,nDx,nDy);
		}
		if (m_iFallinWhere == NLINE )
		{
			DrawGhost(m_headPoint14,m_tailPoint14,nDx,nDy);
		}
		if (m_iFallinWhere == DASH )
		{
			DrawGhost(m_headPoint5,m_tailPoint5,nDx,nDy);
		}
		if (m_iFallinWhere == CIRCLELINE )
		{
			DrawGhost(m_headPoint16,m_tailPoint16,nDx,nDy);
		}

		// 		m_FlagPointL.x =  m_FlagPointL.x - nDx ; 
		// 		m_FlagPointL.y =   m_FlagPointL.y-nDy;
		// 		m_FlagPointR.x =   m_FlagPointR.x -nDx;
		// 		m_FlagPointR.y =  m_FlagPointR.y -nDy ;	

		//DrawWavy(m_FlagPointL,m_FlagPointR,5,&dcDc);
		// 			Sleep(30);
		// 			Invalidate(0);

	}
	if(m_bDrawLine == TRUE) 
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) //����Ԥ��  ǰ�����ʼ�հ���
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint[i],this->m_tailPoint[i]); 
			InvertLine(&dc,this->m_headPoint[i],point);
			m_tailPoint[i] = point; //��һ������Ĩ���ڶ�����
		}
	}
	if(m_bDrawText == TRUE) 
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) //����Ԥ��  ǰ�����ʼ�հ���
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPointText[m_nWord],this->m_tailPointText[m_nWord]); 
			InvertLine(&dc,this->m_headPointText[m_nWord],point);
			m_tailPointText[m_nWord] = point; //��һ������Ĩ���ڶ�����
		}
	}

	/***************/
	else if(m_bDrawCircle == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			//TODO:
			// 			CClientDC dc(this);
			// 			InvertCircle(&dc,this->m_headPoint1[i],this->m_tailPoint1[i]);  //���Ʒ�תԲ
			// 			InvertCircle(&dc,this->m_headPoint1[i],point);
			// 			m_tailPoint1[i] = point;
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
	else if(m_bDraw2arrow == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint9[i],this->m_tailPoint9[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint9[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint9[i] = point;
		}
	}
	else if(m_bDraw3arrow == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint10[i],this->m_tailPoint10[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint10[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint10[i] = point;
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
	else if(m_bDrawtententen == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint8[i],this->m_tailPoint8[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint8[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint8[i] = point;
		}
	}
	else if(m_bDrawtenten == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint7[i],this->m_tailPoint7[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint7[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint7[i] = point;
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
		//CTFigureDlg::OnMouseMoveDrawLine(point,m_headPoint4[i],m_tailPoint4[i]);
	}

	else if(m_bDrawDash == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint5[i],this->m_tailPoint5[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint5[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint5[i] = point;
		}
	}
	else if(m_bDrawTupdown == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint13[i],this->m_tailPoint13[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint13[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint13[i] = point;
		}
	}
	else if(m_bdrawNline == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint14[i],this->m_tailPoint14[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint14[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint14[i] = point;
		}
	}

	else if(m_bDrawO == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			//TODO:
			// 			InvertLine(&dc,this->m_headPoint15[i],this->m_tailPoint15[i]);  //���Ʒ�ת��
			// 			InvertLine(&dc,this->m_headPoint15[i],point);
			// 			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			// 			m_tailPoint15[i] = point;
		}
	}
	else if(m_bDrawCircleLine == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint16[i],this->m_tailPoint16[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint16[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint16[i] = point;
		}
	}
	else if(m_bDrawT == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint6[i],this->m_tailPoint6[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint6[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint6[i] = point;
		}
	}

	else if(m_bDrawTT == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint11[i],this->m_tailPoint11[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint11[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint11[i] = point;
		}
	}

	else if(m_bDraw3T == TRUE)
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if(m_flagTracking == TRUE && m_bTracking == TRUE) 
		{
			CClientDC dc(this);
			InvertLine(&dc,this->m_headPoint12[i],this->m_tailPoint12[i]);  //���Ʒ�ת��
			InvertLine(&dc,this->m_headPoint12[i],point);
			//DrawArrow( m_headPoint2[i], m_tailPoint2[i],45.0,7);
			m_tailPoint12[i] = point;
		}
	}
	//�ж�����Ƿ�������ͼ����
	//if(m_bForbidSizeAll == TRUE)
	//{
	if(m_pPointFourRight[1].x != 0)
	{
		//�ж��Ƿ�������������
		for(int j=0;j<4;j++)
		{	 
			if(m_bTracking == FALSE&& m_bForbidSizeAll == FALSE)  //��������ƶ�ʱ��,�ǰ���״̬
			{	
				//���������ten��
				if(((m_pPointFourRight[j].x-10 < point.x && m_pPointFourRight[j].x + 10 > point.x)
					&&(m_pPointFourRight[j].y-10 < point.y && m_pPointFourRight[j].y+10 > point.y
					/*&&m_bForbidSizeAll == FALSE*/)))
				{
					//��� ������ten�� �����
					m_iFallinWhere = FOURLINE;
					//�������
					SetClassLong(this->GetSafeHwnd(),
						GCL_HCURSOR , 
						(LONG)LoadCursor(NULL , IDC_SIZEALL));//�ķ����ͷ
					//���ҵ�������� m_bSizeAll
					m_bSizeAll = TRUE;
					/*m_bForbidSizeAll = TRUE;*/
					m_iDragFlag = j;//��¼�±�

					break;     //���j++,��ʱ�Ѿ���λ��m_headpoint[j]
				}
				else
				{	
					//m_iFallinWhere = NOTHING;
					//�������
					SetClassLong(this->GetSafeHwnd(),
						GCL_HCURSOR , 
						(LONG)LoadCursor(NULL , IDC_ARROW));
					m_bSizeAll = FALSE;
					//m_bForbidSizeAll == FALSE;
				}
			}
		}
	}

	if(m_pPointSixRight[1].x != 0)
	{
		//�ж��Ƿ�������������
		for(int j=0;j<6;j++)
		{	 
			if(m_bTracking == FALSE&& m_bForbidSizeAll == FALSE)  //��������ƶ�ʱ��,�ǰ���״̬
			{	
				//���������ten��
				if(((m_pPointSixRight[j].x-10 < point.x && m_pPointSixRight[j].x + 10 > point.x)
					&&(m_pPointSixRight[j].y-10 < point.y && m_pPointSixRight[j].y+10 > point.y
					/*&&m_bForbidSizeAll == FALSE*/)))
				{
					//��� ������ten�� �����
					m_iFallinWhere = SIXLINE;
					//�������
					SetClassLong(this->GetSafeHwnd(),
						GCL_HCURSOR , 
						(LONG)LoadCursor(NULL , IDC_SIZEALL));//�ķ����ͷ
					//���ҵ�������� m_bSizeAll
					m_bSizeAll = TRUE;
					/*m_bForbidSizeAll = TRUE;*/
					m_iDragFlag = j;//��¼�±�

					break;     //���j++,��ʱ�Ѿ���λ��m_headpoint[j]
				}
				else
				{	
					//m_iFallinWhere = NOTHING;
					//�������
					SetClassLong(this->GetSafeHwnd(),
						GCL_HCURSOR , 
						(LONG)LoadCursor(NULL , IDC_ARROW));
					m_bSizeAll = FALSE;
					//m_bForbidSizeAll == FALSE;
				}
			}
		}
	}
	if(m_pPointEightLeft[1].x != 0)
	{
		//�ж��Ƿ�������������
		for(int j=0;j<8;j++)
		{	 
			if(m_bTracking == FALSE&& m_bForbidSizeAll == FALSE)  //��������ƶ�ʱ��,�ǰ���״̬
			{	
				//���������ten��
				if(((m_pPointEightRight[j].x-10 < point.x && m_pPointEightRight[j].x + 10 > point.x)
					&&(m_pPointEightRight[j].y-10 < point.y && m_pPointEightRight[j].y+10 > point.y
					/*&&m_bForbidSizeAll == FALSE*/)))
				{
					//��� ������ten�� �����
					m_iFallinWhere = EIGHTLINE;
					//�������
					SetClassLong(this->GetSafeHwnd(),
						GCL_HCURSOR , 
						(LONG)LoadCursor(NULL , IDC_SIZEALL));//�ķ����ͷ
					//���ҵ�������� m_bSizeAll
					m_bSizeAll = TRUE;
					/*m_bForbidSizeAll = TRUE;*/
					m_iDragFlag = j;//��¼�±�

					break;     //���j++,��ʱ�Ѿ���λ��m_headpoint[j]
				}
				else
				{	
					//m_iFallinWhere = NOTHING;
					//�������
					SetClassLong(this->GetSafeHwnd(),
						GCL_HCURSOR , 
						(LONG)LoadCursor(NULL , IDC_ARROW));
					m_bSizeAll = FALSE;
					//m_bForbidSizeAll == FALSE;
				}
			}
		}
	}
	if(m_DragGraphics == TRUE)
	{
		for(int j=0;j<i;j++)
		{	 
			if(m_bTracking == FALSE && m_bForbidSizeAll == FALSE)  //��������ƶ�ʱ��,�ǰ���״̬
			{	
				//LINE
				if(IsinRange(point,m_headPoint[j],m_tailPoint[j],iRange))
				{
					m_FlagPointL = m_headPoint[j];
					m_FlagPointR = m_tailPoint[j];
					IsinWhere(LINE,j);
					break;
				}
				//���������ten��
				if(IsinRange(point,m_headPoint3[j],m_tailPoint3[j],iRange))
				{
					m_FlagPointL = m_headPoint3[j];
					m_FlagPointR = m_tailPoint3[j];
					IsinWhere(TEN,j);
					break;
				}
				//���������wavy��
				else if( IsinRange(point,m_headPoint4[j],m_tailPoint4[j],iRange) )
				{
					// 				m_iFallinWhere = WAVY;
					// 				//�������
					// 				SetClassLong(this->GetSafeHwnd(),
					// 					GCL_HCURSOR , 
					// 					(LONG)LoadCursor(NULL , IDC_SIZEALL));//�ķ����ͷ
					// 				//���ҵ�������� m_bSizeAll
					// 				m_bSizeAll = TRUE;
					// 				
					// 				/*m_bForbidSizeAll = TRUE;*/
					// 				m_iDragFlag = j;//��¼�±�
					// 				//DrawWavy(m_headPoint4[j],point,8);
					m_FlagPointL = m_headPoint4[j];
					m_FlagPointR = m_tailPoint4[j];
					IsinWhere(WAVY,j);
					break;     //���j++,��ʱ�Ѿ���λ��m_headpoint[j]
				}

				//���������arrow��
				else if( IsinRange(point,m_headPoint2[j],m_tailPoint2[j],iRange))
				{
					m_FlagPointL = m_headPoint2[j];
					m_FlagPointR = m_tailPoint2[j];
					IsinWhere(ARROW,j);
					break;     //���j++,��ʱ�Ѿ���λ��m_headpoint[j]
				}

				//���������2arrow��
				else if(IsinRange(point,m_headPoint9[j],m_tailPoint9[j],iRange))
				{
					m_FlagPointL = m_headPoint9[j];
					m_FlagPointR = m_tailPoint9[j];
					IsinWhere(TWOARROW,j);
					break;
				}

				//���������3arrow��
				else if(IsinRange(point,m_headPoint10[j],m_tailPoint10[j],iRange))
				{
					m_FlagPointL = m_headPoint10[j];
					m_FlagPointR = m_tailPoint10[j];
					IsinWhere(THREEARROW,j);
					break;
				}

				//���������tenten��
				else if(IsinRange(point,m_headPoint7[j],m_tailPoint7[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint7[j];
					m_FlagPointR = m_tailPoint7[j];
					IsinWhere(TENTEN,j);
					break;
				}

				//���������tententen��
				else if(IsinRange(point,m_headPoint8[j],m_tailPoint8[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint8[j];
					m_FlagPointR = m_tailPoint8[j];
					IsinWhere(TENTENTEN,j);
					break;
				}


				//���������DASH��
				else if(IsinRange(point,m_headPoint5[j],m_tailPoint5[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint5[j];
					m_FlagPointR = m_tailPoint5[j];
					IsinWhere(DASH,j);
					break;
				}


				//���������TTUPDOWN��
				else if(IsinRange(point,m_headPoint13[j],m_tailPoint13[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint13[j];
					m_FlagPointR = m_tailPoint13[j];
					IsinWhere(TTUPDOWN,j);
					break;
				}


				//���������NLINE��
				else if(IsinRange(point,m_headPoint14[j],m_tailPoint14[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint14[j];
					m_FlagPointR = m_tailPoint14[j];
					IsinWhere(NLINE,j);
					break;
				}

				//���������O��
				else if(IsinRange(point,m_headPoint15[j],m_tailPoint15[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint15[j];
					m_FlagPointR = m_tailPoint15[j];
					IsinWhere(OOO,j);
					break;
				}
				//���������CIRCLELINE��
				else if(IsinRange(point,m_headPoint16[j],m_tailPoint16[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint16[j];
					m_FlagPointR = m_tailPoint16[j];
					IsinWhere(CIRCLELINE ,j);
					break;
				}
				//T
				else if(IsinRange(point,m_headPoint6[j],m_tailPoint6[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint6[j];
					m_FlagPointR = m_tailPoint6[j];
					IsinWhere(T,j);
					break;
				}

				//TT
				else if(IsinRange(point,m_headPoint11[j],m_tailPoint11[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint11[j];
					m_FlagPointR = m_tailPoint11[j];
					IsinWhere(TT,j);
					break;
				}

				//TTT
				else if(IsinRange(point,m_headPoint12[j],m_tailPoint12[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint12[j];
					m_FlagPointR = m_tailPoint12[j];
					IsinWhere(TTT,j);
					break;
				}
				//CIRCLE
				else if(IsinRange(point,m_headPoint1[j],m_tailPoint1[j],iRange))
				{
					//�������
					m_FlagPointL = m_headPoint1[j];
					m_FlagPointR = m_tailPoint1[j];
					IsinWhere(CIRCLE,j);
					break;
				}
				else
				{
					//�������
					//m_iFallinWhere = NOTHING;
					SetClassLong(this->GetSafeHwnd(),
						GCL_HCURSOR , 
						(LONG)LoadCursor(NULL , IDC_ARROW));
					m_bSizeAll = FALSE;
					//m_bForbidSizeAll == FALSE;
				}
			}
		}
	}
	//}
	//else
	//{
	//	m_bForbidSizeAll = TRUE;
	//}
	//CDialogEx::OnMouseMove(nFlags, point);
	// 	if( m_iFallinWhere == WAVY )
	// 		if(m_bTracking == FALSE &&m_flagTracking == FALSE)
	// 	{	
	// 		m_bDragFlag = FALSE;
	// 		m_flagTracking = TRUE;
	// 		int nDx = point.x - m_dragPoint.x;
	// 		int nDy = point.y - m_dragPoint.y;
	// 		
	// 		{	
	// 			IsDrawWhat(m_headPoint4,m_tailPoint4 ,nDx ,nDy);
	// 			DrawWavy(m_headPoint4[m_iDragFlag],m_tailPoint4[m_iDragFlag],5);
	// 		}
	// 	}

}


//���ƶ�׼������
void CTFigureDlg::DrawSubline(CPoint point,CDC* dc,int nOldMode)
{	
	//CPen pen(PS_DASH,1,RGB(0,0,0));
	//int nOldMode = dc->SetROP2(R2_NOT);
	//dcSubline.SelectObject(&pen);
	//CPen pen(PS_DASH,1,RGB(0,0,0));
	//dc->SelectObject(&pen);
	nOldMode = dc->SetROP2(R2_NOT);
	//pDC->MoveTo(x);
	//pDC->LineTo(y);
	//dc->SetROP2(nOldMode);
	//CPen pen(PS_DASH,1,RGB(0,0,0));
	//dc->SelectObject(&pen);
	dc->MoveTo(point.x,point.y - 900);
	dc->LineTo(point.x,point.y + 900);
	dc->MoveTo(point.x - 2000,point.y);
	dc->LineTo(point.x + 2000,point.y);
	//dc->MoveTo(0,0);
	//dc->LineTo(80,80);
	//
	//dc->LineTo(CPoint((point.x,point.y + 500)));
	dc->SetROP2(nOldMode);	

}

void CTFigureDlg::DrawInvertSubline( CPoint point, CClientDC* dc, int nOldMode)
{
	//CPen pen(PS_DASH,1,RGB(0,0,0));
	//int nOldMode = dc->SetROP2(R2_NOT);
	//dcSubline.SelectObject(&pen);
	nOldMode = dc->SetROP2(R2_NOT);
	//pDC->MoveTo(x);
	//pDC->LineTo(y);
	//dc->SetROP2(nOldMode);
	//CPen pen(PS_DASH,1,RGB(0,0,0));
	//dc->SelectObject(&pen);
	dc->MoveTo(point.x,point.y - 501);
	dc->LineTo(point.x,point.y + 501);
	dc->MoveTo(point.x - 1001,point.y);
	dc->LineTo(point.x + 1001,point.y);
	//dc->MoveTo(0,0);
	//dc->LineTo(80,80);
	//
	//dc->LineTo(CPoint((point.x,point.y + 500)));
	dc->SetROP2(nOldMode);	
}

void CTFigureDlg::OnLButtonDown(UINT nFlags, CPoint point) //����������
{

	if (point.x >1850 ||point.y>850 || point.x <40 || point.y<145) //���Ʋ���λ��
	{
		//this->Invalidate();
		m_bNoDraw = TRUE;
		return ;
	}
	m_bNoDraw = FALSE;
	// 	CRectTracker  temp;
	// 	temp.m_rect.SetRect(0,0,50,50);
	// 	temp.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;
	// 
	// 	//TrackRubberBand����ֱ�������������ʱ��Ż᷵�أ�������������λ��Ҳ��¼������
	// 	//�ú��������У������������ƶ���Ϣ
	// 	temp.TrackRubberBand(this,point,TRUE);
	// 	//ʹ�þ���Ϊ��ȷ�����꣬������ָ�������
	// 	temp.m_rect.NormalizeRect();
	// 	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// 	//���������ʽ
	m_bForbidSizeAll = TRUE;
	SetClassLong(this->GetSafeHwnd(),
		GCL_HCURSOR , 
		(LONG)LoadCursor(NULL , IDC_CROSS));
	//������� �������ͷ״̬,Ϊʮ��״̬
	//if(m_bSizeAll == FALSE)
	{
		////���ƶ�׼������
		//DrawSubline(point);
		//���ƶ�׼������״̬��ǿ���
		m_flagSublineTracking = TRUE;
		m_downPoint = point;
		CClientDC dcSubline(this);
		DrawSubline(m_downPoint,&dcSubline,0);
	}
	//AfxMessageBox(_T("����"));
	//ѡ��ֱ��
	if(m_bDrawLine == TRUE&&m_bSizeAll == FALSE)
	{
		m_bTracking = TRUE;              //��λ׷��
		//drawCordinate(point);
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint[i] = point;
		m_tailPoint[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	//����
	if(m_bDrawText == TRUE&&m_bSizeAll == FALSE)
	{
		m_bTracking = TRUE;              //��λ׷��
		//drawCordinate(point);
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPointText[m_nWord] = point;
		m_tailPointText[m_nWord] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}


	/****************************/
	if(m_bDrawCircle == TRUE&&m_bSizeAll == FALSE)  //ѡ����ʵ��Բ
	{
		if(m_bDrawCircle == TRUE)
		{
			m_bTracking = TRUE;  
			//drawCordinate(point);
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
			//drawCordinate(point);
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint2[i] = point;
			m_tailPoint2[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}
	if(m_bDraw2arrow == TRUE&&m_bSizeAll == FALSE)  //ѡ���˼�ͷ
	{
		if(m_bDraw2arrow == TRUE)
		{
			m_bTracking = TRUE;  
			//drawCordinate(point);
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint9[i] = point;
			m_tailPoint9[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}
	if(m_bDraw3arrow == TRUE&&m_bSizeAll == FALSE)  //ѡ���˼�ͷ
	{
		if(m_bDraw3arrow == TRUE)
		{
			m_bTracking = TRUE;  
			//drawCordinate(point);
			//AfxMessageBox(str);
			m_flagTracking = TRUE;
			//��¼���λ��
			m_headPoint10[i] = point;
			m_tailPoint10[i] = point;
			CDialogEx::OnLButtonDown(nFlags, point);
		}
	}
	if(m_bDrawTen == TRUE &&m_bSizeAll == FALSE)  //m_bDrawTen
	{
		m_bTracking = TRUE;  
		//drawCordinate(point);
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint3[i] = point;
		m_tailPoint3[i] = point;
		//this->Invalidate(0);
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bDrawtententen == TRUE &&m_bSizeAll == FALSE)  //m_bDrawTen
	{
		m_bTracking = TRUE;  
		//drawCordinate(point);
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint8[i] = point;
		m_tailPoint8[i] = point;
		//this->Invalidate(0);
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bDrawtenten == TRUE &&m_bSizeAll == FALSE)  //m_bDrawTenten
	{
		m_bTracking = TRUE;  
		//drawCordinate(point);
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint7[i] = point;
		m_tailPoint7[i] = point;
		//this->Invalidate(0);
		CDialogEx::OnLButtonDown(nFlags, point);
	}

	///////////////////////////TODO:DOWNʱ �����m_tailPoint4[i]���λ�ã�
	////�����ʱ�������ͷ״̬�����ܸı���λ��
	if(m_bDrawWavy == TRUE && m_bSizeAll == FALSE)  //m_bDrawWavy
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint4[i] = point;
		m_tailPoint4[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bDrawDash == TRUE && m_bSizeAll == FALSE)  //m_bDrawDash
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint5[i] = point;
		m_tailPoint5[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}

	if(m_bDrawTupdown == TRUE && m_bSizeAll == FALSE)  //m_bDrawDash
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint13[i] = point;
		m_tailPoint13[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bdrawNline == TRUE && m_bSizeAll == FALSE)  //m_bDrawDash
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint14[i] = point;
		m_tailPoint14[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bDrawO == TRUE && m_bSizeAll == FALSE)  //m_bDrawDash
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint15[i] = point;
		m_tailPoint15[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bDrawCircleLine == TRUE && m_bSizeAll == FALSE)  //m_bDrawCircleLine
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint16[i] = point;
		m_tailPoint16[i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	//ѡ����T
	if(m_bDrawT == TRUE && m_bSizeAll == FALSE) 
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint6[i] = point;
		m_tailPoint6[i] = point;
		//m_arrHeadPoint[6][i] = point;
		//m_arrTailPoint[6][i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bDrawTT == TRUE && m_bSizeAll == FALSE) 
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint11[i] = point;
		m_tailPoint11[i] = point;
		//m_arrHeadPoint[6][i] = point;
		//m_arrTailPoint[6][i] = point;
		CDialogEx::OnLButtonDown(nFlags, point);
	}
	if(m_bDraw3T == TRUE && m_bSizeAll == FALSE) 
	{
		m_bTracking = TRUE;  
		//drawCordinate(point); 
		//AfxMessageBox(str);
		m_flagTracking = TRUE;
		//��¼���λ��
		m_headPoint12[i] = point;
		m_tailPoint12[i] = point;
		//m_arrHeadPoint[6][i] = point;
		//m_arrTailPoint[6][i] = point;
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
	dc.Rectangle(CRect(2,86-66,70,106-66));
	dc.DrawText(str,CRect(2,86-66,70,106-66),DT_CENTER);   //2,86  64,106
}

//չʾ�ļ�λ��
void CTFigureDlg::drawDispalyFilePath(CString str)
{
	CClientDC dc(this);
	//CBrush brush((255,255,255));
	//dc.FillRect(CRect(2,86,64,106),&brush);
	dc.SelectStockObject(LTGRAY_BRUSH );
	str.GetLength();
	//dc.Rectangle(CRect(20,0,20+12*str.GetLength(),20));
	//dc.DrawText(str,CRect(0,0,0+8*str.GetLength(),20),DT_CENTER);   //2,86  64,106
	dc.TextOutW( 0,0,str);
}

void CTFigureDlg::OnLButtonUp(UINT nFlags, CPoint point)   //����ɿ�
{	
	if (m_bNoDraw == TRUE)
	{
		m_bNoDraw = FALSE;
		return;
	}
	m_bNoDraw = FALSE;
	//
	m_bSizeAll = false;
	//m_bDragFlag = false;
	m_bForbidSizeAll = FALSE;
	CClientDC dcSubline(this);
	DrawSubline(m_downPoint,&dcSubline,0);

	m_flagSublineTracking = FALSE;
	//���������ʽ
	SetClassLong(this->GetSafeHwnd(),
		GCL_HCURSOR , 
		(LONG)LoadCursor(NULL , IDC_ARROW));
	//UpdateData();
	//this->Invalidate(0);
	//TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bDrawLine == TRUE)
	{
		m_bTracking = FALSE;              //ֹͣ׷��
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint[i] = point;
			if (m_tailPoint[i]!=m_headPoint[i])
			{
				//���������
				//CRect rect(m_headPoint[i].x,m_headPoint[i].y,m_tailPoint[i].x,m_tailPoint[i].y);
				//ShortTextInput(rect);
				++i;
				//��ͼ �޸ı��
				this->m_bChangeFlag = TRUE;
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
	}

	else if(m_bDrawCircle == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint1[i] = point;
			/***********************************/
			//TODO:
			m_headPoint1[i] = point;
			++i;//
			if (this->i > 1) //�Զ�����
			{
				for (int n=0;n<i;n++)
				{
					if( abs(m_tailPoint1[i-1].y - m_tailPoint1[n].y) < 10 )
					{
						m_tailPoint1[i-1].y = m_tailPoint1[n].y ;
						m_headPoint1[i-1].y = m_headPoint1[n].y ;
					}
				}
			}
			this->m_bChangeFlag = TRUE;
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
			if (m_tailPoint2[i]!=m_headPoint2[i])
			{
				this->m_bChangeFlag = TRUE;
				++i;
				this->Invalidate(0);
			}

		}
	}

	else if(m_bDraw2arrow == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint9[i] = point;
			if (m_tailPoint9[i]!=m_headPoint9[i])
			{
				this->m_bChangeFlag = TRUE;
				++i;
				this->Invalidate(0);
			}
		}
	}
	else if(m_bDraw3arrow == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint10[i] = point;
			this->m_bChangeFlag = TRUE;
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
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}
	//�ı�
	else if(m_bDrawText == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPointText[m_nWord] = point;
			if(abs(m_tailPointText[m_nWord].x-m_headPointText[m_nWord].x)<150)
			{
				m_tailPointText[m_nWord].x = m_headPointText[m_nWord].x+150;
			}
			if(abs(m_tailPointText[m_nWord].y-m_headPointText[m_nWord].y)<50)
			{
				m_tailPointText[m_nWord].y = m_headPointText[m_nWord].y+50;
			}
			if (m_tailPointText[m_nWord] !=m_headPointText[m_nWord]&& m_headPointText[m_nWord].x!=0)
			{
				this->m_bChangeFlag = TRUE;
				m_vecEdit.push_back(LongTextInput \
					(CRect(m_headPointText[m_nWord],m_tailPointText[m_nWord])));
				m_vecEdit.back()->ShowWindow(true);
				++m_nWord;
			}
			// 			if (m_tailPointText[m_nWord-1] ==m_headPointText[m_nWord-1] )
			// 			{
			// 				this->m_bChangeFlag = FALSE;
			// 				//m_vecEdit.pop_back();
			// 				--m_nWord;
			// 			}
			this->Invalidate(0);
		}
	}

	else if(m_bDrawtententen == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint8[i] = point;
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}
	else if(m_bDrawtenten == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint7[i] = point;
			this->m_bChangeFlag = TRUE;
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
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}
	else if(m_bDrawDash == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint5[i] = point;
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}
	else if(m_bDrawTupdown == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint13[i] = point;
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}

	else if(m_bdrawNline == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint14[i] = point;
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}
	else if(m_bDrawO == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			{	
				m_tailPoint15[i] = point;
				m_headPoint15[i] = point;
				++i;//
				if (this->i > 1) //�Զ�����
				{
					for (int n=0;n<i;n++)
					{
						if( abs(m_tailPoint15[i-1].y - m_tailPoint15[n].y) < 10 )
						{
							m_tailPoint15[i-1].y = m_tailPoint15[n].y ;
							m_headPoint15[i-1].y = m_headPoint15[n].y ;
						}
					}
				}
				this->m_bChangeFlag = TRUE;
				this->Invalidate(0);

			}
		}
	}

	else if(m_bDrawT == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint6[i] = point;
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}
	else if(m_bDrawCircleLine == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint16[i] = point;
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}

	else if(m_bDrawTT == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint11[i] = point;
			this->m_bChangeFlag = TRUE;
			++i;
			this->Invalidate(0);
		}
	}
	else if(m_bDraw3T == TRUE)
	{
		m_bTracking = FALSE;
		//CDialogEx::OnLButtonUp(nFlags, point);
		if(m_flagTracking == TRUE)
		{	
			m_tailPoint12[i] = point;
			this->m_bChangeFlag = TRUE;
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
		if( m_iFallinWhere == WAVY )
		{	
			IsDrawWhat(m_headPoint4,m_tailPoint4 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == TEN)
		{
			IsDrawWhat(m_headPoint3,m_tailPoint3 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == LINE)
		{
			IsDrawWhat(m_headPoint,m_tailPoint ,nDx ,nDy);
		}
		else if(m_iFallinWhere == FOURLINE)
		{
			//m_pPointFourRight[m_iDragFlag].x = m_pPointFourRight[m_iDragFlag].x + nDx;
			//�����϶���Χ
			m_pPointFourRight[m_iDragFlag].y = m_pPointFourRight[m_iDragFlag].y + nDy;
			//m_pPointFourLeft[m_iDragFlag].x = m_pPointFourLeft[m_iDragFlag].x + nDx;
			m_pPointFourLeft[m_iDragFlag].y = m_pPointFourLeft[m_iDragFlag].y + nDy;
			//��֤�����߶ε�˳��һ��
			if( m_iDragFlag<3 )
			{
				if (m_pPointFourRight[m_iDragFlag].y<300 ||m_pPointFourRight[m_iDragFlag].y>850 || \
					m_pPointFourRight[m_iDragFlag].y >m_pPointFourRight[m_iDragFlag+1].y-13 )
				{
					m_pPointFourRight[m_iDragFlag].y = m_pPointFourRight[m_iDragFlag].y - nDy;
					//m_pPointFourLeft[m_iDragFlag].x = m_pPointFourLeft[m_iDragFlag].x + nDx;
					m_pPointFourLeft[m_iDragFlag].y = m_pPointFourLeft[m_iDragFlag].y - nDy;
				}

			}
			if( m_iDragFlag>0 )
			{
				if (m_pPointFourRight[m_iDragFlag].y<300 ||m_pPointFourRight[m_iDragFlag].y>850 || \
					m_pPointFourRight[m_iDragFlag].y < m_pPointFourRight[m_iDragFlag-1].y+13 )
				{
					m_pPointFourRight[m_iDragFlag].y = m_pPointFourRight[m_iDragFlag].y - nDy;
					//m_pPointFourLeft[m_iDragFlag].x = m_pPointFourLeft[m_iDragFlag].x + nDx;
					m_pPointFourLeft[m_iDragFlag].y = m_pPointFourLeft[m_iDragFlag].y - nDy;
				}

			}

		}
		else if(m_iFallinWhere == SIXLINE)
		{
			//m_pPointSixRight[m_iDragFlag].x = m_pPointSixRight[m_iDragFlag].x + nDx;
			m_pPointSixRight[m_iDragFlag].y = m_pPointSixRight[m_iDragFlag].y + nDy;
			//m_pPointSixLeft[m_iDragFlag].x = m_pPointSixLeft[m_iDragFlag].x + nDx;
			m_pPointSixLeft[m_iDragFlag].y = m_pPointSixLeft[m_iDragFlag].y + nDy;
			if( m_iDragFlag<5 )
			{
				if (m_pPointSixRight[m_iDragFlag].y<300 ||m_pPointSixRight[m_iDragFlag].y>850 || \
					m_pPointSixRight[m_iDragFlag].y >m_pPointSixRight[m_iDragFlag+1].y-13 )
				{
					m_pPointSixRight[m_iDragFlag].y = m_pPointSixRight[m_iDragFlag].y - nDy;
					//m_pPointFourLeft[m_iDragFlag].x = m_pPointFourLeft[m_iDragFlag].x + nDx;
					m_pPointSixLeft[m_iDragFlag].y = m_pPointSixLeft[m_iDragFlag].y - nDy;
				}

			}
			if( m_iDragFlag>0 )
			{
				if (m_pPointSixRight[m_iDragFlag].y<300 ||m_pPointSixRight[m_iDragFlag].y>850 || \
					m_pPointSixRight[m_iDragFlag].y < m_pPointSixRight[m_iDragFlag-1].y +13)
				{
					m_pPointSixRight[m_iDragFlag].y = m_pPointSixRight[m_iDragFlag].y - nDy;
					//m_pPointFourLeft[m_iDragFlag].x = m_pPointFourLeft[m_iDragFlag].x + nDx;
					m_pPointSixLeft[m_iDragFlag].y = m_pPointSixLeft[m_iDragFlag].y - nDy;
				}

			}
		}
		else if(m_iFallinWhere == EIGHTLINE)
		{
			//m_pPointEightRight[m_iDragFlag].x = m_pPointEightRight[m_iDragFlag].x + nDx;
			m_pPointEightRight[m_iDragFlag].y = m_pPointEightRight[m_iDragFlag].y + nDy;
			//m_pPointEightLeft[m_iDragFlag].x = m_pPointEightLeft[m_iDragFlag].x + nDx;
			m_pPointEightLeft[m_iDragFlag].y = m_pPointEightLeft[m_iDragFlag].y + nDy;
			if( m_iDragFlag<7 )
			{
				if (m_pPointEightRight[m_iDragFlag].y<300 ||m_pPointEightRight[m_iDragFlag].y>850 || \
					m_pPointEightRight[m_iDragFlag].y >m_pPointEightRight[m_iDragFlag+1].y-13 )
				{
					m_pPointEightRight[m_iDragFlag].y = m_pPointEightRight[m_iDragFlag].y - nDy;
					//m_pPointFourLeft[m_iDragFlag].x = m_pPointFourLeft[m_iDragFlag].x + nDx;
					m_pPointEightLeft[m_iDragFlag].y = m_pPointEightLeft[m_iDragFlag].y - nDy;
				}

			}
			if( m_iDragFlag>0 )
			{
				if (m_pPointEightRight[m_iDragFlag].y<300 ||m_pPointEightRight[m_iDragFlag].y>850 || \
					m_pPointEightRight[m_iDragFlag].y < m_pPointEightRight[m_iDragFlag-1].y+13 )
				{
					m_pPointEightRight[m_iDragFlag].y = m_pPointEightRight[m_iDragFlag].y - nDy;
					//m_pPointFourLeft[m_iDragFlag].x = m_pPointFourLeft[m_iDragFlag].x + nDx;
					m_pPointEightLeft[m_iDragFlag].y = m_pPointEightLeft[m_iDragFlag].y - nDy;
				}

			}
		}
		else if(m_iFallinWhere == TENTENTEN)
		{
			IsDrawWhat(m_headPoint8,m_tailPoint8 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == ARROW)
		{
			IsDrawWhat(m_headPoint2,m_tailPoint2 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == TWOARROW)
		{
			IsDrawWhat(m_headPoint9,m_tailPoint9,nDx ,nDy);
		}
		else if(m_iFallinWhere == THREEARROW)
		{
			IsDrawWhat(m_headPoint10,m_tailPoint10 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == DASH)
		{
			IsDrawWhat(m_headPoint5,m_tailPoint5 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == TTUPDOWN)
		{
			IsDrawWhat(m_headPoint13,m_tailPoint13 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == NLINE)
		{
			IsDrawWhat(m_headPoint14,m_tailPoint14 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == OOO)
		{
			IsDrawWhatCircle(m_headPoint15,m_tailPoint15 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == CIRCLELINE)
		{
			IsDrawWhat(m_headPoint16,m_tailPoint16 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == CIRCLE)
		{
			IsDrawWhatCircle(m_headPoint1,m_tailPoint1 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == T)
		{
			IsDrawWhat(m_headPoint6,m_tailPoint6 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == TENTEN)
		{
			IsDrawWhat(m_headPoint7,m_tailPoint7 ,nDx ,nDy);
		}
		else if(m_iFallinWhere == TT)
		{
			IsDrawWhat(m_headPoint11,m_tailPoint11,nDx ,nDy);
		}
		else if(m_iFallinWhere == TTT)
		{
			IsDrawWhat(m_headPoint12,m_tailPoint12 ,nDx ,nDy);
		}

		//if(m_headPoint4[m_iDragFlag+1]==m_tailPoint4[m_iDragFlag+1])
		//{m_headPoint4[m_iDragFlag+1].x = 0;
		//m_headPoint4[m_iDragFlag+1].y = 0;
		//m_tailPoint4[m_iDragFlag+1].x = 0;
		//m_tailPoint4[m_iDragFlag+1].y = 0;
		//}
		this->Invalidate(0);  //ȫ��ˢ�£��������� 
		//AfxMessageBox(_T("test"));
	}
}

//���ˣ�ɾ����λ
void CTFigureDlg::DeleteDataPoint()
{	
	for (int j=0; j<sizeof(m_arrHeadPoint)/sizeof(CPoint*)-1;j++)
	{
		this->m_arrHeadPoint[j][i].x = 0;
		this->m_arrHeadPoint[j][i].y = 0;
		this->m_arrTailPoint[j][i].x = 0;
		this->m_arrTailPoint[j][i].y = 0;
	}
	//this->m_headPoint10[i].x = 0;
	//this->m_headPoint10[i].y = 0;
	//this->m_tailPoint10[i].x = 0;
	//this->m_tailPoint10[i].y = 0;
	//this->m_tailPoint9[i].x = 0;
	//this->m_tailPoint9[i].y = 0;
	//this->m_headPoint9[i].x = 0;
	//this->m_headPoint9[i].y = 0;
	//this->m_headPoint8[i].x = 0;
	//this->m_headPoint8[i].y = 0;
	//this->m_tailPoint8[i].x = 0;
	//this->m_tailPoint8[i].y = 0;
	//this->m_tailPoint7[i].x = 0;
	//this->m_tailPoint7[i].y = 0;
	//this->m_headPoint7[i].x = 0;
	//this->m_headPoint7[i].y = 0;
	//this->m_headPoint6[i].x = 0;
	//this->m_headPoint6[i].y = 0;
	//this->m_tailPoint6[i].x = 0;
	//this->m_tailPoint6[i].y = 0;
	//this->m_headPoint5[i].x = 0;
	//this->m_headPoint5[i].y = 0;
	//this->m_tailPoint5[i].x = 0;
	//this->m_tailPoint5[i].y = 0;
	//this->m_headPoint4[i].x = 0;
	//this->m_headPoint4[i].y = 0;
	//this->m_tailPoint4[i].x = 0;
	//this->m_tailPoint4[i].y = 0;
	//this->m_headPoint3[i].x = 0;
	//this->m_headPoint3[i].y = 0;
	//this->m_tailPoint3[i].x = 0;
	//this->m_tailPoint3[i].y = 0;
	//this->m_headPoint2[i].x = 0;
	//this->m_headPoint2[i].y = 0;
	//this->m_tailPoint2[i].x = 0;
	//this->m_tailPoint2[i].y = 0;

	//this->m_headPoint1[i].x = 0;
	//this->m_headPoint1[i].y = 0;
	//this->m_tailPoint1[i].x = 0;
	//this->m_tailPoint1[i].y = 0;

	//this->m_headPoint[i].x = 0;
	//this->m_headPoint[i].y = 0;
	//this->m_tailPoint[i].x = 0;
	//this->m_tailPoint[i].y = 0;
}	
void CTFigureDlg::OnBnClickedButton3()    //����
{
	// 	if (m_bDrawText == TRUE && !m_vecEdit.empty())
	// 	{
	// 		delete m_vecEdit.back();
	// 		m_vecEdit.pop_back();
	// 		m_nWord--;
	// 		this->Invalidate(0);  
	// 		return ;
	// 	}

	if(i==0)
	{ 
		//m_nWord = 0;
		//m_vecEdit.resize(0);
		AfxMessageBox(_T("�޿ɳ���ͼ��"));
		this->Invalidate(0);    //��������Ϊ1��ȫ��ˢ��
	}
	else
	{
		i--;
		// 		if(m_bDrawLine == TRUE) 
		// 		{
		// 			delete vecEdit.back();
		// 			vecEdit.pop_back();
		// 		}
		this->m_bChangeFlag = TRUE;
		DeleteDataPoint();
		this->Invalidate(0);     
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 	if(m_bDrawLine == TRUE)
	// 	{
	// 		if(i==0)
	// 		{
	// 			AfxMessageBox(_T("����������"));
	// 			this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
	// 		}
	// 		else
	// 		{
	// 			//i--;
	// 			//DeleteDataPoint();
	// 			delete vecEdit.back();
	// 			vecEdit.pop_back();
	// 			this->Invalidate(1);
	// 
	// 		}
	// 	}
	///*******************/  //ʵ��Բ
	//if(m_bDrawCircle == TRUE)
	//{
	//	if(i==0)
	//	{
	//		AfxMessageBox(_T("����������"));
	//		this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
	//	}
	//	else
	//	{
	//		i--;
	//		DeleteDataPoint();
	//		this->Invalidate(1);

	//	}
	//}

	///*********************************/  //��ͷ
	//if(m_bDrawArrow == TRUE)
	//{
	//	if(i==0)
	//	{
	//		AfxMessageBox(_T("����������"));
	//		this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
	//	}
	//	else
	//	{
	//		i--;
	//		DeleteDataPoint();
	//		this->Invalidate(1);

	//	}
	//}

	//if(m_bDrawTen == TRUE)
	//{
	//	if(i==0)
	//	{
	//		AfxMessageBox(_T("����������"));
	//		this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
	//	}
	//	else
	//	{
	//		i--;
	//		DeleteDataPoint();
	//		this->Invalidate(1);

	//	}
	//}
	////////////////////
	//if(m_bDrawWavy == TRUE)
	//{
	//	if(i==0)
	//	{
	//		AfxMessageBox(_T("����������"));
	//		this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��
	//	}
	//	else
	//	{
	//		i--;
	//		DeleteDataPoint();
	//		this->Invalidate(1);

	//	}
	//}
}


void CTFigureDlg::OnBnClickedLinebutton() //ѡ����ֱ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_bDrawLine = !m_bDrawLine;   //ֱ�߻��Ʊ��
	if(m_bDrawLine == TRUE)
	{	
		ChangeFlag(&m_bDrawLine);
		//AfxMessageBox(_T("��ѡ����ֱ��"));
	}

}

void CTFigureDlg::OnBnClickedDashbutton() //��������
{	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawDash = !m_bDrawDash;
	if(m_bDrawDash == TRUE)
	{
		ChangeFlag(&m_bDrawDash);
		//AfxMessageBox(_T("��ѡ��������"));
	}

}
void CTFigureDlg::OnBnClickedCirclebutton() //ʵ��Բ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawCircle = !m_bDrawCircle ;  //���߻��Ʊ��
	if(m_bDrawCircle == TRUE)
	{
		ChangeFlag(&m_bDrawCircle);
		//AfxMessageBox(_T("��ѡ����ʵ��Բ"));
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
		//AfxMessageBox(_T("��ѡ���˼�ͷ"));
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
	m_bDrawDash = FALSE;
	m_bDrawT = FALSE;
	m_bDrawTT = FALSE;
	m_bDraw3T = FALSE;
	m_bdrawNline =FALSE;
	m_bDraw3arrow= FALSE;
	m_bDraw2arrow= FALSE;
	m_bDrawO= FALSE;
	m_bDrawTupdown= FALSE;
	m_bDrawtenten= FALSE;
	m_bDrawtententen= FALSE;
	m_bDraw3arrow = FALSE;
	m_bDrawCircleLine = FALSE;
	m_bDrawText = FALSE;
	*b = TRUE;	
	this->Invalidate(0);
}
void CTFigureDlg::OnBnClickedButtonten()  //ѡ����TEN
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawTen = !m_bDrawTen;
	// 	HBITMAP hBmp1=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPARROW));   
	// 	HBITMAP hBmp=::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAPTEN));  
	if(m_bDrawTen == TRUE) 
	{
		//m_buttonTen.SetBitmap(hBmp1);
		//m_buttonTen.SetState(1);
		//��������ͼ�������Ϊfalse
		ChangeFlag(&m_bDrawTen);
		//AfxMessageBox(_T("��ѡ����TEN"));
	}
	// 	else
	// 	{
	// 		//m_buttonTen.SetBitmap(hBmp);
	// 	}

}


void CTFigureDlg::OnBnClickedBwavy()  //ѡ���˲�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawWavy = !m_bDrawWavy;
	if(m_bDrawWavy == TRUE) 
	{
		//��������ͼ�������Ϊfalse
		ChangeFlag(&m_bDrawWavy);
		//AfxMessageBox(_T("��ѡ����WAVY"));
	}
}

void CTFigureDlg::OnBnClickedCurvebutton() //ѡ���˲�����
{
	//AfxMessageBox(_T("��ѡ����WAVY"));
}

//��ת�������Ʋ�����
void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length,CDC* dc)
{
	CPen pen,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen = dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
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
	dc->Polyline(arrPoint,8);
	dc->SetROP2(nOldMode);

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

//����ʮʮ��
void CTFigureDlg::DrawTenten(CPoint p1,CPoint p2,double theta,int length,CDC* dc) 
{
	//CPoint p3;
	//p3.x = (p1.x + p2.x)/2;
	//p3.y = (p2.y + p1.y)/2;
	length =(int)sqrt((double)(p2.x*p2.x+p1.x*p1.x-2*p2.x*p1.x
		+p2.y*p2.y+p1.y*p1.y-2*p1.y*p2.y))/2;
	int lengthUp = length - 10 ;
	int lengthDown = length + 10 ;
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
	double P1xUp = P1x*lengthUp/x1;
	P1y=P1y*length/x1;
	double P1yUp = P1y*lengthUp/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	double P2xUp = P2x*lengthUp/x2;
	P2y=P2y*length/x2;
	double P2yUp = P2y*lengthUp/x2;

	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	//CClientDC dc(this);
	//��ȡ�ͻ�����DC

	//int nOldMode = dc->SetROP2(R2_NOT);
	dc->MoveTo(p1.x,p1.y);
	dc->LineTo(p2.x,p2.y);
	dc->MoveTo(P1x,P1y);
	dc->LineTo(P2x,P2y);
	//dc.MoveTo(P1xUp,P1yUp);
	//dc.LineTo(P2xUp,P2yUp);
	//dc->SelectObject(oldpen);
	//dc->SetROP2(nOldMode);
}
//����ʮʮ��
void CTFigureDlg::DrawTenten(CPoint p1,CPoint p2,double theta,int length) 
{
	//CPoint p3;
	//p3.x = (p1.x + p2.x)/2;
	//p3.y = (p2.y + p1.y)/2;
	length =(int)sqrt((double)(p2.x*p2.x+p1.x*p1.x-2*p2.x*p1.x
		+p2.y*p2.y+p1.y*p1.y-2*p1.y*p2.y))/2;
	int lengthUp = length - 10 ;
	int lengthDown = length + 10 ;
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
	double P1xUp = P1x*lengthUp/x1;
	P1y=P1y*length/x1;
	double P1yUp = P1y*lengthUp/x1;
	x2=sqrt(P2x*P2x+P2y*P2y);
	P2x=P2x*length/x2;
	double P2xUp = P2x*lengthUp/x2;
	P2y=P2y*length/x2;
	double P2yUp = P2y*lengthUp/x2;

	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x=P1x+p2.x;
	P1y=P1y+p2.y;
	P2x=P2x+p2.x;
	P2y=P2y+p2.y;
	CClientDC dc(this);
	//��ȡ�ͻ�����DC
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(p1.x,p1.y);
	dc.LineTo(p2.x,p2.y);
	dc.SelectObject(&pen1);
	dc.MoveTo(P1x,P1y);
	dc.LineTo(P2x,P2y);
	//dc.MoveTo(P1xUp,P1yUp);
	//dc.LineTo(P2xUp,P2yUp);
	dc.SelectObject(oldpen);
}
//һ���Ի���ʮʮ��
void CTFigureDlg::DrawTentenA(CPoint p1,CPoint p2,double theta,int length,CDC* dc) 
{
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen=dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	DrawTenten(p1,p2,15.0,10,dc);
	CPoint tempPoint(0,0);
	tempPoint.x = abs(p1.x + p2.x)/2;
	tempPoint.y = abs(p1.y + p2.y)/2;
	for(int i=0;i<1;i++)
	{
		tempPoint.x = abs(p1.x + tempPoint.x)/2;
		tempPoint.y = abs(p1.y + tempPoint.y)/2;
	}
	DrawTenten(tempPoint, p2,15.0,10,dc);
	DrawTenten(tempPoint, p2,15.0,10,dc);
	dc->SetROP2(nOldMode);
}
//����ʮ��
void CTFigureDlg::DrawTen(CPoint p1,CPoint p2,double theta,int length,CDC* dc) 
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
	//CClientDC dc(this);
	//��ȡ�ͻ�����DC
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen=dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	dc->MoveTo(p1.x,p1.y);
	dc->LineTo(p2.x,p2.y);
	dc->SelectObject(&pen1);
	dc->MoveTo(P1x,P1y);
	dc->LineTo(P2x,P2y);
	dc->SelectObject(oldpen);
	dc->SetROP2(nOldMode);
}
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
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(p1.x,p1.y);
	dc.LineTo(p2.x,p2.y);
	dc.SelectObject(&pen1);
	dc.MoveTo(P1x,P1y);
	dc.LineTo(P2x,P2y);
	dc.SelectObject(oldpen);
}
void CTFigureDlg::DrawArrow(CPoint p1,CPoint p2,double theta,int length,CDC* dc)
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
	//CClientDC dc(this);
	//��ȡ�ͻ�����DC
	CPen pen,pen1,*oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen=dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	dc->MoveTo(p1.x,p1.y);
	dc->LineTo(p2.x,p2.y);
	dc->SelectObject(&pen1);
	dc->MoveTo(p2.x,p2.y);
	dc->LineTo(P1x,P1y);
	dc->MoveTo(p2.x,p2.y);
	dc->LineTo(P2x,P2y);
	dc->SelectObject(oldpen);
	dc->SetROP2(nOldMode);
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
	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
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

CPoint CTFigureDlg::FindDrawArrowPoint(CPoint p1,CPoint p2,double theta,int length)
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
	CPoint ret(P1x,P1y);
	return ret;
	//dc.MoveTo(p1.x,p1.y);
	//dc.LineTo(p2.x,p2.y);
	//dc.SelectObject(&pen1);
	//dc.MoveTo(p2.x,p2.y);
	//dc.LineTo(P1x,P1y);
	//dc.MoveTo(p2.x,p2.y);
	//dc.LineTo(P2x,P2y);
	//dc.SelectObject(oldpen);
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

TiXmlElement SelectElementByName(char* InputInfo, char* pName, int iXMLType,int nLead)
{
	//ע��XMLTYPE Ϊ1ʱ��InputInfoΪXML·������Ϊ2ʱ,InputInfoΪ�������ļ�����
	TiXmlDocument cXmlDoc;
	TiXmlElement* pRootElement = NULL;
	if (iXMLType == 1)
	{
		if (!cXmlDoc.LoadFile(InputInfo))
		{
			AfxMessageBox(CString("�����ļ�")+CString(InputInfo)+CString("������"));
			//printf("parse XML file failed \n");
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
		//�л�����
		while(nLead--)
		{
			pTempElement = pTempElement->Parent()->Parent()->Parent()->NextSiblingElement()->FirstChild() \
				->FirstChild()->NextSiblingElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement();
		}

		//pTempElement = ReadElememt(pRootElement, pName)->Parent()->Parent()->Parent()->NextSiblingElement()->FirstChild() \
		//	->FirstChild()->NextSiblingElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement();
		if (pTempElement)
		{
			printf("find the Name : %s, Text = %s\n", pTempElement->Value(), pTempElement->GetText());
		}
		return *(pTempElement);
	}	
}

//��vector���ֵ
int FindMax(std::vector<int> vecNum )
{
	using std::vector;
	int max = 0;
	for(vector<int>::iterator iter = vecNum.begin();iter !=vecNum.end();iter++)
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
	m_bChangeLead = FALSE; //�����ʼ���ƴ�ʱ�����Ƶ���
	using namespace  std;
	CFileDialog dlg(TRUE,NULL,NULL,
		OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,
		_T("�����ļ�(*.*))|*.*|json�����ļ�(*.json)|*.json|xml�����ļ�(*.xml)|*.xml|�ı��ļ�(*.txt)|*.txt||"),this);
	if(dlg.DoModal() == IDOK)
	{
#if DEBUGS:
		AfxMessageBox(dlg.GetPathName());
#endif
		m_cstrFileLocation = dlg.GetPathName();
		//AnalysisCommandLine();
		USES_CONVERSION;
		char* pathName = T2A(m_cstrFileLocation.GetBuffer(0)); 
		//std::unique_ptr<char> pathName(new char[strlen(pathNameTmp)]);
		m_cstrFileLocation.ReleaseBuffer();
		std::string strFilename = pathName;
		//�õ��ļ���׺
		std::string suffixStr = strFilename.substr(strFilename.find_last_of('.') + 1);
		//�����xml�ļ�
		if(suffixStr == "xml")
		{
			//�ݴ�XML�ļ�·��
			//std::unique_ptr<string> pPathName(new string(pathName));

			//string* pPathName = new string(pathName);
			//std::shared_ptr<string> pp(pPathName) ;
			m_cXmlFilePath = pathName;
			//m_cXmlFilePath = pathName;
#if DEBUGS:
			AfxMessageBox(CString(suffixStr.c_str()));Sleep(1);
#endif
			TiXmlElement pTempEle = SelectElementByName(pathName,"digits", 1,0);
			m_bChangeLead = FALSE;
			//Sleep(1);
			//printf("find the Name : %s, Text = %s\n", pTempEle.Value(), pTempEle.GetText());
			//Sleep(2);
			const char* str = pTempEle.GetText();
			std::vector<CString> vecString;
			std::vector<int> vecNum;
			m_vecPoint.resize(0);
			char tempstr[8];
			char* p = tempstr;
			memset(tempstr,0,8);
			//������
			//std::vector<CPoint>  vecPoint;
			//���±��X
			double nPointX = 20+150 ;
			//Sleep(2);
			if(CString(str)!=CString(""))
			{
				for (unsigned int i=0;i<strlen(str)+1;i++)
				{	

					if((*(str+i) != ' ')&&(*(str+i) != '\0'))
					{	
						*p++ = *(str+i);
					}
					else
					{
						*p++ ='\0';
						vecString.push_back(CString(tempstr));
						//MessageBox(vecString.back());
						m_vecPoint.push_back(CPoint(d_round(nPointX),d_round(( 4200-(atoi(tempstr)+4200))*0.009*m_nMmmV/10+250) ));   //��ŵ�λ
						nPointX = nPointX + 0.1554*m_nMmS/25;/*0.18 ;*//*1554/10000*/ /*0.0250.16098*/
						vecNum.push_back(atoi(tempstr));
						memset(tempstr,0,8);
						p = tempstr;
					}
				}
			}
			//Sleep(3);
			char nnn[10];
			memset(nnn,0,10);
			//sprintf(nnn,"min:%d",FindMin(vecNum));
			sprintf(nnn,"min:%d",m_vecPoint.size());
#if DEBUGS:
			AfxMessageBox(CString(nnn));
#endif
			this->Invalidate(1);
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

		//�����json�ļ�
		else if(suffixStr == "json")
		{
			//this->i = 0;
			m_cXmlFilePath = "";
			m_vecPoint.resize(0);
			ClearPoint(); //��յ�λ
			this->i = 0;
			CTFigureDlg::readfireadFileJson(dlg.GetPathName());
			this->Invalidate();
		}
		else
		{
			AfxMessageBox(_T("��֧���������,\n\r.xml�ĵ�ͼ�����ļ���.json����ͼ��ͼ�����ļ�"));
		}

	}


}

//��յ�λ
void CTFigureDlg::ClearPoint()
{
	for(int i=0;i<this->i;i++)
	{
		for (int j=0; j<sizeof(m_arrHeadPoint)/sizeof(CPoint*)-1;j++)
		{
			this->m_arrHeadPoint[j][i].x = 0;

			this->m_arrHeadPoint[j][i].y = 0;
			this->m_arrTailPoint[j][i].x = 0;
			this->m_arrTailPoint[j][i].y = 0;
		}
		//m_headPoint[i].x = 0;//��
		//m_headPoint[i].y = 0;
		//m_tailPoint[i].x =  0;
		//m_tailPoint[i].y =  0;
		//m_headPoint1[i].x = 0;//Բ ��
		//m_headPoint1[i].y = 0;
		//m_tailPoint1[i].x = 0;
		//m_tailPoint1[i].y = 0;
		////��ͷ

		//m_headPoint2[i].x = 0;
		//m_headPoint2[i].y = 0;
		//m_tailPoint2[i].x = 0;
		//m_tailPoint2[i].y = 0;

		////TEN

		//m_headPoint3[i].x = 0;
		//m_headPoint3[i].y = 0;
		//m_tailPoint3[i].x = 0;
		//m_tailPoint3[i].y = 0;
		////Wavy

		//m_headPoint4[i].x = 0;
		//m_headPoint4[i].y = 0;
		//m_tailPoint4[i].x = 0;
		//m_tailPoint4[i].y = 0;
		////Dash
		//m_headPoint5[i].x = 0;
		//m_headPoint5[i].y = 0;
		//m_tailPoint5[i].x = 0;
		//m_tailPoint5[i].y = 0;

		//m_headPoint6[i].x = 0;
		//m_headPoint6[i].y = 0;
		//m_tailPoint6[i].x = 0;
		//m_tailPoint6[i].y = 0;
		//m_headPoint7[i].x = 0;
		//m_headPoint7[i].y = 0;
		//m_tailPoint7[i].x = 0;
		//m_tailPoint7[i].y = 0;
		//m_headPoint8[i].x = 0;
		//m_headPoint8[i].y = 0;
		//m_tailPoint8[i].x = 0;
		//m_tailPoint8[i].y = 0;
		//m_headPoint9[i].x = 0;
		//m_headPoint9[i].y = 0;
		//m_tailPoint9[i].x = 0;
		//m_tailPoint9[i].y = 0;
		//m_headPoint10[i].x = 0;
		//m_headPoint10[i].y = 0;
		//m_tailPoint10[i].x = 0;
		//m_tailPoint10[i].y = 0;
	}
}

//************************************
// Method:    OnBnClickedButton2
// FullName:  CTFigureDlg::OnBnClickedButton2
// Access:    public 
// Returns:   void
// Qualifier: //���� ���Ϊ
//************************************
void CTFigureDlg::OnBnClickedButton2()  //���� ���Ϊ
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(FALSE,NULL,NULL,
		OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,
		_T("json�����ļ�(*.json)|*.json|DATA�ļ�(*.dat)|*.dat|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*))|*.*||"),this);
	//dlg.m_ofn.lpstrInitialDir = _T("C://");  
	if(dlg.DoModal() == IDOK)
	{

		//AfxMessageBox(dlg.GetPathName());
		//CStdioFile file(dlg.GetPathName(),CFile::modeWrite|CFile::modeCreate);
		//char temp[50];
		//CString strTemp;

		//CString str[1024];
		//for(int i=0;i<1024;i++)
		//{	
		//	memset(temp,0,50); 
		//	sprintf(temp,"hx:%d,hy:%d\t;tx:%d,ty:%d\n",m_headPoint[i].x,m_headPoint[i].y,m_tailPoint[i].x,m_tailPoint[i].y);
		//	str[i] =temp;
		//	strTemp.Append(str[i]);
		//}

		CString Path;
		Path = dlg.GetPathName();

		
		//�Զ���Ӻ�׺ �� ������
		if (Path.Find(CString(".json"))<0)
		{
			Path += CString(".json");
		}
		BOOL rec = PathFileExists(Path);
		if(rec)
		{
			//����
			int ret = AfxMessageBox(_T("�ļ��Ѵ���,ȷ���滻��"),MB_OKCANCEL);
			if(ret == IDCANCEL)
			{
				return ;
			}
			else
			{   m_cstrFileLocation = Path;
			writeFileJson(Path);
			//AfxMessageBox(_T("����ɹ�"));
			this->m_bChangeFlag = FALSE;
			}
		}
		else
		{
			// ������
			//д��json�ļ�
			m_cstrFileLocation = Path;
			writeFileJson(Path);
			//AfxMessageBox(_T("����ɹ�"));
			this->m_bChangeFlag = FALSE;
		}
		//����jpg	
		USES_CONVERSION;
		char* pathName = T2A(Path.GetBuffer(0));
		Path.ReleaseBuffer();
		std::string strFilename = pathName;
		std::string suffixStr = strFilename.substr(0,strFilename.find_last_of('.') + 1) ;
		CString cstr1;
		cstr1 = suffixStr.c_str();
		CString strFileImg  = cstr1 + CString("bmp");
#if DEBUGS:
		AfxMessageBox(strFileImg);
#endif
		CRect rect(40,40+140,1900,900);
		if(!SaveBmp(CaptureScreen(&rect),strFileImg))  
		{
			AfxMessageBox(_T("�洢bmp�ļ�ʧ��"));
		}
		//file.Seek(0, CFile::end);
		//file.WriteString(strTemp);
		//file.Close();
	}
	Invalidate(1);
}


//************************************
// Method:    DrawGrid
// FullName:  CTFigureDlg::DrawGrid
// Access:    public 
// Returns:   void
// Qualifier: �����ĵ�ͼ���
// Parameter: CPoint lP ���϶���λ��
// Parameter: CPoint rP ���¶���λ��
//************************************
void CTFigureDlg::DrawGrid(CPoint lP,CPoint rP)
{

	CDC* ppDC;
	ppDC = GetDC();
	// 	int nWidth = rP.x - lP.x;
	// 	int nHeight = rP.y - lP.y;
	// 	CBitmap MemBitmap;//����һ��λͼ����
	// 	MemDC.CreateCompatibleDC(ppDC); 
	// 	//MemBitmap.CreateCompatibleBitmap(ppDC,nWidth,nHeight);
	// 	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	// 	MemDC.FillSolidRect(CRect(lP,rP), ppDC->GetBkColor());//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ,����ԭ����OnEraseBkgnd���ø���ʵ�ֵģ�

	//MemDC.FillSolidRect(CRect(lP,rP),RGB(240,240,240));
	//MemDC.SetBkMode(TRANSPARENT);
	// 	/* MemDC.MoveTo(����); MemDC.LineTo(����);*/
	ppDC->SetBkMode(TRANSPARENT);
	CClientDC dc(this);
	CPen pen(PS_SOLID ,1,RGB(255,0,0));
	//dc.SelectStockObject(WHITE_BRUSH); //��ɫ
	dc.SelectObject(&pen);
	//dc.Rectangle(lP.x,lP.y,rP.x,rP.y);
	//dc.SelectStockObject(LTGRAY_BRUSH); //��ɫ
	CPoint lPoint2(lP.x,lP.y);
	CPoint rPoint2(rP.x,lP.y);
	for (int m= 0;m<(rP.x-lP.x)/30*5-1;m++)
	{
		lPoint2.x += 6;
		double tempX = lPoint2.x +6;
		for (int n =0;n<(rP.y-lP.y)/30*5-1;n++)
		{
			lPoint2.y += 6;
			ppDC->SetPixel(lPoint2,RGB(255,0,0));
			//MemDC.SetPixel(lPoint2,RGB(255,0,0));
		}
		lPoint2.y = lP.y;
	}
	dc.SetBkMode(TRANSPARENT);
	//dc.Rectangle(CRect(lP,rP));
	CPoint lPoint(lP.x,lP.y);
	CPoint rPoint(rP.x,lP.y);
	CPoint uPoint(lP.x,lP.y);
	CPoint dPoint(lP.x,rP.y);

	dc.MoveTo(lPoint);
	dc.LineTo(rPoint);
	for(int i=0;i<5;i++)
	{
		lPoint.y +=30;
		rPoint.y +=30;
		dc.MoveTo(lPoint);
		dc.LineTo(rPoint);
	}
	dc.MoveTo(uPoint);
	dc.LineTo(dPoint);
	for(int i=0;i<(rP.x-lP.x)/30;i++)
	{
		uPoint.x += 30;
		dPoint.x += 30;
		dc.MoveTo(uPoint);
		dc.LineTo(dPoint);
	}
	dc.TextOutW(lP.x+50,lP.y+50,m_strCurrentLead);
	// 	
	// 	ppDC->BitBlt(lP.x,lP.y,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
	// 	MemDC.SelectObject(pOldBit);
	// 	MemBitmap.DeleteObject(); 
	// 	MemDC.DeleteDC();
	// 	DeleteObject(pOldBit);
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

//����2ARROW
void CTFigureDlg::Draw2Arrow(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{
	nSeg = 3 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	//dc.MoveTo(a[i]);
	//dc.LineTo(a[i+1]);
	dc->MoveTo(a[0]);
	dc->LineTo(a[1]);
	//DrawArrow(a[0],a[1],90.0,10);
	DrawArrow(a[2],a[3],30.0,10,dc);
	dc->SetROP2(nOldMode);
}
void CTFigureDlg::Draw2Arrow(CPoint p1,CPoint p2,int nSeg)
{
	nSeg = 3 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	//dc.MoveTo(a[i]);
	//dc.LineTo(a[i+1]);
	dc.MoveTo(a[0]);
	dc.LineTo(a[1]);
	//DrawArrow(a[0],a[1],90.0,10);
	DrawArrow(a[2],a[3],30.0,10);
}

//����3ARROW
void CTFigureDlg::Draw3Arrow(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	double aX[8] = {0};
	double aY[8] = {0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + (lengthX*1.0/nSeg) ;
		aY[i] = aY[i-1] + (lengthY*1.0/nSeg) ;
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	//dc.MoveTo(a[i]);
	//dc.LineTo(a[i+1]);
	dc->MoveTo(CPoint(aX[0],aY[0]));
	dc->LineTo(CPoint(aX[1],aY[1]));
	dc->MoveTo(CPoint(aX[2],aY[2]));
	dc->LineTo(CPoint(aX[3],aY[3]));
	//DrawArrow(a[0],a[1],90.0,10);
	DrawArrow(CPoint(aX[4],aY[4]),CPoint(aX[5],aY[5]),30.0,10,dc);
	dc->SetROP2(nOldMode);
}
void CTFigureDlg::Draw3Arrow(CPoint p1,CPoint p2,int nSeg)
{
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	double aX[8] = {0};
	double aY[8] = {0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + (lengthX*1.0/nSeg) ;
		aY[i] = aY[i-1] + (lengthY*1.0/nSeg) ;
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	//dc.MoveTo(a[i]);
	//dc.LineTo(a[i+1]);
	dc.MoveTo(CPoint(aX[0],aY[0]));
	dc.LineTo(CPoint(aX[1],aY[1]));
	dc.MoveTo(CPoint(aX[2],aY[2]));
	dc.LineTo(CPoint(aX[3],aY[3]));
	//DrawArrow(a[0],a[1],90.0,10);
	DrawArrow(CPoint(aX[4],aY[4]),CPoint(aX[5],aY[5]),30.0,10);
}
//����TTUP&&DOWN
void CTFigureDlg::DrawTTUpDown(CPoint p1,CPoint p2,int nSeg ,CDC* dc)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	//dc.MoveTo(a[i]);
	//dc.LineTo(a[i+1]);
	DrawArrow(a[0],a[2],90.0,10,dc);
	DrawArrow(a[5],a[3],90.0,10,dc);
	dc->SetROP2(nOldMode);
}
void CTFigureDlg::DrawTTUpDown(CPoint p1,CPoint p2,int nSeg)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	//dc.MoveTo(a[i]);
	//dc.LineTo(a[i+1]);
	DrawArrow(a[0],a[2],90.0,10);
	DrawArrow(a[5],a[3],90.0,10);
}
//����TT
void CTFigureDlg::DrawTT(CPoint p1,CPoint p2,int nSeg)
{
	nSeg = 3 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	dc.MoveTo(a[0]);
	dc.LineTo(a[1]);
	//dc.MoveTo(a[2]);
	//dc.LineTo(a[3]);
	DrawArrow(a[2],a[3],90.0,8);
}
void CTFigureDlg::DrawTT(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{
	nSeg = 3 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	dc->MoveTo(a[0]);
	dc->LineTo(a[1]);
	//dc.MoveTo(a[2]);
	//dc.LineTo(a[3]);
	DrawArrow(a[2],a[3],90.0,8,dc);
	dc->SetROP2(nOldMode);
}
//����3T
void CTFigureDlg::Draw3T(CPoint p1,CPoint p2,int nSeg)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	dc.MoveTo(a[0]);
	dc.LineTo(a[1]);
	dc.MoveTo(a[2]);
	dc.LineTo(a[3]);
	DrawArrow(a[4],a[5],90.0,10);
}
void CTFigureDlg::Draw3T(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	dc->MoveTo(a[0]);
	dc->LineTo(a[1]);
	dc->MoveTo(a[2]);
	dc->LineTo(a[3]);
	DrawArrow(a[4],a[5],90.0,10,dc);
	dc->SetROP2(nOldMode);
}
//����circle&line
void CTFigureDlg::DrawCircleLine(CPoint p1,CPoint p2,int nSeg)
{	                                      
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);

	dc.MoveTo(a[0]);
	dc.LineTo(a[2]);
	CPoint pPoint[4];
	pPoint[0]= a[2];
	pPoint[1]= FindDrawArrowPoint(a[2],CPoint((a[2].x+a[3].x)/2,(a[2].y+a[3].y)/2),90,10); 
	pPoint[2]= FindDrawArrowPoint(a[2],a[3],90,8);
	pPoint[3]= a[3];
	dc.PolyBezier(pPoint,4);
	dc.Ellipse((a[2].x+a[3].x)/2-2,(a[2].y+a[3].y)/2-2,(a[2].x+a[3].x)/2+2,(a[2].y+a[3].y)/2+2);
	dc.MoveTo(a[3]);
	dc.LineTo(a[5]);
}
void CTFigureDlg::DrawCircleLine(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{	                                      
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	/*	CClientDC dc(this);*/
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	dc->MoveTo(a[0]);
	dc->LineTo(a[2]);
	CPoint pPoint[4];
	pPoint[0]= a[2];
	pPoint[1]= FindDrawArrowPoint(a[2],CPoint((a[2].x+a[3].x)/2,(a[2].y+a[3].y)/2),90,10); 
	pPoint[2]= FindDrawArrowPoint(a[2],a[3],90,8);
	pPoint[3]= a[3];
	dc->PolyBezier(pPoint,4);
	dc->Ellipse((a[2].x+a[3].x)/2-2,(a[2].y+a[3].y)/2-2,(a[2].x+a[3].x)/2+2,(a[2].y+a[3].y)/2+2);
	dc->MoveTo(a[3]);
	dc->LineTo(a[5]);
	dc->SetROP2(nOldMode);
}

//������λ�û��Ʋ�ͬ���ȵ�Բ��
//centerΪԲ�ģ�pStartΪԲ��������꣬radianΪԲ����Խ�Ļ��ȷ�Χ��radiusΪ�뾶
void CTFigureDlg::DrawArc(CPoint center, CPoint pStart, double radian, int radius,COLORREF color)
{	
	CClientDC dc(this);
	double angle, max;
	double dy = (double)pStart.y - (double)center.y, dx = (double)pStart.x - (double)center.x;
	angle = atan2(dy,dx);//����ʼ���Ӧ�ĵĻ���
	max = angle + radian;
	int x = pStart.x,y = pStart.y;
	//SetPixel(x, y, color);
	dc.MoveTo((x), (y));
	dc.LineTo((x), (y));
	//PIΪ����ĺ꣬��ֵΪ3.1415926
	//ROUND(x)ҲΪ����ĺ꣬�����������룬�䶨��Ϊ#define ROUND(a) (int)(a+0.5)
	for (angle+=PI/(double)180; angle < max; angle += PI / (double)180)
	{
		x = center.x + radius * cos(angle);
		y = center.y + radius * sin(angle);
		//SetPixel(ROUND(x), ROUND(y), color);
		dc.MoveTo(ROUND(x), ROUND(y));
		dc.LineTo(ROUND(x), ROUND(y));
	}
}

//����ͼƬ
BOOL SaveBmp(HBITMAP hBitmap,CString FileName)         
{         
	HDC     hDC;         
	//��ǰ�ֱ�����ÿ������ռ�ֽ���         
	int     iBits;         
	//λͼ��ÿ������ռ�ֽ���         
	WORD     wBitCount;         
	//�����ɫ���С��     λͼ�������ֽڴ�С     ��λͼ�ļ���С     ��     д���ļ��ֽ���             
	DWORD     dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;             
	//λͼ���Խṹ             
	BITMAP     Bitmap;                 
	//λͼ�ļ�ͷ�ṹ         
	BITMAPFILEHEADER     bmfHdr;                 
	//λͼ��Ϣͷ�ṹ             
	BITMAPINFOHEADER     bi;                 
	//ָ��λͼ��Ϣͷ�ṹ                 
	LPBITMAPINFOHEADER     lpbi;                 
	//�����ļ��������ڴ�������ɫ����             
	HANDLE     fh,   hDib,   hPal,hOldPal=NULL;             

	//����λͼ�ļ�ÿ��������ռ�ֽ���             
	hDC  = CreateDC(TEXT("DISPLAY"),NULL,   NULL,   NULL);         
	iBits  = GetDeviceCaps(hDC,   BITSPIXEL)     *     GetDeviceCaps(hDC,   PLANES);             
	DeleteDC(hDC);             
	if(iBits <=  1)                                                   
		wBitCount = 1;             
	else  if(iBits <=  4)                               
		wBitCount  = 4;             
	else if(iBits <=  8)                               
		wBitCount  = 8;             
	else                                                                                                                               
		wBitCount  = 24;             

	GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);         
	bi.biSize= sizeof(BITMAPINFOHEADER);         
	bi.biWidth = Bitmap.bmWidth;         
	bi.biHeight =  Bitmap.bmHeight;         
	bi.biPlanes =  1;         
	bi.biBitCount = wBitCount;         
	bi.biCompression= BI_RGB;         
	bi.biSizeImage=0;         
	bi.biXPelsPerMeter = 0;         
	bi.biYPelsPerMeter = 0;         
	bi.biClrImportant = 0;         
	bi.biClrUsed =  0;         

	dwBmBitsSize  = ((Bitmap.bmWidth *wBitCount+31) / 32)*4* Bitmap.bmHeight;         

	//Ϊλͼ���ݷ����ڴ�             
	hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));             
	lpbi  = (LPBITMAPINFOHEADER)GlobalLock(hDib);             
	*lpbi  = bi;             

	// �����ɫ��                 
	hPal  = GetStockObject(DEFAULT_PALETTE);             
	if (hPal)             
	{             
		hDC  = ::GetDC(NULL);             
		hOldPal = ::SelectPalette(hDC,(HPALETTE)hPal, FALSE);             
		RealizePalette(hDC);             
	}         

	//     ��ȡ�õ�ɫ�����µ�����ֵ             
	GetDIBits(hDC,hBitmap, 0,(UINT)Bitmap.bmHeight,  
		(LPSTR)lpbi+ sizeof(BITMAPINFOHEADER)+dwPaletteSize,   
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);             

	//�ָ���ɫ��                 
	if (hOldPal)             
	{             
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);             
		RealizePalette(hDC);             
		::ReleaseDC(NULL,   hDC);             
	}             

	//����λͼ�ļ�                 
	fh  = CreateFile(FileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,           
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,   NULL);             

	if (fh     ==  INVALID_HANDLE_VALUE)         return     FALSE;             

	//     ����λͼ�ļ�ͷ             
	bmfHdr.bfType  = 0x4D42;     //     "BM" 
	dwDIBSize  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;                 
	bmfHdr.bfSize  = dwDIBSize;             
	bmfHdr.bfReserved1  = 0;             
	bmfHdr.bfReserved2  = 0;             
	bmfHdr.bfOffBits  = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;             
	//     д��λͼ�ļ�ͷ             
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);             
	//     д��λͼ�ļ���������             
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);             
	//���                 
	GlobalUnlock(hDib);             
	GlobalFree(hDib);             
	CloseHandle(fh);             

	return     TRUE;         
}
//��ͼ
HBITMAP CaptureScreen(LPRECT lpRect)//lpRectΪNULLʱ��ʾȫ��Ļ��ͼ
{
	HDC      hdc, hdcMem ;
	HBITMAP  hemfCopy ;
	HWND     hwndScr ;
	int      dstcx, dstcy ;
	if(lpRect)
	{
		dstcx = lpRect->right - lpRect->left ;
		dstcy = lpRect->bottom - lpRect->top ;
	}
	else
	{
		dstcx = GetSystemMetrics(SM_CXSCREEN) ;
		dstcy = GetSystemMetrics(SM_CYSCREEN) ;
	}
	if (LockWindowUpdate(hwndScr = GetDesktopWindow ()))
	{
		hdc  = GetDCEx (hwndScr, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE) ;
		hdcMem = CreateCompatibleDC (hdc) ;
		if(NULL==hdcMem)
		{
			ReleaseDC (hwndScr, hdc) ;
			LockWindowUpdate (NULL) ;
			return NULL;
		}
		hemfCopy = CreateCompatibleBitmap (hdc, abs(dstcx), abs(dstcy)) ;
		if(NULL==hemfCopy)
		{
			DeleteDC (hdcMem) ;
			ReleaseDC (hwndScr, hdc) ;
			LockWindowUpdate (NULL) ;
			return NULL;
		}
		SelectObject (hdcMem, hemfCopy) ;
		if(lpRect)
			StretchBlt (hdcMem, 0, 0, abs(dstcx), abs(dstcy), 
			hdc, lpRect->left, lpRect->top, dstcx, dstcy, SRCCOPY|CAPTUREBLT) ;
		else
			BitBlt (hdcMem, 0, 0, dstcx, dstcy, 
			hdc, 0, 0, SRCCOPY|CAPTUREBLT) ;
		DeleteDC (hdcMem) ;
		ReleaseDC (hwndScr, hdc) ;
		LockWindowUpdate (NULL) ;
		return hemfCopy;
	}
	return NULL;
}
//����nline
void CTFigureDlg::DrawNLine(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	DrawArrow(a[0],a[2],90.0,10,dc);
	dc->MoveTo(a[2]);
	dc->LineTo(a[3]);
	DrawPointBetweenTwoPoint(p1,CPoint((p1.x+p2.x)/2,(p1.y+p2.y)/2),90.0,10,dc);
	DrawArrow(a[5],a[3],90.0,10,dc);
	dc->SetROP2(nOldMode);
}
void CTFigureDlg::DrawNLine(CPoint p1,CPoint p2,int nSeg)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	DrawArrow(a[0],a[2],90.0,10);
	dc.MoveTo(a[2]);
	dc.LineTo(a[3]);
	DrawPointBetweenTwoPoint(p1,CPoint((p1.x+p2.x)/2,(p1.y+p2.y)/2),90.0,10);
	DrawArrow(a[5],a[3],90.0,10);
}
//����tenten,���õ�NLINE�Ļ��Ʒ���
void CTFigureDlg::DrawTentenB(CPoint p1,CPoint p2,int nSeg)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	DrawArrow(a[0],a[2],90.0,10);
	dc.MoveTo(a[2]);
	dc.LineTo(a[3]);
	//DrawPointBetweenTwoPoint(p1,CPoint((p1.x+p2.x)/2,(p1.y+p2.y)/2),90.0,10);
	DrawArrow(a[5],a[3],90.0,10);
}
void CTFigureDlg::DrawTentenB(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{	
	nSeg = 5 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	/*CClientDC dc(this);*/
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	DrawArrow(a[0],a[2],90.0,10,dc);
	dc->MoveTo(a[2]);
	dc->LineTo(a[3]);
	//DrawPointBetweenTwoPoint(p1,CPoint((p1.x+p2.x)/2,(p1.y+p2.y)/2),90.0,10);
	DrawArrow(a[5],a[3],90.0,10,dc);
	dc->SetROP2(nOldMode);
}
//����tententen,���õ�NLINE�Ļ��Ʒ���
void CTFigureDlg::DrawTententenB(CPoint p1,CPoint p2,int nSeg)
{
	nSeg = 8 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[10];
	double aX[10]={0};
	double aY[10]={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	DrawArrow(CPoint(aX[0],aY[0]),CPoint(aX[3],aY[3]),90.0,10);
	DrawArrow(CPoint(aX[3],aY[3]),CPoint(aX[4],aY[4]),90.0,10);
	DrawArrow(CPoint(aX[4],aY[4]),CPoint(aX[5],aY[5]),90.0,10);
	dc.MoveTo(CPoint(aX[5],aY[5]));
	dc.LineTo(CPoint(aX[8],aY[8]));
	//DrawPointBetweenTwoPoint(p1,CPoint((p1.x+p2.x)/2,(p1.y+p2.y)/2),90.0,10);
}
void CTFigureDlg::DrawTententenB(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{
	nSeg = 8 ;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	double aX[10]={0};
	double aY[10]={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	DrawArrow(CPoint(aX[0],aY[0]),CPoint(aX[3],aY[3]),90.0,10,dc);
	DrawArrow(CPoint(aX[3],aY[3]),CPoint(aX[4],aY[4]),90.0,10,dc);
	DrawArrow(CPoint(aX[4],aY[4]),CPoint(aX[5],aY[5]),90.0,10,dc);
	dc->MoveTo(CPoint(aX[5],aY[5]));
	dc->LineTo(CPoint(aX[8],aY[8]));
	dc->SetROP2(nOldMode);
	//DrawPointBetweenTwoPoint(p1,CPoint((p1.x+p2.x)/2,(p1.y+p2.y)/2),90.0,10);
}
//��������֮��һ���λ��
void CTFigureDlg::DrawPointBetweenTwoPoint(CPoint p1,CPoint p2,double theta,int length)
{
	//CPoint p3;
	//p3.x = (p1.x + p2.x)/2;
	//p3.y = (p2.y + p1.y)/2;
	//length =(int)sqrt((double)(p2.x*p2.x+p1.x*p1.x-2*p2.x*p1.x
	//	+p2.y*p2.y+p1.y*p1.y-2*p1.y*p2.y))/2;
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
	//dc.MoveTo(p1.x,p1.y);
	//dc.LineTo(p2.x,p2.y);
	dc.SelectObject(&pen1);
	//dc.MoveTo(P1x,P1y);
	//dc.LineTo(P2x,P2y);
	DrawDashPoint(CPoint(P1x,P1y),CPoint(P2x,P2y),5);
	dc.SelectObject(oldpen);
}
void CTFigureDlg::DrawPointBetweenTwoPoint(CPoint p1,CPoint p2,double theta,int length,CDC* dc)
{
	//CPoint p3;
	//p3.x = (p1.x + p2.x)/2;
	//p3.y = (p2.y + p1.y)/2;
	//length =(int)sqrt((double)(p2.x*p2.x+p1.x*p1.x-2*p2.x*p1.x
	//	+p2.y*p2.y+p1.y*p1.y-2*p1.y*p2.y))/2;
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
	//CClientDC dc(this);
	//��ȡ�ͻ�����DC
	// 	CPen pen,pen1,*oldpen;
	// 	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	// 	pen1.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	// 	oldpen=dc->SelectObject(&pen);
	//dc.MoveTo(p1.x,p1.y);
	//dc.LineTo(p2.x,p2.y);
	//dc->SelectObject(&pen1);
	//dc.MoveTo(P1x,P1y);
	//dc.LineTo(P2x,P2y);
	DrawDashPoint(CPoint(P1x,P1y),CPoint(P2x,P2y),5,dc);
	//dc->SelectObject(oldpen);
}
//����������һ����
void CTFigureDlg::DrawDashPoint(CPoint p1,CPoint p2,int nSeg)
{
	nSeg = 5;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,4,RGB(0,0,0));
	dc.SelectObject(&pen);


	dc.MoveTo(a[4]);
	dc.LineTo(a[5]);
	//DrawArrow(a[i],a[i+1],15.0,10);

}
void CTFigureDlg::DrawDashPoint(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{
	nSeg = 5;
	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	CPoint a[8];
	a[0] = p1;
	double aX[8]={0};
	double aY[8] ={0};
	aX[0] = p1.x;
	aY[0] = p1.y;
	for(int i=1;i<=nSeg;i++)
	{
		aX[i] = aX[i-1] + lengthX*1.0/nSeg ;
		aY[i] = aY[i-1] + lengthY*1.0/nSeg ;
	}

	for (int n=1;n<8;n++)
	{
		a[n] = CPoint(aX[n],aY[n]);
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,4,RGB(0,0,0));
	dc->SelectObject(&pen);

	int nOldMode = dc->SetROP2(R2_NOT);
	dc->MoveTo(a[4]);
	dc->LineTo(a[5]);
	dc->SetROP2(nOldMode);
	//DrawArrow(a[i],a[i+1],15.0,10);

}
//��������
void CTFigureDlg::DrawDash(CPoint p1,CPoint p2,int nSeg,CDC* dc)
{

	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	//CPoint a[8];
	double arrX[8] = {0};
	double arrY[8] = {0};
	arrX[0] = p1.x;
	arrY[0] = p1.y;

	for(int i=1;i<=nSeg;i++)
	{
		arrX[i] = arrX[i-1] + (lengthX*1.0/nSeg) ;
		arrY[i] = arrY[i-1] + (lengthY*1.0/nSeg) ;
	}
	//CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc->SelectObject(&pen);
	int nOldMode = dc->SetROP2(R2_NOT);
	for(int i=0;i<nSeg+1;i++)
	{
		dc->MoveTo(CPoint(arrX[i],arrY[i]));
		dc->LineTo(CPoint(arrX[i+1],arrY[i+1]));
		//DrawArrow(a[i],a[i+1],15.0,10);
		i++;
	}
	// 	dc->MoveTo(a[nSeg-1]);
	// 	dc->LineTo(p2);

	dc->SetROP2(nOldMode);
}
void CTFigureDlg::DrawDash(CPoint p1,CPoint p2,int nSeg)
{

	int lengthX = (p2.x-p1.x);
	int lengthY = (p2.y-p1.y);
	//int n = 1;
	//CPoint a[8];
	double arrX[8] = {0};
	double arrY[8] = {0};
	arrX[0] = p1.x;
	arrY[0] = p1.y;

	for(int i=1;i<=nSeg;i++)
	{
		arrX[i] = arrX[i-1] + (lengthX*1.0/nSeg) ;
		arrY[i] = arrY[i-1] + (lengthY*1.0/nSeg) ;
	}
	CClientDC dc(this);
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	dc.SelectObject(&pen);
	//int nOldMode = dc.SetROP2(R2_NOT);
	for(int i=0;i<nSeg+1;i++)
	{
		dc.MoveTo(CPoint(arrX[i],arrY[i]));
		dc.LineTo(CPoint(arrX[i+1],arrY[i+1]));
		//DrawArrow(a[i],a[i+1],15.0,10);
		i++;
	}
	// 	dc.MoveTo(a[nSeg-1]);
	// 	dc.LineTo(p2);
}

// //GB2312��UTF-8��ת��
// char* G2U(const char* gb2312)
// {
// 	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
// 	wchar_t* wstr = new wchar_t[len+1];
// 	memset(wstr, 0, len+1);
// 	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
// 	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
// 	char* str = new char[len+1];
// 	memset(str, 0, len+1);
// 	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
// 	if(wstr) delete[] wstr;
// 	return str;
// }
//GB2312��UTF-8��ת��
char* G2U(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}
//UTF-8��GB2312��ת��
char* U2G(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr) delete[] wstr;
	return str;
}
void CTFigureDlg::writeFileJson(const CString cs)
{
	//���ڵ�  
	Json::Value root;
	//Json::Value data;
	//���ڵ�����
	root["Patient_Information"]["name"] = Json::Value("shuiyixin");
	root["Patient_Information"]["age"] = Json::Value(21);
	//std::string tmpUTF8 = GbkToUtf8("�����й���");//\u8bc6\u522b\u5931\u8d25 \u9700\u7ee7\u7eed\u62cd\u7167
	//jsRes["body"]["message"] = tmpUTF8;
	//root["Patient_Information"]["sex"] = tmpUTF8;/*Json::Value("tmpUTF8");*/
	root["Patient_Information"]["sex"] = Json::Value("man");
	//root["Patient_Information"]["sex"] = G2U("�����й���");
	root["data"]["backToWhere"] = Json::Value(this->i);
	root["data"]["mm_s"] = Json::Value(m_CombommS.GetCurSel());
    root["data"]["mm_mV"] = Json::Value(m_Combomm_mV.GetCurSel());
	root["data"]["LeadCombox"] = Json::Value(m_LeadCombox.GetCurSel());
	root["data"]["PatternCombox"] = Json::Value(m_comboPattern.GetCurSel());


	CString strCurrent;
	this->GetDlgItemTextW(IDC_COMBOXCHANGELEAD,strCurrent);
	USES_CONVERSION;
	const char* strbuf = T2A(strCurrent.GetBuffer(0));
	strCurrent.ReleaseBuffer();	 
	int nLead = m_LeadCombox.GetCurSel()+1;
	//AfxMessageBox(CString(cLead[nLead-1]));
	// 	USES_CONVERSION;
	// 		char* pathName = T2A(m_cstrFileLocation.GetBuffer(0));
	// 		m_cstrFileLocation.ReleaseBuffer();
	// 		std::string strFilename = pathName;
	// 		//�õ��ļ���׺
	// 		std::string suffixStr = strFilename.substr(strFilename.find_last_of('.') + 1);
	//�����xml�ļ�
	//AfxMessageBox(CString(m_cXmlFilePath.c_str()));
	//USES_CONVERSION; 
	//ʹ�ÿ��Ա�������
	// 	const char* strbuff = T2A(CString(m_cXmlFilePath.c_str()).GetBuffer(0));
	// 	CString(m_cXmlFilePath.c_str()).ReleaseBuffer();
	// 	DWORD dBufSize = m_cXmlFilePath.length();
	// 	char *dBuf = new char[dBufSize];
	// 	memset(dBuf, 0, dBufSize);   
	// 	WideCharToMultiByte(CP_UTF8, 0, CString(m_cXmlFilePath.c_str()), CString(m_cXmlFilePath.c_str()).GetLength(), dBuf, dBufSize, NULL, FALSE);
	//AfxMessageBox(CString(U2G(G2U(m_cXmlFilePath.c_str()))));
	//AfxMessageBox(CString(U2G(G2U("����"))) );
	//char * test = "����";
	root["XmlFileName"] = G2U(m_cXmlFilePath.c_str());
	//root[G2U(test)] = Json::Value("sdfsegsdfh");
	// 	CString strkey("����");
	// 
	// 		DWORD dBufSize = WideCharToMultiByte(CP_UTF8, 0, strkey, -1, NULL, 0, NULL, FALSE);
	// 
	// 	//����Ŀ�껺��
	// 
	// 	char *dBuf = new char[dBufSize];
	// 
	// 	memset(dBuf, 0, dBufSize);   
	// 
	// 	WideCharToMultiByte(CP_UTF8, 0, strkey, strkey.GetLength(), dBuf, dBufSize, NULL, FALSE);
	// 
	// 	std::string name = dBuf;
	// 	name = name + "\0";
	// 
	// 	
	// 	AfxMessageBox(CString(name.c_str()));
	// 
	// 	root["testdddddddddddddd"] = name.c_str();
	// 	root["testddddddddd"] = Json::Value(name.c_str());
	// 	root[name.c_str()] = Json::Value(name.c_str());
	// 	delete[] dBuf;
	root["Lead"] = Json::Value(nLead) ;
	//string strsss = strbuf;
	//CString cssstring ;
	//cssstring = strsss.c_str();
	//	AfxMessageBox(strCurrent);
	//����AVS
	char bufN[3];
	//char* pCTemp = new char[100];
	for (int n=0;n<20/*sizeof(m_strAVS)/sizeof(m_strAVS[0])*/;n++)
	{
		USES_CONVERSION;
		const char* strbuf = T2A(m_strAVS[n].GetBuffer(0));
		m_strAVS[n].ReleaseBuffer();
		root["strAVS"][n]=  Json::Value(strbuf);
	}
	//delete[] pCTemp;
	//���滭�ָ�����  
	for (int n=0;n<4;n++)
	{
		memset(bufN,0,3);
		sprintf(bufN,"%d",n);
		root["data"]["3_4"][bufN][1] =  Json::Value(m_pPointFourLeft[n].y);
		root["data"]["3_4"][bufN][2] =  Json::Value(m_pPointFourLeft[n].x);
		root["data"]["3_4"][bufN][3] =  Json::Value(m_pPointFourRight[n].y);
		root["data"]["3_4"][bufN][4] =  Json::Value(m_pPointFourRight[n].x);
	}
	for (int n=0;n<6;n++)
	{
		memset(bufN,0,3);
		sprintf(bufN,"%d",n);
		root["data"]["5_6"][bufN][1] =  Json::Value(m_pPointSixLeft[n].y);
		root["data"]["5_6"][bufN][2] =  Json::Value(m_pPointSixLeft[n].x);
		root["data"]["5_6"][bufN][3] =  Json::Value(m_pPointSixRight[n].y);
		root["data"]["5_6"][bufN][4] =  Json::Value(m_pPointSixRight[n].x);
	}
	for (int n=0;n<8;n++)
	{
		memset(bufN,0,3);
		sprintf(bufN,"%d",n);
		root["data"]["7_8"][bufN][1] =  Json::Value(m_pPointEightLeft[n].y);
		root["data"]["7_8"][bufN][2] =  Json::Value(m_pPointEightLeft[n].x);
		root["data"]["7_8"][bufN][3] =  Json::Value(m_pPointEightRight[n].y);
		root["data"]["7_8"][bufN][4] =  Json::Value(m_pPointEightRight[n].x);
	}
	// 	root["data"]["3_4"] 
	// 	m_pPointFourLeft[i].y =0;
	// 	m_pPointFourLeft[i].x =0;
	// 	m_pPointFourRight[i].y =0;
	// 	m_pPointFourRight[i].x =0;
	////�ӽڵ�  
	//Json::Value friends;

	////�ӽڵ�����  
	//friends["friend_name"] = Json::Value("ZhaoWuxian");
	//friends["friend_age"] = Json::Value(21);
	//friends["friend_sex"] = Json::Value("man");

	////�ӽڵ�ҵ����ڵ���  
	//root["friends"] = Json::Value(friends);
	//���ڵ�

	//������ʽ  
	root["hobby"].append("sing");
	//root["data"]["hobby"].append("sing");
	root["hobby"].append("run");
	root["hobby"].append("Tai Chi");
	char buf[10];
	char bufHeadX[8];
	char bufHeadY[8];
	char bufTailX[8];
	char bufTailY[8];
	for(int i=0;i<this->i;i++)
	{
		//���ٴ洢
		for (int j = 0;j<17;j++)
		{
			memset(buf,0,10);
			memset(bufHeadX,0,8);
			memset(bufHeadY,0,8);
			memset(bufTailX,0,8);
			memset(bufTailY,0,8);
			sprintf(buf,"%d",m_arrHeadPoint[j][i].x);

			sprintf(bufHeadX,"%s%d","headX",j);
			sprintf(bufHeadY,"%s%d","headY",j);
			sprintf(bufTailX,"%s%d","tailX",j);
			sprintf(bufTailY,"%s%d","tailY",j);

			memset(buf,0,10);
			sprintf(buf,"%d",m_arrHeadPoint[j][i].x);
			root["data"][bufHeadX].append(std::string(buf));
			memset(buf,0,10);
			sprintf(buf,"%d",m_arrHeadPoint[j][i].y);
			root["data"][bufHeadY].append(std::string(buf));
			memset(buf,0,10);
			sprintf(buf,"%d",m_arrTailPoint[j][i].x);
			root["data"][bufTailX].append(std::string(buf));
			memset(buf,0,10);
			sprintf(buf,"%d",m_arrTailPoint[j][i].y);
			root["data"][bufTailY].append(std::string(buf));
		}
		//int a=234;
		//char intStr[4];
		//memset(intStr,0,4);
		//itoa(a,intStr,3);	
		//ֱ�ߵ�洢
		//head
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint[i].x);
		// 		//std::string str1 = std::string(buf);
		// 		//root["headX"].append(std::string(buf));
		// 		root["data"]["line_headX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint[i].y);
		// 		//root["headY"].append(std::string(buf));
		// 		root["data"]["line_headY"].append(std::string(buf));
		// 		//tail
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint[i].x);
		// 		//std::string str1 = std::string(buf);
		// 		//root["headX"].append(std::string(buf));
		// 		root["data"]["line_tailX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint[i].y);
		// 		//root["headY"].append(std::string(buf));
		// 		root["data"]["line_tailY"].append(std::string(buf));
		// 
		// 		//Բ��洢
		// 		//head
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint1[i].x);
		// 		root["data"]["circle_headX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint1[i].y);
		// 		root["data"]["circle_headY"].append(std::string(buf));
		// 		//tail
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint1[i].x);
		// 		root["data"]["circle_tailX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint1[i].y);
		// 		root["data"]["circle_tailY"].append(std::string(buf));
		// 
		// 		//arrow
		// 		//head
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint2[i].x);
		// 		root["data"]["arrow_headX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint2[i].y);
		// 		root["data"]["arrow_headY"].append(std::string(buf));
		// 		//tail
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint2[i].x);
		// 		root["data"]["arrow_tailX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint2[i].y);
		// 		root["data"]["arrow_tailY"].append(std::string(buf));
		// 
		// 		//ten
		// 		//head
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint3[i].x);
		// 		root["data"]["ten_headX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint3[i].y);
		// 		root["data"]["ten_headY"].append(std::string(buf));
		// 		//tail
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint3[i].x);
		// 		root["data"]["ten_tailX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint3[i].y);
		// 		root["data"]["ten_tailY"].append(std::string(buf));
		// 
		// 		//wavy
		// 		//head
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint4[i].x);
		// 		root["data"]["wavy_headX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint4[i].y);
		// 		root["data"]["wavy_headY"].append(std::string(buf));
		// 		//tail
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint4[i].x);
		// 		root["data"]["wavy_tailX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint4[i].y);
		// 		root["data"]["wavy_tailY"].append(std::string(buf));
		// 
		// 		//dash
		// 		//head
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint5[i].x);
		// 		root["data"]["dash_headX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_headPoint5[i].y);
		// 		root["data"]["dash_headY"].append(std::string(buf));
		// 		//tail
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint5[i].x);
		// 		root["data"]["dash_tailX"].append(std::string(buf));
		// 		memset(buf,0,10);
		// 		sprintf(buf,"%d",m_tailPoint5[i].y);
		// 		root["data"]["dash_tailY"].append(std::string(buf));
	}

	//ֱ�����  
	//std::cout << "FastWriter:" << std::endl;
	Json::FastWriter fw;
	//std::cout << fw.write(root) << std::endl << std::endl;

	//�������  
	//std::cout << "StyledWriter:" << std::endl;
	Json::StyledWriter sw;
	sw.write(root);
	//std::cout << sw.write(root) << std::endl << std::endl;

	//������ļ�  
	//std::ofstream os;
// 	CStdioFile file(cs,CFile::modeWrite|CFile::modeCreate);
// 	//os.open("f:\\aaa.json", std::ios::out | std::ios::app);
// 	//if (!os.is_open())
// 	//std::cout << "error��can not find or create the file which named \" demo.json\"." << std::endl;
// 	//AfxMessageBox(_T("warning"));
// 	//os << sw.write(root);
// 	//os.close();
// 	file.Seek(0, CFile::end);
// 	//stringתcstring
// 	std::string str = sw.write(root);
// 	CString cstr;
// 	cstr = G2U(str.c_str());
// 	//AfxMessageBox(cstr);
// 	//file.WriteString(cstr);
// 	file.Write(str.c_str(),cstr.GetLength()+1);
// 	file.Close();

	//������ļ�  
	std::ofstream os; //�ڴ浽�ļ�  д�ļ�
	//USES_CONVERSION;
	CString CS = cs;
	const char* cOpen = T2A(CS.GetBuffer(0));
	CS.ReleaseBuffer();	 
	os.open(cOpen, std::ios::out);
	os.seekp(0,std::ios::beg);
	string outStr = (sw.write(root).c_str());
	if (!os.is_open())
		AfxMessageBox(CString("��ʧ��:")+cs);
		//cout << "error��can not find or create the file which named \" demo.json\"." << endl;
	os << outStr.c_str();
	os.close();
}

//��ȡjson�ļ�
void CTFigureDlg:: readfireadFileJson(CString cs)
{
	using namespace std;
	Json::Reader reader;
	Json::Value root;

	//ת��
	USES_CONVERSION;
	const char* ccs = T2A(cs.GetBuffer(0));
	cs.ReleaseBuffer();

	// 	CStdioFile file(cs,CFile::modeRead);
	// 	//file.Seek(0, CFile::end);
	// 	CString mstring;
	// 	CString temp;
	// 	file.Seek(0, CFile::begin);
	// 	while(file.ReadString(temp))
	// 	{
	// 		mstring += temp;
	// 	}

	ifstream in(ccs);
	string line;
	string allLine;
	in.seekg(0,ios::beg);
	if(in) // �и��ļ�
	{
		while (getline (in, line)) // line�в�����ÿ�еĻ��з�
		{ 
			allLine = allLine + line;
		}
	}

	//AfxMessageBox(CString(allLine.c_str()));
	//AfxMessageBox(mstring);
	//char*  mmstring = new char[mstring.GetLength()];
	//file.Seek(0, CFile::begin);
	//file.Read(mmstring,mstring.GetLength());
	//char *buff = new char[file.GetLength()];
	//file.Read(buff,file.GetLength());
	//cstringתchar *
	//USES_CONVERSION;
	//const char* strbuf = T2A(mstring.GetBuffer(0));
	//mstring.ReleaseBuffer();
	//string strsss = strbuf;
	//CString cssstring ;
	//cssstring = strsss.c_str();
#if DEBUGS:
	AfxMessageBox(csstring);
#endif
	//Sleep(1);
	//���ļ��ж�ȡ����֤��ǰ�ļ���demo.json�ļ�  
	//std::ifstream in("F:\\Users\\zousijia\\Desktop\\data.json", std::ios::binary);
	//std::ifstream in;
	//in.open("F\\data.json");
	//in.clear();
	//if (!in.is_open())
	//{
	//	std::cout << "Error opening file\n";
	//	AfxMessageBox(_T("EERROR"));
	//	//return;
	//}
	//string inString = mmstring;
	//AfxMessageBox(CString(mmstring));
	//AfxMessageBox(CString(U2G(inString.c_str())));
	if (reader.parse(/*U2G(inString.c_str())*//*strbuf*/allLine, root))
	{


		//��ȡ���ڵ���Ϣ  
#if DEBUGS:
		AfxMessageBox(_T("success"));
#endif
		this->i = root["data"]["backToWhere"].asInt();
		//for(int i = 0; i<root["line_headX"]["line_headX"].size();i++)
		//TODO: ���ܻ�������˴�
		m_flagTracking = TRUE;
		char bufHeadX[8];
		char bufHeadY[8];
		char bufTailX[8];
		char bufTailY[8];
		////�����ĵ�ͼ
		int x = root["Lead"].asInt();
		//����ѡ�������
		//CString strCurrent(root["Lead"].asString().c_str());
		char tempBuf[5];
		sprintf_s(tempBuf,"%d",x);
		this->SetDlgItemTextW(IDC_COMBOXCHANGELEAD,CString(cLead[x-1]));
		m_strCurrentLead = CString(cLead[x-1]);
		char* cXmlFilename = new char[root["XmlFileName"].asString().length()+100] ;
		strcpy(cXmlFilename,U2G(root["XmlFileName"].asString().c_str()));
		//AfxMessageBox(CString(U2G(root["XmlFileName"].asString().c_str())));
		if(strlen(root["XmlFileName"].asString().c_str())>2)
		{
			m_cXmlFilePath = U2G(root["XmlFileName"].asString().c_str());
			LeadPaintJson(x,cXmlFilename);
		}
		delete[] cXmlFilename;

		//m_LeadCombox����ѡ��
		m_LeadCombox.SetCurSel(root["data"]["LeadCombox"].asInt());
		m_comboPattern.SetCurSel(root["data"]["PatternCombox"].asInt());
		//��ȡmms mm_mV
		m_CombommS.SetCurSel(root["data"]["mm_s"].asInt()); 
		OnCbnSelchangeCombomms();
		m_Combomm_mV.SetCurSel(root["data"]["mm_mV"].asInt()); 
		OnCbnSelchangeCombommmv();

		//��ȡ�ָ���λ��
		char bufN[3];
		for (int n=0;n<4;n++)
		{
			memset(bufN,0,3);
			sprintf(bufN,"%d",n);
			m_pPointFourLeft[n].y = root["data"]["3_4"][bufN][1].asInt(); 
			m_pPointFourLeft[n].x = root["data"]["3_4"][bufN][2].asInt() ;
			m_pPointFourRight[n].y = root["data"]["3_4"][bufN][3].asInt();
			m_pPointFourRight[n].x = root["data"]["3_4"][bufN][4].asInt();
		}
		for (int n=0;n<6;n++)
		{
			memset(bufN,0,3);
			sprintf(bufN,"%d",n);
			m_pPointSixLeft[n].y = root["data"]["5_6"][bufN][1].asInt();
			m_pPointSixLeft[n].x=root["data"]["5_6"][bufN][2].asInt() ;
			m_pPointSixRight[n].y=root["data"]["5_6"][bufN][3].asInt() ;
			m_pPointSixRight[n].x=root["data"]["5_6"][bufN][4].asInt() ;
		}
		for (int n=0;n<8;n++)
		{
			memset(bufN,0,3);
			sprintf(bufN,"%d",n);
			m_pPointEightLeft[n].y = root["data"]["7_8"][bufN][1].asInt();
			m_pPointEightLeft[n].x=root["data"]["7_8"][bufN][2].asInt() ;
			m_pPointEightRight[n].y=root["data"]["7_8"][bufN][3].asInt() ;
			m_pPointEightRight[n].x=root["data"]["7_8"][bufN][4].asInt() ;
		}
		//��ȡAVS
		for (int n=0;n<20/*sizeof(m_strAVS)/sizeof(m_strAVS[0])*/;n++)
		{
			m_strAVS[n] = root["strAVS"][n].asString().c_str();
		}
		//��ȡ��ͼ����
		for(int i = 0; i<this->i;i++)
		{
			for (int j=0;j<16;j++)
			{
				sprintf(bufHeadX,"%s%d","headX",j);
				sprintf(bufHeadY,"%s%d","headY",j);
				sprintf(bufTailX,"%s%d","tailX",j);
				sprintf(bufTailY,"%s%d","tailY",j);

				m_arrHeadPoint[j][i].x =atoi(root["data"][bufHeadX][i].asString().c_str());
				m_arrHeadPoint[j][i].y =atoi(root["data"][bufHeadY][i].asString().c_str());
				m_arrTailPoint[j][i].x =atoi(root["data"][bufTailX][i].asString().c_str());
				m_arrTailPoint[j][i].y =atoi(root["data"][bufTailY][i].asString().c_str());

			}

//			delete[] cXmlFilename;
			// 			m_headPoint[i].x = atoi(root["data"]["line_headX"][i].asString().c_str());//��
			// 			m_headPoint[i].y = atoi(root["data"]["line_headY"][i].asString().c_str());
			// 			m_tailPoint[i].x =  atoi(root["data"]["line_tailX"][i].asString().c_str());
			// 			m_tailPoint[i].y =  atoi(root["data"]["line_tailY"][i].asString().c_str());
			// 			m_headPoint1[i].x = atoi(root["data"]["circle_headX"][i].asString().c_str());//Բ ��
			// 			m_headPoint1[i].y = atoi(root["data"]["circle_headY"][i].asString().c_str());
			// 			m_tailPoint1[i].x = atoi(root["data"]["circle_tailX"][i].asString().c_str());
			// 			m_tailPoint1[i].y = atoi(root["data"]["circle_tailY"][i].asString().c_str());
			// 			//��ͷ
			// 
			// 			m_headPoint2[i].x = atoi(root["data"]["arrow_headX"][i].asString().c_str());
			// 			m_headPoint2[i].y = atoi(root["data"]["arrow_headY"][i].asString().c_str());
			// 			m_tailPoint2[i].x = atoi(root["data"]["arrow_tailX"][i].asString().c_str());
			// 			m_tailPoint2[i].y = atoi(root["data"]["arrow_tailY"][i].asString().c_str());
			// 
			// 			//TEN
			// 
			// 			m_headPoint3[i].x = atoi(root["data"]["ten_headX"][i].asString().c_str());
			// 			m_headPoint3[i].y = atoi(root["data"]["ten_headY"][i].asString().c_str());
			// 			m_tailPoint3[i].x = atoi(root["data"]["ten_tailX"][i].asString().c_str());
			// 			m_tailPoint3[i].y = atoi(root["data"]["ten_tailY"][i].asString().c_str());
			// 			//Wavy
			// 
			// 			m_headPoint4[i].x = atoi(root["data"]["wavy_headX"][i].asString().c_str());
			// 			m_headPoint4[i].y = atoi(root["data"]["wavy_headY"][i].asString().c_str());
			// 			m_tailPoint4[i].x = atoi(root["data"]["wavy_tailX"][i].asString().c_str());
			// 			m_tailPoint4[i].y = atoi(root["data"]["wavy_tailY"][i].asString().c_str());
			// 			//Dash
			// 			m_headPoint5[i].x = atoi(root["data"]["dash_headX"][i].asString().c_str());
			// 			m_headPoint5[i].y = atoi(root["data"]["dash_headY"][i].asString().c_str());
			// 			m_tailPoint5[i].x = atoi(root["data"]["dash_tailX"][i].asString().c_str());
			// 			m_tailPoint5[i].y = atoi(root["data"]["dash_tailY"][i].asString().c_str());
		}
		Invalidate(1);
		//string name = root["name"].asString();
		//int age = root["age"].asInt();
		//string sex = root["sex"].asString();

		//cout << "My name is " << name << endl;
		//cout << "I'm " << age << " years old" << endl;
		//cout << "I'm a " << sex << endl;

		////��ȡ�ӽڵ���Ϣ  
		//string friend_name = root["friends"]["friend_name"].asString();
		//int friend_age = root["friends"]["friend_age"].asInt();
		//string friend_sex = root["friends"]["friend_sex"].asString();

		//cout << "My friend's name is " << friend_name << endl;
		//cout << "My friend's sex is "<<friend_sex << endl;
		//cout << "My friend is " << friend_age << " years old" << endl;

		////��ȡ������Ϣ  
		//cout << "Here's my hobby:" << endl;
		//for (unsigned int i = 0; i < root["hobby"].size(); i++)
		//{
		//	string ach = root["hobby"][i].asString();
		//	cout << ach << '\t';
		//}
		//cout << endl;

		//cout << "Reading Complete!" << endl;
	}
	 	else
	 	{
	 		cout << "parse error\n" << endl;
	 		AfxMessageBox(CString("�ļ��򿪴���:")+cs);
	 	}
	//file.Close();
	//delete[] buff;
	in.close();

}

void CTFigureDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



//TODO: ������ݲ�ͬ�������⣬����취���ڻ滭ʱɾ��ͬ�����ݣ�������������һ��
void CTFigureDlg::OnBnClickedRemake()
{
	// 	//AfxMessageBox(_T("����"));
	// 	this->i++;
	// 	this->m_bChangeFlag = TRUE;
	// 	//DeleteDataPoint();
	// 	if(m_tailPoint5[i]==CPoint(0,0)&&m_tailPoint4[i]==CPoint(0,0)&&m_tailPoint3[i]==CPoint(0,0) \
	// 		&&m_tailPoint2[i]==CPoint(0,0)\
	// 		&&m_tailPoint1[i]==CPoint(0,0)&&m_tailPoint[i]==CPoint(0,0))
	// 	{
	// 		AfxMessageBox(_T("��������"));
	// 		i--;
	// 		return ;
	// 	}
	// 
	// 	this->Invalidate(1);
	ClearPoint();
	this->i = 0;

	//��������
	for (int n = 0;n<m_nWord;n++)
	{
		delete m_vecEdit[n];
		m_headPointText[n] = 0;
		m_tailPointText[n] = 0;
	}
	m_vecEdit.resize(0);
	this ->m_nWord = 0 ;
	this->Invalidate(1);
}

// void CTFigureDlg::DrawSubline(CPoint point)
// {
// 	throw std::logic_error("The method or operation is not implemented.");
// }
// BOOL CTFigureDlg::PreCreateWindow(CREATESTRUCT& cs) 
// { 	
// 	// TODO:    �ڴ����ר�ô����/����û��� 
// 	cs.style &= ~FWS_ADDTOTITLE;//�ɸı䴰�ڱ��� 
// 	cs.style &=    ~WS_MAXIMIZEBOX;//������󻯰�ť 	
// 	cs.style &= ~WS_THICKFRAME;//�������ı䴰�ڴ�С��Ϊ
// 	cs.style &= ~WS_CAPTION; 	
// 	return CDialogEx::PreCreateWindow(cs); 
// }

//�����л�
void CTFigureDlg::OnCbnSelchangeComboxchangelead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_bChangeLead = TRUE;
	CString strCurrent;
	this->GetDlgItemTextW(IDC_COMBOXCHANGELEAD,strCurrent);
	//OnBnClickedOpenfilebutton();
	CString strChoosed;
	m_LeadCombox.GetLBText(m_LeadCombox.GetCurSel(),strChoosed);
	m_strCurrentLead = strChoosed;
	//AfxMessageBox(strChoosed);
	LeadPaint();
	// 	UpdateData();
	// 	CString strCurrent;
	// 	this->GetDlgItemTextW(IDC_COMBOXCHANGELEAD,strCurrent);
	// 	//OnBnClickedOpenfilebutton();
	//  	AfxMessageBox(strCurrent);
	// 	AfxMessageBox(_T("2"));

}
//���Ƶ���
void CTFigureDlg::LeadPaint()
{
#if DEBUGS:
	AfxMessageBox(m_cstrFileLocation);
#endif
	CString strCurrent;
	//m_LeadCombox.GetLBText(m_LeadCombox.GetCurSel(),strCurrent);
	strCurrent = m_strCurrentLead;    
	//AfxMessageBox(m_strCurrentLead);
	//m_Lead =_ttoi(strCurrent)
	USES_CONVERSION;
	char* pathName = T2A(m_cstrFileLocation.GetBuffer(0));
	m_cstrFileLocation.ReleaseBuffer();
	//AfxMessageBox(m_cstrFileLocation);
	std::string strFilename = pathName;
	//�õ��ļ���׺
	std::string suffixStr = strFilename.substr(strFilename.find_last_of('.') + 1);
	//�ļ�·����ȥ��׺��
	//std::string suffixStr = strFilename.substr(0,strFilename.find_last_of('.') + 1);
	//CString cstr1;
	//cstr1 = suffixStr.c_str();
	//AfxMessageBox(cstr1);
	//MessageBox();
	//�����xml�ļ�
	if(suffixStr == "xml")
	{
#if DEBUGS:
		AfxMessageBox(CString(suffixStr.c_str()));//Sleep(1);
#endif	
		// 		TiXmlElement pTempEle = SelectElementByName(pathName,"digits", 1,_ttoi(strCurrent)-1);//תint
		// 		m_bChangeLead = FALSE;
		// 		//Sleep(1);
		// 		//printf("find the Name : %s, Text = %s\n", pTempEle.Value(), pTempEle.GetText());
		// 		//Sleep(2);
		// 		const char* str = pTempEle.GetText();
		// 		std::vector<CString> vecString;
		// 		std::vector<int> vecNum;
		// 		m_vecPoint.resize(0);
		// 		char tempstr[8];
		// 		char* p = tempstr;
		// 		memset(tempstr,0,8);
		// 		//������
		// 		//std::vector<CPoint>  vecPoint;
		// 		//���±��X
		// 		double nPointX = 20+100+50 ;
		// 		//Sleep(2);
		// 		for (unsigned int i=0;i<strlen(str)+1;i++)
		// 		{	
		// 
		// 			if((*(str+i) != ' ')&&(*(str+i) != '\0') )
		// 			{	
		// 				*p++ = *(str+i);
		// 			}
		// 			else
		// 			{
		// 				*p++ ='\0';
		// 				vecString.push_back(CString(tempstr));
		// 				//MessageBox(vecString.back());
		// 				m_vecPoint.push_back(CPoint(d_round(nPointX),d_round(( 4200-(atoi(tempstr)+4200))*2.52*0.*m_nMmmV/10+250) ));   //��ŵ�λ
		// 				nPointX = nPointX + 0.1554*m_nMmS/25;/*0.18 ;*//*1554/10000*/ /*0.0250.16098*/
		// 				vecNum.push_back(atoi(tempstr));
		// 				memset(tempstr,0,8);
		// 				p = tempstr;
		// 			}
		// 		}
		// 		//Sleep(3);
		// 		char nnn[10];                
		// 		memset(nnn,0,10);
		// 		//sprintf(nnn,"min:%d",FindMin(vecNum));
		// 		sprintf(nnn,"min:%d",m_vecPoint.size());
#if DEBUGS:
		//AfxMessageBox(CString(nnn));
#endif
		CString strCurrent;
		strCurrent = m_strCurrentLead;
		/*m_LeadCombox.GetLBText(m_LeadCombox.GetCurSel(),strCurrent);*/

		USES_CONVERSION;
		const char* strbuf = T2A(strCurrent.GetBuffer(0));
		strCurrent.ReleaseBuffer();
		//int x = atoi(strbuf);
		int x = m_LeadCombox.GetCurSel()+1;
		char temp[1000];
		strcpy_s(temp,m_cXmlFilePath.c_str());
		LeadPaintJson(x,temp);	
		//this->Invalidate(0);
	}
	else if(suffixStr == "json")
	{
		////�����ĵ�ͼ
		CString strCurrent;
		strCurrent = m_strCurrentLead;
		/*m_LeadCombox.GetLBText(m_LeadCombox.GetCurSel(),strCurrent);*/

		USES_CONVERSION;
		const char* strbuf = T2A(strCurrent.GetBuffer(0));
		strCurrent.ReleaseBuffer();
		int x = m_LeadCombox.GetCurSel()+1;
		char temp[1000];
		strcpy_s(temp,m_cXmlFilePath.c_str());
		LeadPaintJson(x,temp);		
	}
	this->Invalidate();
}

//��json�ļ����ص���
void CTFigureDlg::LeadPaintJson(int x,char* cXmlFilename )
{
	//AfxMessageBox(m_cstrFileLocation);
	CString strCurrent;
	this->GetDlgItemTextW(IDC_COMBOXCHANGELEAD,strCurrent);
	//m_Lead =_ttoi(strCurrent)
	USES_CONVERSION;
	char* pathName = T2A(m_cstrFileLocation.GetBuffer(0));
	m_cstrFileLocation.ReleaseBuffer();
	std::string strFilename = pathName;
	//�õ��ļ���׺
	std::string suffixStr = strFilename.substr(strFilename.find_last_of('.') + 1);
	//�ļ�·����ȥ��׺��
	//std::string suffixStr = strFilename.substr(0,strFilename.find_last_of('.') + 1);
	//CString cstr1;
	//cstr1 = suffixStr.c_str();
	//AfxMessageBox(cstr1);
	//MessageBox();
	//�����xml�ļ�

	TiXmlElement pTempEle = SelectElementByName(cXmlFilename,"digits", 1,x-1);
	//m_bChangeLead = FALSE;
	//Sleep(1);
	//printf("find the Name : %s, Text = %s\n", pTempEle.Value(), pTempEle.GetText());
	//Sleep(2);
	const char* str = pTempEle.GetText();
	std::vector<CString> vecString;
	std::vector<int> vecNum;
	m_vecPoint.resize(0);
	char tempstr[8];
	char* p = tempstr;
	memset(tempstr,0,8);
	//������
	//std::vector<CPoint>  vecPoint;
	//���±��X
	double nPointX = 20.0+150 ;
	//Sleep(2);
	//AfxMessageBox(CString(str));
	double n_IncreaseY = 0.009*m_nMmmV/10;
	double n_IncreaseX = 0.1554*m_nMmS/25;
	if(CString(str)!=CString(""))
	{
		for (unsigned int i=0;i<strlen(str)+1;i++)
		{	

			if((*(str+i) != ' ')&&(*(str+i) != '\0'))
			{	
				*p++ = *(str+i);
			}
			else
			{
				*p++ ='\0';
				vecString.push_back(CString(tempstr));
				//MessageBox(vecString.back());
				m_vecPoint.push_back(CPoint(d_round(nPointX),d_round((4200-(atoi(tempstr)+4200))*n_IncreaseY+250) ));   //��ŵ�λ
				nPointX = nPointX + n_IncreaseX;/*0.18 ;*//*1554/10000*/ /*0.0250.16098*/
				vecNum.push_back(atoi(tempstr));
				memset(tempstr,0,8);
				p = tempstr;
			}
		}
		//Sleep(3);
		char nnn[10];
		memset(nnn,0,10);
		//sprintf(nnn,"min:%d",FindMin(vecNum));
		sprintf(nnn,"min:%d",m_vecPoint.size());
#if DEBUGS:
		AfxMessageBox(CString(nnn));
#endif
		this->Invalidate(0);

	}
}

void CTFigureDlg::OnBnClicked3arrow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDraw3arrow = !m_bDraw3arrow;   //ֱ�߻��Ʊ��
	if(m_bDraw3arrow == TRUE)
	{	
		ChangeFlag(&m_bDraw3arrow);
		//AfxMessageBox(_T("��ѡ����m_bDraw3arrow"));
	}
}


void CTFigureDlg::OnBnClickedDrawt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawT = !m_bDrawT;   //ֱ�߻��Ʊ��
	if(m_bDrawT == TRUE)
	{	
		ChangeFlag(&m_bDrawT);
		//AfxMessageBox(_T("��ѡ����Drawt"));
	}
}


void CTFigureDlg::OnBnClicked2arrow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDraw2arrow = !m_bDraw2arrow;   //ֱ�߻��Ʊ��
	if(m_bDraw2arrow == TRUE)
	{	
		ChangeFlag(&m_bDraw2arrow);
		//AfxMessageBox(_T("��ѡ����m_bDraw2arrow"));
	}
}


void CTFigureDlg::OnBnClickedButtonoo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawO = !m_bDrawO;   //ֱ�߻��Ʊ��
	if(m_bDrawO == TRUE)
	{	
		ChangeFlag(&m_bDrawO);
		//AfxMessageBox(_T("��ѡ����m_bDrawO"));
	}
}


void CTFigureDlg::OnBnClickedButtonttupdown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawTupdown = !m_bDrawTupdown;   //ֱ�߻��Ʊ��
	if(m_bDrawTupdown == TRUE)
	{	
		ChangeFlag(&m_bDrawTupdown);
		//AfxMessageBox(_T("��ѡ����m_bDrawTupdown"));
	}
}


void CTFigureDlg::OnBnClickedDrawtenten()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//Sleep(2020);
	m_bDrawtenten = !m_bDrawtenten;   //ֱ�߻��Ʊ��
	if(m_bDrawtenten == TRUE)
	{	
		ChangeFlag(&m_bDrawtenten);
		//AfxMessageBox(_T("��ѡ����m_bDrawtenten"));
	}
}
//���ı�����
CEdit* CTFigureDlg::LongTextInput(CRect rect)
{
	//static int i = 0 ;
	CString str(_T("��������"));
	CEdit* pEdit  = new CEdit;
	pEdit->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP |WS_BORDER|ES_LEFT|ES_AUTOHSCROLL|\
		ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL |WS_HSCROLL| WS_VSCROLL, rect, this, ID_EDIT1+ m_nWord);
	//pEdit->Create(ES_LEFT|ES_AUTOHSCROLL|WS_BORDER|WS_VISIBLE|WS_CHILD|WS_TABSTOP, rect, this, ID_EDIT1+ m_nWord);
	//pEdit->ModifyStyleEx(WS_HSCROLL|ES_AUTOHSCROLL|ES_WANTRETURN,0);
	pEdit->SetWindowText(str);
	//i++;
	//vecEdit.push_back(pEdit);
	return pEdit;
}
//���ı�����
void CTFigureDlg::ShortTextInput(CRect rect)
{
	static int i = 0 ;
	CString str(_T("��������"));
	CEdit* pEdit  = new CEdit;
	pEdit->Create(ES_LEFT|ES_AUTOHSCROLL|WS_BORDER|WS_VISIBLE|WS_CHILD|WS_TABSTOP, \
		rect, this,  ID_EDIT2 + i);
	pEdit->ModifyStyleEx(0, WS_EX_CLIENTEDGE|WS_EX_STATICEDGE, 0);
	pEdit->SetWindowText(str);
	i++;
	vecEdit.push_back(pEdit);
}
//������һ���ļ������
void CTFigureDlg::CleanEdit()
{
	delete vecEdit.back();
	vecEdit.pop_back();
}
void CTFigureDlg::OnBnClickedDrawtententen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawtententen = !m_bDrawtententen;   //ֱ�߻��Ʊ��
	if(m_bDrawtententen == TRUE)
	{	
		ChangeFlag(&m_bDrawtententen);
		//AfxMessageBox(_T("��ѡ����m_bDrawtententen"));

	}
}


void CTFigureDlg::OnBnClickedButtonword()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//AfxMessageBox(_T("����"));
	m_bDrawText = !m_bDrawText;
	if(m_bDrawText == TRUE) 
	{
		//��������ͼ�������Ϊfalse
		ChangeFlag(&m_bDrawText);
		//this->Invalidate(1);
		//AfxMessageBox(_T("��ѡ����WAVY"));
	}
	this->Invalidate(0);


}


void CTFigureDlg::OnBnClickedButton3t()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDraw3T = !m_bDraw3T;   //ֱ�߻��Ʊ��
	if(m_bDraw3T == TRUE)
	{	
		ChangeFlag(&m_bDraw3T);
		//AfxMessageBox(_T("��ѡ����m_bDraw2arrow"));
	}
}


void CTFigureDlg::OnBnClickedButtontt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawTT = !m_bDrawTT;   //ֱ�߻��Ʊ��
	if(m_bDrawTT == TRUE)
	{	
		ChangeFlag(&m_bDrawTT);
		//AfxMessageBox(_T("��ѡ����m_bDraw2arrow"));
	}
}


void CTFigureDlg::OnBnClickedButtonsave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	USES_CONVERSION;
	char* pathName = T2A(m_cstrFileLocation.GetBuffer(0));
	m_cstrFileLocation.ReleaseBuffer();
	std::string strFilename = pathName;
	//�õ��ļ���׺
	std::string suffixStr = strFilename.substr(strFilename.find_last_of('.') + 1);

	//�����json�ļ�
	if(suffixStr == "json")
	{
		writeFileJson(m_cstrFileLocation);
		//AfxMessageBox(_T("����ɹ�"));
		this->m_bChangeFlag = FALSE;

		//����jpg
		USES_CONVERSION;
		char* pathName = T2A(m_cstrFileLocation.GetBuffer(0));
		m_cstrFileLocation.ReleaseBuffer();
		std::string strFilename = pathName;
		std::string suffixStr = strFilename.substr(0,strFilename.find_last_of('.') + 1) ;
		CString cstr1;
		cstr1 = suffixStr.c_str();
		CString strFileImg  = cstr1 + CString("bmp");
#if DEBUGS:
		AfxMessageBox(strFileImg);
#endif
		CRect rect(40,40+140,1900,900);
		//AfxMessageBox(CString("BMP������"));
		long t1=GetTickCount();//����ο�ʼǰȡ��ϵͳ����ʱ��(ms) ����
		if(!SaveBmp(CaptureScreen(&rect),strFileImg))  
		{
			AfxMessageBox(_T("����ͼƬʧ��"));
		}
		CString strr;
		long t2=GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms) ����
		strr.Format(_T("time:%dms"),t2-t1);//ǰ��֮� ��������ʱ�� ����
		//AfxMessageBox(strr);//��ȡϵͳ����ʱ�� ��

	}
	else if(suffixStr == "xml") 
	{

		USES_CONVERSION;
		char* pathName = T2A(m_cstrFileLocation.GetBuffer(0));
		m_cstrFileLocation.ReleaseBuffer();
		std::string strFilename = pathName;
		std::string suffixStr = strFilename.substr(0,strFilename.find_last_of('.') + 1) ;
		CString Path;
		Path = CString(suffixStr.c_str()) + CString("json");
		BOOL rec = PathFileExists(Path);
		if(rec)
		{
			//����
			int ret = AfxMessageBox(CString(Path)+CString("��ͼ�����ļ��Ѵ���,ȷ���滻��"),MB_OKCANCEL);
			if(ret == IDCANCEL)
			{
				return ;
			}
			else
			{   
				m_cstrFileLocation = Path;
				writeFileJson(Path);
				//AfxMessageBox(_T("����ɹ�"));
				this->m_bChangeFlag = FALSE;
			}
		}
		else
		{
			// ������
			//д��json�ļ�
			m_cstrFileLocation = Path;
			writeFileJson(Path);
			//AfxMessageBox(_T("����ɹ�"));
			this->m_bChangeFlag = FALSE;
		}
		//����jpg	
		//USES_CONVERSION;
		CString cstr1;
		cstr1 = suffixStr.c_str();
		CString strFileImg  = cstr1 + CString("bmp");
#if DEBUGS:
		AfxMessageBox(strFileImg);
#endif
		CRect rect(40,40+140,1900,900);
		if(!SaveBmp(CaptureScreen(&rect),strFileImg))  
		{
			AfxMessageBox(_T("�洢bmp�ļ�ʧ��"));
		}
		//file.Seek(0, CFile::end);
		//file.WriteString(strTemp);
		//file.Close();

		Invalidate(1);
	}
	else
	{
		int ret = AfxMessageBox(_T("��ǰ�޿����ļ�,\n\r�����Ϊ.json�ļ�") ,MB_OKCANCEL);
		if(ret == IDCANCEL)
		{
			return ;
		}
		else
		{
			OnBnClickedButton2();//���Ϊ
		}

	}
}




void CTFigureDlg::OnBnClickedButtonnline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bdrawNline = !m_bdrawNline;   //ֱ�߻��Ʊ��
	if(m_bdrawNline == TRUE)
	{	
		ChangeFlag(&m_bdrawNline);
		//AfxMessageBox(_T("��ѡ����m_bdrawNline"));
	}

}

//�ж��Ƿ��ڷ�Χ��
bool CTFigureDlg::IsinRange(CPoint point ,CPoint headPoint,CPoint tailPoint,int range )
{
	//���������wavy��
	if( (  (headPoint.x-range < point.x && headPoint.x+range > point.x) //TODO:��������������ֵΪ��������λ����һ��
		&&  (headPoint.y-range < point.y && headPoint.y+range > point.y ))
		/*&&m_bForbidSizeAll == FALSE*/ || ((tailPoint.x-range < point.x && tailPoint.x+range > point.x)
		&&(tailPoint.y-range < point.y && tailPoint.y+range > point.y)) 
		/*&&m_bForbidSizeAll == FALSE*/ || (((tailPoint.x+headPoint.x)/2-range < point.x \
		&& (tailPoint.x+headPoint.x)/2+range > point.x)
		&&((tailPoint.y+headPoint.y)/2-range < point.y && (tailPoint.y+headPoint.y)/2+range > point.y 
		/*&&m_bForbidSizeAll == FALSE*/)) )
	{
		//��ջ��ƹ켣�Ļ���
		Temp = CPoint(0,0);
		Temp2 = CPoint(0,0);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


//�������//��¼�±�
void CTFigureDlg::IsinWhere(int nWhere,int j)
{
	m_iFallinWhere = nWhere;
	SetClassLong(this->GetSafeHwnd(),
		GCL_HCURSOR , 
		(LONG)LoadCursor(NULL , IDC_SIZEALL));//�ķ����ͷ
	//���ҵ�������� m_bSizeAll
	m_bSizeAll = TRUE;
	/*m_bForbidSizeAll = TRUE;*/
	m_iDragFlag = j;//��¼�±�
	//��¼��Ӧ����������

}
/*static CPoint tempDrag ;*/
void CTFigureDlg::IsDrawWhatAdd(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy)
{
	// 	if (tempDrag.x != m_dragPoint.x)
	// 	{
	// 		Temp = CPoint(0,0);
	// 		Temp2 = CPoint(0,0);
	// 	}
	// 	else tempDrag = m_dragPoint;
	if(abs(m_dragPoint.x-headPoint[m_iDragFlag].x)<10&&abs(m_dragPoint.y-headPoint[m_iDragFlag].y)<10)
	{			
		m_FlagPointL.x = nDx + m_FlagPointL.x; 
		m_FlagPointL.y = nDy + m_FlagPointL.y;
	}

	else if(abs(m_dragPoint.x-tailPoint[m_iDragFlag].x)<10&&abs(m_dragPoint.y-tailPoint[m_iDragFlag].y)<10)
	{
		m_FlagPointR.x = nDx + m_FlagPointR.x;
		m_FlagPointR.y = nDy + m_FlagPointR.y;
	}
	else
	{
		m_FlagPointL.x = nDx + m_FlagPointL.x; 
		m_FlagPointL.y = nDy + m_FlagPointL.y;
		m_FlagPointR.x = nDx + m_FlagPointR.x;
		m_FlagPointR.y = nDy + m_FlagPointR.y;  
	}
}
void CTFigureDlg::IsDrawWhatSub(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy)
{
	if(abs(m_dragPoint.x-headPoint[m_iDragFlag].x)<10&&abs(m_dragPoint.y-headPoint[m_iDragFlag].y)<10)
	{			
		m_FlagPointL.x =  m_FlagPointL.x - nDx ; 
		m_FlagPointL.y =   m_FlagPointL.y-nDy;
	}

	else if(abs(m_dragPoint.x-tailPoint[m_iDragFlag].x)<10&&abs(m_dragPoint.y-tailPoint[m_iDragFlag].y)<10)
	{
		m_FlagPointR.x =   m_FlagPointR.x -nDx;
		m_FlagPointR.y =  m_FlagPointR.y -nDy ;	
	}
	else
	{
		m_FlagPointL.x =  m_FlagPointL.x - nDx ; 
		m_FlagPointL.y =   m_FlagPointL.y-nDy;
		m_FlagPointR.x =   m_FlagPointR.x -nDx;
		m_FlagPointR.y =  m_FlagPointR.y -nDy ;	

	}
}
void CTFigureDlg::IsDrawWhat(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy)
{
	if(abs(m_dragPoint.x-headPoint[m_iDragFlag].x)<10&&abs(m_dragPoint.y-headPoint[m_iDragFlag].y)<10)
	{			
		headPoint[m_iDragFlag].x = headPoint[m_iDragFlag].x + nDx;
		headPoint[m_iDragFlag].y = headPoint[m_iDragFlag].y + nDy;
	}
	// 			else if(abs(m_dragPoint.x-abs(m_headPoint4[m_iDragFlag].x -m_tailPoint4[m_iDragFlag].x)/2)<10 \
	// 				/*&& abs(m_dragPoint.y-abs(m_headPoint4[m_iDragFlag].y -m_tailPoint4[m_iDragFlag].y)/2)<10*/)
	// 			{
	// 				//AfxMessageBox(_T("vv"));
	// 				m_headPoint4[m_iDragFlag].x = m_headPoint4[m_iDragFlag].x + nDx;
	// 				m_headPoint4[m_iDragFlag].y = m_headPoint4[m_iDragFlag].y + nDy;
	// 				m_tailPoint4[m_iDragFlag].x = m_tailPoint4[m_iDragFlag].x + nDx;
	// 				m_tailPoint4[m_iDragFlag].y = m_tailPoint4[m_iDragFlag].y + nDy; 
	// 			}
	else if(abs(m_dragPoint.x-tailPoint[m_iDragFlag].x)<10&&abs(m_dragPoint.y-tailPoint[m_iDragFlag].y)<10)
	{
		tailPoint[m_iDragFlag].x = tailPoint[m_iDragFlag].x + nDx;
		tailPoint[m_iDragFlag].y = tailPoint[m_iDragFlag].y + nDy;
	}
	else
	{
		headPoint[m_iDragFlag].x = headPoint[m_iDragFlag].x + nDx;
		headPoint[m_iDragFlag].y = headPoint[m_iDragFlag].y + nDy;
		tailPoint[m_iDragFlag].x = tailPoint[m_iDragFlag].x + nDx;
		tailPoint[m_iDragFlag].y = tailPoint[m_iDragFlag].y + nDy; 
	}
}

void CTFigureDlg::IsDrawWhatCircle(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy)
{

	{
		headPoint[m_iDragFlag].x = headPoint[m_iDragFlag].x + nDx;
		headPoint[m_iDragFlag].y = headPoint[m_iDragFlag].y + nDy;
		tailPoint[m_iDragFlag].x = tailPoint[m_iDragFlag].x + nDx;
		tailPoint[m_iDragFlag].y = tailPoint[m_iDragFlag].y + nDy; 
	}
}



void CTFigureDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(i==0)
	{ 
		AfxMessageBox(_T("�޿ɳ���ͼ��"));
		/*		this->Invalidate(1);    //��������Ϊ1��ȫ��ˢ��*/
		CPoint left1(0,0),right1(10,10); 
		InvalidateRect(CRect(left1,right1),0);//ʹ�̶�������Ч�ػ�   
		UpdateWindow();
	}
	else
	{
		i--;
		// 		if(m_bDrawLine == TRUE) 
		// 		{
		// 			delete vecEdit.back();
		// 			vecEdit.pop_back();
		// 		}
		this->m_bChangeFlag = TRUE;
		DeleteDataPoint();
		CPoint left1(15+25,300),right1(1850,850); 
		InvalidateRect(CRect(left1,right1),0);//ʹ�̶�������Ч�ػ�   
		UpdateWindow();

	}
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CTFigureDlg::OnXButtonDblClk(UINT nFlags, UINT nButton, CPoint point)
{
	// �ù���Ҫ��ʹ�� Windows 2000 ����߰汾��
	// ���� _WIN32_WINNT �� WINVER ���� >= 0x0500��
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵxXXXXXXX
	CDialogEx::OnXButtonDblClk(nFlags, nButton, point);
}


void CTFigureDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->Invalidate(1);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


// void CTFigureDlg::OnEnChangeEdit1()
// {
// 	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
// 	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
// 	// ���������� CRichEditCtrl().SetEventMask()��
// 	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
// 	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// 	//AfxMessageBox(_T("1"));
// 	CString strCurrent;
// 	this->GetDlgItemTextW(IDC_EDIT1,strCurrent);  //��ȡ�ı����������
// 	AfxMessageBox(strCurrent);
// }


void CTFigureDlg::OnCbnSelchangeCombox1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//AfxMessageBox(_T("1"));
	OnBnClickedStartbutton();
	//this->Invalidate(0);
}


// void CTFigureDlg::OnEnChangeEditaV()
// {
// 	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
// 	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
// 	// ���������� CRichEditCtrl().SetEventMask()��
// 	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
// 
// 	// TODO:  �ڴ���ӿؼ�֪ͨ����������
// }

vector<string> split(const string &str,const string &pattern)
{
	//const char* convert to char*
	char * strc = new char[strlen(str.c_str())+1];
	strcpy(strc, str.c_str());
	vector<string> resultVec;
	char* tmpStr = strtok(strc, pattern.c_str());
	while (tmpStr != NULL)
	{
		resultVec.push_back(string(tmpStr));
		tmpStr = strtok(NULL, pattern.c_str());
	}

	delete[] strc;

	return resultVec;
}



void CTFigureDlg::OnEnChangeEditavs()
{
	CString strCurrent;
	this->GetDlgItemTextW(IDC_EDITAVS,strCurrent);  //��ȡ�ı����������
	//AfxMessageBox(strCurrent);
	USES_CONVERSION;
	const char* strbuf = T2A(strCurrent.GetBuffer(0));
	strCurrent.ReleaseBuffer();
	string str(strbuf); 
	vector<string> vecstr = split(str,";");
	// 	for (vector<string>::iterator it = vecstr.begin();it !=vecstr.end();it++)
	// 	{
	// 
	// 	}
	for (int n=0;n<20;n++)
	{
		m_strAVS[n] = "";
	}
	for(unsigned int n = 0; n < vecstr.size(); ++n)
	{
		m_strAVS[n]= vecstr[n].c_str();
	}
	this->Invalidate(0);
	// 	for (int n=0;n<3;n++)
	// 	{
	// 		AfxMessageBox(m_strAVS[n]);
	// 	}


}


//void CTFigureDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	this->Invalidate(1);
//	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
//}


void CTFigureDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
#if DEBUGS:
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC pDC(this);
	int iVERTSIZE=pDC.GetDeviceCaps(VERTSIZE); // �õ���ǰ��ʾ�豸�Ĵ�ֱ��С�����ף�
	int iLOGPIXELSY=pDC.GetDeviceCaps(LOGPIXELSY); // �õ���ǰ��ʾ�豸�Ĵ�ֱ��λӢ��������
	int iLOGPIXELSX=pDC.GetDeviceCaps(LOGPIXELSX); // �õ���ǰ��ʾ�豸�Ĵ�ֱ��λӢ��������
	int iHORZSIZE=pDC.GetDeviceCaps(HORZSIZE); // �õ���ǰ��ʾ�豸��ˮƽ��С�����ף�
	int iHORZRES=pDC.GetDeviceCaps(HORZRES); // �õ���ǰ��ʾ�豸��ˮƽ������
	int iVERTRES = pDC.GetDeviceCaps(VERTRES);//��ֱ��������
	double res = (double)iHORZSIZE/(double)iHORZRES;
	double res1 = (double)iVERTSIZE/(double)iVERTRES;


	double scaleX = 254.0/(double)GetDeviceCaps(pDC.m_hAttribDC,LOGPIXELSX)*10;
	double scaleY = 254.0/(double)GetDeviceCaps(pDC.m_hAttribDC, LOGPIXELSY)*10;
	CString str;
	// ����һ�������豸��λ���ڶ���mm

	str.Format(_T("scaleX %.4f"),scaleX);
	AfxMessageBox(str);
	str.Format(_T("scaleY %.4f"),scaleY);
	AfxMessageBox(str);
	str.Format(_T("res %.4f"),res);
	AfxMessageBox(str);
	str.Format(_T("res1 %.4f"),res1);
	AfxMessageBox(str);

	str.Format(_T("iVERTSIZE=%d"),iVERTSIZE);
	AfxMessageBox(str);
	str.Format(_T("iLOGPIXELSY = %d"),iLOGPIXELSY);
	AfxMessageBox(str);
	str.Format(_T("iLOGPIXELSX = %d"),iLOGPIXELSX);
	AfxMessageBox(str);
	int nScreenWidth, nScreenHeight;  
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);  
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	str.Format(_T("nScreenWidth=%d"),nScreenWidth);
	AfxMessageBox(str);
	str.Format(_T("nScreenHeight = %d"),nScreenHeight);
	AfxMessageBox(str);
	str.Format(_T("iHORZSIZE = %d"),iHORZSIZE);
	AfxMessageBox(str);
	str.Format(_T("iVERTSIZE = %d"),iVERTSIZE);
	AfxMessageBox(str);																																		
	str.Format(_T("ˮƽ������ĿiHORZRES = %d"),iHORZRES);
	AfxMessageBox(str);
#endif
	this->Invalidate(1);
	// 	CPoint left1(40,300),right1(1800,850); 
	// 	InvalidateRect(CRect(left1,right1));//ʹ�̶�������Ч�ػ�   
	// 	UpdateWindow();
	CDialogEx::OnMButtonDown(nFlags, point);
}

//���ƾ����ı�
void CTFigureDlg::DrawDistenceText(CPoint* headPoint)
{
	CClientDC dc(this);
	double nDistance;
	char tem[10];
	dc.SetBkMode(TRANSPARENT);//����͸��
	LOGFONT lf; //�߼���
	::ZeroMemory(&lf, sizeof(lf));//���ڴ棬::���Ե���API����
	lf.lfHeight = 80;//9����
	lf.lfWeight =  FW_SEMIBOLD;//���
	lf.lfItalic = TRUE;//б��
	::lstrcpy(lf.lfFaceName, TEXT("Times New Roman"));
	CFont font2;
	font2.CreatePointFontIndirect(&lf);
	dc.SelectObject(&font2);
	//���ƾ����ı�
	vector<CPoint> vecPointTemp;
	for (int n=0;n<this->i;n++)
	{
		vecPointTemp.push_back(headPoint[n]);
	}
	//����
	std::sort(vecPointTemp.begin(),vecPointTemp.end(),cmp);
	int k=0;
	for (int n=0;n<this->i-1;n++)
	{
		if (vecPointTemp[n].x != 0)
		{
			nDistance = (vecPointTemp[n+1].x - vecPointTemp[n].x)*0.1609*(25.0/m_nMmS);
			memset(tem,0,10);
			sprintf(tem,"%dms",d_round(nDistance*40));
			CString strDistance(tem);
			dc.TextOutW( (vecPointTemp[n].x+vecPointTemp[n+1].x)/2 - 20,vecPointTemp[n+1].y - 10 -12,strDistance);
		}
	}
}

void CTFigureDlg::OnBnClickedCircleline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bDrawCircleLine = !m_bDrawCircleLine;   //ֱ�߻��Ʊ��
	if(m_bDrawCircleLine == TRUE)
	{	
		ChangeFlag(&m_bDrawCircleLine);
#if DEBUGS:
		AfxMessageBox(_T("��ѡ����m_bDrawCircleLine"));
#endif
	}
}


void CTFigureDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if((nChar==98)||(nChar==66))
	{
		AfxMessageBox(_T("fff"));
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

//���������Ϣ
BOOL CTFigureDlg::PreTranslateMessage(MSG* pMsg)
{
	//TODO: �ڴ����ר�ô����/����û���

	if(pMsg->message == WM_KEYDOWN) 

	{
		// ��Ӧkeyup��Ϣ
		//MessageBox(_T("�м�������"));
		//�жϾ����

		switch( pMsg->wParam )
		{ 
		case 17:   
#if DEBUGS:
			MessageBox(_T("������ctrl"));
#endif
			//m_FlashPlayer.CallFunction(temp);
			m_DragGraphics = !m_DragGraphics; 
			if (m_DragGraphics == TRUE)
			{
				CClientDC dc(this);
				dc.TextOutW(40,300,_T("�̿����϶�"));
			}
			else
			{
				CClientDC dc(this);
				dc.TextOutW(40,300,_T("���ر��϶�"));       
			}
			//return TRUE;
			break;
		case VK_DELETE :  //shift�� 16
			//VK_DELETE del
			//alt ==> VK_MENU
			//AfxMessageBox(_T("D"));	
			//�������
			SetClassLong(this->GetSafeHwnd(),
				GCL_HCURSOR , 
				(LONG)LoadCursor(NULL , IDC_ARROW));
			//ɾ����λ
			if(m_bSizeAll == TRUE)
			{
				for (int j=0; j<sizeof(m_arrHeadPoint)/sizeof(CPoint*)-1;j++)
				{
					this->m_arrHeadPoint[j][m_iDragFlag].x = 0;
					this->m_arrHeadPoint[j][m_iDragFlag].y = 0;
					this->m_arrTailPoint[j][m_iDragFlag].x = 0;
					this->m_arrTailPoint[j][m_iDragFlag].y = 0;
				}
				//��ǰ�ƶ�һλ
				for (int j=0; j<sizeof(m_arrHeadPoint)/sizeof(CPoint*)-1;j++)
					for (int n=m_iDragFlag; n<this->i;n++)
					{
						CPoint temp;
						temp = this->m_arrHeadPoint[j][n+1];
						this->m_arrHeadPoint[j][n] = temp;
						this->m_arrHeadPoint[j][n+1] = this->m_arrHeadPoint[j][n];
						temp = this->m_arrTailPoint[j][n+1];
						this->m_arrTailPoint[j][n] = temp;
						this->m_arrTailPoint[j][n+1] = this->m_arrTailPoint[j][n];
					}
					--i;
					m_bSizeAll = FALSE;

					this->Invalidate(0);
					//CClientDC dc(this);
					//dc.TextOutW(40,300,_T("ɾ��ͼ��")); 
			}
			break;

		case VK_LEFT://�������
			//MessageBox(_T("��"));
			//return TRUE;
			break;

		default: 
			//return TRUE;
			break; 
		}
		UpdateData(FALSE); 
	}
	// 
	//  	else if(pMsg->message == WM_KEYUP) 
	//  
	//  	{
	//  		// ��Ӧkeyup��Ϣ
	//  		//�жϾ����
	//  		switch( pMsg->wParam )
	//  		{ 
	//  		case 17:    
	//  #if DEBUGS:
	//  			MessageBox(_T("�ſ���ctrl"));
	//  #endif
	//  			m_DragGraphics = FALSE; 
	//  			//m_FlashPlayer.CallFunction(temp);
	//  			//return TRUE;
	//  			break;
	//  
	//  		case VK_LEFT://�������
	//  			//MessageBox(_T("��"));
	//  			//return TRUE;
	//  			break;
	//  
	//  		default: 
	//  			//return TRUE;
	//  			break; 
	//  		}
	// 		//UpdateData(FALSE);  
	//  	}



	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CTFigureDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialogEx::OnEraseBkgnd(pDC);
	/*	return TRUE;*/
}


// void CTFigureDlg::OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult)
// {
// 	// �ù���Ҫ��ʹ�� Windows XP ����߰汾��
// 	// ���� _WIN32_WINNT ���� >= 0x0501��
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	//*pResult = 0;
// 	//*pResult = 20;
// 	AfxMessageBox(_T(" f"));
// }


void CTFigureDlg::OnNMThemeChangedScrollbar2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �ù���Ҫ��ʹ�� Windows XP ����߰汾��
	// ���� _WIN32_WINNT ���� >= 0x0501��
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CTFigureDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	static CClientDC dc(this);
	CPoint point[10002];
	static int oldPos = 100 ;
	//int nNot = 0;
	int n =0 ;
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos = m_scroChange.GetScrollPos();    // ��ȡ��������ǰλ��  
	switch (nSBCode)   
	{   
		// ����������һ�У���pos��1  
	case SB_LINEUP:   
		pos -= 10;   
		if(m_vecPoint.size()!=0)
		{
			for (int n=0;n<10000;n++)
			{
				m_vecPoint[n].y = int(m_vecPoint[n].y) - 10 ;
			}
		} 
		this->Invalidate(1);
		break; 
		// ������ҹ���һ�У���pos��1  
	case SB_LINEDOWN:   
		pos  += 10;   
		if(m_vecPoint.size()!=0)
		{
			for (int n=0;n<10000;n++)
			{
				m_vecPoint[n].y = m_vecPoint[n].y + 10;
			}
		} 
		this->Invalidate(1);
		break;   
		// ����������һҳ����pos��10  
	case SB_PAGEUP:   
		pos -= 10;  
		//  		if(m_vecPoint.size()!=0)
		//   		{
		//   			for (int n=0;n<10000;n++)
		//   			{
		//   				m_vecPoint[n].y = m_vecPoint[n].y  - pos;
		//   			}
		//   		}
		break;
		//AfxMessageBox(_T(" s"));
		//dc.TextOutW(100,100,CString("ddd")); 
		// ������ҹ���һҳ����pos��10  
	case SB_PAGEDOWN:   
		pos  += 10;   
		break;   
		// �������������ˣ���posΪ1  
	case SB_TOP:   
		pos = 1;   
		break;   
		// ������������Ҷˣ���posΪ100  
	case SB_BOTTOM:   
		pos = 100;   
		break;     
		// ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ  
	case SB_THUMBTRACK:
		pos = nPos;  
		//nNot = dc.SetROP2(R2_NOT);

		for(std::vector<CPoint>::iterator iter = m_vecPoint.begin();iter !=m_vecPoint.end();iter++)
		{
			point[n] = *iter;	
			n++;
		}
		//dc.PolyBezier(point,10000);
		dc.Polyline(point,10000);
		if(m_vecPoint.size()!=0)
		{
			for (int n=0;n<10000;n++)
			{
				m_vecPoint[n].y = m_vecPoint[n].y  - (oldPos - pos);            
			}
		}
		n=0;
		for(std::vector<CPoint>::iterator iter = m_vecPoint.begin();iter !=m_vecPoint.end();iter++)
		{
			point[n] = *iter;	
			n++;
		}
		//dc.PolyBezier(point,10000);
		dc.SetROP2(R2_NOT);
		dc.Polyline(point,10000);
		//this->InvalidateRect(CRect(40,150 ,1845,290),1 );
		//Invalidate(0);
		oldPos = pos;

		break;   
	case SB_THUMBPOSITION:   
		this->InvalidateRect(CRect(40,150 ,1845,290),1 );
		// 		pos = nPos;  
		// 		if(m_vecPoint.size()!=0)
		// 		{
		// 			for (int n=0;n<10000;n++)
		// 			{
		// 				m_vecPoint[n].y = m_vecPoint[n].y  - (50 - pos);            
		// 			}
		// 		}
		// 		this->Invalidate(1);
		break;   
		// �����m_horiScrollbar.SetScrollPos(pos);ִ��ʱ��ڶ��ν���˺���������ȷ��������λ�ã����һ�ֱ�ӵ�default��֧�������ڴ˴����ñ༭������ʾ��ֵ  
	default:   
		//SetDlgItemInt(IDC_HSCROLL_EDIT, pos);  
		return;   
	}   

	// ���ù�����λ��  
	//this->Invalidate(1);
	m_scroChange.SetScrollPos(pos);  
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CTFigureDlg::OnCbnEditchangeComboxchangelead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 	m_bChangeLead = TRUE;
	// 	UpdateData();
	// 	CString strCurrent;
	// 	this->GetDlgItemTextW(IDC_COMBOXCHANGELEAD,strCurrent);
	// 	//OnBnClickedOpenfilebutton();
	// 	AfxMessageBox(strCurrent);
}



void CTFigureDlg::OnCbnCloseupComboxchangelead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bChangeLead = TRUE;
	//UpdateData();

	//AnalysisCommandLine();
	//AfxMessageBox(GetCommandLine()); 
	//this->Invalidate(1);
}


void CTFigureDlg::OnCbnSelchangeCombomms()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strChoosed;
	m_CombommS.GetLBText(m_CombommS.GetCurSel(),strChoosed);
	m_nMmS = _ttoi(strChoosed);
	LeadPaint();
	//AfxMessageBox(strChoosed);

}


void CTFigureDlg::OnCbnSelchangeCombommmv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bChangeLead = TRUE;
	CString strChoosed;
	m_Combomm_mV.GetLBText(m_Combomm_mV.GetCurSel(),strChoosed);
	m_nMmmV = _ttoi(strChoosed);
	LeadPaint();
}


void CTFigureDlg::OnNMOutofmemoryHotkey1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
