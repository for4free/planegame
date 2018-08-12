// PlaneGameView.h : CPlaneGameView 类的接口
//


#pragma once

class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType{ enEnemy, enBomb, enBall, enExplosion };

protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 属性
public:
	CPlaneGameDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//*******TEACHER*****
protected:
	//内存DC
	CDC*        m_pMemDC;
	//设备DC
	CClientDC*  m_pDC;
	//内存位图
	CBitmap*    m_pMemBitmap;

protected:
	//初始化游戏
	BOOL InitGame();
	//结束游戏
	void StopGame();



	//刷新游戏的帧画面
	void UpdateFrame(CDC* pMemDC);
	int m_x;
	int m_y;
	int m_z1 = -280, m_z2 = -280, m_z3 = -280, m_z4 = -280, m_z5 = -280, m_z6 = -280, m_z7 = -280, m_z8 = -280, m_z9 = -280, m_z10 = -280;//关卡显示
	int m_z11 = -280;
	//背景图
	CImageList m_Images;


	void AI();

	//获得键的状态1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;

	CObList    m_ObjList[4];

//计分  生命值  关卡 等
private:
	int sc=0;//存储摧毁敌机成功一次, 加1
	int lv=300 ;//储存被战机生命值 每次减10  
	int e_lv =0;  //被击中次数
	float  b_sc = 0;// 统计导弹发射次数
	float  b_i=0;
	int cp;//关于关卡
	int m_sc=0;//储存分数，击毁敌机得分“10*cp”
	int m_br=0;//关于大招的变量
	int m_mi = 100;//导弹数目
	long t1=0;
	long t2=0;// 计算时间
	long t=0;
	long t3=0;
	long t4 = 0;//获取关卡时间
	

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

