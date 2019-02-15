//==========================================================================================
//
// [SCeneMode.h] Author : Masaki Kuboki
//
//==========================================================================================
#include "2D.h"
#include "SceneMeter.h"
#include "RendererDX.h"
#include "XInput.h"
#include "Sound.h"

#define PRIORITY (2)

float i = 0.0f;

//============================================================================================================
//
//  Create
//
//============================================================================================================
CSceneMeter *CSceneMeter::Create()
{
	CSceneMeter *SceneMeter = new CSceneMeter(PRIORITY);
	SceneMeter->Init();
	return SceneMeter;
}

//==========================================================================================
//
//
//
//==========================================================================================
CSceneMeter::CSceneMeter(int Priority):CScene(Priority)
{
	m_pDevice = CRendererDX::GetD3DDevice();
	m_fHari = 0.0f;
	m_fHariBoost = 0.0f;
	m_nGear = 1;
	m_nGearTexTcx = 0;
	m_nGearTexTcy = 0;

	m_nFireCntX = 0;
	m_nFireCntY = 0;
	m_nFireCnt = 0;
	m_bFire = false;
}

//==========================================================================================
//
// Init
//
//==========================================================================================
void CSceneMeter::Init(void)
{

}

//==========================================================================================
//
// Uninit
//
//==========================================================================================
void CSceneMeter::Uninit(void)
{
	
}

//==========================================================================================
//
// Update
//
//==========================================================================================
void CSceneMeter::Update(void)
{
	if (0 <= m_nGear && m_nGear <= 5)
	{
		// シフトアップ
		if (CInput::GetKeyboardTrigger(DIK_U) || CXinput::GetTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER, 0))
		{
			if (m_nGear > 0) { m_fHari = 1.8f; }
			if (m_nGear < 5) { m_nGear++; }
		}

		// シフトダウン
		if (CInput::GetKeyboardTrigger(DIK_J) || CXinput::GetTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER, 0))
		{
			if (m_nGear > 0) { m_nGear--; }
			m_fHari = 2.5f;
		}

		
	}

	// ギアによって数字を変える
	switch (m_nGear)
	{
	case 0:
		m_nGearTexTcx = 0;
		m_nGearTexTcy = 0;
		break;

	case 1:
		m_nGearTexTcx = 150;
		m_nGearTexTcy = 0;
		break;

	case 2:
		m_nGearTexTcx = 300;
		m_nGearTexTcy = 0;
		break;

	case 3:
		m_nGearTexTcx = 450;
		m_nGearTexTcy = 0;
		break;

	case 4:
		m_nGearTexTcx = 600;
		m_nGearTexTcy = 0;
		break;

	case 5:
		m_nGearTexTcx = 750;
		m_nGearTexTcy = 282;
		break;
	}

	if (CXinput::GetPress(XINPUT_GAMEPAD_A, 0) || CInput::GetKeyboardPress(DIK_W))
	{
		// ブーストメーター
		if (m_fHariBoost < 4.1f) { m_fHariBoost += 0.5f; }

		// レブリミッター
		if (m_fHari > 4.7f)	{ m_fHari -= 0.3f;}

		switch (m_nGear)	// ギアによってハリの回転速度を変える
		{
		case 0:
			m_fHari += 0.08f;
			break;

		case 1:
			m_fHari += 0.05f;
			break;

		case 2:
			m_fHari += 0.04f;
			break;

		case 3:
			m_fHari += 0.03f;
			break;

		case 4:
			m_fHari += 0.02f;
			break;

		case 5:
			m_fHari += 0.01f;
			break;
		}
	}
	else if(m_fHari > 0.0f)		// ハリの戻る速度
	{
		m_fHari -= 0.05f;

		if (m_fHariBoost >= 0.3f){ m_fHariBoost -= 0.3f;}
	}

	// アフターファイアアニメーション
	if (CXinput::GetRelease(XINPUT_GAMEPAD_A, 0) || CInput::GetKeyboardRelease(DIK_W))
	{ 
		m_bFire = true; 
		CSound::PlaySound(SOUND_LABEL_SE_AFTER_FIRE);
	}

	if (m_bFire)
	{
		m_nFireCntX += 61;
		m_nFireCntY += 64;
		m_nFireCnt++;

		if (m_nFireCntX >= 366) { m_nFireCntX = 0; }
		if (m_nFireCntY >= 448) { m_nFireCntY = 0; }
		if (m_nFireCnt >= 44) { m_bFire = false; }
	}
	else
	{
		m_nFireCntX = 0;
		m_nFireCntY = 0;
		m_nFireCnt = 0;
	}

}

//==========================================================================================
//
// Draw
//
//==========================================================================================
void CSceneMeter::Draw(void)
{
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	
	// タコメーター
	C2D::Draw(TEXTURE_METER, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.5f, 0.5f, { 1630.0f,610.0f,0.0f },true);

	// ハリ（タコメーター）
	C2D::SetRotation(250, 250, m_fHari);
	C2D::Draw(TEXTURE_HARI, 0, 0, 500, 500, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.5f, 0.5f, { 1630.0f+125.0f,610.0f + 125.0f,0.0f }, false);

	// メーターの中の現在のギアの数字
	C2D::Draw(TEXTURE_NUMBER, m_nGearTexTcx, m_nGearTexTcy, 150, 282, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.2f, 0.2f, { 1780.0f,760.0f,0.0f }, true);
	
	// ブーストメーター
	C2D::Draw(TEXTURE_BOOSTMETER, 0, 0, 1000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.15f, 0.15f, { 1520.0f,500.0f,0.0f }, true);
	
	// ハリ（ブーストメーター）
	C2D::SetRotation(500, 500, m_fHariBoost);
	C2D::Draw(TEXTURE_HARI_BOOST, 0, 0, 1000, 1000, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.15f, 0.15f, { 1520.0f + 75.0f,500.0f + 80.0f,0.0f }, false);
	
	C2D::Draw(TEXTURE_NAME, 0, 0, 1024, 256, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 0.55f, 0.55f, { 1360.0f,900.0f,0.0f }, true);

	// シフトインジゲータ（左下のやつ）
	C2D::Draw(TEXTURE_SHIFT_01, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);

	switch (m_nGear)
	{
	case 0:
		C2D::Draw(TEXTURE_GEAR_01, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);
		break;

	case 1:
		C2D::Draw(TEXTURE_GEAR_01, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);
		break;

	case 2:
		C2D::Draw(TEXTURE_GEAR_02, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);
		break;

	case 3:
		C2D::Draw(TEXTURE_GEAR_03, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);
		break;

	case 4:
		C2D::Draw(TEXTURE_GEAR_04, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);
		break;

	case 5:
		C2D::Draw(TEXTURE_GEAR_05, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);
		break;
	}

	C2D::Draw(TEXTURE_SHIFT_03, 0, 0, 256, 300, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 1.0f, 0.9f, { 50.0f,800.0f,0.0f }, true);


	// アフターファイア（アニメーション）
	if (m_bFire)
	{
		C2D::Draw(TEXTURE_FIRE, m_nFireCntX, m_nFireCntY, 61, 64, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, 2.0f, 2.0f, { 1100.0f,950.0f,0.0f }, true);
	}

	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}