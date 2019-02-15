//=====================================================================================================================
//
// [sound.h]  Author : Masaki Kuboki
//
//=====================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=====================================================================================================================
//
// パラメータ構造体定義
//
//=====================================================================================================================
typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDPARAM;


//=====================================================================================================================
//
// サウンドファイル
//
//=====================================================================================================================
typedef enum
{
	SOUND_LABEL_BGM_START = 0,		// BGM0
	SOUND_LABEL_BGM_RACE,		// 弾発射音
	SOUND_LABEL_SE_SKIL,		// ヒット音
	SOUND_LABEL_SE_AFTER_FIRE,	// アフターファイア

	SOUND_LABEL_MAX,
} SOUND_LABEL;

// 各音素材のパラメータ -1:ループ 0:単発
static const SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{   
	 
	{ "data/sound/bgm_start.wav",  -1 },	// BGM0      
	{ "data/sound/bgm_race.wav",   -1 },	// 弾発射音
	{ "data/sound/skil.wav", 0 },			// スキール音
	{ "data/sound/after_fire.wav", 0 }		// アフターファイア
};


//==========================================================================================
//
// class
//
//==========================================================================================
class CSound
{
public:
	CSound() {};
	~CSound() {}

	static HRESULT InitSound(HWND hWnd);
	static void UninitSound(void);
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);


private:


};


#endif


/*

//=====================================================================================================================
//
// プロトタイプ宣言
//
//=====================================================================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

*/