#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();//BOOL���߱���ƽ̨��
};

class CMyWnd : public CFrameWnd
{
public:
	CMyWnd()//���캯��
	{
		Create(NULL,TEXT("hellooo"));
	}
};