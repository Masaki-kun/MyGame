//==========================================================================================
//
//	[Field.h] Author : Masaki Kuboki
//
//==========================================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

//============================================================================================================
//
// マクロ宣言
//
//============================================================================================================
// debug(prote)
//#define FIELD_SIZE_WIDTH (10.0f)	// フィールド（横幅）
//#define FIELD_SIZE_HEIGHT (10.0f)	// フィールド（立幅）
//#define FIELD_SIZE (1)				// 計算で使うint型のフィールドの大きさ
//
//#define MESH_SIZE_WIDTH (1.0f)		// フィールドのメッシュ１つあたりの大きさ（横幅）
//#define MESH_SIZE_HEIGHT (1.0f)		// フィールドのメッシュ１つあたりの大きさ（縦幅）
//
//#define FIELD_DIVISION_NUM (11)		// フィールドの頂点数
//
//#define FIELD_VERTEX_NUM (121)		//　フィールドの総頂点数



//#define FIELD_SIZE_WIDTH (100.0f)	// フィールド（横幅）
//#define FIELD_SIZE_HEIGHT (100.0f)	// フィールド（立幅）
//#define FIELD_SIZE (1)				// 計算で使うint型のフィールドの大きさ
//
//#define MESH_SIZE_WIDTH (1.0f)		// フィールドのメッシュ１つあたりの大きさ（横幅）
//#define MESH_SIZE_HEIGHT (1.0f)		// フィールドのメッシュ１つあたりの大きさ（縦幅）
//
//#define FIELD_DIVISION_NUM (101)		// フィールドの頂点数
//
//#define FIELD_VERTEX_NUM (10201)		//　フィールドの総頂点数


#define FIELD_SIZE_WIDTH (10.0f)	// フィールド（横幅）
#define FIELD_SIZE_HEIGHT (10.0f)	// フィールド（立幅）
#define FIELD_SIZE (10)				// 計算で使うint型のフィールドの大きさ

#define MESH_SIZE_WIDTH (10.0f)		// フィールドのメッシュ１つあたりの大きさ（横幅）
#define MESH_SIZE_HEIGHT (10.0f)		// フィールドのメッシュ１つあたりの大きさ（縦幅）

#define FIELD_DIVISION_NUM (2)		// フィールドの頂点数

#define FIELD_VERTEX_NUM (4)		//　フィールドの総頂点数



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
	// テクスチャのアドレス
	LPDIRECT3DTEXTURE9 m_pTextures[7/*TEXTURE_MAX*/];

	int m_nVertexCount;	//	頂点数
	int m_nIndexCount;	//	インデックス頂点の数
	int m_nPrimitiveCount;

	D3DXMATRIX m_mtxWorld[5];		//ワールド行列
	D3DXMATRIX m_mtxParallel[5];		//平行移動行列
	D3DXMATRIX m_mtxRotation[5];		//回転行列

	D3DXVECTOR3 m_RotAxis;	//回転軸

	// 平行移動距離
	float m_fParallelMoveX;
	float m_fParallelMoveY;
	float m_fParallelMoveZ;
	bool m_bParallelMove;

	// 凹凸フィールドのリセットのカウント処理
	int m_nMeshCountX;
	int	m_nMeshCountZ;

	float m_fFieldHeight;	// フィールドの高さ(プラスする値)

	// アドレス格納 
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;

	int m_i;
};

#endif // !_FIELD_H_
