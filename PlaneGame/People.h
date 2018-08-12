#pragma once

class CPeople
{
private:
	CString Name;
	CString ID;
public:
	CPeople(CString name, CString id);
	CPeople(void);
	~CPeople(void);
	void Print(int x, int y, CDC *pDC);
};

class People
{
public:
	People(void);
	~People(void);
};
