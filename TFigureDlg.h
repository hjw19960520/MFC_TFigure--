
// TFigureDlg.h : ͷ�ļ�
//

#pragma once


// CTFigureDlg �Ի���
class CTFigureDlg : public CDialogEx
{
// ����
public:
	CTFigureDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void InvertLine(CDC* pDC,CPoint x,CPoint y);
	void InvertCircle(CDC* pDC,CPoint x,CPoint y);
// �Ի�������
	enum { IDD = IDD_TFIGURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;   //ͼ����


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
	// ����
	void DrawLine(CPoint left, CPoint right);
	//��ʼ����������
	void CTFigureDlg::InitArea(CPoint left, CPoint right);
	//���Ƽ�ͷ
	void DrawArrow(CPoint p1,CPoint p2,double theta,int length);
	bool bSixFive;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// //��ʼ��Ƥ���
	bool m_flagTracking;
	// ��¼���µĵ�
	CPoint m_headPoint[1024];//ֱ�ߵ�
	CPoint m_tailPoint[1024];
	CPoint m_headPoint1[1024];//Բ ��
	CPoint m_tailPoint1[1024];
	CPoint m_headPoint2[1024];//��ͷ
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
	// ���Ƽ�ͷ
	bool b_DrawArrow;
	// ���Ƽ�ͷ
	bool m_bDrawArrow;
	afx_msg void OnBnClickedArrowbutton();
};
