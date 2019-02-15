//==========================================================================================
//
// [SCene2D.h] Author : Masaki Kuboki
//
//==========================================================================================
#ifndef _SCENETIMER_H_
#define _SCENETIMER_H_

#include "Scene.h"

//==========================================================================================
//
// class
//
//==========================================================================================
class CSceneTime :public CScene
{
public:
	CSceneTime(int Priority);
	~CSceneTime() {};

	// エラー、テクスチャの種類、テクスチャサイズ、テクスチャサイズ、スケール、スケール、色、スケール、スケール、スケール、スケール
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//static CScenePlayer* GetPlayerPos(void);

	static CSceneTime *Create(void);
	//static bool GetFinish(void);

private:

	int m_nPriority;

	LPDIRECT3DDEVICE9 m_pDevice;
	D3DXVECTOR3 m_PlayerPos;

	int m_nTimeCnt;
	int m_nTimeCnt0;
	int m_nTimeCnt00;
	int m_nScore;

	int m_tcx;
	int m_tcy;
	int m_tcw;
	int m_tch;

	float m_fScale;
	float m_fScaleX;
	float m_fScaleY;

	bool m_bFinish;
	int m_nTime;

	int m_nTime0;
	int m_tcx0;
	int m_tcy0;

	int m_nTime00;
	int m_tcx00;
	int m_tcy00;

	int m_nTimeCnt10;
	int m_nTime10;
	int m_tcx10;
	int m_tcy10;

	int m_nTimeCnt100;
	int m_nTime100;
	int m_tcx100;
	int m_tcy100;

	// 過去のタイム
	int m_nLapTime00[3];
	int m_nLapTime0[3];
	int m_nLapTime[3];
	int m_nLapTime10[3];
	int m_nLapTime100[3];

	// 周回計算処理
	int m_nLapCnt;
	bool m_bLap;
	bool m_bLapStart;
	float m_fLapScale;

	float m_fResultLapScale;
	//static bool m_bGetFinish;

	int m_nAlpha;
	bool m_bAlphaSwitch;

	float m_PlayerPosSetX;
	float m_PlayerPosSetY;

	// 開始処理（カウントダウン）
	int m_nCountdownCnt;
	int m_nCountdown;
	int m_nCountdown2;
	bool m_bStart;
};

#endif