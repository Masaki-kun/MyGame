//========================================================================================================
//
// [SCene3D.h] Author : Masaki Kuboki
//
//========================================================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "Scene.h"

//========================================================================================================
//
// class
//
//========================================================================================================
class CScene3D:public CScene
{
public:
	CScene3D(int Priority);
	~CScene3D();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene3D *Create();

private:
	D3DXVECTOR3 m_Position;
	D3DXMATRIX m_mtxWorld;		//ワールド変換行列
	D3DXMATRIX m_mtxView;		//ビュー行列
	D3DXMATRIX m_mtxProjection;	//プロジェクション変換行列
	float m_fRot;			//立方体の回転速度
	bool m_bSwitch;		//カメラ位置の上下反転
	int m_nPosZ;
	int m_nPosX;

};

#endif