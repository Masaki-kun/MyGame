//=====================================================================================================================
//
// [SCeneLight.h] Author : Masaki Kuboki
//
//=====================================================================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Scene.h"

//=====================================================================================================================
//
// class
//
//=====================================================================================================================
class CSceneLight :public CScene
{
public:
	CSceneLight(int Priority) :CScene(Priority) {};
	~CSceneLight() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSceneLight *Create();

private:
	//DLightXVECTOR3 m_Position;
};

#endif


//D3DXVECTOR3 GetPlayerFront(void);
//D3DXVECTOR3 GetPlayerEye(void);
//D3DXVECTOR3 GetPlayerAt(void);