//============================================================================================================
//
//	[Camera.c] Author : Masaki Kuboki
//
//============================================================================================================
#include "main.h"
#include "SceneCamera.h"
#include "ScenePlayer.h"
#include "Input.h"
#include "XInput.h"
#include "RendererDX.h"


#define CAMERA_SPEED	(0.001f)
#define PRIORITY (1)

#define CAMERA_RENDERING_AREA (10000.0f)　

//============================================================================================================
//
//
//
//============================================================================================================
CSceneCamera::CSceneCamera(int Priority) :CScene(Priority)
{
	//カメラ
	m_Eye = { 0.0f, 3.0f, 7.0f };	//自分の位置;
	m_At = CScenePlayer::GetPosition();	//注視点;
	m_Up = { 0.0f, 1.0f, 0.0f };	//自分の上下がどちらか;

	//単位ベクトル
	m_Front;
	m_Right;
	m_Right2;

	m_mtxView;			//ビュー行列
	m_mtxProjection;	//プロジェクション行列

	m_fMoveSpeed = 0.1f;	//移動速度
	m_fRotSpeed = 0.01f;	//回転速度

	m_bEye;

	m_mtxRotation;
	m_vecFront = { 0.0,0.0,0.0 };;
	m_fAngle = 0.0f;

	m_mtxWorld;
}

//============================================================================================================
// 
// Create
//
//============================================================================================================
CSceneCamera *CSceneCamera::Create()
{
	CSceneCamera *SceneCamera = new CSceneCamera(PRIORITY);
	SceneCamera->Init();
	return SceneCamera;
}

//============================================================================================================
//
//	Init
//
//============================================================================================================
void CSceneCamera::Init(void)
{

}

//============================================================================================================
//
//  Uninit
//
//============================================================================================================
void CSceneCamera::Uninit(void)
{

}

//============================================================================================================
//
//  Update
//
//============================================================================================================
void CSceneCamera::Update(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRendererDX::GetD3DDevice();

	D3DXMATRIX Mtx;

	D3DXVECTOR3 Vec = m_Front;
	D3DXVECTOR3 Dir = m_At - m_Eye;
	D3DXVECTOR3 Dir2 = m_Eye - m_At;

	D3DXVECTOR3 PlayerPos = CScenePlayer::GetPosition();
	D3DXVECTOR3 CameraPos = { 0.0f, 3.0f, 7.0f };	//ｚを＋にすると車の背後に移動
	D3DXVECTOR3 PlayerFrontVec = CScenePlayer::GetVec();

	float fFront = 0.0f;
	Vec.y = 0;


	//前後移動 設定
	m_Front = PlayerFrontVec;

	//m_Front = m_At - m_Eye;	//前方向を求める

	//右方向ベクトルを求める
	D3DXVec3Cross(&m_Right, &m_Up, &m_Front);	//計算順序によって外積の表裏が異なる

	//正規化 (ノーマライズ)
	D3DXVec3Normalize(&m_Front, &m_Front);
	D3DXVec3Normalize(&m_Right, &m_Right);
	D3DXVec3Normalize(&Dir, &Dir);

	m_Eye = PlayerPos + m_Front * 5.0f;
	m_Eye.y += 2.5f;
	m_At = PlayerPos;
	m_At.y += 1.2f;

	// *** デバグ用 *********************************************
	//注視点左回転
	//if (CInput::GetKeyboardPress(DIK_Q))
	//{
	//	D3DXMatrixRotationY(&Mtx, m_fRotSpeed);
	//	D3DXVec3TransformNormal(&Dir2, &Dir2, &Mtx);
	//	m_Eye = m_At + Dir2;
	//}

	////注視点右回転
	//if (CInput::GetKeyboardPress(DIK_E))
	//{
	//	D3DXMatrixRotationY(&Mtx, -m_fRotSpeed);
	//	D3DXVec3TransformNormal(&Dir2, &Dir2, &Mtx);
	//	m_Eye = m_At + Dir2;
	//}

	/*if (CInput::GetKeyboardPress(DIK_Q))
		{
			
		m_Eye.y += 5000.0f;
		}*/

	// *** デバグ用 *********************************************

	//ビュー行列
	D3DXMatrixLookAtLH(&m_mtxView, &m_Eye, &m_At, &m_Up);

	//プロジェクション（パースペクティブ）行列の作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(60), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 5000.0f);

	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}




//============================================================================================================
//
//  Draw
//
//============================================================================================================
void CSceneCamera::Draw(void)
{

}
