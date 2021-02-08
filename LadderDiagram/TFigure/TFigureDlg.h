
// TFigureDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "atltypes.h"


// CTFigureDlg 对话框
class CTFigureDlg : public CDialogEx
{
// 构造
public:
	CTFigureDlg(CWnd* pParent = NULL);	// 标准构造函数
	void InvertLine(CDC* pDC,CPoint x,CPoint y);
	void InvertCircle(CDC* pDC,CPoint x,CPoint y);
// 对话框数据
	enum { IDD = IDD_TFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;   //图标句柄


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
	// 划线
	void DrawLine(CPoint left, CPoint right);
	//初始化划线区域
	void InitArea(CPoint left, CPoint right);
	//绘制十字
	void DrawTen(CPoint p1,CPoint p2,double theta,int length);
	//绘制箭头
	void DrawArrow(CPoint p1,CPoint p2,double theta,int length);
	bool bSixFive;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// //开始橡皮筋划线
	bool m_flagTracking;
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
	//点向量
	std::vector<CPoint>  m_vecPoint;

	CPoint point[10002];
	int i;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedLinebutton();
	afx_msg void OnBnClickedCurvebutton();
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
	//afx_msg void OnStnClickedPicten();
	//afx_msg void OnBnClickedMfcbutton1();
	// CButton 直线
	CButton buttonLine;
	afx_msg void OnBnClickedButtonten();
	// CButton TEN
	CButton m_buttonTen;
	// 箭头button
	CButton m_buttonArrow;
	//afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButtonwavy();
	// 波浪线
	CButton m_buttonWavy;
	// TEN
	bool m_bDrawTen;
	void CTFigureDlg::ChangeFlag(bool* b);
	void CTFigureDlg::DeleteDataPoint();
	void CTFigureDlg::drawCordinate(CPoint point);
	void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length);

	//绘制心电图表格
	void DrawGrid(CPoint lP,CPoint rP);
	afx_msg void OnBnClickedBwavy(); //选择波浪线
	// 绘制波浪线
	bool m_bDrawWavy;
	// 找到位置，切换四向箭头
	bool m_bSizeAll;
	// 记录拖拽鼠标按下位置
	CPoint m_dragPoint;
	// 记录鼠标拖拽开始
	bool m_bDragFlag;
	// Drag起始点的head 下标
	int m_iDragFlag;
	// 禁止四向箭头标记
	bool m_bForbidSizeAll;
};
