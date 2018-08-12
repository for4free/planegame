// WzdSplash.cpp : 实现文件
//
#include "stdafx.h"
//#include "TinyPlusCompiler.h"
#include "WzdSplash.h"

//背景音乐
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
// CWzdSplash 消息处理程序
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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CPaintDC dc(this); // device context forpainting
	BITMAP bitmap;
	m_bitmap.GetBitmap(&bitmap);
	CDC dcComp;
	dcComp.CreateCompatibleDC(&dc);
	dcComp.SelectObject(&m_bitmap);
	// draw bitmap
	dc.BitBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, &dcComp, 0, 0, SRCCOPY);
	//打开开启音乐
	mciSendString(_T("Open res\\music\\logo.mp3 alias logo"), NULL, 0, NULL);
	//播放开启音乐(重复播放)C:\\Users\\a\\Desktop\\C++实训\\planegamecode\\PlaneGame\\res\\music\\logo.mp3
	mciSendString(_T("Play logo"), NULL, 0, NULL);
}
void CWzdSplash::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CWnd::OnTimer(nIDEvent);
	DestroyWindow(); //销毁初始画面窗口
}
