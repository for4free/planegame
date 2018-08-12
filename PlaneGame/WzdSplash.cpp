// WzdSplash.cpp : ʵ���ļ�
//
#include "stdafx.h"
//#include "TinyPlusCompiler.h"
#include "WzdSplash.h"

//��������
#include <mmsystem.h>
//

// CWzdSplash
IMPLEMENT_DYNAMIC(CWzdSplash, CWnd)
CWzdSplash::CWzdSplash()
{
}
CWzdSplash::~CWzdSplash()
{
}
BEGIN_MESSAGE_MAP(CWzdSplash, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()
// CWzdSplash ��Ϣ�������
void CWzdSplash::Create(UINT nBitmapID)
{
	m_bitmap.LoadBitmap(nBitmapID);
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	//CreateEx(0,AfxRegisterWndClass(0),"",WS_POPUP|WS_VISIBLE|WS_BORDER,0,0,bitmap.bmWidth,bitmap.bmHeight,NULL,0);
	CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bitmap.bmWidth, bitmap.bmHeight, NULL, NULL);
}
void CWzdSplash::OnPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CPaintDC dc(this); // device context forpainting
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	CDC dcComp;
	dcComp.CreateCompatibleDC(&dc);
	dcComp.SelectObject(&m_bitmap);
	// draw bitmap
	dc.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, &dcComp, 0, 0, SRCCOPY);
	//�򿪿�������
	mciSendString(_T("Open res\\music\\logo.mp3 alias logo"), NULL, 0, NULL);
	//���ſ�������(�ظ�����)C:\\Users\\a\\Desktop\\C++ʵѵ\\planegamecode\\PlaneGame\\res\\music\\logo.mp3
	mciSendString(_T("Play logo"), NULL, 0, NULL);
}
void CWzdSplash::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CWnd::OnTimer(nIDEvent);
	DestroyWindow(); //���ٳ�ʼ���洰��
}
