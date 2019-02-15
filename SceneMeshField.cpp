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

//���_
VERTEX_3D* pV;

//==========================================================================================
//
//	�}�N���錾
//
//==========================================================================================
//�A���r�G���g�̐F
#define AMBIENT_COLOR_R (0.5f)
#define AMBIENT_COLOR_G (0.5f)
#define AMBIENT_COLOR_B (0.5f)
#define AMBIENT_COLOR_A (0.5f)

// �D�揇��
#define PRIORITY (1)

#define FIELD_MAKE (0.1f)

//==========================================================================================
//
// �t�B�[���h���ʐݒ�
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
// �C���X�^���X
//
//==========================================================================================
CSceneMeshField::CSceneMeshField(int Priority) :CScene(Priority)
{
	m_pTextures[TEXTURE_MAX];

	m_nVertexCount = 0;	//	���_��
	m_nIndexCount = 0;	//	�C���f�b�N�X���_�̐�
	m_nPrimitiveCount = 0;

	m_mtxWorld[5];		//���[���h�s��
	m_mtxParallel[5];	//���s�ړ��s��
	m_mtxRotation[5];	//��]�s��

	m_RotAxis;	//��]��

	// ���s�ړ�����
	m_fParallelMoveX = 0.0f;
	m_fParallelMoveY = 0.0f;
	m_fParallelMoveZ = 0.0f;
	m_bParallelMove = true;

	// �A�h���X�i�[ 
	m_pVertexBuffer = NULL;
	m_pIndexBuffer  = NULL;

	// ���ʃt�B�[���h�̃��Z�b�g�̃J�E���g����
	m_nMeshCountX = 0;
	m_nMeshCountZ = 0;

	// �t�B�[���h�̍���(�v���X����l)
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
//	//�������W
//	vPos.x = -fFieldWidth / 2;
//	vPos.y = fFieldHeight / 2;
//
//	// �t�B�[���h�̔z�񏉊���
//	for (int i = 0; i < FIELD_VERTEX_NUM; i++)
//	{
//		g_FieldHeight[i] = 0;
//	}
//
//	//���b�V����
//	m_nPrimitiveCount = nMeshCountX * nMeshCountZ * 2 + 4 * (nMeshCountZ - 1);
//
//	//���_���v�Z
//	m_nVertexCount = (nMeshCountX + 1) * (nMeshCountZ + 1);
//	m_nIndexCount = (nMeshCountX + 1) * (nMeshCountZ + 1) + (nMeshCountX + 1) * (nMeshCountZ - 1) + 2 * (nMeshCountZ - 1);
//
//	//D3DXMatrixRotationAxis(&g_mtxRot,/*���x�N�g���̃A�h���X(&vecRot)*/,/*��]�ʁi���W�A���j*/);
//
//	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexCount,	D3DUSAGE_WRITEONLY, FVF_VERTEX3D,D3DPOOL_MANAGED,&m_pVertexBuffer,NULL);
//	hr = pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexCount,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_pIndexBuffer,NULL);
//
//	// �e�N�X�`���ǂݍ���
//	hr = D3DXCreateTextureFromFile(pDevice, g_aTexture[TEXTURE_GROUND].fileName, &m_pTextures[TEXTURE_GROUND]);
//	
//	// �e�N�X�`�� �G���[�m�F
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���(�t�B�[���h)", "�G���[���b�Z�[�W", MB_OK | MB_ICONASTERISK);
//		return;
//	}
//
//	// ���b�N( ���b�N���ł��Ȃ����Flag��肩VRAM�̌͊� )
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
//	// �@���x�N�g���̌v�Z(���ʃt�B�[���h)
//	D3DXVECTOR3 vx, vz, nx, nz, n = { 0.0f,0.0f,0.0f };
//
//	for (int z = 1; z < FIELD_SIZE; z++)
//	{
//		for (int x = 1; x < FIELD_SIZE; x++)
//		{
//			// x��
//			vx = pV[z * FIELD_DIVISION_NUM + x + 1].pos - pV[z * FIELD_DIVISION_NUM + x - 1].pos;
//			nx.x = vx.y;
//			nx.y = -vx.x;
//			nx.z = 0.0f;
//			
//			// z��
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
//	// �A�����b�N
//	m_pVertexBuffer->Unlock();
//
//	//Index
//	LPWORD pIndex;
//
//	// ���b�N( ���b�N���ł��Ȃ����Flag��肩VRAM�̌͊� )
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
//	// �A�����b�N
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
	//// ���b�N( ���b�N���ł��Ȃ����Flag��肩VRAM�̌͊� )
	//m_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	////�E
	//if (CInput::GetKeyboardTrigger(DIK_RIGHT))
	//{
	//	m_i += 1; 
	//}

	////��
	//if (CInput::GetKeyboardTrigger(DIK_LEFT))
	//{ 
	//	m_i -=1 ;
	//}

	////��
	//if (CInput::GetKeyboardTrigger(DIK_UP))
	//{ 
	//	m_i -= FIELD_SIZE +1;
	//}

	////��
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

	//// �A�����b�N
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

	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);//���C�g������TRUE
	//pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(AMBIENT_COLOR_R, AMBIENT_COLOR_G, AMBIENT_COLOR_B, AMBIENT_COLOR_A));

	//// ������g�p���钸�_�̏���ݒ肷��( �ǂ�ȏ������邩���߂� )
	//pDevice->SetFVF(FVF_VERTEX3D);

	////�s��̐ݒ�
	//pDevice->SetMaterial(&mat);

	//pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(VERTEX_3D));
	//pDevice->SetIndices(m_pIndexBuffer);

	//// �e�N�X�`���̎擾
	//pDevice->SetTexture(0, m_pTextures[TEXTURE_GROUND]);
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexCount, 0, m_nPrimitiveCount);
}

//==========================================================================================
//
//	�t�B�[���h�̉��ʎ擾
//
//==========================================================================================
//float CSceneMeshField::GetHeight(D3DXVECTOR3 Position)
//{
//	D3DXVECTOR3 v01, v12, v20, v0p, v1p, v2p, n, vPos;
//	float c0, c1, c2 = 0.0f;	// �O�ς̌v�Z����
//
//	D3DXVECTOR3 v012, v122, v202, v3p, v4p, v5p, n2, vPos2;
//	float c02, c12, c22 = 0.0f;	// �O�ς̌v�Z����
//		
//	for (int z = 1; z < FIELD_SIZE; z++)
//	{
//		for (int x = 1; x < FIELD_SIZE; x++)
//		{
//			// �E��
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
//			// �E��
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

