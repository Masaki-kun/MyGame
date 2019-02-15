//============================================================================================================
//
//	[Player] Author : Masaki Kuboki
//
//============================================================================================================
#include "main.h"
//#include "Scene.h"
#include <math.h>
#include "ScenePlayer.h"
#include "RendererDX.h"
#include "SceneCircuit.h"
#include "SceneSector.h"
#include "XInput.h"
#include "SceneMeshField.h"
#include "Manager.h"
#include "Sound.h"
#include "2D.h"
#include "ModeGame.h"

#define PRIORITY (0)
#define MOVE_SPEED (0.1f)
#define PENALTY (0.05f)
#define ANGLE (0.8f)

static D3DXVECTOR3 m_Pos;
static D3DXVECTOR3 g_GetPlayerVec = {0.0f,0.0f,0.0f};

BOOL pHit;
FLOAT distance;

BOOL pHit2;
FLOAT distance2;

static bool m_bStart = true;

//============================================================================================================
//
//
//
//============================================================================================================
CScenePlayer::CScenePlayer(int Priority) :CScene(Priority)
{
	m_Position = { 0.0f,0.0f,0.0f };

	m_mtxWorld;		//ワールド変換行列
	m_mtxTrans;		//平行移動行列
	m_mtxRotation;	//回転行列

	vecCross;

	//カメラ
	m_Pos = { -100.0f, 0.0f, 0.0f };
	m_At = { 0.0f, 0.0f, 0.0f };
	m_Up = { 0.0f, 1.0f, 0.0f };

	m_pMesh = NULL;
	m_nMaterialNum = 0;
	m_pMaterials = NULL;

	m_mat1;

	m_vecFront = { 0.0f,0.0f,0.0f };

	m_pMeshMat;
	m_pMeshTex;
	m_bSwicth = true;
	m_bAt = true;
	m_bControl = true;

	m_nMove = 0;

	//m_PlayerPos = { 0.0f,0.0f,0.0f };
	m_pDevice = CRendererDX::GetD3DDevice();

	// 慣性処理
	m_bKansei = false;
	m_fKanseiSpeed = 0.0f;

	// 速度
	m_fSpeed = 0.0f;
	m_fShiftSpeed = 0.01f;	// シフトによる加速度変更(ギア１で0.001f)

	m_fRegulationSpeed = 0.0f;

	// 左右操作の回転量（車の切れ角）
	m_Rot = { 0.0f,0.0f,0.0f };


	m_nGear = 1;

	m_fbrake = 0.1f;

	m_pCircuitMesh = CSceneCircuit::GetMesh();
	m_pSectorMesh = CSceneSector::GetMesh();
	m_Rotation = { 0.0f,1.25f,0.0f };
	//m_Rotation = { 0.0f,0.0f,0.0f };

	m_fAngle = 0.01f; 

	// カウントダウン
	m_nCountdown = 0;
	m_bCountdown = true;
	
}

//============================================================================================================
// 
//
//
//============================================================================================================
CScenePlayer::~CScenePlayer()
{

}

//============================================================================================================
//
//  Create
//
//============================================================================================================
CScenePlayer *CScenePlayer::Create(D3DXVECTOR3 SetPosition)
{
	CScenePlayer *ScenePlayer = new CScenePlayer(PRIORITY);
	ScenePlayer->Init();
	ScenePlayer->SetPosition(SetPosition);
	return ScenePlayer;
}

//============================================================================================================
//
//	Init
//
//============================================================================================================
void CScenePlayer::Init(void)
{
	//LPDIRECT3DDEVICE9 pDevice = CRendererDX::GetD3DDevice();
	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;

	LPD3DXMESH pCloneMesh;

	m_Pos = { -100.0f, 0.0f, 0.0f };

	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];
	
	m_bStart = true; // ゲーム開始かどうか

	hr = D3DXLoadMeshFromX(m_aPlayer[XMODEL_EVO7].fileName, D3DXMESH_SYSTEMMEM, m_pDevice, &pAdjacency, &m_pMaterials, NULL, &m_nMaterialNum, &m_pMesh);

	hr = m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)pAdjacency->GetBufferPointer(), NULL, NULL, NULL);

	LPD3DXMATERIAL pMaterial = (LPD3DXMATERIAL)m_pMaterials->GetBufferPointer();

	m_pMeshMat = new D3DMATERIAL9[m_nMaterialNum];
	m_pMeshTex = new LPDIRECT3DTEXTURE9[m_nMaterialNum];

	for (int i = 0; i < m_nMaterialNum; i++)
	{
		m_pMeshTex[i] = NULL;
		m_pMeshMat[i] = pMaterial[i].MatD3D;

		if (pMaterial[i].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(m_pDevice, pMaterial[i].pTextureFilename, &m_pMeshTex[i]);
		}
	}

	m_pMesh->GetDeclaration(elements);
	hr = m_pMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, m_pDevice, &pCloneMesh);
	m_pMesh->Release();
	m_pMesh = pCloneMesh;

	float fFront = 0.0f;

	// フィールドのメッシュをコピー
	m_pCircuitMesh = CSceneCircuit::GetMesh();
	//m_mtxRotation = m_Rotation;

	//D3DXMatrixRotationY(&m_mtxRotation, fFront);
	D3DXMatrixRotationYawPitchRoll(&m_mtxRotation, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&m_mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxRotation, &m_mtxTrans);

}

//============================================================================================================
//
//	Uninit
//
//============================================================================================================
void CScenePlayer::Uninit(void)
{
	if (m_pMesh != NULL)
	{
 		m_pMesh->Release();
		m_pMesh = NULL;
	}

	if (m_pMaterials != NULL)
	{
		m_pMaterials->Release();
		m_pMaterials = NULL;
	}

	if (m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//============================================================================================================
//
//	Update
//
//============================================================================================================
void CScenePlayer::Update(void)
{
	D3DXVECTOR3 Dir;

	float fFront = 0.0f;

	m_vecFront = D3DXVECTOR3{ 0.0f,0.0f,-1.0f };	//前方向ベクトル

	D3DXVec3TransformNormal(&m_vecFront, &m_vecFront, &m_mtxRotation);

	CSceneMeshField *field;
	field = CManager::GetField();

	D3DXVECTOR3 RightFront = { 1.0f,0.0f,3.0f };

	// ゲーム開始時の車の向き(筑波のみ使用)
	//if (m_bStart)
	//{
	//	m_Rot.y = -1.55f;
	//	m_bStart = false;
	//}

	// 前進処理
	static D3DXVECTOR3 Front = { 0.0f,0.0f,0.0f };
	Front.x = m_mtxWorld._31;
	Front.y = m_mtxWorld._32;
	Front.z = m_mtxWorld._33;
	g_GetPlayerVec = Front;

	if (m_nGear < 5) 
	{
		// シフトアップ
		if (CInput::GetKeyboardTrigger(DIK_U) || CXinput::GetTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER, 0))
		{
			m_nGear++;

			if (m_nGear == 1) { m_fShiftSpeed = 0.010f; }
			if (m_nGear == 2) { m_fShiftSpeed = 0.009f; }
			if (m_nGear == 3) { m_fShiftSpeed = 0.008f; }
			if (m_nGear == 4) { m_fShiftSpeed = 0.007f; }
			if (m_nGear == 5) { m_fShiftSpeed = 0.006f; }
		}
	}

	if (m_nGear > 0) {
		// シフトダウン
		if (CInput::GetKeyboardTrigger(DIK_J) || CXinput::GetTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER, 0))
		{
			 m_nGear--; 

			 if (m_nGear == 1) { m_fShiftSpeed = 0.010f; }
			 if (m_nGear == 2) { m_fShiftSpeed = 0.009f; }
			 if (m_nGear == 3) { m_fShiftSpeed = 0.008f; }
			 if (m_nGear == 4) { m_fShiftSpeed = 0.007f; }
			 if (m_nGear == 5) { m_fShiftSpeed = 0.006f; }
		}
	}


	if (m_bCountdown)
	{
		m_nCountdown++;

		if (m_nCountdown >= 185) { m_bCountdown = false; }
	}
	else
	{
		// ギアが0ではないとき(前進)
		if (m_nGear != 0)
		{
			// 前進
			if (CXinput::GetPress(XINPUT_GAMEPAD_A, 0) || CInput::GetKeyboardPress(DIK_W))
			{
				if (m_nGear == 1)
				{
					if (m_fSpeed < 1.3f) { m_fSpeed += m_fShiftSpeed; }
				}

				if (m_nGear == 2)
				{
					if (m_fSpeed < 1.7f) { m_fSpeed += m_fShiftSpeed; }
				}

				if (m_nGear == 3)
				{
					if (m_fSpeed < 2.1f) { m_fSpeed += m_fShiftSpeed; }
				}

				if (m_nGear == 4)
				{
					if (m_fSpeed < 2.5f) { m_fSpeed += m_fShiftSpeed; }
				}

				if (m_nGear == 5) 
				{
					if (m_fSpeed < 3.0f) { m_fSpeed += m_fShiftSpeed;}
				}

				//m_fSpeed += m_fShiftSpeed;
				m_Pos += -Front * m_fSpeed;
				m_bKansei = false;
				m_fbrake = 0.2f;
			}
		}

		// ブレーキ（後退）
		if (CXinput::GetPress(XINPUT_GAMEPAD_X, 0) || CInput::GetKeyboardPress(DIK_S))
		{
			m_fbrake += 0.01f;
			m_Pos += Front * m_fbrake;
		}

		// 慣性処理（突入処理）
		if (CXinput::GetRelease(XINPUT_GAMEPAD_A, 0) || CInput::GetKeyboardRelease(DIK_W))
		{

			// ギアに応じて慣性処理の初期値を変更
			if (m_nGear == 1) { m_fKanseiSpeed = 0.51f; }
			if (m_nGear == 2) { m_fKanseiSpeed = 0.56f; }
			if (m_nGear == 3) { m_fKanseiSpeed = 0.64f; }
			if (m_nGear == 4) { m_fKanseiSpeed = 0.79f; }
			if (m_nGear == 5) { m_fKanseiSpeed = 0.99f; }
			m_bKansei = true;
		}

		// 慣性処理
		if (m_bKansei)
		{
			if (m_fSpeed > 0.0f)
			{
				m_fSpeed -= 0.005;
				m_Pos += -Front * m_fSpeed;
			}
			else
			{
				m_bKansei = false;
			}

		}

		// ハンドル
		// 左
		if (CXinput::GetPress(XINPUT_GAMEPAD_DPAD_LEFT, 0) || CInput::GetKeyboardPress(DIK_A))
		{
			CSound::PlaySound(SOUND_LABEL_SE_SKIL);

			// 切れ角調節
			if (CXinput::GetPress(XINPUT_GAMEPAD_A, 0) || CInput::GetKeyboardPress(DIK_W)/* || CInput::GetKeyboardPress(DIK_S)*/)
			{
				m_fRegulationSpeed = ANGLE/*m_fSpeed*/;
				m_Rot.y -= m_fAngle * m_fRegulationSpeed;
				if (m_fAngle < 0.03) { m_fAngle += 0.001; }
			}
			else if (m_fSpeed > 0.0f)
			{
				m_fRegulationSpeed = ANGLE/*m_fSpeed*/;
				m_Rot.y -= m_fAngle * m_fRegulationSpeed;
				if (m_fAngle < 0.03) { m_fAngle += 0.001; }
			}
		}

		// 右
		if (CXinput::GetPress(XINPUT_GAMEPAD_DPAD_RIGHT, 0) || CInput::GetKeyboardPress(DIK_D))
		{
			CSound::PlaySound(SOUND_LABEL_SE_SKIL);

			// 切れ角調節
			if (CXinput::GetPress(XINPUT_GAMEPAD_A, 0) || CInput::GetKeyboardPress(DIK_W)/* || CInput::GetKeyboardPress(DIK_W)*/)
			{
				m_Rot.y += m_fAngle * ANGLE/*m_fSpeed*/;
				if (m_fAngle < 0.025) { m_fAngle += 0.001; }
			}
			else if (m_fSpeed > 0.0f)
			{
				m_Rot.y += m_fAngle * ANGLE/*m_fSpeed*/;
				if (m_fAngle < 0.025) { m_fAngle += 0.001; }
			}
		}
	}
	
	// 切れ角初期化
	if (CXinput::GetRelease(XINPUT_GAMEPAD_DPAD_LEFT, 0) || CInput::GetKeyboardRelease(DIK_A)|| 
		CXinput::GetRelease(XINPUT_GAMEPAD_DPAD_RIGHT, 0) || CInput::GetKeyboardRelease(DIK_D))
	{
		m_fAngle = 0.01f;	
	}

	//-----------------------------------------------------------
	// サーキットとの当たり判定(地面)
	//-----------------------------------------------------------
	// フィールドのメッシュ情報を代入
	m_pCircuitMesh = CSceneCircuit::GetMesh();
	
	// 地面
	m_Pos.y += 2.0f;
	D3DXIntersect(m_pCircuitMesh, &m_Pos, &D3DXVECTOR3(0, -1, 0), &pHit, NULL, NULL, NULL, &distance, NULL, NULL);

	if (pHit) { m_Pos.y -= distance; }
		else { m_Pos.y -= 2.0f; }
	

	// プレイヤー 後ろ方向当たり判定
	D3DXVECTOR3 PosBack;
	PosBack = m_Pos;
	PosBack.y += 1.0f;
	D3DXIntersect(m_pCircuitMesh, &PosBack, &D3DXVECTOR3(-1, 0, 0), &pHit, NULL, NULL, NULL, &distance, NULL, NULL);
	if (pHit && distance <= 3.0f)
	{
		m_Pos.x += 3.0f - distance;

		// プレイヤー減速
		if (m_fSpeed >= 0.2f) { m_fSpeed -= PENALTY; }
	}


	// プレイヤー 前方向当たり判定
	D3DXVECTOR3 PosFront;
	PosFront = m_Pos;
	PosFront.y += 1.0f;
	D3DXIntersect(m_pCircuitMesh, &PosFront, &D3DXVECTOR3(1, 0, 0), &pHit, NULL, NULL, NULL, &distance, NULL, NULL);
	if (pHit && distance <= 3.0f)
	{
		m_Pos.x -= 3.0f - distance;

		// プレイヤー減速
		if (m_fSpeed >= 0.2f) { m_fSpeed -= PENALTY; }
	}

	
	// プレイヤー 右方向当たり判定
	D3DXVECTOR3 PosRight;
	PosRight = m_Pos;
	PosRight.y += 1.0f;
	D3DXIntersect(m_pCircuitMesh, &PosRight, &D3DXVECTOR3(0, 0, -1), &pHit, NULL, NULL, NULL, &distance, NULL, NULL);
	if (pHit && distance <= 3.0f)
	{
		m_Pos.z += 3.0f - distance;

		// プレイヤー減速
		if (m_fSpeed >= 0.2f) { m_fSpeed -= PENALTY; }
	}

	
	// プレイヤー 左方向当たり判定
	D3DXVECTOR3 PosLeft;
	PosLeft = m_Pos;
	PosLeft.y += 1.0f;
	D3DXIntersect(m_pCircuitMesh, &PosLeft, &D3DXVECTOR3(0, 0, 1), &pHit, NULL, NULL, NULL, &distance, NULL, NULL);
	if (pHit && distance <= 3.0f)
	{
		m_Pos.z -= 3.0f - distance;

		// プレイヤー減速
		if (m_fSpeed >= 0.2f) { m_fSpeed -= PENALTY; }
	}

	
	D3DXMatrixTranslation(&m_mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);			// 移動マトリクス
	D3DXMatrixRotationYawPitchRoll(&m_mtxRotation, m_Rot.y, m_Rot.x, m_Rot.z);	// 回転マトリクス
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxRotation, &m_mtxTrans);

}

//============================================================================================================
//
//	Darw
//
//============================================================================================================
void CScenePlayer::Draw(void)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	for (int i = 0; i < m_nMaterialNum; i++)
	{
		m_pDevice->SetMaterial(&m_pMeshMat[i]);
		m_pDevice->SetTexture(0, m_pMeshTex[i]);
		m_pMesh->DrawSubset(i);
	}



	

}

//==========================================================================================================
//
//	プレイヤーの位置取得
//
//==========================================================================================================
D3DXVECTOR3 CScenePlayer::GetPosition(void)
{
	return m_Pos;
}

//==========================================================================================================
//
//	プレイヤーの前方向ベクトル取得
//
//==========================================================================================================
D3DXVECTOR3 CScenePlayer::GetVec(void)
{
	return g_GetPlayerVec;
}


//============================================================================================================
//
//	プレイヤー初期位置
//
//============================================================================================================
void CScenePlayer::SetPosition(D3DXVECTOR3 Position)
{
	m_Pos = Position;
}