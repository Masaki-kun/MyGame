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

	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��
	D3DXMATRIX m_mtxTrans;		//���s�ړ��s��
	D3DXMATRIX m_mtxRotation;	//��]�s��
	D3DXMATRIX m_mtxScale;	//��]�s��

	D3DXVECTOR3 vecCross;

	//�J����
	//D3DXVECTOR3 m_Eye;
	D3DXVECTOR3 m_At;
	D3DXVECTOR3 m_Up;

	LPD3DXMESH m_pMesh;
	DWORD m_nMaterialNum;
	LPD3DXBUFFER m_pMaterials;

	D3DMATERIAL9 m_mat1;

	//static D3DXVECTOR3 g_Front;			//�O�x�N�g��
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
