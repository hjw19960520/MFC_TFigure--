#include <afxwin.h>

class CMyApp : public CWinApp
{
public:
	BOOL InitInstance() //BOOL���߱���ƽ̨��
	{
		CFrameWnd *f = new CFrameWnd(); //����ʵ��
		//return 0;
		this->m_pMainWnd = f;//��Ӧ���봰�������

		f->Create(NULL,TEXT("hello "));
		f->ShowWindow(SW_SHOW);
		return true;
	}
};

