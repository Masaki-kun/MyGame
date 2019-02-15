//=====================================================================================================
//
// [input.cpp]  Author : Masaki Kuboki
//	����o����c:\program files (x86)\microsoft directx sdk (june 2010)\include\dinput.h: DIRECTINPUT_VERSION undefined. Defaulting to version 0x0800
//=====================================================================================================
#include <windows.h>
#define DIRECTINPUT_VERSION	(0x0800)
#include <dinput.h>
#include "Input.h"

//=====================================================================================================
//
// static�����o�ϐ�
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
// ���͏����̏�����
//
//=====================================================================================================
HRESULT CInput::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	UNREFERENCED_PARAMETER(hWnd);				// �Q�Ƃ��ĂȂ�����Ă����}�N��	windows���L
												//hWnd = hWnd;	// ���[�j���O���������@

	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//====================================================================================================
//
// ���͏����̏I������
//
//====================================================================================================
void CInput::UninitInput(void)
{
	if (m_pInput != NULL)
	{
		// DirectInput�I�u�W�F�N�g�̊J��
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//====================================================================================================
//
// ���͏����̍X�V����
//
//====================================================================================================
void CInput::UpdateInput(void)
{

}

//====================================================================================================
//
// �L�[�{�[�h�̏�����
//
//====================================================================================================
HRESULT CInput::InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL))) // �������Ƀ}�E�X�A�p�b�h�p�ɂł���
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j	�����厖�I�I�I�I�I	��������BACK��FORE��	
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)		acquire(����)
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//=====================================================================================================
//
// �L�[�{�[�h�̏I������
//
//=====================================================================================================
void CInput::UninitKeyboard(void)
{
	if (m_pDevKeyboard != NULL)
	{
		// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)		�A�N�Z�X����������Ă��烊���[�X
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// ���͏����̏I������
	UninitInput();
}

//=====================================================================================================
//
// �L�[�{�[�h�̍X�V����
//
//=====================================================================================================
void CInput::UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// akeyState[] = 

		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			m_aKeyStateTrigger[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];	// �L�[�������ꂽ�΂������ǂ������ׂ�
			m_aKeyStateRelease[nCnKey] = (m_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & m_aKeyState[nCnKey];// 

																										 // �L�[���s�[�g���𐶐�
			if (aKeyState[nCnKey])
			{
				if (m_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					m_aKeyStateRepeatCnt[nCnKey]++;
					if (m_aKeyStateRepeatCnt[nCnKey] == 1 || m_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{
						// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
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

			// �L�[�v���X����ۑ�		���ꂪ��{	�ߋ������
			m_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevKeyboard->Acquire();
	}
}

//============================================================================================================
//
// �L�[�{�[�h�̃v���X��Ԃ��擾
//
//====================================================================================================
bool CInput::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;	// ���[�j���O���Ƃ邽��
}


//====================================================================================================
//
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//
//====================================================================================================
bool CInput::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//====================================================================================================
//
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//
//====================================================================================================
bool CInput::GetKeyboardRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//====================================================================================================
//
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//
//====================================================================================================
bool CInput::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
