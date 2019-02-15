//=====================================================================================================
//
// [input.cpp]  Author : Masaki Kuboki
//	これ覚えるc:\program files (x86)\microsoft directx sdk (june 2010)\include\dinput.h: DIRECTINPUT_VERSION undefined. Defaulting to version 0x0800
//=====================================================================================================
#include <windows.h>
#define DIRECTINPUT_VERSION	(0x0800)
#include <dinput.h>
#include "Input.h"

//=====================================================================================================
//
// staticメンバ変数
//
//=====================================================================================================
LPDIRECTINPUT8		 CInput::m_pInput = NULL;
LPDIRECTINPUTDEVICE8 CInput::m_pDevKeyboard = NULL;
BYTE				 CInput::m_aKeyState[NUM_KEY_MAX];
BYTE				 CInput::m_aKeyStateTrigger[NUM_KEY_MAX];
BYTE				 CInput::m_aKeyStateRelease[NUM_KEY_MAX];
BYTE				 CInput::m_aKeyStateRepeat[NUM_KEY_MAX];
int					 CInput::m_aKeyStateRepeatCnt[NUM_KEY_MAX];

//=====================================================================================================
//
//
//
//=====================================================================================================
CInput::CInput()
{

}

//=====================================================================================================
//
//
//
//=====================================================================================================
CInput::~CInput()
{

}

//=====================================================================================================
//
// 入力処理の初期化
//
//=====================================================================================================
HRESULT CInput::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	UNREFERENCED_PARAMETER(hWnd);				// 参照してないよっていうマクロ	windows特有
												//hWnd = hWnd;	// ワーニングを消す方法

	if (m_pInput == NULL)
	{
		// DirectInputオブジェクトの作成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//====================================================================================================
//
// 入力処理の終了処理
//
//====================================================================================================
void CInput::UninitInput(void)
{
	if (m_pInput != NULL)
	{
		// DirectInputオブジェクトの開放
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//====================================================================================================
//
// 入力処理の更新処理
//
//====================================================================================================
void CInput::UpdateInput(void)
{

}

//====================================================================================================
//
// キーボードの初期化
//
//====================================================================================================
HRESULT CInput::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// 入力処理の初期化
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL))) // 第一引数にマウス、パッド用にできる
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）	ここ大事！！！！！	第一引数はBACKかFOREか	
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)		acquire(得る)
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//=====================================================================================================
//
// キーボードの終了処理
//
//=====================================================================================================
void CInput::UninitKeyboard(void)
{
	if (m_pDevKeyboard != NULL)
	{
		// 入力デバイス(キーボード)の開放
		// キーボードへのアクセス権を開放(入力制御終了)		アクセス権を放棄してからリリース
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// 入力処理の終了処理
	UninitInput();
}

//=====================================================================================================
//
// キーボードの更新処理
//
//=====================================================================================================
void CInput::UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// akeyState[] = 

		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];	// キーが押されたばっかかどうか調べる
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];// 

																										 // キーリピート情報を生成
			if (aKeyState[nCnKey])
			{
				if (m_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					m_aKeyStateRepeatCnt[nCnKey]++;
					if (m_aKeyStateRepeatCnt[nCnKey] == 1 || m_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{
						// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						m_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						m_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCnKey] = 0;
				m_aKeyStateRepeat[nCnKey] = 0;
			}

			// キープレス情報を保存		これが基本	過去を作る
			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		m_pDevKeyboard->Acquire();
	}
}

//============================================================================================================
//
// キーボードのプレス状態を取得
//
//====================================================================================================
bool CInput::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;	// ワーニングをとるため
}


//====================================================================================================
//
// キーボードのトリガー状態を取得
//
//====================================================================================================
bool CInput::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//====================================================================================================
//
// キーボードのリピート状態を取得
//
//====================================================================================================
bool CInput::GetKeyboardRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//====================================================================================================
//
// キーボードのリリ－ス状態を取得
//
//====================================================================================================
bool CInput::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
