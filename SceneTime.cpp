//============================================================================================================
//
//  [SCeneTime.cpp] Author : Masaki Kuboki
//		2018/08/21:���񐔏����ɕύX
//============================================================================================================
#include "main.h"
#include "2D.h"
#include "SceneTime.h"
#include "ScenePlayer.h"
#include "RendererDX.h"
#include "Number.h"

//============================================================================================================
//
// �}�N��
//
//============================================================================================================
#define SCORE_POS_X (800.0f)
#define SCORE_POS_Y (750.0f)
#define PRIORITY (2)
#define SCALE (0.3f)

#define SECOND (10)
static bool g_bGetFinish = false;
//============================================================================================================
//
//
//
//============================================================================================================
CSceneTime::CSceneTime(int Priority) :CScene(Priority)
{
	m_pDevice = CRendererDX::GetD3DDevice();
	m_nPriority;

	m_PlayerPos = CScenePlayer::GetPosition();

	m_tcx = 0;	// �e�N�X�`���̐؂�����W�iX�j
	m_tcy = 0;	// �e�N�X�`���̐؂�����W�iY�j
	m_tcw = 0;	// �e�N�X�`���̐؂��蕝�i���j
	m_tch = 0;	// �e�N�X�`���̐؂��蕝�i�c�j
	
	m_fScale  = 0.3f;	// �g��E�k���i�S���j
	m_fScaleX = 0.3f;	// �g��E�k���iX�j
	m_fScaleY = 0.3f;	// �g��E�k���iY�j

	m_bFinish = false;	// �Q�[���I�����ǂ���
	m_nTime = 0;		// �o�ߎ���
	m_nTimeCnt = 0;		// ���t���[���J�E���g

	m_nScore = 0;		// �X�R�A�i�o�ߎ��ԁj

	// 0.1�b
	m_nTime0 = 0;
	m_nTimeCnt0 = 0;
	m_tcx0 = 0;
	m_tcy0 = 0;

	// 0.01�b
	m_nTime00 = 0;
	m_tcx00 = 0;
	m_tcy00 = 0;

	// 10�b
	m_nTimeCnt10 = 0;
	m_nTime10 = 0;
	m_tcx10 = 0;
	m_tcy10 = 0;

	// 1��
	m_nTimeCnt100 = 0;
	m_nTime100 = 0;
	m_tcx100 = 0;
	m_tcy100 = 0;

	// ���b�v�^�C��
	m_nLapTime00[0] = 0;
	m_nLapTime00[1] = 0;
	m_nLapTime00[2] = 0;

	m_nLapTime0[0] = 0;
	m_nLapTime0[1] = 0;
	m_nLapTime0[2] = 0;

	m_nLapTime[0] = 0;
	m_nLapTime[1] = 0;
	m_nLapTime[2] = 0;

	m_nLapTime10[0] = 0;
	m_nLapTime10[1] = 0;
	m_nLapTime10[2] = 0;

	m_nLapTime100[0] = 0;
	m_nLapTime100[1] = 0;
	m_nLapTime100[2] = 0;

	m_fLapScale = 0.12f;

	// ����
	m_nLapCnt = 0; 
	m_bLap = false;

	m_nAlpha = 0;
	m_bAlphaSwitch = false;

	m_fResultLapScale = 0.35f;

	m_nCountdown = 0;
	m_nCountdown2 = 0;
	m_nCountdownCnt = 0;
	m_bStart = false;

}

//============================================================================================================
//
//  Create
//
//============================================================================================================
CSceneTime *CSceneTime::Create(void)
{
	CSceneTime *SceneTime = new CSceneTime(PRIORITY);
	SceneTime->Init();
	return SceneTime;
}

//============================================================================================================
//
// Init
//
//============================================================================================================
void CSceneTime::Init(void)
{
	m_nLapCnt = 0;
	m_bFinish = false;

	m_nLapTime00[0] = 0;
	m_nLapTime00[1] = 0;
	m_nLapTime00[2] = 0;

	m_nLapTime0[0] = 0;
	m_nLapTime0[1] = 0;
	m_nLapTime0[2] = 0;

	m_nLapTime[0] = 0;
	m_nLapTime[1] = 0;
	m_nLapTime[2] = 0;

	m_nLapTime10[0] = 0;
	m_nLapTime10[1] = 0;
	m_nLapTime10[2] = 0;

	m_nLapTime100[0] = 0;
	m_nLapTime100[1] = 0;
	m_nLapTime100[2] = 0;

	//m_bGetFinish = false;

	m_PlayerPos = CScenePlayer::GetPosition();
	m_PlayerPosSetX = 0.0f;
	m_PlayerPosSetY = 0.0f;

	m_nCountdown = 4;
	m_nCountdown2 = 0;
	m_nCountdownCnt = 0;
	m_bStart = false;
}

//============================================================================================================
//
// Uninit
//
//============================================================================================================
void CSceneTime::Uninit(void)
{

}

//============================================================================================================
//
// �X�V
//
//============================================================================================================
void CSceneTime::Update(void)
{	
	// �J�E���g�_�E���I����^�C���v���J�n
	if (!m_bStart)
	{
		m_nCountdownCnt++;
		if (m_nCountdownCnt >= 60)
		{
			m_nCountdown--;
			m_nCountdownCnt = 0;
		}

		if (m_nCountdown <= 0) { m_bStart = true; }
	}
	else
	{


		if (!m_bFinish)
		{

			//******* �^�C�� ****************************
			m_nTimeCnt++;
			m_nTimeCnt0++;
			m_nTime00++;
			m_nTimeCnt10++;

			m_nTime0 = m_nTimeCnt0 / 6;			// 0.1�b
			m_nTime = m_nTimeCnt / 60;			// 1�b
			m_nTime10 = m_nTimeCnt10 / 600;		// 10�b

												// 0.01�b
			if (m_nTime00 >= 10)
			{
				m_nTime00 = 0;
			}

			// 0.1�b
			if (m_nTime0 >= 10)
			{
				m_nTime0 = 0;
				m_nTimeCnt0 = 0;
			}

			// 1�b
			if (m_nTime >= 10)
			{
				m_nTime = 0;
				m_nTimeCnt = 0;
			}

			// 10�b
			if (m_nTime10 >= 6)
			{
				m_nTime10 = 0;
				m_nTimeCnt10 = 0;

				m_nTime100++;
			}

			//**********************************************

			// ����
			//if ((-20.0f <= CScenePlayer::GetPosition().z) && (CScenePlayer::GetPosition().z <= 20.0f)
			//	&& (0.0f <= CScenePlayer::GetPosition().x) && (CScenePlayer::GetPosition().x <= 3.0f))
			// ��s��
			if ((-25.0f <= CScenePlayer::GetPosition().x) && (CScenePlayer::GetPosition().x <= 25.0f)
				&& (-8.0f <= CScenePlayer::GetPosition().z) && (CScenePlayer::GetPosition().z <= -5.0f))
			{
				
					
				if (!m_bLap)
				{
					m_nLapCnt++;

					if (m_nLapCnt >= 1)
					{
						m_nLapTime00[m_nLapCnt - 1] = m_nTime00;
						m_nLapTime0[m_nLapCnt - 1] = m_nTime0;
						m_nLapTime[m_nLapCnt - 1] = m_nTime;
						m_nLapTime10[m_nLapCnt - 1] = m_nTime10;
						m_nLapTime100[m_nLapCnt - 1] = m_nTime100;

						// ���񐔉��Z����
					
						m_bLap = true;

						// �^�C������
						// 1�b
						m_nTime = 0;
						m_nTimeCnt = 0;

						// 0.1�b
						m_nTime0 = 0;
						m_nTimeCnt0 = 0;

						// 0.01�b
						m_nTime00 = 0;
						m_nTimeCnt00 = 0;

						// 10�b
						m_nTimeCnt10 = 0;
						m_nTime10 = 0;


						m_nTime100 = 0;
					}
				}
			}
			else
			{
				m_bLap = false;
			}
		}

		if (m_nLapCnt >= 3)
		{
			m_bFinish = true;
			g_bGetFinish = true;

			if (m_bAlphaSwitch)
			{
				m_nAlpha -= 5;

				if (m_nAlpha <= 0)m_bAlphaSwitch = false;
			}
			else
			{
				m_nAlpha += 5;

				if (m_nAlpha >= 255)m_bAlphaSwitch = true;
			}
		}

	}

	m_PlayerPos = CScenePlayer::GetPosition();

	m_PlayerPosSetX = -m_PlayerPos.x;
	m_PlayerPosSetY = m_PlayerPos.z;

}

//============================================================================================================
//
// �`��
//
//============================================================================================================
void CSceneTime::Draw(void)
{
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	if (!m_bStart)
	{
		m_nCountdown2 = m_nCountdown - 1;
		if (m_nCountdown2 == 3) { C2D::Draw(TEXTURE_COUNTDOWN_3,  0, 0, 512, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.5f, 0.5f, { 825.0f,300.0f,0.0f }, true); }
		if (m_nCountdown2 == 2) { C2D::Draw(TEXTURE_COUNTDOWN_2,  0, 0, 512, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.5f, 0.5f, { 825.0f,300.0f,0.0f }, true); }
		if (m_nCountdown2 == 1) { C2D::Draw(TEXTURE_COUNTDOWN_1,  0, 0, 512, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.5f, 0.5f, { 825.0f,300.0f,0.0f }, true); }
		if (m_nCountdown2 <= 0) { C2D::Draw(TEXTURE_COUNTDOWN_GO, 0, 0, 768, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.5f, 0.5f, { 765.0f,300.0f,0.0f }, true); }
	}



	// �~�j�}�b�v
	C2D::Draw(TEXTURE_MINIMAP_BACKGROUND, 0, 0, 256, 256, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.25f, 1.35f, { 25.0f,													  430.0f,0.0f }, true );
	C2D::Draw(TEXTURE_MINIMAP,			  0, 0, 599, 1043,D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f,  0.4f, 0.35f, { 70.0f,													  420.0f,0.0f }, true );
	C2D::Draw(TEXTURE_MINIPLAYER,		  0, 0, 711, 711, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.08f, 0.08f, { 75.0f + m_PlayerPosSetX * 0.1f, 650.0f + m_PlayerPosSetY * 0.1f,0.0f }, true );
	
	// ���݃��b�v�^�C��
	C2D::Draw(TEXTURE_TIME,	        0, 0, 1280, 128, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 25.0f,170.0f,0.0f }, true);
	C2D::Draw(TEXTURE_TIME_HISTORY, 0, 0, 1280, 128, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 25.0f,212.0f,0.0f }, true);
				
	// �ߋ����b�v�^�C��
	C2D::Draw(TEXTURE_TIME_LAP,     0, 0, 1280, 128, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 25.0f,254.0f,0.0f }, true);
	C2D::Draw(TEXTURE_TIME_HISTORY, 0, 0, 1280, 128, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 25.0f,296.0f,0.0f }, true);
	C2D::Draw(TEXTURE_TIME_HISTORY, 0, 0, 1280, 128, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 25.0f,338.0f,0.0f }, true);
	C2D::Draw(TEXTURE_TIME_HISTORY, 0, 0, 1280, 128, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 25.0f,380.0f,0.0f }, true);
	
	// �^�C��
	CSceneNumber::Draw(m_nTime100,		D3DCOLOR_RGBA(255, 255, 255, 255),						  125.0f, 213.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			D3DCOLOR_RGBA(255, 255, 255, 255), 150.0f * m_fLapScale + 125.0f, 213.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nTime10,		D3DCOLOR_RGBA(255, 255, 255, 255), 300.0f * m_fLapScale + 125.0f, 213.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nTime,			D3DCOLOR_RGBA(255, 255, 255, 255), 450.0f * m_fLapScale + 125.0f, 213.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			D3DCOLOR_RGBA(255, 255, 255, 255), 600.0f * m_fLapScale + 125.0f, 213.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nTime0,		D3DCOLOR_RGBA(255, 255, 255, 255), 750.0f * m_fLapScale + 125.0f, 213.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nTime00,		D3DCOLOR_RGBA(255, 255, 255, 255), 900.0f * m_fLapScale + 125.0f, 213.0f, m_fLapScale, m_fLapScale);

	// ���b�v�P
	CSceneNumber::Draw(m_nLapTime100[0],D3DCOLOR_RGBA(255, 255, 255, 255),						  125.0f, 298.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			D3DCOLOR_RGBA(255, 255, 255, 255), 150.0f * m_fLapScale + 125.0f, 298.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime10[0], D3DCOLOR_RGBA(255, 255, 255, 255), 300.0f * m_fLapScale + 125.0f, 298.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime[0],	D3DCOLOR_RGBA(255, 255, 255, 255), 450.0f * m_fLapScale + 125.0f, 298.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			D3DCOLOR_RGBA(255, 255, 255, 255), 600.0f * m_fLapScale + 125.0f, 298.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime0[0],	D3DCOLOR_RGBA(255, 255, 255, 255), 750.0f * m_fLapScale + 125.0f, 298.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime00[0], D3DCOLOR_RGBA(255, 255, 255, 255), 900.0f * m_fLapScale + 125.0f, 298.0f, m_fLapScale, m_fLapScale);

	// ���b�v�Q
	CSceneNumber::Draw(m_nLapTime100[1], D3DCOLOR_RGBA(255, 255, 255, 255),						   125.0f, 339.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 150.0f * m_fLapScale + 125.0f, 339.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime10[1],  D3DCOLOR_RGBA(255, 255, 255, 255), 300.0f * m_fLapScale + 125.0f, 339.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime[1],    D3DCOLOR_RGBA(255, 255, 255, 255), 450.0f * m_fLapScale + 125.0f, 339.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 600.0f * m_fLapScale + 125.0f, 339.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime0[1],   D3DCOLOR_RGBA(255, 255, 255, 255), 750.0f * m_fLapScale + 125.0f, 339.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime00[1],  D3DCOLOR_RGBA(255, 255, 255, 255), 900.0f * m_fLapScale + 125.0f, 339.0f, m_fLapScale, m_fLapScale);

	// ���b�v�R
	CSceneNumber::Draw(m_nLapTime100[2], D3DCOLOR_RGBA(255, 255, 255, 255),						   125.0f, 380.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 150.0f * m_fLapScale + 125.0f, 380.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime10[2],  D3DCOLOR_RGBA(255, 255, 255, 255), 300.0f * m_fLapScale + 125.0f, 380.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime[2],    D3DCOLOR_RGBA(255, 255, 255, 255), 450.0f * m_fLapScale + 125.0f, 380.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 600.0f * m_fLapScale + 125.0f, 380.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime0[2],   D3DCOLOR_RGBA(255, 255, 255, 255), 750.0f * m_fLapScale + 125.0f, 380.0f, m_fLapScale, m_fLapScale);
	CSceneNumber::Draw(m_nLapTime00[2],  D3DCOLOR_RGBA(255, 255, 255, 255), 900.0f * m_fLapScale + 125.0f, 380.0f, m_fLapScale, m_fLapScale);

	// ����
	C2D::Draw(TEXTURE_LAP, 0, 0, 768, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f,		 { 85.5f,20.0f,0.0f }, true);
	if (m_nLapCnt == 0)
	{
		C2D::Draw(TEXTURE_LAP0, 0, 0, 768, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 85.0f,20.0,0.0f }, true);
	}
	else if (m_nLapCnt == 1)
	{
		C2D::Draw(TEXTURE_LAP1, 0, 0, 768, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 85.0f,20.0f,0.0f }, true);
	}
	else if (m_nLapCnt == 2)
	{
		C2D::Draw(TEXTURE_LAP2, 0, 0, 768, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 85.0f,20.0f,0.0f }, true);
	}
	else if (m_nLapCnt == 3)
	{
		C2D::Draw(TEXTURE_LAP3, 0, 0, 768, 512, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.25f, 0.25f, { 85.0f,20.0f,0.0f }, true);
	}

	//�@�I������
	if (m_bFinish)
	{
		C2D::Draw(TEXTURE_FINISH, 0, 0, 1980, 1080, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 1.0f, { 0.0f,0.0f,0.0f }, true);
		C2D::Draw(TEXTURE_PRESS_START, 0, 0, 512, 128, D3DCOLOR_RGBA(255, 255, 255, m_nAlpha), 0.0f, 0.0f, 0.5f, 0.5f, { 850.0f,380.0f,0.0f }, true);

		// ���b�v�P
		CSceneNumber::Draw(m_nLapTime100[0], D3DCOLOR_RGBA(255, 255, 255, 255),                              780.0f, 650.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 150.0f * m_fResultLapScale + 780.0f, 650.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime10[0],  D3DCOLOR_RGBA(255, 255, 255, 255), 300.0f * m_fResultLapScale + 780.0f, 650.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime[0],    D3DCOLOR_RGBA(255, 255, 255, 255), 450.0f * m_fResultLapScale + 780.0f, 650.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 600.0f * m_fResultLapScale + 780.0f, 650.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime0[0],   D3DCOLOR_RGBA(255, 255, 255, 255), 750.0f * m_fResultLapScale + 780.0f, 650.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime00[0],  D3DCOLOR_RGBA(255, 255, 255, 255), 900.0f * m_fResultLapScale + 780.0f, 650.0f, m_fResultLapScale, m_fResultLapScale);
																											
		// ���b�v�Q																							
		CSceneNumber::Draw(m_nLapTime100[1], D3DCOLOR_RGBA(255, 255, 255, 255),                              780.0f, 785.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 150.0f * m_fResultLapScale + 780.0f, 785.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime10[1],  D3DCOLOR_RGBA(255, 255, 255, 255), 300.0f * m_fResultLapScale + 780.0f, 785.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime[1],    D3DCOLOR_RGBA(255, 255, 255, 255), 450.0f * m_fResultLapScale + 780.0f, 785.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 600.0f * m_fResultLapScale + 780.0f, 785.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime0[1],   D3DCOLOR_RGBA(255, 255, 255, 255), 750.0f * m_fResultLapScale + 780.0f, 785.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime00[1],  D3DCOLOR_RGBA(255, 255, 255, 255), 900.0f * m_fResultLapScale + 780.0f, 785.0f, m_fResultLapScale, m_fResultLapScale);
																											
		// ���b�v�R																							
		CSceneNumber::Draw(m_nLapTime100[2], D3DCOLOR_RGBA(255, 255, 255, 255),						         780.0f, 915.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 150.0f * m_fResultLapScale + 780.0f, 915.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime10[2],  D3DCOLOR_RGBA(255, 255, 255, 255), 300.0f * m_fResultLapScale + 780.0f, 915.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime[2],    D3DCOLOR_RGBA(255, 255, 255, 255), 450.0f * m_fResultLapScale + 780.0f, 915.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(SECOND,			 D3DCOLOR_RGBA(255, 255, 255, 255), 600.0f * m_fResultLapScale + 780.0f, 915.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime0[2],   D3DCOLOR_RGBA(255, 255, 255, 255), 750.0f * m_fResultLapScale + 780.0f, 915.0f, m_fResultLapScale, m_fResultLapScale);
		CSceneNumber::Draw(m_nLapTime00[2],  D3DCOLOR_RGBA(255, 255, 255, 255), 900.0f * m_fResultLapScale + 780.0f, 915.0f, m_fResultLapScale, m_fResultLapScale);
	}

	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================================================================================================
//
// �`��
//
//============================================================================================================
//bool CSceneTime::GetFinish(void)
//{
//	return g_bGetFinish;
//}