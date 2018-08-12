// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//


#pragma once

class CMyPlane;
class CPlaneGameView : public CView
{

	enum ObjType{ enEnemy, enBomb, enBall, enExplosion };

protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//*******TEACHER*****
protected:
	//�ڴ�DC
	CDC*        m_pMemDC;
	//�豸DC
	CClientDC*  m_pDC;
	//�ڴ�λͼ
	CBitmap*    m_pMemBitmap;

protected:
	//��ʼ����Ϸ
	BOOL InitGame();
	//������Ϸ
	void StopGame();



	//ˢ����Ϸ��֡����
	void UpdateFrame(CDC* pMemDC);
	int m_x;
	int m_y;
	int m_z1 = -280, m_z2 = -280, m_z3 = -280, m_z4 = -280, m_z5 = -280, m_z6 = -280, m_z7 = -280, m_z8 = -280, m_z9 = -280, m_z10 = -280;//�ؿ���ʾ
	int m_z11 = -280;
	//����ͼ
	CImageList m_Images;


	void AI();

	//��ü���״̬1->down
	int GetKey(int nVirtKey)
	{
		return (GetKeyState(nVirtKey) & 0x8000)? 1 : 0;
	}
	
	CMyPlane*  m_pMe;

	CObList    m_ObjList[4];

//�Ʒ�  ����ֵ  �ؿ� ��
private:
	int sc=0;//�洢�ݻٵл��ɹ�һ��, ��1
	int lv=300 ;//���汻ս������ֵ ÿ�μ�10  
	int e_lv =0;  //�����д���
	float  b_sc = 0;// ͳ�Ƶ����������
	float  b_i=0;
	int cp;//���ڹؿ�
	int m_sc=0;//������������ٵл��÷֡�10*cp��
	int m_br=0;//���ڴ��еı���
	int m_mi = 100;//������Ŀ
	long t1=0;
	long t2=0;// ����ʱ��
	long t=0;
	long t3=0;
	long t4 = 0;//��ȡ�ؿ�ʱ��
	

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

