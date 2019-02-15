//============================================================================================================
//
// ���͏��� [input.h] Author : Masaki Kuboki
//
//============================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>
#include <dinput.h>

//============================================================================================================
//
// �}�N����`
//
//============================================================================================================
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	LIMIT_COUNT_REPEAT	(20)	// ���s�[�g�J�E���g���~�b�^�[

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

	static LPDIRECTINPUT8		m_pInput;							// DirectInput�I�u�W�F�N�g�ւ̃|�C���^		<dinput.h>
	static LPDIRECTINPUTDEVICE8	m_pDevKeyboard;						// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^		<dinput.h>
	static BYTE					m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	static BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
	static BYTE					m_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
	static BYTE					m_aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	static int					m_aKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

};

#endif