//============================================================================================================
//
//  [SCene2D.cpp] Author : Masaki Kuboki
//
//============================================================================================================
#include "main.h"
#include "2D.h"
#include "RendererDX.h"

//============================================================================================================
//
// グローバル変数
//
//============================================================================================================
//static LPDIRECT3DDEVICE9 g_pDevice;

#define ARRAYCOUNT(x)	sizeof(x)/sizeof(x[0])
static const int TEXTURE_FILE_COUNT = ARRAYSIZE(g_aTexture);	// 定数　const

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_MAX];				// テクスチャー
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;			// この人も使ったらリリース

bool  C2D::m_bAffine;
float C2D::m_dx;
float C2D::m_dy;
int   C2D::m_tcx;
int   C2D::m_tcy;
int   C2D::m_tcw;
int   C2D::m_tch;
float C2D::m_fScaleX;
float C2D::m_fScaleY;
float C2D::m_fScaleOffsetX;
float C2D::m_fScaleOffsetY;
float C2D::m_fAngle;
float C2D::m_fRotationOffsetX;
float C2D::m_fRotationOffsetY;
float C2D::m_fAngleMode;
float C2D::m_fRotationOffsetXMode;
float C2D::m_fRotationOffsetYMode;
int   C2D::m_nSCeneTextureNum;
int   C2D::m_nPriority;
D3DCOLOR C2D::m_Color;
D3DXVECTOR3 C2D::m_Position;
LPDIRECT3DDEVICE9 C2D::m_pDevice;

//============================================================================================================
//
//
//
//============================================================================================================
C2D::C2D(int Priority)//:CScene(Priority)
{
	m_dx = 0.0f;	// テクスチャ座標X
	m_dy = 0.0f;	// テクスチャ座標Y
	m_tcx = 0;		// テクスチャ切り取り始め座標X
	m_tcy = 0;		// テクスチャ切り取り始め座標Y
	m_tcw = 0;		// テクスチャ切り取り幅
	m_tch = 0;		// テクスチャ切り取り高さ
	m_bAffine = true;

	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fScaleOffsetX = 0.0f;
	m_fScaleOffsetY = 0.0f;
	
	m_fAngle = 0.0f;
	m_fRotationOffsetX = 0.0f;
	m_fRotationOffsetY = 0.0f;

	m_fAngleMode = 0.0f;
	m_fRotationOffsetXMode = 0.0f;
	m_fRotationOffsetYMode = 0.0f;

	m_nSCeneTextureNum = 0;
	m_Color = (255,255,255,255);

	m_Position = { 1000.0f,0.0f,0.0f };

	m_pDevice;

	m_nPriority;
}

//============================================================================================================
//
// Init
//
//============================================================================================================
bool C2D::Init(HWND hWnd)
{
	m_pDevice = CRendererDX::GetD3DDevice();

	if (m_pDevice == NULL) { return false; }

	HRESULT hr;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		hr = D3DXCreateTextureFromFile(m_pDevice, g_aTexture[i].fileName, &g_pTextures[i]);

		if (FAILED(hr))
		{

			MessageBox(hWnd, "テクスチャーが読み込めなかった", "error", MB_OK);
			return false;
		}
	}

	// バッファー
	hr = m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);

	if (FAILED(hr)) { MessageBox(NULL, "バッファーの作成に失敗しました", "error", MB_OK); }
}

//============================================================================================================
//
// Uninit
//
//============================================================================================================
void C2D::Uninit(void)
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++) {
		if (g_pTextures[i] != NULL)
		{
			// デバイスの開放
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

//============================================================================================================
//
//
//
//
//============================================================================================================
void C2D::Update(void)
{
	
}

//============================================================================================================
//
//
// 回転
//
//============================================================================================================
void C2D::SetRotation(float cx, float cy, float angle)
{
	m_fRotationOffsetXMode = cx;
	m_fRotationOffsetYMode = cy;
	m_fAngleMode = angle;


}

//============================================================================================================
//
//
//
//============================================================================================================
void C2D::Draw(TEXTURE_ENUM TexNum, int tcx, int tcy, int tcw, int tch, D3DCOLOR color, float sfx, float sfy, float sx, float sy, D3DXVECTOR3 Position, bool affine)
{
	m_nSCeneTextureNum = TexNum;
	m_Color = color;
	m_fScaleOffsetX = sfx;
	m_fScaleOffsetY = sfy;
	m_fScaleX = sx;
	m_fScaleY = sy;
	m_bAffine = affine;
	
	if (m_pDevice == NULL){ return;	}

	if (m_bAffine)
	{
		//CreateVertexAffineMode(Position.x, Position.y, tcx, tcy, tcw, tch);
		CreateVertexAffine(Position.x, Position.y, tcx, tcy, tcw, tch);
	}
	else
	{
		CreateVertexAffineMode(Position.x, Position.y, tcx, tcy, tcw, tch);
		//CreateVertex(Position.x, Position.y, tcx, tcy, tcw, tch);
	}

	// FVF（今から使用する頂点情報）の設定
	m_pDevice->SetFVF(FVF_VERTEX_2D);
	m_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX_2D));	
	m_pDevice->SetTexture(0, g_pTextures[m_nSCeneTextureNum]);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//==========================================================================================================================================================
//
// CreateVertex
//
//==========================================================================================================================================================
void C2D::CreateVertex(float dx, float dy, int tcx, int tcy, int tcw, int tch)	// バッファーのロック　擬似のアドレス
{
	VERTEX_2D* pV;			// 擬似アドレスの格納先

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);		// ロックの選択範囲　0なら全選択	pVにアドレス入らなかったら最後の引数に０

	pV[0].pos = D3DXVECTOR4(-0.5f + dx       * m_fScaleX, -0.5f + dy       * m_fScaleY, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(-0.5f + dx + tcw * m_fScaleX, -0.5f + dy       * m_fScaleY, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(-0.5f + dx       * m_fScaleX, -0.5f + dy + tch * m_fScaleY, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(-0.5f + dx + tcw * m_fScaleX, -0.5f + dy + tch * m_fScaleY, 1.0f, 1.0f);

	pV[0].color =
	pV[1].color =
	pV[2].color =
	pV[3].color = m_Color;

	int tw = g_aTexture[m_nSCeneTextureNum].width;
	int th = g_aTexture[m_nSCeneTextureNum].height;

	float u0 = (float)tcx / tw;			// 左上
	float v0 = (float)tcy / th;			// 右下
	float u1 = (float)(tcx + tcw) / tw;		// 
	float v1 = (float)(tcy + tch) / th;		// 

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();

}

//==========================================================================================================================================================
//
// CreateVertexAffine
//
//==========================================================================================================================================================
void C2D::CreateVertexAffine(float dx, float dy, int tcx, int tcy, int tcw, int tch)	// バッファーのロック　擬似のアドレス
{
	VERTEX_2D* pV;			// 擬似アドレスの格納先

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);		// ロックの選択範囲　0なら全選択	pVにアドレス入らなかったら最後の引数に０


	float fRotationOffsetX = m_fRotationOffsetX * m_fScaleX;
	float fRotationOffsetY = m_fRotationOffsetY * m_fScaleY;

	//1616で演算する場合
	float x   = (0.0f - m_fRotationOffsetX) * m_fScaleX + ( m_fRotationOffsetX * m_fScaleX);
	float x_w = (tcw -  m_fRotationOffsetX) * m_fScaleX + ( m_fRotationOffsetX * m_fScaleX);
	float y   = (0.0f - m_fRotationOffsetY) * m_fScaleY + ( m_fRotationOffsetY * m_fScaleY);
	float y_h = (tch -  m_fRotationOffsetY) * m_fScaleY + ( m_fRotationOffsetY * m_fScaleY);

	x   -= fRotationOffsetX;
	x_w -= fRotationOffsetX;
	y   -= fRotationOffsetY;
	y_h -= fRotationOffsetY;

	dx += m_fRotationOffsetX - 0.5f;
	dy += m_fRotationOffsetY - 0.5f;

	pV[0].pos = D3DXVECTOR4(x   * cosf(m_fAngle) - y   * sinf(m_fAngle) + dx, x   * sinf(m_fAngle) + y   * cosf(m_fAngle) + dy, 0.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(x_w * cosf(m_fAngle) - y   * sinf(m_fAngle) + dx, x_w * sinf(m_fAngle) + y   * cosf(m_fAngle) + dy, 0.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(x   * cosf(m_fAngle) - y_h * sinf(m_fAngle) + dx, x   * sinf(m_fAngle) + y_h * cosf(m_fAngle) + dy, 0.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(x_w * cosf(m_fAngle) - y_h * sinf(m_fAngle) + dx, x_w * sinf(m_fAngle) + y_h * cosf(m_fAngle) + dy, 0.0f, 1.0f);

	pV[0].color =
	pV[1].color =
	pV[2].color =
	pV[3].color = m_Color;

	int tw = g_aTexture[m_nSCeneTextureNum].width;
	int th = g_aTexture[m_nSCeneTextureNum].height;

	float u0 = (float)tcx / tw;				// 左上
	float v0 = (float)tcy / th;				// 右下
	float u1 = (float)(tcx + tcw) / tw;		// 
	float v1 = (float)(tcy + tch) / th;		// 

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();
}

//==========================================================================================================================================================
//
// CreateVertexAffineMode
//
//==========================================================================================================================================================
void C2D::CreateVertexAffineMode(float dx, float dy, int tcx, int tcy, int tcw, int tch)	// バッファーのロック　擬似のアドレス
{
	VERTEX_2D* pV;			// 擬似アドレスの格納先

	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);		// ロックの選択範囲　0なら全選択	pVにアドレス入らなかったら最後の引数に０


	float fRotationOffsetX = m_fRotationOffsetXMode * m_fScaleX;
	float fRotationOffsetY = m_fRotationOffsetYMode * m_fScaleY;

	//1616で演算する場合
	float x   = (0.0f - m_fRotationOffsetXMode) * m_fScaleX + (m_fRotationOffsetXMode * m_fScaleX);
	float x_w = (tcw  - m_fRotationOffsetXMode) * m_fScaleX + (m_fRotationOffsetXMode * m_fScaleX);
	float y   = (0.0f - m_fRotationOffsetYMode) * m_fScaleY + (m_fRotationOffsetYMode * m_fScaleY);
	float y_h = (tch  - m_fRotationOffsetYMode) * m_fScaleY + (m_fRotationOffsetYMode * m_fScaleY);

	x   -= fRotationOffsetX;
	x_w -= fRotationOffsetX;
	y   -= fRotationOffsetY;
	y_h -= fRotationOffsetY;

	dx += m_fRotationOffsetX - 0.5f;
	dy += m_fRotationOffsetY - 0.5f;

	pV[0].pos = D3DXVECTOR4(x   * cosf(m_fAngleMode) - y   * sinf(m_fAngleMode) + dx, x   * sinf(m_fAngleMode) + y   * cosf(m_fAngleMode) + dy, 1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(x_w * cosf(m_fAngleMode) - y   * sinf(m_fAngleMode) + dx, x_w * sinf(m_fAngleMode) + y   * cosf(m_fAngleMode) + dy, 1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(x   * cosf(m_fAngleMode) - y_h * sinf(m_fAngleMode) + dx, x   * sinf(m_fAngleMode) + y_h * cosf(m_fAngleMode) + dy, 1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(x_w * cosf(m_fAngleMode) - y_h * sinf(m_fAngleMode) + dx, x_w * sinf(m_fAngleMode) + y_h * cosf(m_fAngleMode) + dy, 1.0f, 1.0f);

	pV[0].color =
pV[1].color =
pV[2].color =
pV[3].color = m_Color;

	int tw = g_aTexture[m_nSCeneTextureNum].width;
	int th = g_aTexture[m_nSCeneTextureNum].height;

	float u0 = (float)tcx / tw;				// 左上
	float v0 = (float)tcy / th;				// 右下
	float u1 = (float)(tcx + tcw) / tw;		// 
	float v1 = (float)(tcy + tch) / th;		// 

	pV[0].texcoord = D3DXVECTOR2(u0, v0);
	pV[1].texcoord = D3DXVECTOR2(u1, v0);
	pV[2].texcoord = D3DXVECTOR2(u0, v1);
	pV[3].texcoord = D3DXVECTOR2(u1, v1);

	g_pVertexBuffer->Unlock();
}
