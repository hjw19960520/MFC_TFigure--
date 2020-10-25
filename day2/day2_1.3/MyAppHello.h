#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{
public:
	CMainWindow()//¹¹Ôìº¯Êý
	{
		this->Create(NULL,TEXT("hellooo"),WS_VSCROLL|WS_OVERLAPPEDWINDOW);
	}
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	DECLARE_MESSAGE_MAP();
};