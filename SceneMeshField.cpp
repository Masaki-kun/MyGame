//==========================================================================================
//
//	[Field.c] Author : Masaki Kuboki
//
//==========================================================================================
#include "main.h"
#include "RendererDX.h"
#include "Input.h"

#include "2D.h"
#include "Scene3D.h"
#include "SceneCamera.h"
#include "SceneLight.h"
#include "ScenePlayer.h"
#include "SceneMeshField.h"

//頂点
VERTEX_3D* pV;

//==========================================================================================
//
//	マクロ宣言
//
//==========================================================================================
//アンビエントの色
#define AMBIENT_COLOR_R (0.5f)
#define AMBIENT_COLOR_G (0.5f)
#define AMBIENT_COLOR_B (0.5f)
#define AMBIENT_COLOR_A (0.5f)

// 優先順位
#define PRIORITY (1)

#define FIELD_MAKE (0.1f)

//==========================================================================================
//
// フィールド凹凸設定
//
//==========================================================================================
//float g_FieldHeight[121] =
//{
//	2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//};

float g_FieldHeight[FIELD_VERTEX_NUM];


//==========================================================================================
//
// インスタンス
//
//==========================================================================================
CSceneMeshField::CSceneMeshField(int Priority) :CScene(Priority)
{
	m_pTextures[TEXTURE_MAX];

	m_nVertexCount = 0;	//	頂点数
	m_nIndexCount = 0;	//	インデックス頂点の数
	m_nPrimitiveCount = 0;

	m_mtxWorld[5];		//ワールド行列
	m_mtxParallel[5];	//平行移動行列
	m_mtxRotation[5];	//回転行列

	m_RotAxis;	//回転軸

	// 平行移動距離
	m_fParallelMoveX = 0.0f;
	m_fParallelMoveY = 0.0f;
	m_fParallelMoveZ = 0.0f;
	m_bParallelMove = true;

	// アドレス格納 
	m_pVertexBuffer = NULL;
	m_pIndexBuffer  = NULL;

	// 凹凸フィールドのリセットのカウント処理
	m_nMeshCountX = 0;
	m_nMeshCountZ = 0;

	// フィールドの高さ(プラスする値)
	m_fFieldHeight = 0.3f;

	m_i = 0;
}

//==========================================================================================
//
// Create
//
//==========================================================================================
//CSceneMeshField *CSceneMeshField::Create(HWND hWnd, float fFieldWidth, float fFieldHeight, float fSizeX, float fSizeZ,D3DXVECTOR3 SetPosition)
//{
//	CSceneMeshField *SceneMeshField = new CSceneMeshField(PRIORITY);
//	SceneMeshField->Init(hWnd, fFieldWidth, fFieldHeight, fSizeX,fSizeZ);
//	//SceneMeshField->SetPosition(SetPosition);
//	return SceneMeshField;
//}

//==========================================================================================
//
//	Init
//
//==========================================================================================
void CSceneMeshField::Init(HWND hWnd, float fFieldWidth, float fFieldHeight, float fSizeX, float fSizeZ)
{


//	LPDIRECT3DDEVICE9 pDevice = CRendererDX::GetD3DDevice();
//	HRESULT hr;
//	D3DXVECTOR2 vPos;
//
//	int  nMeshCountX = fFieldWidth / fSizeX;
//	int  nMeshCountZ = fFieldHeight / fSizeZ;
//
//	m_nMeshCountX = nMeshCountX;
//	m_nMeshCountZ = nMeshCountZ;
//
//	//初期座標
//	vPos.x = -fFieldWidth / 2;
//	vPos.y = fFieldHeight / 2;
//
//	// フィールドの配列初期化
//	for (int i = 0; i < FIELD_VERTEX_NUM; i++)
//	{
//		g_FieldHeight[i] = 0;
//	}
//
//	//メッシュ数
//	m_nPrimitiveCount = nMeshCountX * nMeshCountZ * 2 + 4 * (nMeshCountZ - 1);
//
//	//頂点数計算
//	m_nVertexCount = (nMeshCountX + 1) * (nMeshCountZ + 1);
//	m_nIndexCount = (nMeshCountX + 1) * (nMeshCountZ + 1) + (nMeshCountX + 1) * (nMeshCountZ - 1) + 2 * (nMeshCountZ - 1);
//
//	//D3DXMatrixRotationAxis(&g_mtxRot,/*軸ベクトルのアドレス(&vecRot)*/,/*回転量（ラジアン）*/);
//
//	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexCount,	D3DUSAGE_WRITEONLY, FVF_VERTEX3D,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);
//	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexCount,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_pIndexBuffer,NULL);
//
//	// テクスチャ読み込み
//	hr = D3DXCreateTextureFromFile(pDevice, g_aTexture[TEXTURE_GROUND].fileName, &m_pTextures[TEXTURE_GROUND]);
//	
//	// テクスチャ エラー確認
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, "テクスチャの読み込みに失敗しました(フィールド)", "エラーメッセージ", MB_OK | MB_ICONASTERISK);
//		return;
//	}
//
//	// ロック( ロックができなければFlag誤りかVRAMの枯渇 )
//	m_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
//
//	for (int nHeight = 0; nHeight < nMeshCountZ + 1; nHeight++)
//	{
//		for (int nWidth = 0; nWidth < nMeshCountX + 1; nWidth++)
//		{
//			pV[nHeight * (nMeshCountX + 1) + nWidth].pos      = D3DXVECTOR3(vPos.x + fSizeX * nWidth, g_FieldHeight[nHeight * (nMeshCountX + 1) + nWidth], vPos.y - 1.0f * (fSizeZ * nHeight));
//			pV[nHeight * (nMeshCountX + 1) + nWidth].normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//			pV[nHeight * (nMeshCountX + 1) + nWidth].texcoord = D3DXVECTOR2(1.0f * (nWidth % 2), 1.0f * (nHeight % 2));
//			pV[nHeight * (nMeshCountX + 1) + nWidth].color    = D3DCOLOR_RGBA(255, 255, 255, 255);
//		}
//	}
//
//	// 法線ベクトルの計算(凹凸フィールド)
//	D3DXVECTOR3 vx, vz, nx, nz, n = { 0.0f,0.0f,0.0f };
//
//	for (int z = 1; z < FIELD_SIZE; z++)
//	{
//		for (int x = 1; x < FIELD_SIZE; x++)
//		{
//			// x軸
//			vx = pV[z * FIELD_DIVISION_NUM + x + 1].pos - pV[z * FIELD_DIVISION_NUM + x - 1].pos;
//			nx.x = vx.y;
//			nx.y = -vx.x;
//			nx.z = 0.0f;
//			
//			// z軸
//			vz = pV[(z - 1) * FIELD_DIVISION_NUM + x].pos - pV[(z + 1) * FIELD_DIVISION_NUM - x].pos;
//			nz.x = 0.0f;
//			nz.y = vz.z;
//			nz.z = -vz.y;
//			
//			n = nx + nz;
//			D3DXVec3Normalize(&n, &n);
//			pV[z * FIELD_DIVISION_NUM + x].normal = n;
//		}
//	}
//	
//	// アンロック
//	m_pVertexBuffer->Unlock();
//
//	//Index
//	LPWORD pIndex;
//
//	// ロック( ロックができなければFlag誤りかVRAMの枯渇 )
//	m_pIndexBuffer->Lock(0, 0,(void**)&pIndex, D3DLOCK_DISCARD);
//
//	int nPosC = 0;
//
//	for (int Height = 0; Height < nMeshCountZ; Height++)
//	{
//		if (Height != 0)
//		{
//			pIndex[nPosC++] = (nMeshCountX + 1) * Height + (nMeshCountX + 1);
//		}
//
//		for (int Width = 0; Width < nMeshCountX + 1; Width++)
//		{
//			pIndex[nPosC++] = (Height + 1)* (nMeshCountX + 1) + Width;
//			pIndex[nPosC++] = (Height * (nMeshCountX + 1)) + Width;
//		}
//
//		if (Height != nMeshCountZ - 1)
//		{
//			pIndex[nPosC++] = nMeshCountX + (nMeshCountX + 1) * Height;
//		}
//	}
//
//	// アンロック
//	m_pVertexBuffer->Unlock();
//
//	D3DXMatrixIdentity(&m_mtxWorld[0]);

}

//==========================================================================================
//
//	Uninit
//
//==========================================================================================
void CSceneMeshField::Uninit(void)
{

}

//==========================================================================================
//
//	update
//
//==========================================================================================
void CSceneMeshField::Update(void)
{
	//// ロック( ロックができなければFlag誤りかVRAMの枯渇 )
	//m_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	////右
	//if (CInput::GetKeyboardTrigger(DIK_RIGHT))
	//{
	//	m_i += 1; 
	//}

	////左
	//if (CInput::GetKeyboardTrigger(DIK_LEFT))
	//{ 
	//	m_i -=1 ;
	//}

	////上
	//if (CInput::GetKeyboardTrigger(DIK_UP))
	//{ 
	//	m_i -= FIELD_SIZE +1;
	//}

	////下
	//if (CInput::GetKeyboardTrigger(DIK_DOWN))
	//{ 
	//	m_i += FIELD_SIZE +1;
	//}

	//if (CInput::GetKeyboardTrigger(DIK_0))
	//{
	//	pV[m_i].pos.y -= m_fFieldHeight;
	//}

	//if (CInput::GetKeyboardTrigger(DIK_1))
	//{
	//	pV[m_i].pos.y += m_fFieldHeight;
	//}

	//if (CInput::GetKeyboardTrigger(DIK_9))
	//{
	//	for (int nHeight = 0; nHeight < m_nMeshCountZ + 1; nHeight++)
	//	{
	//		for (int nWidth = 0; nWidth < m_nMeshCountX + 1; nWidth++)
	//		{
	//			pV[nHeight * (m_nMeshCountX + 1) + nWidth].pos.y = 0.0f;
	//		}
	//	}
	//}

	//// アンロック
	//m_pVertexBuffer->Unlock();
}

//==========================================================================================
//
//	Draw
//
//==========================================================================================
void CSceneMeshField::Draw(void)
{
	

	//LPDIRECT3DDEVICE9 pDevice = CRendererDX::GetD3DDevice();
	//
	//D3DMATERIAL9 mat;

	//ZeroMemory(&mat, sizeof(mat));
	//mat.Diffuse.r = 
	//mat.Diffuse.g = 
	//mat.Diffuse.b = 
	//mat.Diffuse.a = 1.0f;

	//mat.Ambient.r = 
	//mat.Ambient.g = 
	//mat.Ambient.b = 
	//mat.Ambient.a = 1.0f;

	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld[0]);

	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);//ライトつけたらTRUE
	//pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(AMBIENT_COLOR_R, AMBIENT_COLOR_G, AMBIENT_COLOR_B, AMBIENT_COLOR_A));

	//// 今から使用する頂点の情報を設定する( どんな情報を入れるか決める )
	//pDevice->SetFVF(FVF_VERTEX3D);

	////行列の設定
	//pDevice->SetMaterial(&mat);

	//pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	//pDevice->SetIndices(m_pIndexBuffer);

	//// テクスチャの取得
	//pDevice->SetTexture(0, m_pTextures[TEXTURE_GROUND]);
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexCount, 0, m_nPrimitiveCount);
}

//==========================================================================================
//
//	フィールドの凹凸取得
//
//==========================================================================================
//float CSceneMeshField::GetHeight(D3DXVECTOR3 Position)
//{
//	D3DXVECTOR3 v01, v12, v20, v0p, v1p, v2p, n, vPos;
//	float c0, c1, c2 = 0.0f;	// 外積の計算結果
//
//	D3DXVECTOR3 v012, v122, v202, v3p, v4p, v5p, n2, vPos2;
//	float c02, c12, c22 = 0.0f;	// 外積の計算結果
//		
//	for (int z = 1; z < FIELD_SIZE; z++)
//	{
//		for (int x = 1; x < FIELD_SIZE; x++)
//		{
//			// 右下
//			v01 = pV[z        * FIELD_DIVISION_NUM + x].pos - pV[(z + 1) * FIELD_DIVISION_NUM + x].pos;
//			v12 = pV[z * FIELD_DIVISION_NUM + (x + 1)].pos  - pV[z       * FIELD_DIVISION_NUM + x].pos;
//			v20 = pV[(z + 1) * FIELD_DIVISION_NUM + x].pos  - pV[z * FIELD_DIVISION_NUM + (x + 1)].pos;
//
//			v0p = Position - pV[(z + 1) * FIELD_DIVISION_NUM + x].pos;
//			v1p = Position - pV[z       * FIELD_DIVISION_NUM + x].pos;
//			v2p = Position - pV[z * FIELD_DIVISION_NUM + (x + 1)].pos;
//
//			c0 = v01.x * v0p.z - v01.z * v0p.x;
//			c1 = v12.x * v1p.z - v12.z * v1p.x;
//			c2 = v20.x * v2p.z - v20.z * v2p.x;
//		
//
//			if (c0 <= 0.0f && c1 <= 0.0f && c2 <= 0.0f)
//			{
//				vPos = pV[(z + 1) * FIELD_DIVISION_NUM + x].pos;
//				D3DXVec3Cross(&n, &v01, &v12);
//				Position.y = vPos.y - (n.x*(Position.x - vPos.x) + n.z*(Position.z - vPos.z) / n.y);
//				return Position.y;
//			}
//
//			// 右下
//			v012 = pV[z       * FIELD_DIVISION_NUM + (x + 1)].pos - pV[(z + 1) * FIELD_DIVISION_NUM + x].pos;
//			v122 = pV[(z + 1) * FIELD_DIVISION_NUM + (x + 1)].pos - pV[z       * FIELD_DIVISION_NUM + (x + 1)].pos;
//			v202 = pV[(z + 1) * FIELD_DIVISION_NUM + x].pos       - pV[(z + 1) * FIELD_DIVISION_NUM + (x + 1)].pos;
//			
//			v3p = Position - pV[(z + 1) * FIELD_DIVISION_NUM + (x + 1)].pos;
//			v4p = Position - pV[(z + 1) * FIELD_DIVISION_NUM + x].pos;
//			v5p = Position - pV[z  * FIELD_DIVISION_NUM + (x + 1)].pos;
//						
//			c02 = v202.x * v3p.z - v202.z * v3p.x;
//			c12 = v012.x * v4p.z - v012.z * v4p.x;
//			c22 = v122.x * v5p.z - v122.z * v5p.x;
//				
//			if (c02 <= 0.0f && c12 <= 0.0f && c22 <= 0.0f)
//			{
//				vPos2 = pV[(z+1) * FIELD_DIVISION_NUM + x].pos;
//				D3DXVec3Cross(&n2, &v012, &v122);
//				Position.y = vPos2.y - (n2.x*(Position.x - vPos2.x) + n2.z*(Position.z - vPos2.z) / n2.y);
//				return Position.y;
//			}
//		}
//	}
//}

