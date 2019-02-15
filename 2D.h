//==========================================================================================
//
// [SCene2D.h] Author : Masaki Kuboki
//
//==========================================================================================
#ifndef _2D_H_
#define _2D_H_

#include "Scene.h"

typedef struct {				//テクスチャー情報構造体　ファイルネーム、幅、高さ
	char fileName[256];
	int width;
	int height;
}TEXTURE;

static const TEXTURE g_aTexture[] = {
	{ "data/texture/field/skybox.jpg",       1200,1600 },

	// 数字
	{ "data/texture/number/number.png",       750, 564 },	// 150*282 (横＊高さ)
	{ "data/texture/number/second.png",	      150, 282 },
	{ "data/texture/number/minute.png",	      150, 282 },

	// メーター
	{ "data/texture/meter/meter.png",		  500, 500 },
	{ "data/texture/meter/hari.png",		  500, 500 },
	{ "data/texture/meter/boost_meter.png",  1000,1000 },
	{ "data/texture/meter/hari_boost.png",   1000,1000 },

	// 画面遷移
	{ "data/texture/finish.png",	         1920,1080 },
	{ "data/texture/title.png",	             1920,1080 },
	{ "data/texture/result.png",	         1920,1080 },
	{ "data/texture/fade.png",	             1920,1080 },
	{ "data/texture/pose.png",	             1920,1080 },
	{ "data/texture/sky.png" ,	             1920,1080 },

	{ "data/texture/press_space.png" ,	      480, 135 },
	{ "data/texture/press_start.png" ,		  512, 128 },

	// チュートリアル
	{ "data/texture/road.png" ,				 3000,3000 },
	{ "data/texture/tutorial.png" ,			 1920,1080 },

	// 周回数
	{ "data/texture/lap/lap.png" ,			 768, 512  },
	{ "data/texture/lap/lap0.png" ,				768, 512  },
	{ "data/texture/lap/lap1.png" ,				768, 512  },
	{ "data/texture/lap/lap2.png" ,				768, 512  },
	{ "data/texture/lap/lap3.png" ,				768, 512  },

	// ミニマップ
	{ "data/texture/minimap/minimap.png" ,		 599, 1043 },
	{ "data/texture/minimap/miniplayer.png" ,	 711, 711 },
	{ "data/texture/minimap/minimapBackground.png",	256,256 },

	// 左下　シフトの図
	{ "data/texture/shift/shift01.png",		 256,300 },
	{ "data/texture/shift/shift03.png",		 256,300 },
	{ "data/texture/shift/gear01.png",		 256,300 },
	{ "data/texture/shift/gear02.png",		 256,300 },
	{ "data/texture/shift/gear03.png",		 256,300 },
	{ "data/texture/shift/gear04.png",		 256,300 },
	{ "data/texture/shift/gear05.png",		 256,300 },

	// タイム関係
	{ "data/texture/time/time.png",			1280,128 },
	{ "data/texture/time/timeHistory.png",  1280,128 },
	{ "data/texture/time/laptime.png",		1280,128 },
	{ "data/texture/name.png",				1024,256},

	{ "data/texture/fire.png",				 384,512 }, // 横61　縦64

	// カウントダウン
	{ "data/texture/countdown/countdown_1.png", 512,512 },
	{ "data/texture/countdown/countdown_2.png", 512,512 },
	{ "data/texture/countdown/countdown_3.png", 512,512 },
	{ "data/texture/countdown/countdown_go.png", 768,512 }

	
	
};

//==========================================================================================
//
// テクスチャ列挙
//
//==========================================================================================
typedef enum TEXTURE_ENUM
{
	TEXTURE_SKYBOX,
	// 数字
	TEXTURE_NUMBER,
	TEXTURE_SECOND,
	TEXTURE_MINUTE,
	
	// メーター
	TEXTURE_METER,
	TEXTURE_HARI,
	TEXTURE_BOOSTMETER,
	TEXTURE_HARI_BOOST,

	// 画面遷移
	TEXTURE_FINISH,
	TEXTURE_TITLE,
	TEXTURE_RESULT,
	TEXTURE_FADE,
	TEXTURE_POSE,
	TEXTURE_SKY,

	TEXTURE_PRESS_SPACE,
	TEXTURE_PRESS_START,

	// チュートリアル
	TEXTURE_ROAD,
	TEXTURE_TUTORIAL,

	// 周回数
	TEXTURE_LAP,
	TEXTURE_LAP0,
	TEXTURE_LAP1,
	TEXTURE_LAP2,
	TEXTURE_LAP3,

	// ミニマップ
	TEXTURE_MINIMAP,
	TEXTURE_MINIPLAYER,
	TEXTURE_MINIMAP_BACKGROUND,

	// 左下　シフトの図
	TEXTURE_SHIFT_01,
	TEXTURE_SHIFT_03,
	TEXTURE_GEAR_01,
	TEXTURE_GEAR_02,
	TEXTURE_GEAR_03,
	TEXTURE_GEAR_04,
	TEXTURE_GEAR_05,

	// タイム関係
	TEXTURE_TIME,
	TEXTURE_TIME_HISTORY,
	TEXTURE_TIME_LAP,
	TEXTURE_NAME,

	TEXTURE_FIRE,

	// カウントダウン
	TEXTURE_COUNTDOWN_1,
	TEXTURE_COUNTDOWN_2,
	TEXTURE_COUNTDOWN_3,
	TEXTURE_COUNTDOWN_GO,

	TEXTURE_MAX
};

//==========================================================================================
//
// 構造体
//
//==========================================================================================
typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
} VERTEX_2D;

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |D3DFVF_TEX1)	

//==========================================================================================
//
// class
//
//==========================================================================================
class C2D
{
public:
	C2D(int Priority);
	~C2D() {}

	static bool Init(HWND hWnd);
	static void Uninit(void);
	static void Update(void);
	static void Draw(TEXTURE_ENUM TexNum, int tcx, int tcy, int tcw, int tch, D3DCOLOR color, float sfx, float sfy, float sx, float sy, D3DXVECTOR3 Position,bool affine);

	static void SetRotation(float cx, float cy, float angle);

	static void CreateVertex(float dx, float dy, int tcx, int tcy, int tcw, int tch);
	static void CreateVertexAffine(float dx, float dy, int tcx, int tcy, int tcw, int tch);
	static void CreateVertexAffineMode(float dx, float dy, int tcx, int tcy, int tcw, int tch);

	// static void

private:
	static D3DXVECTOR3 m_Position;
	static D3DCOLOR m_Color;
	static float m_dx;
	static float m_dy;
	static int m_tcx;
	static int m_tcy;
	static int m_tcw;
	static int m_tch;
	static bool m_bAffine;
	static float m_fScaleX;
	static float m_fScaleY;

	static float m_fScaleOffsetX;
	static float m_fScaleOffsetY;
	static float m_fAngle;

	static float m_fRotationOffsetXMode;
	static float m_fRotationOffsetYMode;
	static float m_fAngleMode;

	static float m_fRotationOffsetX;
	static float m_fRotationOffsetY;
	static int m_nSCeneTextureNum;
	static int m_nPriority;
	static LPDIRECT3DDEVICE9 m_pDevice;

};

// zバッファ無効
//m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

//m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

#endif