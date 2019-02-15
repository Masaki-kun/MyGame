//=============================================================================
//
// [Renderer.h] Author : Masaki Kuboki
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*************************************
// class
//*************************************
class CRendererDX
{
public:
	CRendererDX();
	~CRendererDX();

	static bool Init(HWND hWnd, BOOL bWindow);
	static void Uninit(void);
	static void DrawBegin(void);
	static void DrawEnd(void);
	static LPDIRECT3DDEVICE9 GetD3DDevice(void);
	static void Drawing(void);

private:
	static LPDIRECT3D9 m_pD3D;
	static LPDIRECT3DDEVICE9 m_pD3DDevice;
	

};

#endif