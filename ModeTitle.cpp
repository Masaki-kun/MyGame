//==========================================================================================
//
// [Mode.c] Author : Masaki Kuboki
//
//==========================================================================================
#include "Mode.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeTutorial.h"

#include "Scene.h"
#include "Manager.h"

#include "2D.h"


#include "XInput.h"
#include "Input.h"


//==========================================================================================
//
// Init
//
//==========================================================================================
void CModeTitle::Init(void)
{
	m_nFade = 255;
	m_bFade = false;
	m_fHari = 0.0f;

	// press spaceのフェード処理
	m_nAlpha = 0;
	m_bSwitch = false;
	CSound::PlaySound(SOUND_LABEL_BGM_START);	//サウンド再生
}

//==========================================================================================
//
// Uninit
//
//==========================================================================================
void CModeTitle::Uninit(void)
{

}

//==========================================================================================
//
// Update
//
//==========================================================================================
void CModeTitle::Update(void)
{
	

	//--------------------------------------------------------------
	// フェード処理
	//--------------------------------------------------------------
	// フェードイン
	if (!m_bFade)
	{ 
		m_nFade -= 5;

		if (m_nFade <= 0) { m_nFade = 0; }
	}

	// フェードアウト
	if (CInput::GetKeyboardTrigger(DIK_SPACE) || CXinput::GetTrigger(XINPUT_GAMEPAD_START, 0)){ m_bFade = true; }

	if (m_bFade)
	{ 
		m_nFade += 5;

		if (m_nFade >= 260)
		{
			CManager::SetMode(new CModeTutorial());
			m_nFade = 255;
		}
	}

	if (m_bSwitch)
	{
		m_nAlpha -= 5;

		if (m_nAlpha <= 0)m_bSwitch = false;
	}
	else
	{
		m_nAlpha += 5;

		if (m_nAlpha >= 255)m_bSwitch = true;
	}

	if (m_fHari > -0.99) { m_fHari += 0.3f; }

	// レブリミッター
	if (m_fHari > 4.7f) { m_fHari -= 0.3f; }

}

//==========================================================================================
//
// Draw
//
//==========================================================================================
void CModeTitle::Draw(void)
{
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	C2D::Draw(TEXTURE_TITLE, 0, 0, 1920, 1080, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 1.0f, { 0.0f,0.0f,0.0f }, true);

	C2D::Draw(TEXTURE_PRESS_START, 0, 0, 512, 128, D3DCOLOR_RGBA(255, 255, 255, m_nAlpha), 0.0f, 0.0f, 1.0f, 1.0f, { 720.0f,800.0f,0.0f }, true);

	C2D::Draw(TEXTURE_FADE, 0, 0, 1920, 1080, D3DCOLOR_RGBA(0, 0, 0, m_nFade), 0.0f, 0.0f, 1.0f, 1.0f, { 0.0f,0.0f,0.0f }, true);


	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}