/*
Բ�εĻ��� ��Ϣ�������
*/
#include "MyAppHello.h"

CMyApp app;

BOOL CMyApp::InitInstance()
{
	this->m_pMainWnd = new CMainWindow();
	this->m_pMainWnd->ShowWindow(this->m_nCmdShow);
	this->m_pMainWnd->UpdateWindow();
	return true;
}

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd) //΢����ĺ귽����Ϣӳ��
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN(UINT nFlags,CPoint point)
END_MESSAGE_MAP()

void CMainWindow::OnPaint()//���������Ϣ
{
	CPaintDC dc(this); //������DC����
	dc.Ellipse(100,100,200,200);
	CRect rect(100,100,500,500);
	this->GetClientRect(&rect);
	dc.DrawText(TEXT("MFC init"),-1,&rect,DT_SINGLELINE|DT_CENTER);
}

void CMainWindow::OnLButtonDown(UINT nFlags,CPoint point)
{
	this->MessageBox(TEXT("MFC"));
}

