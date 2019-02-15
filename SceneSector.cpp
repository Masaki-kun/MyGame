//============================================================================================================
//
//	[3D] Author : Masaki Kuboki
//
//============================================================================================================
#include "main.h"
#include "2D.h"
#include "SceneSector.h"
#include "RendererDX.h"
#include "ScenePlayer.h"

//============================================================================================================
//
// �}�N���錾
//
//============================================================================================================
// �O���b�h�F
#define R (72)
#define G (209)
#define B (204)
#define A (255)

#define PRIORITY (0)

#define MODEL_SCALE (2.0f)

static LPD3DXMESH m_pMesh;

//============================================================================================================
//
//
//
//============================================================================================================
CSceneSector::CSceneSector(int Priority) :CScene(Priority)
{
	m_Position = { 0.0f,0.0f,0.0f };

	m_mtxWorld;		//���[���h�ϊ��s��
	m_mtxTrans;		//���s�ړ��s��
	m_mtxRotation;	//��]�s��
	m_mtxScaling;	// �g��k���s��

	vecCross;

	//�J����
	m_Eye = { 0.0f, 0.0f, 0.0f };
	m_At = { 0.0f, 0.0f, 0.0f };
	m_Up = { 0.0f, 1.0f, 0.0f };

	m_pMesh = NULL;
	m_nMaterialNum = 0;
	m_pMaterials = NULL;

	m_mat1;

	m_vecFront = { 0.0,0.0,0.0 };

	m_fAngle = 0.0f;

	m_pMeshMat;
	m_pMeshTex;
	m_bSwicth = true;
	m_bAt = true;
	m_bControl = true;

	m_nMove = 0;

	//m_CircuitPos = { 0.0f,0.0f,0.0f };
	m_pDevice = CRendererDX::GetD3DDevice();
}

//============================================================================================================
// 
//
//
//============================================================================================================
CSceneSector *CSceneSector::Create()
{
	CSceneSector *SceneSector = new CSceneSector(PRIORITY);
	SceneSector->Init();
	return SceneSector;
}

//============================================================================================================
//
// Init
//
//============================================================================================================
void CSceneSector::Init(void)
{

	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;
	LPD3DXMESH pCloneMesh;
	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];

	// ���f���̉�]�p�x
	float fFront = 20.3f;

	hr = D3DXLoadMeshFromX(m_aPlayer[XMODEL_SECTOR].fileName, D3DXMESH_SYSTEMMEM, m_pDevice, &pAdjacency, &m_pMaterials, NULL, &m_nMaterialNum, &m_pMesh);

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

	//m_pMesh->GetDeclaration(elements);
	//hr = m_pMesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, m_pDevice, &pCloneMesh);
	//m_pMesh->Release();
	//m_pMesh = pCloneMesh;

	

	//D3DXMatrixRotationX(&m_mtxRotation, fFront);
	D3DXMatrixTranslation(&m_mtxTrans, 0.0f, 0.0f, -10.0f);
	D3DXMatrixScaling(&m_mtxScaling, MODEL_SCALE, MODEL_SCALE, MODEL_SCALE);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxScaling, &m_mtxRotation);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxScaling, &m_mtxTrans);

}

//============================================================================================================
//
// Uninit	
//
//============================================================================================================
void CSceneSector::Uninit(void)
{}

//============================================================================================================
//
//	Update
//
//============================================================================================================
void CSceneSector::Update(void)
{

}

//============================================================================================================
//
//	Draw
//
//============================================================================================================
void CSceneSector::Draw(void)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	for (int i = 0; i < m_nMaterialNum; i++)
	{
		m_pDevice->SetMaterial(&m_pMeshMat[i]);
		m_pDevice->SetTexture(0, m_pMeshTex[i]);
		m_pMesh->DrawSubset(i);
	}

	
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

LPD3DXMESH CSceneSector::GetMesh()
{

	return m_pMesh;
}