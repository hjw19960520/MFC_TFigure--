
// TFigureDlg.h : 头文件
//

#pragma once


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
	void CTFigureDlg::InitArea(CPoint left, CPoint right);
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
};
