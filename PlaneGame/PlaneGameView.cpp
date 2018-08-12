// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include <atlimage.h>
//背景音乐
#include <mmsystem.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: 在此处添加构造代码
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	


	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

}


// CPlaneGameView 打印

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView 消息处理程序



//********TEAVHER*******


void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	//初始化游戏
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
	
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

		 t1 = GetTickCount();  //程序段开始前取得系统运行时间(ms)   


	//产生随机数种子
	srand( (unsigned)time( NULL ) );

	//建立设备DC
	m_pDC = new CClientDC(this);

	//建立内存DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//建立内存位图
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//将位图选入内存DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();

	//产生主角(战机)
	m_pMe = new CMyPlane;

	//启动游戏
	SetTimer(1,30,NULL);

	//加载背景图 背景图移动相关代码
	CBitmap bmp;
		bmp.LoadBitmap(IDB_BK);
		m_Images.Create(1364, 1384, ILC_COLOR24 | ILC_MASK, 2, 0); 
		m_Images.Add(&bmp, RGB(0, 0, 0));
	
	m_x = 0;
	m_y = -692;

	SetTimer(1, 30, NULL);

	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//绘制天空
	//pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,0);//RGB(84, 142, 239)

	//绘制我方战机
	if (m_pMe != NULL)
	{
		m_pMe->Draw(m_pMemDC, FALSE);

	}
	else
	{  
		//game over
		//画结束背景
		//CDC *pDC = GetDC();
		//CRect rect;
		//GetClientRect(&rect);
		//CBrush m_brushBackground;
		//CBitmap bg;
		//bg.LoadBitmap(IDB_GO);///加载位图
		//m_brushBackground.CreatePatternBrush(&bg);//创建位图画刷
		//m_pMemDC->FillRect(rect, &m_brushBackground);///用背景画刷填充区域
		//结束背景
		if (cp > 19)
		{
			CBitmap over;
			CImageList image;
			over.LoadBitmap(IDB_WIN);
			image.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
			image.Add(&over, RGB(0, 0, 0));
			image.Draw(m_pMemDC, 0, CPoint(0, 0), ILD_TRANSPARENT);
		}
		if (cp <= 19)
		{
			CBitmap over;
			CImageList image;
			over.LoadBitmap(IDB_LOS);
			image.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
			image.Add(&over, RGB(0, 0, 0));
			image.Draw(m_pMemDC, 0, CPoint(0, 0), ILD_TRANSPARENT);
		}

		//结束页面显示计分
		//CString str;
		//if (lv - (t3 - t1) / 1000<=0)
		//	str.Format(_T("战况记录:坚持 %d 秒,被击中 %d 次,发射 %d 次导弹,剩余 0 生命力,剩余 %d 导弹,摧毁 %d 架敌机,到达第 %d 关,共得 %d 分"), (t3 - t1) / 1000, e_lv, int(b_sc), m_mi, sc, cp + 1, m_sc - (t3 - t1) / 1000);
		//else
		//	str.Format(_T("战况记录:坚持 %d 秒,被击中 %d 次,发射 %d 次导弹,剩余 %d 生命力,剩余 %d 导弹,摧毁 %d 架敌机,到达第 %d 关,共得 %d 分"), (t3 - t1) / 1000, e_lv, int(b_sc), lv - (t3 - t1) / 1000, m_mi, sc, cp + 1, m_sc - (t3 - t1) / 1000);
		////dc.TextOut(0, 0, str);
		//	pMemDC->SetBkMode(TRANSPARENT);
		//	pMemDC->SetTextAlign(TA_LEFT);
		//	pMemDC->SetTextColor(RGB(255, 255, 0));
		//	pMemDC->TextOut(100, 230, str);
		//结束时的音乐
		mciSendString(_T("Close gamebg"), NULL, 0, NULL);//停止音乐
		mciSendString(_T("Open res\\music\\overbg.mp3 alias overbg"), NULL, 0, NULL);//打开文件
		mciSendString(_T("Play overbg"), NULL, 0, NULL);//播放音乐（重复）

	}
	
	//绘制 导弹、爆炸、敌机、子弹
	for(int i=0;i<4;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//复制内存DC到设备DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	if (m_pMe != NULL)
	{
		static int nCreator = rand() % 5 + 10;
	
		//随机产生敌机
		if (nCreator <= 0)
		{
			
			if (cp == 5)  //第6关
			{
				nCreator = rand() % 2 +7;
				m_ObjList[enEnemy].AddTail(new CEnemy);
			}
			else if (cp>=6&&cp<10) //第七关
			{
				nCreator = rand() % 2 + 6;
				m_ObjList[enEnemy].AddTail(new CEnemy);
			}
			else if (cp>=10)
			{
				nCreator = rand() % 1 + 1;
				m_ObjList[enEnemy].AddTail(new CEnemy);
			}
		    else

			{
				nCreator = rand() % (10 - cp * 2) + (23 - cp * 3);
				m_ObjList[enEnemy].AddTail(new CEnemy);
			}

		}
		nCreator--;
	}
	

		if (m_pMe == NULL)
			return;

		//检测四个方向键，移动战机
		for (int i = 0; i < 4; i++)
		{
			int nMeMotion = 0;
			m_pMe->SetVerMotion(0);
			m_pMe->SetHorMotion(0);

			nMeMotion = GetKey(VK_UP);
			if (nMeMotion == 1)
				m_pMe->SetVerMotion(2);//括号中为飞机移动速度

			nMeMotion = GetKey(VK_DOWN);
			if (nMeMotion == 1)
				m_pMe->SetVerMotion(-2);

			nMeMotion = GetKey(VK_RIGHT);
			if (nMeMotion == 1)
				m_pMe->SetHorMotion(2);

			nMeMotion = GetKey(VK_LEFT);
			if (nMeMotion == 1)
				m_pMe->SetHorMotion(-2);
		}
		// 关于大招   
		if (GetKey(VK_CONTROL) == 1 && m_mi > 0)   //获取CTRL键的值 并且 导弹数大于0
		{
					CPoint pt = (0, 0);
					if (m_br == 30 )
					{
						for (int i = 20; i <= 1350; i += 50)
							m_ObjList[enBomb].AddTail(new CBomb(pt.x + i, pt.y + 692));
						m_br -= 30;    //发射一次  大招值减30
						b_sc += 50;     //导弹数减十
					}
		
		}
	
		//产生战机导弹
		if (GetKey(VK_SPACE) == 1 && m_mi > 0)//按下了空格键 并且 导弹数大于0
		{
		
				if (m_pMe != NULL && m_pMe->Fired())
				{
					CPoint pt = m_pMe->GetPoint();
					if (m_sc-t < 500)  //分数
					{

						m_ObjList[enBomb].AddTail(new CBomb(pt.x + 45, pt.y + 0));
					}
					if (m_sc-t >= 500)
					{
						m_ObjList[enBomb].AddTail(new CBomb(pt.x + 22, pt.y + 20));
						m_ObjList[enBomb].AddTail(new CBomb(pt.x + 67, pt.y + 20));
					}
					if (m_sc-t >= 3000)
					{
						m_ObjList[enBomb].AddTail(new CBomb(pt.x + 0, pt.y + 40));
						m_ObjList[enBomb].AddTail(new CBomb(pt.x + 90, pt.y + 40));
					}
					if (m_sc-t >= 10000)
					{


						m_ObjList[enBomb].AddTail(new CBomb(pt.x + -10, pt.y + 40));
						m_ObjList[enBomb].AddTail(new CBomb(pt.x + 100, pt.y + 40));
						 

					}
					PlaySound(TEXT("res\\music\\attack.wav"), NULL, SND_FILENAME | SND_ASYNC);
					b_sc += 1;		//统计发射导弹数目  每发射一次算一个
					m_mi -= 1;      //导弹数
					b_i = b_sc / 5;
					if (b_i == int(b_i)) //根据导弹数目减少生命值
					{
						m_sc -= 1;
					}

				}
			
			
		}


		//敌机发射子弹

		CPoint PlanePt = m_pMe->GetPoint();
		for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
			if (!pEnemy->Fired())
				continue;
			CPoint  ePt = pEnemy->GetPoint();

			BOOL by = FALSE;

			//敌机在战机前面
			if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
				by = TRUE;
			//敌机在战机后面
			if (pEnemy->GetMontion() == -1 && ePt.y > PlanePt.y)
				by = TRUE;

			if (by && ePt.x >= PlanePt.x && ePt.x < PlanePt.x + CMyPlane::PLANE_WIDTH)
			{
				if (cp>=0)
				{
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 35, ePt.y + 25, pEnemy->GetMontion()));
				}
				if (cp >= 2)
				{
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 10, ePt.y + 25, pEnemy->GetMontion()));
					m_ObjList[enBall].AddTail(new CBall(ePt.x + 60, ePt.y + 25, pEnemy->GetMontion()));
				}

			}
		}
	
		//敌机子弹炸掉战机
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
			CRect bRect = pBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//生命值记录   分数记录
				lv -= 10 ; //生命值
				m_sc -= 15; //分数减少
				e_lv += 1;//击中次数统计
				//删除子弹
				m_ObjList[enBall].RemoveAt(bPos2);
				delete pBall;

				if (lv-t <= 0 )
				{
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
					//PlaySound(TEXT("res\\music\\die.wav"), NULL, SND_FILENAME | SND_ASYNC);
					//删除战机
					delete m_pMe;
					m_pMe = NULL;
					t3= GetTickCount();// 时间停止
					break;
				}
			}
		}
		//导弹剩余为0 
		if (m_mi == 0 && GetKey(VK_SHIFT)==1)
		{
			if (lv - t > 10)
			{
				lv -= 10;
				m_mi += 50;
			}
		}

		//战机导弹炸掉敌机
		POSITION mPos1 = NULL, mPos2 = NULL;
		for (mPos1 = m_ObjList[enBomb].GetHeadPosition(); (mPos2 = mPos1) != NULL;)
		{
			CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
			CRect bRect = pBomb->GetRect();

			POSITION ePos1 = NULL, ePos2 = NULL;
			for (ePos1 = m_ObjList[enEnemy].GetHeadPosition(); (ePos2 = ePos1) != NULL;)
			{
				CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
				CRect mRect = pEnemy->GetRect();
				CRect tmpRect;
				if (tmpRect.IntersectRect(&bRect, mRect))
				{

					//计分
					sc += 1;//敌机数
					if (sc/50==10)
						t4 = GetTickCount();// 获取时间
					m_mi += 5;//导弹数增加
					if (m_br<30)  //大招值最多30 也就是击毁30架敌机可以使用一次
						m_br += 1;//大招值加一
					if (lv < 300)
					{
						lv += 2;
						m_sc += 10 * (cp + 1);//得分数
					}
					else
					{
						m_sc += 10 * (cp + 1);//得分数
						m_sc += 2;
					}
					//添加爆炸效果
					m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
					//播放音乐
					PlaySound(TEXT("res\\music\\die.wav"), NULL, SND_FILENAME | SND_ASYNC);
					//删除导弹
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					//删除敌机
					m_ObjList[enEnemy].RemoveAt(ePos2);
					delete pEnemy;
					break;
					
				}
			}
		}

		//打开背景音乐
		mciSendString(_T("Open res\\music\\gamebg.mp3 alias gamebg"), NULL, 0, NULL);
		//播放背景音乐(重复播放)
		mciSendString(_T("Play gamebg repeat"), NULL, 0, NULL);
	
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{

	//刷新游戏帧画面: 在内存DC上绘图
	UpdateFrame(m_pMemDC);
	AI();
	CView::OnTimer(nIDEvent);
	//背景绘制  静态
	//CDC *pDC = GetDC();
	//CRect rect;
	//GetClientRect(&rect);
	//CBrush m_brushBackground;
	//CBitmap bg;
	//bg.LoadBitmap(IDB_BK);///加载位图
	//m_brushBackground.CreatePatternBrush(&bg);//创建位图画刷
	//m_pMemDC->FillRect(rect, &m_brushBackground);///用背景画刷填充区域

	//背景移动
	m_pMemDC->FillSolidRect(0, 0, 1364, 692, RGB(210, 210, 210));
	m_Images.Draw(m_pMemDC, 0, CPoint(m_x, m_y), ILD_TRANSPARENT);
	//m_pDC->BitBlt(0, 0, 2000, 2000, m_pMemDC, 0, 0, SRCCOPY);
	m_y++;
	if (m_y >= 0)
		m_y = -692;



	//左上角图片
	//CBitmap sec;
	//CImageList second;
	//sec.LoadBitmap(IDB_BXX);
	//second.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
	//second.Add(&sec, RGB(0, 0, 0));
	//second.Draw(m_pMemDC, 0, CPoint(0, 0), ILD_TRANSPARENT);


	//计分显示
	CString str;
	//计分
	if (lv - t > 0 && m_pMe != NULL)
		str.Format(_T("累计得 %d 分"), m_sc - t);  //时间增加一秒  分值减一
	else
		str.Format(_T("累计得 %d 分"), m_sc - (t3 - t1) / 1000);  //时间增加一秒  分值减一		
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (m_sc - t > 0)
		m_pMemDC->SetTextColor(RGB(102, 204, 51));
	else
		m_pMemDC->SetTextColor(RGB(255, 0, 0));
	m_pMemDC->TextOut(10, 0, str);

	//摧毁敌机
	str.Format(_T("摧毁 %d 架敌机"), sc);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	m_pMemDC->SetTextColor(RGB(102, 204, 51));  //绿色
	m_pMemDC->TextOut(10, 16, str);

	//生命值显示
	if (m_pMe != NULL||cp>19)
		str.Format(_T("生命值：%d/300 "), lv - t);
	if(m_pMe == NULL && cp<19)
		str.Format(_T("生命值：%d/300 "),lv-(t3-t1)/1000);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (lv - t >= 150)
		m_pMemDC->SetTextColor(RGB(102, 204, 51));  //绿色
	else
	{
		if (t % 2 == 0)
			m_pMemDC->SetTextColor(RGB(255, 0, 0));
		if (t % 2 == 1)
			m_pMemDC->SetTextColor(RGB(255, 255, 0));
	}
	if (lv - t >=150  || m_pMe== NULL)
	{
		m_pMemDC->TextOut(10, 32, str);
	}
	else
	{
		m_pMemDC->TextOut(10, 32, str);
		m_pMemDC->TextOut(600, 280, str);
	}
	//关卡显示
	cp = sc / 50;
	if (cp<=9)
		str.Format(_T("处于第 %d 关 "), cp + 1);
	if (cp>=10)
		str.Format(_T("看你还能坚挺几秒"));
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	m_pMemDC->SetTextColor(RGB(255, 255, 204));
	m_pMemDC->TextOut(10, 48, str);

	//被击中次数
	str.Format(_T("被击中 %d 次 "), e_lv);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (e_lv == 0)
		m_pMemDC->SetTextColor(RGB(102, 204, 51));
	else
		m_pMemDC->SetTextColor(RGB(255, 0, 0));
	m_pMemDC->TextOut(10, 64, str);

	//战机损坏程度
	if (b_sc==0)
		str.Format(_T("命中率 0.00%% "));
	else
	str.Format(_T("命中率 %.2f%% "), (sc*1.0 /b_sc)*100);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	if ((sc*1.0 / b_sc) * 100 >= 20)
		m_pMemDC->SetTextColor(RGB(102, 204, 51));
	else
	{
		if (t % 2 == 0)
			m_pMemDC->SetTextColor(RGB(255, 0, 0));
		if (t % 2 == 1)
			m_pMemDC->SetTextColor(RGB(255, 255, 0));
	}
	m_pMemDC->TextOut(10, 80, str);

	//导弹数目
	if (m_mi > 0)
	{
		str.Format(_T("剩余发射导弹次数：%d"), m_mi);
	}
	else
	{
		str.Format(_T("按 SHIFT 键重新加载导弹"));
	}
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (m_mi > 0) 
		m_pMemDC->SetTextColor(RGB(102, 204, 51));
	else
	{
		if (t % 2 == 0)
			m_pMemDC->SetTextColor(RGB(255, 0, 0));
		if (t % 2 == 1)
			m_pMemDC->SetTextColor(RGB(255, 255, 0));
	}
	if (m_mi > 0 ||  m_pMe == NULL)
		m_pMemDC->TextOut(10, 96, str);
	else
	{
		m_pMemDC->TextOut(600, 300, str);
		m_pMemDC->TextOut(10, 96, str);
	}
	//关于大招
	if (m_br == 30)
	{
		str.Format(_T("按 CTRL 键发大招"));
	}
	else
	{
		str.Format(_T("大招值：%d/30"), m_br);
	}
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (m_br == 30)
	{
		if (t % 2 == 0)
			m_pMemDC->SetTextColor(RGB(102, 204, 51));
		if (t % 2 == 1)
			m_pMemDC->SetTextColor(RGB(255, 255, 0));
	}
	else
		m_pMemDC->SetTextColor(RGB(255, 0, 0));
	if (m_br == 30 && m_pMe != NULL)
	{
		m_pMemDC->TextOut(10, 112, str);
		m_pMemDC->TextOut(600, 320, str);
	}
	else
	{
		m_pMemDC->TextOut(10, 112, str);
	}
	

	//计算运行时间
	t2 = GetTickCount();//程序段运行时间(ms)   
	t = (t2 - t1) / 1000;
		
	if (m_pMe == NULL&&t3!=0)
		str.Format(_T("已经进行 %d 秒"), (t3 - t1) / 1000);
	else
		str.Format(_T("已经进行 %d 秒"), t);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  透明背景
	m_pMemDC->SetTextAlign(TA_LEFT);
	m_pMemDC->SetTextColor(RGB(51, 255, 255));
	m_pMemDC->TextOut(10, 128, str);


	// 关卡	
	CBitmap fir;
	CImageList first;

	if (cp == 0)
	{
		fir.LoadBitmap(IDB_FIR);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z1), ILD_TRANSPARENT);
		m_z1+= 4;
	}
	if (cp == 1)
	{
		fir.LoadBitmap(IDB_SEC);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z2), ILD_TRANSPARENT);
		m_z2+=4;
	}

	if (cp == 2)
	{
		fir.LoadBitmap(IDB_THR);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z3), ILD_TRANSPARENT);
		m_z3+=4;
		m_y+=1;
	}
	if (cp == 3)
	{
		fir.LoadBitmap(IDB_FOU);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z4), ILD_TRANSPARENT);
		m_z4+=4;
		m_y+=1;
	}
	if (cp == 4)
	{	
		fir.LoadBitmap(IDB_FIV);
	    first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
	    first.Add(&fir, RGB(0, 0, 0));
	    first.Draw(m_pMemDC, 0, CPoint(m_x, m_z5), ILD_TRANSPARENT);
	    m_z5+=4;
		m_y+=1;
    }
	if (cp == 5)
	{
		fir.LoadBitmap(IDB_SIX);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z6), ILD_TRANSPARENT);
		m_z6+=4;
		m_y+=2;
	}
	if (cp == 6)
	{
		fir.LoadBitmap(IDB_SEV);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z7), ILD_TRANSPARENT);
		m_z7+=4;
		m_y+=2;
	}
	if (cp == 7)
	{
		fir.LoadBitmap(IDB_EIG);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z8), ILD_TRANSPARENT);
		m_z8+=4;
		m_y+=2;
	}
	if (cp == 8)
	{
		fir.LoadBitmap(IDB_NIN);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z9), ILD_TRANSPARENT);
		m_z9+=4;
		m_y+=3;
	}
	if (cp == 9)
	{
		fir.LoadBitmap(IDB_TEN);
		first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
		first.Add(&fir, RGB(0, 0, 0));
		first.Draw(m_pMemDC, 0, CPoint(m_x, m_z10), ILD_TRANSPARENT);
		m_z10+=4;
		m_y+=3;
	}
	if (cp >= 10&&cp<=19 )
	{
			fir.LoadBitmap(IDB_ELE);
			first.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
			first.Add(&fir, RGB(0, 0, 0));
			first.Draw(m_pMemDC, 0, CPoint(m_x, m_z11), ILD_TRANSPARENT);
			m_z11 += 4;
	    	m_y+=3;
	}

	if (cp>19) //通关
	{
		delete m_pMe;
		m_pMe = NULL;
	   m_y += 3;
	}
}

