//=====================================================================================================================
//
// [SCeneCircuit.h] Author : Masaki Kuboki
//
//=====================================================================================================================
#ifndef _SCENE_TUTORIAL_H_
#define _SCENE_TUTORIAL_H_

#include "Scene.h"
#include "ScenePlayer.h"

//=====================================================================================================================
//
// class
//
//=====================================================================================================================
class CSceneTutorial :public CScene
{
public:
	CSceneTutorial(int Priority);
	~CSceneTutorial();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position);
	static D3DXVECTOR3 GetPosition();

	static CSceneTutorial *Create(D3DXVECTOR3 SetPosition);

private:
	D3DXVECTOR3 m_Position;

	D3DXMATRIX m_mtxWorld;		//ワールド変換行列
	D3DXMATRIX m_mtxTrans;		//平行移動行列
	D3DXMATRIX m_mtxRotation;	//回転行列
	D3DXMATRIX m_mtxScale;	//回転行列

	D3DXVECTOR3 vecCross;

	//カメラ
	//D3DXVECTOR3 m_Eye;
	D3DXVECTOR3 m_At;
	D3DXVECTOR3 m_Up;

	LPD3DXMESH m_pMesh;
	DWORD m_nMaterialNum;
	LPD3DXBUFFER m_pMaterials;

	D3DMATERIAL9 m_mat1;

	//static D3DXVECTOR3 g_Front;			//前ベクトル
	D3DXVECTOR3 m_vecFront;

	float m_fAngle;

	D3DMATERIAL9* m_pMeshMat;
	LPDIRECT3DTEXTURE9* m_pMeshTex;
	bool m_bSwicth;
	bool m_bAt;
	bool m_bControl;

	int m_nMove;

	LPDIRECT3DDEVICE9 m_pDevice;
};

#endif
