//========================================================================================================
//
// [SCeneSector.h] Author : Masaki Kuboki
//
//========================================================================================================
#ifndef _SCENE_SECTOR_H_
#define _SCENE_SECTOR_H_

#include "Scene.h"

//========================================================================================================
//
// class
//
//========================================================================================================
class CSceneSector :public CScene
{
public:
	CSceneSector(int Priority);
	~CSceneSector() {};

	//void Init(HWND hWnd, float fFieldWidth, float fFieldHeight, float fSizeX, float fSizeY);
	void Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//static CSceneSkybox *Create(HWND hWnd, float fFieldWidth, float fFieldHeight, float fSizeX, float fSizeY);
	static CSceneSector *Create();
	static LPD3DXMESH GetMesh();

private:
	D3DXVECTOR3 m_Position;

	D3DXMATRIX m_mtxWorld;		//ワールド変換行列
	D3DXMATRIX m_mtxTrans;		//平行移動行列
	D3DXMATRIX m_mtxRotation;	//回転行列
	D3DXMATRIX m_mtxScaling;	//回転行列

	D3DXVECTOR3 vecCross;

	//カメラ
	D3DXVECTOR3 m_Eye;
	D3DXVECTOR3 m_At;
	D3DXVECTOR3 m_Up;

	//LPD3DXMESH m_pMesh;
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