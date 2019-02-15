//=====================================================================================================================================
//
//	[Camera.h] Author : Masaki Kuboki
//
//=====================================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Scene.h"

//=====================================================================================================================
//
// class
//
//=====================================================================================================================
class CSceneCamera:public CScene
{
public:
	CSceneCamera(int Priority);
	~CSceneCamera() {}

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneCamera *Create();

private:
	//カメラ
	D3DXVECTOR3 m_Eye;
	D3DXVECTOR3 m_At;
	D3DXVECTOR3 m_Up;

	//単位ベクトル
	D3DXVECTOR3 m_Front;
	D3DXVECTOR3 m_Right;
	D3DXVECTOR3 m_Right2;

	D3DXMATRIX m_mtxView;			//ビュー行列
	D3DXMATRIX m_mtxProjection;	//プロジェクション行列

	D3DXMATRIX m_mtxRotation;	//回転行列
	D3DXVECTOR3 m_vecFront;
	float m_fAngle;

	float m_fMoveSpeed;	//移動速度
	float m_fRotSpeed;	//回転速度

	bool m_bEye;

	D3DXMATRIX m_mtxWorld;
};


#endif

/*

void CCamera::Update()
// 鳥始点
{
CModeGame *game = (CModegame*)CManager::GetMode();
CPlayer *Player = game->GetPlayer();
D3DXVECTOR3 playerPosition = player->GetPosition();
m_AtPosition = playerPosition;
m_EyePosition = m_AtPosition + D3DXVEXTOR3(0.0f,5.0f,-10.0f);
}
{
D3DXVECTOR3 playerFront = player->GetFront();
m_AtPosition = playerPosition;
m_EyePosition = m_AtPosition - playerFront * 10.0f;
m_EyePosition = playerPosition.y + 5.0f;
}

D3DXVECTOR3 CPlayer::GetFront()
{
D3DXVECTOR3 front;
flont.x = m_WorldMatrix._31;
flont.y = m_WorldMatrix._32;
flont.z = m_WorldMatrix._33;
return front;
}

一人称始点
{
D3DXMatrixLookAtLH(---);


D3DXMatrixRoatationYawPitchRoll(&m_ViewRotation, m_Potation.y, m_Rotation.x, m_Rotation.z);
D3DXMatrixTranslation(&m_ViewTranslation, m_EyePosition.x, ---);
D3DXMatrixMultiply(&m_View, &m_ViewRotation, m_ViewTranslation);

}

m_TgtEyePosition = m_AtPosition + D3DXVECTOR3(0.0f,5.0f,-10.0f);
m_Eyeposition += (m_TgtEyePosition - m_EyePosition)*1.0f;

//注視点左回転
if (CInput::GetKeyboardPress(DIK_Q))
{
D3DXMatrixRotationY(&Mtx, m_fRotSpeed);
D3DXVec3TransformNormal(&Dir2, &Dir2, &Mtx);
m_Eye = m_At + Dir2;
}

//注視点右回転
if (CInput::GetKeyboardPress(DIK_E))
{
D3DXMatrixRotationY(&Mtx, -m_fRotSpeed);
D3DXVec3TransformNormal(&Dir2, &Dir2, &Mtx);
m_Eye = m_At + Dir2;
}

//ズームイン
if (CInput::GetKeyboardPress(DIK_Z))
{
m_Eye += m_Front * 0.8f;
m_At += m_Front *  0.8f;
}

//ズームアウト
if (CInput::GetKeyboardPress(DIK_X))
{
m_Eye -= m_Front * 0.8f;
m_At -= m_Front *  0.8f;
}



*/