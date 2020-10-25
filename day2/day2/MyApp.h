#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
	BOOL InitInstance() //BOOL不具备跨平台性
	{
		CFrameWnd *f = new CFrameWnd(); //窗口实例
		//return 0;
		this->m_pMainWnd = f;//将应用与窗口相关联

		f->Create(NULL,TEXT("hello "));
		f->ShowWindow(SW_SHOW);
		return true;
	}
};

