
// TFigureDlg.h : ͷ�ļ�
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
// CTFigureDlg �Ի���
class CTFigureDlg : public CDialogEx
{
// ����
public:
	CTFigureDlg(CWnd* pParent = NULL);	// ��׼���캯��
	 ~CTFigureDlg();
	void InvertLine(CDC* pDC,CPoint x,CPoint y);
	void InvertCircle(CDC* pDC,CPoint x,CPoint y);
	BOOL PreTranslateMessage(MSG* pMsg);
// �Ի�������
	enum { IDD = IDD_TFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void CTFigureDlg::writeFileJson( const CString cs);
	//BOOL CTFigureDlg::PreCreateWindow(CREATESTRUCT& cs) ;
// ʵ��
protected:
	HICON m_hIcon;   //ͼ����
	//�����ı��༭���
	std::vector<CEdit*> vecEdit;


	// ���ɵ���Ϣӳ�亯��
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

	//��յ�λ
	void CTFigureDlg::ClearPoint();
	//�ļ�λ��
	void CTFigureDlg::drawDispalyFilePath(CString str);
	// ����
	void DrawLine(CPoint left, CPoint right,CDC* dc);
	void CTFigureDlg::DrawLine(CPoint left, CPoint right);
	//����tenten,���õ�NLINE�Ļ��Ʒ���
	void CTFigureDlg::DrawTentenB(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawTentenB(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	void CTFigureDlg::DrawTententenB(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::DrawTententenB(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	//��ʼ����������
	void InitArea(CPoint left, CPoint right);
	//����ʮ��
	void DrawTen(CPoint p1,CPoint p2,double theta,int length);
	void CTFigureDlg::DrawTen(CPoint p1,CPoint p2,double theta,int length,CDC* dc); 
	//���Ƽ�ͷ
	void DrawArrow(CPoint p1,CPoint p2,double theta,int length);
	void CTFigureDlg::DrawArrow(CPoint p1,CPoint p2,double theta,int length,CDC* dc);
	bool bSixFive;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// //��ʼ��Ƥ��� paint����������ΪTRUE
	bool m_flagTracking;

	CPoint m_tempPoint;

	CPoint* m_pPointFourLeft ;
	CPoint* m_pPointFourRight ;
	CPoint* m_pPointSixLeft;
	CPoint* m_pPointSixRight ;
	CPoint* m_pPointEightLeft ;
	CPoint* m_pPointEightRight ;
	// ��¼���µĵ�
	CPoint m_headPoint[1024];//ֱ�ߵ�
	CPoint m_tailPoint[1024];
	CPoint m_headPoint1[1024];//Բ ��
	CPoint m_tailPoint1[1024];
	CPoint m_headPoint2[1024];//��ͷ
	CPoint m_tailPoint2[1024];
	CPoint m_headPoint3[1024];//TEN
	CPoint m_tailPoint3[1024];
	CPoint m_headPoint4[1024];//Wavy
	CPoint m_tailPoint4[1024];
	CPoint m_headPoint5[1024];//Dash
	CPoint m_tailPoint5[1024];
	CPoint m_headPoint6[1024];//T
	CPoint m_tailPoint6[1024];
	CPoint m_headPoint7[1024];//ʮʮ
	CPoint m_tailPoint7[1024];
	CPoint m_headPoint8[1024];//ʮʮʮ
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

	//������

	//��ά���� 
	CPoint* m_arrHeadPoint[18];
	CPoint* m_arrTailPoint[18];
	std::vector<CPoint>  m_vecPoint;
	//�Ƿ������޸ı��
	bool m_bChangeFlag;

	CPoint point[10002];
	//��λ�����±�
	int i;
	int m_nWord;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedLinebutton();
	afx_msg void OnBnClickedCurvebutton();
	afx_msg void OnBnClickedDashbutton();
	//������λ׷��
	bool m_bTracking;
	bool m_bDrawLine;
	afx_msg void OnBnClickedCirclebutton();
	bool m_bDrawCircle;
	afx_msg void OnBnClickedArrow();
	// ���Ƽ�ͷ
	bool b_DrawArrow;
	// ���Ƽ�ͷ
	bool m_bDrawArrow;
	afx_msg void OnBnClickedArrowbutton();
	afx_msg void OnBnClickedOpenfilebutton();
	afx_msg void OnBnClickedButton2();

	//void CTFigureDlg::LeadPaint(int x);
	//afx_msg void OnStnClickedPicten();
	//afx_msg void OnBnClickedMfcbutton1();
	//XML�ļ�λ��	
	std::string m_cXmlFilePath ;
	// CButton ֱ��
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
	// ��ͷbutton
	CButton m_buttonArrow;
	CButton m_button2Arrow;
	CButton m_button3Arrow;

	//afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButtonwavy();
	// ������
	CButton m_buttonWavy;
	// TEN
	bool m_bDrawTen;
	//��ȡjson�ļ�
	void CTFigureDlg:: readfireadFileJson(CString cs);
	void CTFigureDlg::ChangeFlag(bool* b);
	void CTFigureDlg::DeleteDataPoint();
	void CTFigureDlg::drawCordinate(CPoint point);
	void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length);
	//��������
	void CTFigureDlg::DrawDash(CPoint p1,CPoint p2,int seg);
	void CTFigureDlg::DrawDash(CPoint p1,CPoint p2,int nSeg,CDC* dc);
	//�������//��¼�±�
	void CTFigureDlg::IsinWhere(int nWhere ,int j);
	void CTFigureDlg::Draw2Arrow(CPoint p1,CPoint p2,int nSeg);
	void CTFigureDlg::Draw2Arrow(CPoint p1,CPoint p2,int nSeg,CDC* dc);

	void CTFigureDlg::OnMouseMoveDrawLine(CPoint point,CPoint headPoint, CPoint tailPoint);
	bool CTFigureDlg::IsinRange(CPoint point ,CPoint headPoint,CPoint tailPoint ,int range );

	void CTFigureDlg::IsDrawWhat(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy);
	void CTFigureDlg::IsDrawWhatCircle(CPoint* headPoint,CPoint* tailPoint ,int nDx ,int nDy);
	//�����ĵ�ͼ���
	void DrawGrid(CPoint lP,CPoint rP);
	afx_msg void OnBnClickedBwavy(); //ѡ������
	CPoint m_FlagPointL;
	CPoint m_FlagPointR;
	// ���Ʋ�����
	bool m_bDrawWavy;
	// �ҵ�λ�ã��л������ͷ
	bool m_bSizeAll;
	// ��¼��ק��갴��λ��
	CPoint m_dragPoint;
	// ��¼�����קͼ�ο�ʼ
	bool m_bDragFlag;
	// Drag��ʼ���head �±�
	int m_iDragFlag;
	// ��ֹ�����ͷ���
	bool m_bForbidSizeAll;
	// ������ʲôͼ���ϵı��
	int m_iFallinWhere;
	//afx_msg void OnBnClickedDashbutton();
	// //��������
	bool m_bDrawDash;
	//�ļ�λ��
	CString m_cstrFileLocation;
	//���ƶ�׼������״̬��ǿ���
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
		//���Ʋ�Ӱ
		void CTFigureDlg::DrawGhost(CPoint* m_headPoint4,CPoint* m_tailPoint4,int nDx,int nDy);
	//��ת�������Ʋ�����
	void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length,CDC* dc);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedRemake();
	//���ƶ�׼������
	void DrawSubline(CPoint point,CDC* dc,int nOldMode);
	void DrawInvertSubline(class CPoint, CClientDC* dc, int nOldMode);
	afx_msg void OnCbnSelchangeComboxchangelead();
	void CTFigureDlg::LeadPaintJson(int x,char* cXmlFilename );
	//���Ƶ���
	void CTFigureDlg::LeadPaint();
// 	CDC MemDC;
// 	//CClientDC pDC(this);
// 	CDC* ppDC ;
	int m_Lead;
	CPoint m_dragPointMove;
	BOOL m_DragGraphics;      //���϶�ͼ��;
		
		afx_msg void OnBnClicked3arrow();
	afx_msg void OnBnClickedDrawt();
	afx_msg void OnBnClicked2arrow();
	afx_msg void OnBnClickedButtonoo();
	afx_msg void OnBnClickedButtonttupdown();
	afx_msg void OnBnClickedDrawtenten();
	afx_msg void OnBnClickedDrawtententen();
	void CTFigureDlg::DrawTenten(CPoint p1,CPoint p2,double theta,int length);
	void CTFigureDlg::DrawTenten(CPoint p1,CPoint p2,double theta,int length,CDC* dc) ;
	//����TTUP&&DOWN
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
	//HBITMAP CTFigureDlg::CaptureScreen(LPRECT lpRect);//lpRectΪNULLʱ��ʾȫ��Ļ��ͼ
	//BOOL CTFigureDlg::SaveBmp(HBITMAP hBitmap,CString FileName)  ;
	//��������֮��һ���λ��
	void CTFigureDlg::DrawPointBetweenTwoPoint(CPoint p1,CPoint p2,double theta,int length,CDC* dc);
void CTFigureDlg::DrawPointBetweenTwoPoint(CPoint p1,CPoint p2,double theta,int length);
//����ʮʮ��
void CTFigureDlg::DrawTentenA(CPoint p1,CPoint p2,double theta,int length,CDC* dc);
//����������һ����
void CTFigureDlg::DrawDashPoint(CPoint p1,CPoint p2,int nSeg);
void CTFigureDlg::DrawDashPoint(CPoint p1,CPoint p2,int nSeg,CDC* dc);

//�������еĽ���
BOOL CTFigureDlg::AnalysisCommandLine();

//���ı����ı�����
CEdit* CTFigureDlg::LongTextInput(CRect rect);
std::vector<CEdit* > m_vecEdit; //�������༭�����
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
//���ƾ����ı�
void CTFigureDlg::DrawDistenceText(CPoint* headPoint);
afx_msg void OnBnClickedCircleline();
afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
afx_msg BOOL OnEraseBkgnd(CDC* pDC);
afx_msg void OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult);
afx_msg void OnNMThemeChangedScrollbar2(NMHDR *pNMHDR, LRESULT *pResult);
// ������
CScrollBar m_scroChange;
afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
afx_msg void OnCbnEditchangeComboxchangelead();
afx_msg void OnCbnCloseupComboxchangelead();
// ����ѡ���
CComboBox m_LeadCombox;
// mm/s
CComboBox m_CombommS;
// mm/mV
CComboBox m_Combomm_mV;
int  m_nMmmV;
int m_nMmS;
CString m_strCurrentLead;
bool m_bDrawText; //����ѡ��
CPoint  m_headPointText[1024];
CPoint  m_tailPointText[1024];
afx_msg void OnCbnSelchangeCombomms();
afx_msg void OnCbnSelchangeCombommmv();
afx_msg void OnNMOutofmemoryHotkey1(NMHDR *pNMHDR, LRESULT *pResult);
// ģʽ�л�
CComboBox m_comboPattern;
BOOL m_bNoDraw;
};
