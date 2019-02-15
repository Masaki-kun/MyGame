//=====================================================================================================
//
// [SCene.h] Author : Masaki Kuboki
//
//=====================================================================================================
#ifndef _MODE_RESULT_H_
#define _MODE_RESULT_H_
#include "main.h"
#include "Mode.h"
#include "RendererDX.h"
//=====================================================================================================
//
// class
//
//=====================================================================================================
class CModeResult :public CMode
{
protected:

public:
	CModeResult() { m_pDevice = CRendererDX::GetD3DDevice(); }
	~CModeResult() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	int m_nFade;
	bool m_bFade;

	int m_nAlpha;
	bool m_bSwitch;

	bool m_bDebug;
};


#endif