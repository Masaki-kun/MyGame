//============================================================================================================
//
// 入力処理 [input.h] Author : Masaki Kuboki
//
//============================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>
#include <dinput.h>

//============================================================================================================
//
// マクロ定義
//
//============================================================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター

//============================================================================================================
//
// class
//
//============================================================================================================
class CInput
{
public:
	CInput();
	~CInput();

	static HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
	static void UninitKeyboard(void);
	static void UpdateKeyboard(void);
	
	static bool GetKeyboardPress(int nKey);
	static bool GetKeyboardTrigger(int nKey);
	static bool GetKeyboardRepeat(int nKey);
	
	static bool GetKeyboardRelease(int nKey);


private:
	static HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	static void UninitInput(void);
	static void UpdateInput(void);

	static LPDIRECTINPUT8		m_pInput;							// DirectInputオブジェクトへのポインタ		<dinput.h>
	static LPDIRECTINPUTDEVICE8	m_pDevKeyboard;						// 入力デバイス(キーボード)へのポインタ		<dinput.h>
	static BYTE					m_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
	static BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
	static BYTE					m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
	static BYTE					m_aKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
	static int					m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

};

#endif