//=====================================================================================================
//
// [SCene.h] Author : Masaki Kuboki
//
//=====================================================================================================
#ifndef _MODE_TITLE_H_
#define _MODE_TITLE_H_
#include "main.h"
#include "Mode.h"
#include "RendererDX.h"
//=====================================================================================================
//
// class
//
//=====================================================================================================
class CModeTitle :public CMode
{
protected:

public:
	CModeTitle() { m_pDevice = CRendererDX::GetD3DDevice(); }
	~CModeTitle() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	LPDIRECT3DDEVICE9 m_pDevice;
	int m_nFade;
	bool m_bFade;
	float m_fHari;

	int m_nAlpha;
	bool m_bSwitch;
};


#endif