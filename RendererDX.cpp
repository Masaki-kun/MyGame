//=====================================================================================================================
//
//  [Renderer.cpp] Author : Masaki Kuboki
//
//=====================================================================================================================
#include "main.h"
#include "RendererDX.h"

//=====================================================================================================================
//
// staticメンバ変数
//
//=====================================================================================================================
LPDIRECT3D9 CRendererDX::m_pD3D;
LPDIRECT3DDEVICE9 CRendererDX::m_pD3DDevice;

//=====================================================================================================================
//
//
//
//=====================================================================================================================
CRendererDX::CRendererDX()
{

}

//=====================================================================================================================
// 
//
//
//=====================================================================================================================
CRendererDX::~CRendererDX()
{

}

//=====================================================================================================================
//
//
//
//=====================================================================================================================
bool CRendererDX::Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3Dインターフェースの取得
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);		// エンドユーザーランタイム
	if (m_pD3D == NULL)
	{
		return false;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) { return false/*E_FAIL*/; }

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		// d3dpp分０で埋めてください

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーRGBA32bit
	d3dpp.BackBufferCount = 1;										// 後ろ画面何枚いる？
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//
	d3dpp.EnableAutoDepthStencil = TRUE;							// 基本的にtrueにする　映像信号に同期してフリップ
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//
	d3dpp.Windowed = !bWindow;										// windowにするのかフルスクリーンか	!bWindowでフルスクリーン
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// 秒間 ONEだと一回終わったというメッセージがきたら再描画 今どれくらいで描画できるのか試したいときはIMMEDIATE
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		MessageBox(hWnd, "デバイスが作成できませんでした", "check", MB_OK);
		return false/*E_FAIL*/;
	}




	// レンダステートパラメータの設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// 第1引数アルファのタイプ    第2引数 使うかどうかの判断
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// α
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// α

																			// α値の乗算ができるように
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // 第2引数   ポリゴンとテクスチャをどうブレンドさせるか
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // 第2引数   ポリゴンとテクスチャをどうブレンドさせるか
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // 第2引数   ポリゴンとテクスチャをどうブレンドさせるか

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//=====================================================================================================================
	// フィルター
	//=====================================================================================================================
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);	
}

//=====================================================================================================================
//
//
//
//=====================================================================================================================
void CRendererDX::Uninit(void)
{
	if (m_pD3DDevice != NULL)					// これをやらないと他の人に悪影響　マナー　メモリは必ず返す
	{
		// デバイスの開放
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	if (m_pD3D != NULL)							// これをやらないと他の人に悪影響
	{
		// Direct3Dオブジェクトの開放
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=====================================================================================================================
//
// DrawBegin
//
//=====================================================================================================================
void CRendererDX::DrawBegin(void)
{
	//clear, Beginシーン,Endシーン,presentは１フレームに一つ
	// カウント、範囲クリア（今回は全画面）、色のこと、何色でクリア、ZBUFFERのクリア値、ステンシルバッファーのクリアー
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	m_pD3DDevice->BeginScene();
	//bDraw = true;
}

//=====================================================================================================================
//
// DrawEnd
//
//=====================================================================================================================
void CRendererDX::DrawEnd(void)
{
	m_pD3DDevice->EndScene();	// Direct3Dによる描画の終了
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);	// present は送る　Drawの最後に呼ぶ
}

LPDIRECT3DDEVICE9 CRendererDX::GetD3DDevice(void)
{
	return m_pD3DDevice;
}

void CRendererDX::Drawing(void)
{

}