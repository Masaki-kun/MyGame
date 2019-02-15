//==========================================================================================
//
//	[Field.h] Author : Masaki Kuboki
//
//==========================================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

//============================================================================================================
//
// �}�N���錾
//
//============================================================================================================
// debug(prote)
//#define FIELD_SIZE_WIDTH (10.0f)	// �t�B�[���h�i�����j
//#define FIELD_SIZE_HEIGHT (10.0f)	// �t�B�[���h�i�����j
//#define FIELD_SIZE (1)				// �v�Z�Ŏg��int�^�̃t�B�[���h�̑傫��
//
//#define MESH_SIZE_WIDTH (1.0f)		// �t�B�[���h�̃��b�V���P������̑傫���i�����j
//#define MESH_SIZE_HEIGHT (1.0f)		// �t�B�[���h�̃��b�V���P������̑傫���i�c���j
//
//#define FIELD_DIVISION_NUM (11)		// �t�B�[���h�̒��_��
//
//#define FIELD_VERTEX_NUM (121)		//�@�t�B�[���h�̑����_��



//#define FIELD_SIZE_WIDTH (100.0f)	// �t�B�[���h�i�����j
//#define FIELD_SIZE_HEIGHT (100.0f)	// �t�B�[���h�i�����j
//#define FIELD_SIZE (1)				// �v�Z�Ŏg��int�^�̃t�B�[���h�̑傫��
//
//#define MESH_SIZE_WIDTH (1.0f)		// �t�B�[���h�̃��b�V���P������̑傫���i�����j
//#define MESH_SIZE_HEIGHT (1.0f)		// �t�B�[���h�̃��b�V���P������̑傫���i�c���j
//
//#define FIELD_DIVISION_NUM (101)		// �t�B�[���h�̒��_��
//
//#define FIELD_VERTEX_NUM (10201)		//�@�t�B�[���h�̑����_��


#define FIELD_SIZE_WIDTH (10.0f)	// �t�B�[���h�i�����j
#define FIELD_SIZE_HEIGHT (10.0f)	// �t�B�[���h�i�����j
#define FIELD_SIZE (10)				// �v�Z�Ŏg��int�^�̃t�B�[���h�̑傫��

#define MESH_SIZE_WIDTH (10.0f)		// �t�B�[���h�̃��b�V���P������̑傫���i�����j
#define MESH_SIZE_HEIGHT (10.0f)		// �t�B�[���h�̃��b�V���P������̑傫���i�c���j

#define FIELD_DIVISION_NUM (2)		// �t�B�[���h�̒��_��

#define FIELD_VERTEX_NUM (4)		//�@�t�B�[���h�̑����_��



//==========================================================================================
//
// class
//
//==========================================================================================
class CSceneMeshField :public CScene
{
public:
	CSceneMeshField(int Priority);
	~CSceneMeshField() {};

	void Init(HWND hWnd, float fFieldWidth, float fFieldHeight, float fSizeX, float fSizeZ);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position);
	float GetHeight(D3DXVECTOR3 Position);

	static CSceneMeshField *Create(HWND hWnd, float fFieldWidth, float fFieldHeight, float fSizeX, float fSizeZ, D3DXVECTOR3 SetPosition);

private:
	// �e�N�X�`���̃A�h���X
	LPDIRECT3DTEXTURE9 m_pTextures[7/*TEXTURE_MAX*/];

	int m_nVertexCount;	//	���_��
	int m_nIndexCount;	//	�C���f�b�N�X���_�̐�
	int m_nPrimitiveCount;

	D3DXMATRIX m_mtxWorld[5];		//���[���h�s��
	D3DXMATRIX m_mtxParallel[5];		//���s�ړ��s��
	D3DXMATRIX m_mtxRotation[5];		//��]�s��

	D3DXVECTOR3 m_RotAxis;	//��]��

	// ���s�ړ�����
	float m_fParallelMoveX;
	float m_fParallelMoveY;
	float m_fParallelMoveZ;
	bool m_bParallelMove;

	// ���ʃt�B�[���h�̃��Z�b�g�̃J�E���g����
	int m_nMeshCountX;
	int	m_nMeshCountZ;

	float m_fFieldHeight;	// �t�B�[���h�̍���(�v���X����l)

	// �A�h���X�i�[ 
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;

	int m_i;
};

#endif // !_FIELD_H_
