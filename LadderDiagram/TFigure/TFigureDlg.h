
// TFigureDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "atltypes.h"


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
	void InitArea(CPoint left, CPoint right);
	//����ʮ��
	void DrawTen(CPoint p1,CPoint p2,double theta,int length);
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
	CPoint m_headPoint3[1024];//TEN
	CPoint m_tailPoint3[1024];
	CPoint m_headPoint4[1024];//Wavy
	CPoint m_tailPoint4[1024];
	//������
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
	// ���Ƽ�ͷ
	bool b_DrawArrow;
	// ���Ƽ�ͷ
	bool m_bDrawArrow;
	afx_msg void OnBnClickedArrowbutton();
	afx_msg void OnBnClickedOpenfilebutton();
	afx_msg void OnBnClickedButton2();
	//afx_msg void OnStnClickedPicten();
	//afx_msg void OnBnClickedMfcbutton1();
	// CButton ֱ��
	CButton buttonLine;
	afx_msg void OnBnClickedButtonten();
	// CButton TEN
	CButton m_buttonTen;
	// ��ͷbutton
	CButton m_buttonArrow;
	//afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButtonwavy();
	// ������
	CButton m_buttonWavy;
	// TEN
	bool m_bDrawTen;
	void CTFigureDlg::ChangeFlag(bool* b);
	void CTFigureDlg::DeleteDataPoint();
	void CTFigureDlg::drawCordinate(CPoint point);
	void CTFigureDlg::DrawWavy(CPoint p1,CPoint p2,double length);

	//�����ĵ�ͼ���
	void DrawGrid(CPoint lP,CPoint rP);
	afx_msg void OnBnClickedBwavy(); //ѡ������
	// ���Ʋ�����
	bool m_bDrawWavy;
	// �ҵ�λ�ã��л������ͷ
	bool m_bSizeAll;
	// ��¼��ק��갴��λ��
	CPoint m_dragPoint;
	// ��¼�����ק��ʼ
	bool m_bDragFlag;
	// Drag��ʼ���head �±�
	int m_iDragFlag;
	// ��ֹ�����ͷ���
	bool m_bForbidSizeAll;
};
