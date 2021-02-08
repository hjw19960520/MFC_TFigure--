#pragma once
#include "afxwin.h"
#include "atltypes.h"
class CGragh
{
protected: 
	CPoint m_lu;
	CPoint m_rd;
	CPen m_pen;
public:
	CGragh(CPoint lu,CPoint rd,CPen pen):m_lu(lu),m_rd(rd),m_pen(pen)
	{

	}
	virtual ~CGragh()
	{

	}
	virtual void Draw(CPoint lu,CPoint rd);

};

class circle:public CGragh
{
public:
	circle();
	~circle();
	void Draw(CPoint lu,CPoint rd);
};

class line:public CGragh
{
public:
	line();
	~line();
	void Draw(CPoint lu,CPoint rd);
};