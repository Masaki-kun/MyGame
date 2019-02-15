//=====================================================================================================================
//
// [SCenePlayer.h] Author : Masaki Kuboki
//
//=====================================================================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include "Scene.h"

//=====================================================================================================================================
//
// �\����
//
//=====================================================================================================================================
//Player�\����
typedef struct {
	char fileName[256];	//�t�@�C����
}XMODEL;

// ���f����
typedef enum XMODEL_ENUM
{
	XMODEL_EVO7,
	XMODEL_CIRCUIT,
	XMODE_SKYDOME,
	XMODEL_ROAD,
	XMODEL_MIKU,
	XMODEL_C1,
	XMODEL_SECTOR,
	XMODEL_MAX
};

// ���f���f�[�^
static const XMODEL m_aPlayer[] =
{
	{ "data/xmodel/evo7.x" },
	{ "data/xmodel/circuit.x" },
	{ "data/xmodel/asky.x" },
	{ "data/xmodel/road.x" },
	{"data/xmodel/magicalmirai2014.x"},
	{ "data/xmodel/c1.x" },
	{ "data/xmodel/sector.x" }

};

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} VERTEX_3D;

//FVF�̐錾�i�萔�j
#define FVF_VERTEX3D ((D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 ))

//=====================================================================================================================
//
// class
//
//=====================================================================================================================
class CScenePlayer :public CScene
{
public:
	CScenePlayer(int Priority);
	~CScenePlayer();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position);

	static D3DXVECTOR3 GetPosition();
	static D3DXVECTOR3 GetVec();
	static bool Judge();

	static CScenePlayer *Create(D3DXVECTOR3 SetPosition);

private:
	D3DXVECTOR3 m_Position;

	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��
	D3DXMATRIX m_mtxTrans;		//���s�ړ��s��
	D3DXMATRIX m_mtxRotation;	//��]�s��

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

	D3DMATERIAL9* m_pMeshMat;
	LPDIRECT3DTEXTURE9* m_pMeshTex;
	bool m_bSwicth;
	bool m_bAt;
	bool m_bControl;

	int m_nMove;

	LPDIRECT3DDEVICE9 m_pDevice;

	// ��������
	bool m_bKansei;
	float m_fKanseiSpeed;

	// �Ԃ̐؂�p
	D3DXVECTOR3 m_Rot;
	float m_fAngle;

	// �����֌W
	float m_fSpeed;			// �Ԃ̑��x
	float m_fShiftSpeed;	// �M�A�ɉ�����������


	// �j���[�g��������
	int m_nGear;

	float m_fbrake;

	// �t�B�[���h�֌W�̃��b�V��
	LPD3DXMESH m_pCircuitMesh;
	LPD3DXMESH m_pSectorMesh;

	D3DXVECTOR3 m_Rotation;

	float m_fRegulationSpeed;

	// �J�E���g�_�E��
	int m_nCountdown;
	bool m_bCountdown;
	
};

#endif