//============================================================================================================
//
//	[Player] Author : Masaki Kuboki
//
//============================================================================================================
#include "main.h"
#include <math.h>
#include "SceneTutorial.h"
#include "RendererDX.h"
#include "XInput.h"
#include "2D.h"

#define PRIORITY (0)

static D3DXVECTOR3 m_Eye;

//============================================================================================================
//
//
//
//============================================================================================================
CSceneTutorial::CSceneTutorial(int Priority) :CScene(Priority)
{
	m_Position = { 0.0f,0.0f,0.0f };

	m_mtxWorld;		//ワールド変換行列
	m_mtxTrans;		//平行移動行列
	m_mtxRotation;	//回転行列
	m_mtxScale;

	vecCross;

	//カメラ
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
CSceneTutorial::~CSceneTutorial()
{

}

//============================================================================================================
//
//  Create
//
//============================================================================================================
CSceneTutorial *CSceneTutorial::Create(D3DXVECTOR3 SetPosition)
{
	CSceneTutorial *SceneTutorial = new CSceneTutorial(PRIORITY);
	SceneTutorial->Init();
	SceneTutorial->SetPosition(SetPosition);
	return SceneTutorial;
}

//============================================================================================================
//
//	Init
//
//============================================================================================================
void CSceneTutorial::Init(void)
{
	//LPDIRECT3DDEVICE9 pDevice = CRendererDX::GetD3DDevice();
	HRESULT hr;
	LPD3DXBUFFER pAdjacency = NULL;
	LPD3DXMESH pCloneMesh;
	D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH + 1];

	//hr = D3DXLoadMeshFromX(m_aPlayer[XMODEL_CIRCUIT].fileName, D3DXMESH_SYSTEMMEM, m_pDevice, &pAdjacency, &m_pMaterials, NULL, &m_nMaterialNum, &m_pMesh);
	hr = D3DXLoadMeshFromX(m_aPlayer[XMODEL_ROAD].fileName, D3DXMESH_SYSTEMMEM, m_pDevice, &pAdjacency, &m_pMaterials, NULL, &m_nMaterialNum, &m_pMesh);

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

	float fFront = 0.0f;

	//D3DXMatrixRotationY(&m_mtxRotation, fFront);
	D3DXMatrixTranslation(&m_mtxTrans, m_Eye.x, m_Eye.y, m_Eye.z);

	// デバグ
	D3DXMatrixScaling(&m_mtxScale, 100.0f, 100.0f, 100.0f);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxScale/*m_mtxRotation*/, &m_mtxTrans);

	//m_mtxWorld = &m_mtxRotation  &m_mtxTrans);
}
//============================================================================================================
//
//	Uninit
//
//============================================================================================================
void CSceneTutorial::Uninit(void)
{

}

//============================================================================================================
//
//	Update
//
//============================================================================================================
void CSceneTutorial::Update(void)
{

}

//============================================================================================================
//
//	Darw
//
//============================================================================================================
void CSceneTutorial::Draw(void)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < m_nMaterialNum; i++)
	{
		m_pDevice->SetMaterial(&m_pMeshMat[i]);
		m_pDevice->SetTexture(0, m_pMeshTex[i]);
		m_pMesh->DrawSubset(i);
	}

	C2D::Draw(TEXTURE_TUTORIAL, 0, 0, 1920, 1080, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 1.0f, { 0.0f,0.0f,0.0f }, true);
}

//==========================================================================================================
//
//	プレイヤーの位置
//
//==========================================================================================================
D3DXVECTOR3 CSceneTutorial::GetPosition(void)
{
	return m_Eye;
}



//============================================================================================================
//
//	
//
//============================================================================================================
void CSceneTutorial::SetPosition(D3DXVECTOR3 Position)
{
	m_Eye = Position;
}

