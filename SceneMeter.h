//==========================================================================================
//
// [SCeneMode.h] Author : Masaki Kuboki
//
//==========================================================================================
#ifndef _SCENE_METER_H_
#define _SCENE_METER_H_

#include "Scene.h"

//==========================================================================================
//
// class
//
//==========================================================================================
class CSceneMeter :public CScene
{
public:
	CSceneMeter(int Priority);
	~CSceneMeter() {}

	static CSceneMeter *Create(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	float m_fHari;
	int m_nGear;
	int m_nGearTexTcx;
	int m_nGearTexTcy;

	float m_fHariBoost;

	// アフターファイア
	int m_nFireCntX;
	int m_nFireCntY;
	int m_nFireCnt;
	bool m_bFire;


};



#endif