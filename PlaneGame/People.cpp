#include "StdAfx.h"
#include "People.h"

CPeople::CPeople()
{
	Name = "NONE";
	ID = "0";
}

CPeople::CPeople(CString name, CString id)
{
	Name = name;
	ID = id;
}

CPeople::~CPeople(void)
{
}

void CPeople::Print(int x, int y, CDC *pDC)
{
	CString s;
	s.Format(_T("������%s,ѧ�ţ�%s"), Name, ID);
	pDC->TextOutW(x, y, s, s.GetLength());
}

People::People(void)
{
}

People::~People(void)
{
}
