#include "StdAfx.h"
#include "Enemy.h"
#include "resource.h"


CImageList CEnemy::m_Images;

CEnemy::CEnemy(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand()%(GAME_WIDTH-ENEMY_HEIGHT)+1;

	//���ȷ��ͼ������
	m_nImgIndex = rand()%5;


	//����ͼ������ȷ������
	m_nMotion=1;
	m_ptPos.y=-ENEMY_HEIGHT;
	if (m_nImgIndex%2!=0)//�����ͼ��������ż��
	{
		m_nMotion=-1;
		m_ptPos.y = GAME_HEIGHT+ENEMY_HEIGHT;
	}
	//���ȷ���ٶ�
	m_V = rand()%8+2;

	m_nWait=0;
}

CEnemy::~CEnemy(void)
{
}
BOOL CEnemy::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_ENEMY,RGB(0,0,0),80,80,5);
}
BOOL CEnemy::Draw(CDC* pDC,BOOL bPause)
{
	
		m_nWait++;
		if (m_nWait > 20)
			m_nWait = 0;

		if (!bPause)
		{
			m_ptPos.y = m_ptPos.y + m_nMotion * m_V;
		}

		if (m_ptPos.y > GAME_HEIGHT + ENEMY_HEIGHT)
			return FALSE;
		if (m_ptPos.y < -ENEMY_HEIGHT)
			return FALSE;

		m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

		return TRUE;
	
}
BOOL CEnemy::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;
}