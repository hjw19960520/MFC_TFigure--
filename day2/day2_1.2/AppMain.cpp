#include "MyApp.h"

BOOL CMyApp::InitInstance()
{
	this->m_pMainWnd = new CMyWnd();
	this->m_pMainWnd->ShowWindow(this->m_nCmdShow);
	this->m_pMainWnd->UpdateWindow();
	return true;
}
CMyApp app;