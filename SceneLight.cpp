//============================================================================================================
//
//	[Light] Author : Masaki Kuboki
//
//============================================================================================================
#include "main.h"
//#include "Scene.h"
#include "SceneLight.h"
#include "RendererDX.h"

//============================================================================================================
//
//  グローバル変数宣言
//
//============================================================================================================
#define PRIORITY (0)

//D3DXVECTOR3 vecDir(1.0f, 1.0f, 1.0f);
//============================================================================================================
// 
//
//
//============================================================================================================
CSceneLight *CSceneLight::Create()
{
	CSceneLight *SceneLight = new CSceneLight(PRIORITY);
	SceneLight->Init();
	return SceneLight;
}

//============================================================================================================
//
//	Init
//
//============================================================================================================
void CSceneLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRendererDX::GetD3DDevice();

	//マテリアルのつくりかた
	D3DMATERIAL9 mat;	//マテリアル一つにつき一つ用意する
	ZeroMemory(&mat, sizeof(mat));
	mat.Diffuse.r = 1.0f;
	mat.Diffuse.g = 1.0f;
	mat.Diffuse.b = 1.0f;
	mat.Diffuse.a = 1.0f;

	mat.Ambient.r = 0.8f;
	mat.Ambient.g = 0.1f;
	mat.Ambient.b = 0.9f;
	mat.Ambient.a = 2.0f;

	pDevice->SetMaterial(&mat);	//描画前に設置
	pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);	//うまくいなかったら使う
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));

	//pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.0f,0.0f,0.0f, 1.0f));


	////平行ライト
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;

	D3DXVECTOR3 vecDir(1.0f, 1.0f, 1.0f);
	//vecDir = { 1.0f, 1.0f, 1.0f };
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	//ライトの色
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;

	pDevice->SetLight(0, &light);	//SetLight(ライト番号(0～3)

									//pDevice->LightEnable(0, FALSE);	//ライトのON/OF
	pDevice->LightEnable(0, TRUE);	//ライトのON/OF
}

//============================================================================================================
//
//  Uninit
//
//============================================================================================================
void CSceneLight::Uninit(void)
{

}

//============================================================================================================
//
//  Update
//
//============================================================================================================
void CSceneLight::Update(void)
{

	
}

//============================================================================================================
//
//  Draw
//
//============================================================================================================
void CSceneLight::Draw(void)
{

}