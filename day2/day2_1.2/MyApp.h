#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();//BOOL不具备跨平台性
};

class CMyWnd : public CFrameWnd
{
public:
	CMyWnd()//构造函数
	{
		Create(NULL,TEXT("hellooo"));
	}
};