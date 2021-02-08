
// TFigureDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "atltypes.h"
#define LINE 15
#define TEN 1
#define WAVY 2 
#define ARROW 3 
#define DASH 4
#define T 5
#define TENTEN 6
#define TENTENTEN 7
#define TWOARROW 8
#define THREEARROW 9
#define TT 10
#define TTT 11
#define TTUPDOWN 12
#define NLINE 13
#define OOO 14
#define CIRCLE 16
#define CIRCLELINE 17


#define  FOURLINE 101
#define  SIXLINE 102
#define  EIGHTLINE 103
#define NOTHING 0 
#if 1:

#endif
// CTFigureDlg 对话框
class CTFigureDlg : public CDialogEx
{
// 构造
public:
	CTFigureDlg(CWnd* pParent = NULL);	// 标准构造函数
	 ~CTFigureDlg();
	void InvertLine(CDC* pDC,CPoint x,CPoint y);
	void InvertCircle(CDC* pDC,CPoint x,CPoint y);
	BOOL PreTranslateMessage(MSG* pMsg);
// 对话框数据
	enum { IDD = IDD_TFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void CTFigureDlg::writeFileJson( const CString cs);
	//BOOL CTFigureDlg::PreCreateWindow(CREATESTRUCT& cs) ;
// 实现
protected:
	HICON m_hIcon;   //图标句柄
	//保存文本编辑框的
	std::vector<CEdit*> vecEdit;


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedStartbutton();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedCheck1();

	bool bFourThree;
	bool bEightSeven;

	//清空点位
	void CTFigureDlg::ClearPoint();
	//文件位置
	void CTFigureDlg::drawDispalyFilePath(CString str);
	// 划线
	void DrawLine(CPoint left, CPoint right,CDC* dc);
	void CTFigureDlg::DrawLine(CPoint left, CPoint right);
	//绘制tenten,利用到NLINE的绘制方法
	void CTFigureDlg::DrawTentenB(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawTentenB(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	void CTFigureDlg::DrawTententenB(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawTententenB(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	//初始化划线区域
	void InitArea(CPoint left, CPoint right);
	//绘制十字
	void DrawTen(CPoint p1,CPoint p2,double theta,int length);
	void CTFigureDlg::DrawTen(CPoint p1,CPoint p2,double theta,int length,CDC* dc); 
	//绘制箭头
	void DrawArrow(CPoint p1,CPoint p2,double theta,int length);
	void CTFigureDlg::DrawArrow(CPoint p1,CPoint p2,double theta,int length,CDC* dc);
	bool bSixFive;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// //开始橡皮筋划线 paint画线条件此为TRUE
	bool m_flagTracking;

	CPoint m_tempPoint;

	CPoint* m_pPointFourLeft ;
	CPoint* m_pPointFourRight ;
	CPoint* m_pPointSixLeft;
	CPoint* m_pPointSixRight ;
	CPoint* m_pPointEightLeft ;
	CPoint* m_pPointEightRight ;
	// 记录按下的点
	CPoint m_headPoint[1024];//直线点
	CPoint m_tailPoint[1024];
	CPoint m_headPoint1[1024];//圆 点
	CPoint m_tailPoint1[1024];
	CPoint m_headPoint2[1024];//箭头
	CPoint m_tailPoint2[1024];
	CPoint m_headPoint3[1024];//TEN
	CPoint m_tailPoint3[1024];
	CPoint m_headPoint4[1024];//Wavy
	CPoint m_tailPoint4[1024];
	CPoint m_headPoint5[1024];//Dash
	CPoint m_tailPoint5[1024];
	CPoint m_headPoint6[1024];//T
	CPoint m_tailPoint6[1024];
	CPoint m_headPoint7[1024];//十十
	CPoint m_tailPoint7[1024];
	CPoint m_headPoint8[1024];//十十十
	CPoint m_tailPoint8[1024];
	CPoint m_headPoint9[1024];//2arrow
	CPoint m_tailPoint9[1024];
	CPoint m_headPoint10[1024];//3arrow
	CPoint m_tailPoint10[1024];
	CPoint m_headPoint11[1024];//TT
	CPoint m_tailPoint11[1024];
	CPoint m_headPoint12[1024];//3T
	CPoint m_tailPoint12[1024];
	CPoint m_headPoint13[1024];//Tupdown
	CPoint m_tailPoint13[1024];
	CPoint m_headPoint14[1024];//Nline
	CPoint m_tailPoint14[1024];
	CPoint m_headPoint15[1024];//O
	CPoint m_tailPoint15[1024];
	CPoint m_headPoint16[1024];//CIRCLELINE
	CPoint m_tailPoint16[1024];

	//点向量

	//二维数组 
	CPoint* m_arrHeadPoint[18];
	CPoint* m_arrTailPoint[18];
	std::vector<CPoint>  m_vecPoint;
	//是否做了修改标记
	bool m_bChangeFlag;

	CPoint point[10002];
	//点位数组下标
	int i;
	int m_nWord;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedLinebutton();
	afx_msg void OnBnClickedCurvebutton();
	afx_msg void OnBnClickedDashbutton();
	//开启点位追踪
	bool m_bTracking;
	bool m_bDrawLine;
	afx_msg void OnBnClickedCirclebutton();
	bool m_bDrawCircle;
	afx_msg void OnBnClickedArrow();
	// 绘制箭头
	bool b_DrawArrow;
	// 绘制箭头
	bool m_bDrawArrow;
	afx_msg void OnBnClickedArrowbutton();
	afx_msg void OnBnClickedOpenfilebutton();
	afx_msg void OnBnClickedButton2();

	//void CTFigureDlg::LeadPaint(int x);
	//afx_msg void OnStnClickedPicten();
	//afx_msg void OnBnClickedMfcbutton1();
	//XML文件位置	
	std::string m_cXmlFilePath ;
	// CButton 直线
	CButton m_buttonLine;
	CButton m_buttonDash;
	CButton m_buttonCircle;
	CButton m_buttonCircleO;
	CButton m_buttonT;
	CButton m_buttonTT;
	CButton m_button3T;
	CButton m_buttonNline;
	CButton m_buttonTTUpDown;
	CButton m_buttonTen;
	CButton m_buttonTenten;
	CButton m_buttonTententen;
	CButton m_buttonCircleLine;
	afx_msg void OnBnClickedButtonten();
	// CButton TEN
	//CButton m_buttonTen;
	// 箭头button
	CButton m_buttonArrow;
	CButton m_button2Arrow;
	CButton m_button3Arrow;

	//afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButtonwavy();
	// 波浪线
	CButton m_buttonWavy;
	// TEN
	bool m_bDrawTen;
	//读取json文件
	void CTFigureDlg:: readfireadFileJson(CString cs);
	void CTFigureDlg::ChangeFlag(bool* b);
	void CTFigureDlg::DeleteDataPoint();
	void CTFigureDlg::drawCordinate(CPoint point);
	void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length);
	//绘制虚线
	void CTFigureDlg::DrawDash(CPoint p1,CPoint p2,int seg);
	void CTFigureDlg::DrawDash(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	//更改鼠标//记录下标
	void CTFigureDlg::IsinWhere(int nWhere ,int j);
	void CTFigureDlg::Draw2Arrow(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::Draw2Arrow(CPoint p1,CPoint p2,int nSeg,CDC* dc);

	void CTFigureDlg::OnMouseMoveDrawLine(CPoint point,CPoint headPoint, CPoint tailPoint);
	bool CTFigureDlg::IsinRange(CPoint point ,CPoint headPoint,CPoint tailPoint ,int range );

	void CTFigureDlg::IsDrawWhat(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy);
	void CTFigureDlg::IsDrawWhatCircle(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy);
	//绘制心电图表格
	void DrawGrid(CPoint lP,CPoint rP);
	afx_msg void OnBnClickedBwavy(); //选择波浪线
	CPoint m_FlagPointL;
	CPoint m_FlagPointR;
	// 绘制波浪线
	bool m_bDrawWavy;
	// 找到位置，切换四向箭头
	bool m_bSizeAll;
	// 记录拖拽鼠标按下位置
	CPoint m_dragPoint;
	// 记录鼠标拖拽图形开始
	bool m_bDragFlag;
	// Drag起始点的head 下标
	int m_iDragFlag;
	// 禁止四向箭头标记
	bool m_bForbidSizeAll;
	// 落在了什么图形上的标记
	int m_iFallinWhere;
	//afx_msg void OnBnClickedDashbutton();
	// //绘制虚线
	bool m_bDrawDash;
	//文件位置
	CString m_cstrFileLocation;
	//绘制对准辅助线状态标记开启
	//AVS
	CString m_strAVS[20]; 
	BOOL m_flagSublineTracking;
	BOOL m_bChangeLead;
	bool m_bDrawT;
	bool m_bDraw3arrow;
	bool m_bDraw2arrow;
	bool m_bDrawO;//
	bool m_bDrawCircleLine;
	bool m_bDrawTupdown;//
	bool m_bDrawtenten;
	bool m_bDrawtententen;
	bool m_bDrawTT;//
	bool m_bDraw3T;//
	bool m_bdrawNline;
	CPoint m_downPoint;
	void CTFigureDlg::IsDrawWhatAdd(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy);
		void CTFigureDlg::IsDrawWhatSub(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy);
		//绘制残影
		void CTFigureDlg::DrawGhost(CPoint* m_headPoint4,CPoint* m_tailPoint4,int nDx,int nDy);
	//反转方法绘制波浪线
	void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length,CDC* dc);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedRemake();
	//绘制对准辅助线
	void DrawSubline(CPoint point,CDC* dc,int nOldMode);
	void DrawInvertSubline(class CPoint, CClientDC* dc, int nOldMode);
	afx_msg void OnCbnSelchangeComboxchangelead();
	void CTFigureDlg::LeadPaintJson(int x,char* cXmlFilename );
	//绘制导联
	void CTFigureDlg::LeadPaint();
// 	CDC MemDC;
// 	//CClientDC pDC(this);
// 	CDC* ppDC ;
	int m_Lead;
	CPoint m_dragPointMove;
	BOOL m_DragGraphics;      //可拖动图形;
		
		afx_msg void OnBnClicked3arrow();
	afx_msg void OnBnClickedDrawt();
	afx_msg void OnBnClicked2arrow();
	afx_msg void OnBnClickedButtonoo();
	afx_msg void OnBnClickedButtonttupdown();
	afx_msg void OnBnClickedDrawtenten();
	afx_msg void OnBnClickedDrawtententen();
	void CTFigureDlg::DrawTenten(CPoint p1,CPoint p2,double theta,int length);
	void CTFigureDlg::DrawTenten(CPoint p1,CPoint p2,double theta,int length,CDC* dc) ;
	//绘制TTUP&&DOWN
	void CTFigureDlg::DrawTTUpDown(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawTTUpDown(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	void CTFigureDlg::DrawTT(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawTT(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	void CTFigureDlg::Draw3T(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::Draw3T(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	void CTFigureDlg::Draw3Arrow(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::Draw3Arrow(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	//void CTFigureDlg::Draw2Arrow(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawCircleLine(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawCircleLine(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	void CTFigureDlg::DrawNLine(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawNLine(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	void CTFigureDlg::DrawArc(CPoint center, CPoint pStart, double radian, int radius,COLORREF color);
	CPoint CTFigureDlg::FindDrawArrowPoint(CPoint p1,CPoint p2,double theta,int length);
	//HBITMAP CTFigureDlg::CaptureScreen(LPRECT lpRect);//lpRect为NULL时表示全屏幕截图
	//BOOL CTFigureDlg::SaveBmp(HBITMAP hBitmap,CString FileName)  ;
	//绘制俩点之间一点的位置
	void CTFigureDlg::DrawPointBetweenTwoPoint(CPoint p1,CPoint p2,double theta,int length,CDC* dc);
void CTFigureDlg::DrawPointBetweenTwoPoint(CPoint p1,CPoint p2,double theta,int length);
//绘制十十字
void CTFigureDlg::DrawTentenA(CPoint p1,CPoint p2,double theta,int length,CDC* dc);
//绘制虚线上一个点
void CTFigureDlg::DrawDashPoint(CPoint p1,CPoint p2,int nSeg);
void CTFigureDlg::DrawDashPoint(CPoint p1,CPoint p2,int nSeg,CDC* dc);

//对命令行的解析
BOOL CTFigureDlg::AnalysisCommandLine();

//长文本短文本输入
CEdit* CTFigureDlg::LongTextInput(CRect rect);
std::vector<CEdit* > m_vecEdit; //保存管理编辑框对象
void CTFigureDlg::ShortTextInput(CRect rect);
void CTFigureDlg::CleanEdit();


afx_msg void OnBnClickedButtonword();
afx_msg void OnBnClickedButton3t();
afx_msg void OnBnClickedButtontt();
afx_msg void OnBnClickedButtonsave();
afx_msg void OnBnClickedButtonnline();
afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
afx_msg void OnXButtonDblClk(UINT nFlags, UINT nButton, CPoint point);
afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
afx_msg void OnEnChangeEdit1();
afx_msg void OnCbnSelchangeCombox1();
afx_msg void OnEnChangeEditavs();
//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
//绘制距离文本
void CTFigureDlg::DrawDistenceText(CPoint* headPoint);
afx_msg void OnBnClickedCircleline();
afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
afx_msg BOOL OnEraseBkgnd(CDC* pDC);
afx_msg void OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult);
afx_msg void OnNMThemeChangedScrollbar2(NMHDR *pNMHDR, LRESULT *pResult);
// 滚动条
CScrollBar m_scroChange;
afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
afx_msg void OnCbnEditchangeComboxchangelead();
afx_msg void OnCbnCloseupComboxchangelead();
// 导联选择框
CComboBox m_LeadCombox;
// mm/s
CComboBox m_CombommS;
// mm/mV
CComboBox m_Combomm_mV;
int  m_nMmmV;
int m_nMmS;
CString m_strCurrentLead;
bool m_bDrawText; //文字选项
CPoint  m_headPointText[1024];
CPoint  m_tailPointText[1024];
afx_msg void OnCbnSelchangeCombomms();
afx_msg void OnCbnSelchangeCombommmv();
afx_msg void OnNMOutofmemoryHotkey1(NMHDR *pNMHDR, LRESULT *pResult);
// 模式切换
CComboBox m_comboPattern;
BOOL m_bNoDraw;
};
