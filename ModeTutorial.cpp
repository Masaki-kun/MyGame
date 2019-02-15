//==========================================================================================
//
// [ModeTutorial.c] Author : Masaki Kuboki
//
//==========================================================================================
#include "ModeTutorial.h"
#include "ModeResult.h"
#include "ModeGame.h"

#include "Manager.h"
#include "Sound.h"

#include "Scene.h"
#include "Scene3D.h"
#include "SceneCamera.h"
#include "ScenePlayer.h"
#include "SceneLight.h"
#include "SceneMeshField.h"
#include "SceneTime.h"
#include "SceneTutorial.h"
#include "SceneMeter.h"
#include "SceneSkydome.h"

#include "RendererDX.h"
#include "XInput.h"
#include "Input.h"

//==========================================================================================
//
// 静的変数
//
//==========================================================================================
CScene3D         *CModeTutorial::m_3D = nullptr;
CSceneTutorial   *CModeTutorial::m_Tutorial = nullptr;
CSceneTime       *CModeTutorial::m_Time = nullptr;
CSceneCamera     *CModeTutorial::m_Camera = nullptr;
CScenePlayer     *CModeTutorial::m_Player = nullptr;
CSceneLight      *CModeTutorial::m_Light = nullptr;
CSceneMeshField  *CModeTutorial::m_MeshField = nullptr;
CSceneMeshField  *CModeTutorial::m_Field = nullptr;
CSceneMeter      *CModeTutorial::m_Meter = nullptr;
CSceneSkydome    *CModeTutorial::m_Skydome = nullptr;

//==========================================================================================
//
// Init
//
//==========================================================================================
void CModeTutorial::Init(void)
{
	m_nFade = 255;
	m_bFade = false;

	m_Skydome = CSceneSkydome::Create();

	// 3D
	m_Player = CScenePlayer::Create({ 0.0f,0.0f,0.0f });
	m_Camera = CSceneCamera::Create();
	m_Light = CSceneLight::Create();
	m_3D = CScene3D::Create();
	m_Tutorial = CSceneTutorial::Create({ 0.0f,0.0f,0.0f });

	// 2D
	m_Meter = CSceneMeter::Create();
	m_Time = CSceneTime::Create();

}

//==========================================================================================
//
// Uninit
//
//==========================================================================================
void CModeTutorial::Uninit(void)
{
	CScene::ReleaseAll();
	//CScene::UninitAll();
}

//==========================================================================================
//
// Update
//
//==========================================================================================
void CModeTutorial::Update(void)
{
	// フェードイン
	if (!m_bFade)
	{
		m_nFade -= 5;

		if (m_nFade <= 0) { m_nFade = 0; }
	}

	// フェードアウト
	if (CInput::GetKeyboardTrigger(DIK_SPACE) || CXinput::GetTrigger(XINPUT_GAMEPAD_START, 0)) { m_bFade = true; }

	if (m_bFade)
	{
		m_nFade += 5;

		if (m_nFade >= 260)
		{
			CManager::SetMode(new CModeGame());
			m_nFade = 255;
			CSound::StopSound(SOUND_LABEL_BGM_START);	// サウンド停止
		}
	}
}

//==========================================================================================
//
// Draw
//
//==========================================================================================
void CModeTutorial::Draw(void)
{
	C2D::Draw(TEXTURE_FADE, 0, 0, 1920, 1080, D3DCOLOR_RGBA(0, 0, 0, m_nFade), 0.0f, 0.0f, 1.0f, 1.0f, { 0.0f,0.0f,0.0f }, true);
}