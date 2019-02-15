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
	D3DXMATRIX m_mtxWorld;		//���[���h�ϊ��s��
	D3DXMATRIX m_mtxView;		//�r���[�s��
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����ϊ��s��
	float m_fRot;			//�����̂̉�]���x
	bool m_bSwitch;		//�J�����ʒu�̏㉺���]
	int m_nPosZ;
	int m_nPosX;

};

#endif