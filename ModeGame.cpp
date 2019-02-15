//==========================================================================================
//
// [Mode.c] Author : Masaki Kuboki
//
//==========================================================================================
#include "ModeGame.h"
#include "ModeResult.h"

#include "Manager.h"
#include "Sound.h"

#include "Scene.h"
#include "Scene3D.h"
#include "SceneCamera.h"
#include "ScenePlayer.h"
#include "SceneLight.h"
#include "SceneMeshField.h"
#include "SceneTime.h"
#include "SceneCircuit.h"
#include "SceneMeter.h"
#include "SceneSkydome.h"
#include "SceneSector.h"

#include "RendererDX.h"
#include "XInput.h"
#include "Input.h"

//==========================================================================================
//
// 静的変数
//
//==========================================================================================
CScene3D         *CModeGame::m_3D = nullptr;
CSceneCircuit    *CModeGame::m_Circuit = nullptr;
CSceneTime       *CModeGame::m_Time = nullptr;
CSceneCamera     *CModeGame::m_Camera = nullptr;
CScenePlayer     *CModeGame::m_Player = nullptr;
CSceneLight      *CModeGame::m_Light = nullptr;
CSceneMeshField  *CModeGame::m_MeshField = nullptr;
CSceneMeshField  *CModeGame::m_Field = nullptr;
CSceneMeter      *CModeGame::m_Meter = nullptr;
CSceneSkydome    *CModeGame::m_Skydome = nullptr;
CSceneSector	 *CModeGame::m_Sector = nullptr;

//==========================================================================================
//
// Init
//
//==========================================================================================
void CModeGame::Init(void)
{
	m_nFade = 255;
	m_bFade = false;

	//m_Skydome = CSceneSkydome::Create();
	m_Sector = CSceneSector::Create();

	// 3D
	//m_Field = CSceneMeshField::Create(GethWnd(), FIELD_SIZE_WIDTH, FIELD_SIZE_HEIGHT, MESH_SIZE_WIDTH, MESH_SIZE_HEIGHT, { 0.0f,0.0f,0.0f });
	//CSceneMeshField::Create(GethWnd(), FIELD_SIZE_WIDTH, FIELD_SIZE_HEIGHT, MESH_SIZE_WIDTH, MESH_SIZE_HEIGHT, { 0.0f,0.0f,0.0f });
	m_Player = CScenePlayer::Create({ 0.0f,0.0f,0.0f });
	m_Camera = CSceneCamera::Create();
	m_Light = CSceneLight::Create();
	m_3D = CScene3D::Create();
	m_Circuit = CSceneCircuit::Create({ 0.0f,0.0f,0.0f });

	// 2D
	m_Meter = CSceneMeter::Create();
	m_Time = CSceneTime::Create();
	
	CSound::PlaySound(SOUND_LABEL_BGM_RACE);	//サウンド再生
	
}

//==========================================================================================
//
// Uninit
//
//==========================================================================================
void CModeGame::Uninit(void)
{
	CScene::ReleaseAll();
}

//==========================================================================================
//
// Update
//
//==========================================================================================
void CModeGame::Update(void)
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
	if (CInput::GetKeyboardTrigger(DIK_SPACE) || CXinput::GetTrigger(XINPUT_GAMEPAD_START, 0)) { m_bFade = true; }

	if (m_bFade)
	{
		//if (CSceneTime::GetFinish())
		//{
			m_nFade += 5;

			if (m_nFade >= 260)
			{
				CManager::SetMode(new CModeResult());
				m_nFade = 255;
				CSound::StopSound(SOUND_LABEL_BGM_RACE);	// サウンド停止
			}
		//}
	}
}

//==========================================================================================
//
// Draw
//
//==========================================================================================
void CModeGame::Draw(void)
{
	C2D::Draw(TEXTURE_FADE, 0, 0, 1920, 1080, D3DCOLOR_RGBA(0, 0, 0, m_nFade), 0.0f, 0.0f, 1.0f, 1.0f, { 0.0f,0.0f,0.0f }, true);
}