// PlaneGameView.cpp : CPlaneGameView ���ʵ��
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
//��������
#include <mmsystem.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

END_MESSAGE_MAP()

// CPlaneGameView ����/����

CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
	
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	


	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������



//********TEAVHER*******


void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ϸ
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

		 t1 = GetTickCount();  //����ο�ʼǰȡ��ϵͳ����ʱ��(ms)   


	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();

	//��������(ս��)
	m_pMe = new CMyPlane;

	//������Ϸ
	SetTimer(1,30,NULL);

	//���ر���ͼ ����ͼ�ƶ���ش���
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
	//�������
	//pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,0);//RGB(84, 142, 239)

	//�����ҷ�ս��
	if (m_pMe != NULL)
	{
		m_pMe->Draw(m_pMemDC, FALSE);

	}
	else
	{  
		//game over
		//����������
		//CDC *pDC = GetDC();
		//CRect rect;
		//GetClientRect(&rect);
		//CBrush m_brushBackground;
		//CBitmap bg;
		//bg.LoadBitmap(IDB_GO);///����λͼ
		//m_brushBackground.CreatePatternBrush(&bg);//����λͼ��ˢ
		//m_pMemDC->FillRect(rect, &m_brushBackground);///�ñ�����ˢ�������
		//��������
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

		//����ҳ����ʾ�Ʒ�
		//CString str;
		//if (lv - (t3 - t1) / 1000<=0)
		//	str.Format(_T("ս����¼:��� %d ��,������ %d ��,���� %d �ε���,ʣ�� 0 ������,ʣ�� %d ����,�ݻ� %d �ܵл�,����� %d ��,���� %d ��"), (t3 - t1) / 1000, e_lv, int(b_sc), m_mi, sc, cp + 1, m_sc - (t3 - t1) / 1000);
		//else
		//	str.Format(_T("ս����¼:��� %d ��,������ %d ��,���� %d �ε���,ʣ�� %d ������,ʣ�� %d ����,�ݻ� %d �ܵл�,����� %d ��,���� %d ��"), (t3 - t1) / 1000, e_lv, int(b_sc), lv - (t3 - t1) / 1000, m_mi, sc, cp + 1, m_sc - (t3 - t1) / 1000);
		////dc.TextOut(0, 0, str);
		//	pMemDC->SetBkMode(TRANSPARENT);
		//	pMemDC->SetTextAlign(TA_LEFT);
		//	pMemDC->SetTextColor(RGB(255, 255, 0));
		//	pMemDC->TextOut(100, 230, str);
		//����ʱ������
		mciSendString(_T("Close gamebg"), NULL, 0, NULL);//ֹͣ����
		mciSendString(_T("Open res\\music\\overbg.mp3 alias overbg"), NULL, 0, NULL);//���ļ�
		mciSendString(_T("Play overbg"), NULL, 0, NULL);//�������֣��ظ���

	}
	
	//���� ��������ը���л����ӵ�
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

	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	if (m_pMe != NULL)
	{
		static int nCreator = rand() % 5 + 10;
	
		//��������л�
		if (nCreator <= 0)
		{
			
			if (cp == 5)  //��6��
			{
				nCreator = rand() % 2 +7;
				m_ObjList[enEnemy].AddTail(new CEnemy);
			}
			else if (cp>=6&&cp<10) //���߹�
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

		//����ĸ���������ƶ�ս��
		for (int i = 0; i < 4; i++)
		{
			int nMeMotion = 0;
			m_pMe->SetVerMotion(0);
			m_pMe->SetHorMotion(0);

			nMeMotion = GetKey(VK_UP);
			if (nMeMotion == 1)
				m_pMe->SetVerMotion(2);//������Ϊ�ɻ��ƶ��ٶ�

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
		// ���ڴ���   
		if (GetKey(VK_CONTROL) == 1 && m_mi > 0)   //��ȡCTRL����ֵ ���� ����������0
		{
					CPoint pt = (0, 0);
					if (m_br == 30 )
					{
						for (int i = 20; i <= 1350; i += 50)
							m_ObjList[enBomb].AddTail(new CBomb(pt.x + i, pt.y + 692));
						m_br -= 30;    //����һ��  ����ֵ��30
						b_sc += 50;     //��������ʮ
					}
		
		}
	
		//����ս������
		if (GetKey(VK_SPACE) == 1 && m_mi > 0)//�����˿ո�� ���� ����������0
		{
		
				if (m_pMe != NULL && m_pMe->Fired())
				{
					CPoint pt = m_pMe->GetPoint();
					if (m_sc-t < 500)  //����
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
					b_sc += 1;		//ͳ�Ʒ��䵼����Ŀ  ÿ����һ����һ��
					m_mi -= 1;      //������
					b_i = b_sc / 5;
					if (b_i == int(b_i)) //���ݵ�����Ŀ��������ֵ
					{
						m_sc -= 1;
					}

				}
			
			
		}


		//�л������ӵ�

		CPoint PlanePt = m_pMe->GetPoint();
		for (POSITION ePos = m_ObjList[enEnemy].GetHeadPosition(); ePos != NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
			if (!pEnemy->Fired())
				continue;
			CPoint  ePt = pEnemy->GetPoint();

			BOOL by = FALSE;

			//�л���ս��ǰ��
			if (pEnemy->GetMontion() == 1 && ePt.y < PlanePt.y)
				by = TRUE;
			//�л���ս������
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
	
		//�л��ӵ�ը��ս��
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
			CRect bRect = pBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
				//����ֵ��¼   ������¼
				lv -= 10 ; //����ֵ
				m_sc -= 15; //��������
				e_lv += 1;//���д���ͳ��
				//ɾ���ӵ�
				m_ObjList[enBall].RemoveAt(bPos2);
				delete pBall;

				if (lv-t <= 0 )
				{
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
					//PlaySound(TEXT("res\\music\\die.wav"), NULL, SND_FILENAME | SND_ASYNC);
					//ɾ��ս��
					delete m_pMe;
					m_pMe = NULL;
					t3= GetTickCount();// ʱ��ֹͣ
					break;
				}
			}
		}
		//����ʣ��Ϊ0 
		if (m_mi == 0 && GetKey(VK_SHIFT)==1)
		{
			if (lv - t > 10)
			{
				lv -= 10;
				m_mi += 50;
			}
		}

		//ս������ը���л�
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

					//�Ʒ�
					sc += 1;//�л���
					if (sc/50==10)
						t4 = GetTickCount();// ��ȡʱ��
					m_mi += 5;//����������
					if (m_br<30)  //����ֵ���30 Ҳ���ǻ���30�ܵл�����ʹ��һ��
						m_br += 1;//����ֵ��һ
					if (lv < 300)
					{
						lv += 2;
						m_sc += 10 * (cp + 1);//�÷���
					}
					else
					{
						m_sc += 10 * (cp + 1);//�÷���
						m_sc += 2;
					}
					//��ӱ�ըЧ��
					m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
					//��������
					PlaySound(TEXT("res\\music\\die.wav"), NULL, SND_FILENAME | SND_ASYNC);
					//ɾ������
					m_ObjList[enBomb].RemoveAt(mPos2);
					delete pBomb;
					//ɾ���л�
					m_ObjList[enEnemy].RemoveAt(ePos2);
					delete pEnemy;
					break;
					
				}
			}
		}

		//�򿪱�������
		mciSendString(_T("Open res\\music\\gamebg.mp3 alias gamebg"), NULL, 0, NULL);
		//���ű�������(�ظ�����)
		mciSendString(_T("Play gamebg repeat"), NULL, 0, NULL);
	
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{

	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	UpdateFrame(m_pMemDC);
	AI();
	CView::OnTimer(nIDEvent);
	//��������  ��̬
	//CDC *pDC = GetDC();
	//CRect rect;
	//GetClientRect(&rect);
	//CBrush m_brushBackground;
	//CBitmap bg;
	//bg.LoadBitmap(IDB_BK);///����λͼ
	//m_brushBackground.CreatePatternBrush(&bg);//����λͼ��ˢ
	//m_pMemDC->FillRect(rect, &m_brushBackground);///�ñ�����ˢ�������

	//�����ƶ�
	m_pMemDC->FillSolidRect(0, 0, 1364, 692, RGB(210, 210, 210));
	m_Images.Draw(m_pMemDC, 0, CPoint(m_x, m_y), ILD_TRANSPARENT);
	//m_pDC->BitBlt(0, 0, 2000, 2000, m_pMemDC, 0, 0, SRCCOPY);
	m_y++;
	if (m_y >= 0)
		m_y = -692;



	//���Ͻ�ͼƬ
	//CBitmap sec;
	//CImageList second;
	//sec.LoadBitmap(IDB_BXX);
	//second.Create(1366, 696, ILC_COLOR24 | ILC_MASK, 1, 0);
	//second.Add(&sec, RGB(0, 0, 0));
	//second.Draw(m_pMemDC, 0, CPoint(0, 0), ILD_TRANSPARENT);


	//�Ʒ���ʾ
	CString str;
	//�Ʒ�
	if (lv - t > 0 && m_pMe != NULL)
		str.Format(_T("�ۼƵ� %d ��"), m_sc - t);  //ʱ������һ��  ��ֵ��һ
	else
		str.Format(_T("�ۼƵ� %d ��"), m_sc - (t3 - t1) / 1000);  //ʱ������һ��  ��ֵ��һ		
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (m_sc - t > 0)
		m_pMemDC->SetTextColor(RGB(102, 204, 51));
	else
		m_pMemDC->SetTextColor(RGB(255, 0, 0));
	m_pMemDC->TextOut(10, 0, str);

	//�ݻٵл�
	str.Format(_T("�ݻ� %d �ܵл�"), sc);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
	m_pMemDC->SetTextAlign(TA_LEFT);
	m_pMemDC->SetTextColor(RGB(102, 204, 51));  //��ɫ
	m_pMemDC->TextOut(10, 16, str);

	//����ֵ��ʾ
	if (m_pMe != NULL||cp>19)
		str.Format(_T("����ֵ��%d/300 "), lv - t);
	if(m_pMe == NULL && cp<19)
		str.Format(_T("����ֵ��%d/300 "),lv-(t3-t1)/1000);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (lv - t >= 150)
		m_pMemDC->SetTextColor(RGB(102, 204, 51));  //��ɫ
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
	//�ؿ���ʾ
	cp = sc / 50;
	if (cp<=9)
		str.Format(_T("���ڵ� %d �� "), cp + 1);
	if (cp>=10)
		str.Format(_T("���㻹�ܼ�ͦ����"));
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
	m_pMemDC->SetTextAlign(TA_LEFT);
	m_pMemDC->SetTextColor(RGB(255, 255, 204));
	m_pMemDC->TextOut(10, 48, str);

	//�����д���
	str.Format(_T("������ %d �� "), e_lv);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
	m_pMemDC->SetTextAlign(TA_LEFT);
	if (e_lv == 0)
		m_pMemDC->SetTextColor(RGB(102, 204, 51));
	else
		m_pMemDC->SetTextColor(RGB(255, 0, 0));
	m_pMemDC->TextOut(10, 64, str);

	//ս���𻵳̶�
	if (b_sc==0)
		str.Format(_T("������ 0.00%% "));
	else
	str.Format(_T("������ %.2f%% "), (sc*1.0 /b_sc)*100);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
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

	//������Ŀ
	if (m_mi > 0)
	{
		str.Format(_T("ʣ�෢�䵼��������%d"), m_mi);
	}
	else
	{
		str.Format(_T("�� SHIFT �����¼��ص���"));
	}
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
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
	//���ڴ���
	if (m_br == 30)
	{
		str.Format(_T("�� CTRL ��������"));
	}
	else
	{
		str.Format(_T("����ֵ��%d/30"), m_br);
	}
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
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
	

	//��������ʱ��
	t2 = GetTickCount();//���������ʱ��(ms)   
	t = (t2 - t1) / 1000;
		
	if (m_pMe == NULL&&t3!=0)
		str.Format(_T("�Ѿ����� %d ��"), (t3 - t1) / 1000);
	else
		str.Format(_T("�Ѿ����� %d ��"), t);
	//dc.TextOut(0, 0, str);
	m_pMemDC->SetBkMode(TRANSPARENT);//  ͸������
	m_pMemDC->SetTextAlign(TA_LEFT);
	m_pMemDC->SetTextColor(RGB(51, 255, 255));
	m_pMemDC->TextOut(10, 128, str);


	// �ؿ�	
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

	if (cp>19) //ͨ��
	{
		delete m_pMe;
		m_pMe = NULL;
	   m_y += 3;
	}
}

