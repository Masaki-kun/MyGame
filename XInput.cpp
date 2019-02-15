//=================================================================================================
// 
// XInput(�R���g���[���[)    Author:	Masaki Kuboki
// 
//=================================================================================================
#pragma comment (lib, "xinput.lib")				// ���C�u�����̃C���|�[�g
#include "main.h"
#include "XInput.h"

//=====================================================================================================
//
// static�����o�ϐ�
//
//=====================================================================================================
XINPUT_STATE CXinput::m_State[PLAYER_MAX];		// �C���X�^���X�쐬
XINPUT_STATE CXinput::m_Oldstate[PLAYER_MAX];	// �ߋ��̏�Ԃ��擾
int			 CXinput::m_nRegisterNum;			// �v���C���[�̓o�^��
DWORD		 CXinput::m_dwResult;				// �擾�̌���

//=================================================================================================
//
// �\����
//
//=================================================================================================
//XINPUT_STATE g_State[PLAYER_MAX];				// �C���X�^���X�쐬
//XINPUT_STATE g_Oldstate[PLAYER_MAX];				// �ߋ��̏�Ԃ��擾
//
//static int g_nRegisterNum = 0;					// �v���C���[�̓o�^��
//
//DWORD dwResult;				// �擾�̌���

//=================================================================================================
//	
// Init
//
//=================================================================================================
void CXinput::Init(PLAYER_NUM playerNum, HWND hWnd)
{
	// �o�^���̑��
	m_nRegisterNum = playerNum + 1;

	for(WORD i = 0; i < m_nRegisterNum; i++)
	{
		// ���g�����ꂢ�ɂ���
		ZeroMemory(&m_State[i], sizeof(XINPUT_STATE));

		// �R���g���[���[�̏��̎擾(dwResult�Ɍ���)
		m_dwResult = XInputGetState(i,					// �R���g���[���[�̔ԍ�
									&m_State[i]);		// ��Ԋi�[����Ă����̐擪�A�h���X

		//�擾���s���̃��b�Z�[�W
		if(m_dwResult != ERROR_SUCCESS)
		{
			MessageBox(hWnd, "�R���g���[���[���ڑ�����Ă��܂���", "���s", MB_OK | MB_ICONEXCLAMATION);
		}
	}
}

//=================================================================================================
//	XInput�I��
//
//
//=================================================================================================
void CXinput::Uninit(void)
{

}

//=================================================================================================
//	XInput�X�V
//
//
//=================================================================================================
void CXinput::Update(void)
{
	for(WORD i = 0 ; i < m_nRegisterNum; i++)
	{
		// �ߋ��̃R���g���[�����̎擾
		m_Oldstate[i] = m_State[i];

		// �R���g���[���[�̏��̎擾
		XInputGetState(i, &m_State[i]);

		// ���X�e�B�b�N�̃f�b�h�]�[��
		if( (m_State[i].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) && 
			(m_State[i].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)    )
		{
			m_State[i].Gamepad.sThumbLX = 0;
			m_State[i].Gamepad.sThumbLY = 0;
		}

		// �E�X�e�B�b�N�̃f�b�h�]�[��
		if( (m_State[i].Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) && 
			(m_State[i].Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_State[i].Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)    )
		{
			m_State[i].Gamepad.sThumbRX = 0;
			m_State[i].Gamepad.sThumbRY = 0;
		}
		
	}

}

//=================================================================================================
//
// PRESS�ŃL�[�̎擾
//
//=================================================================================================
bool CXinput::GetPress(int button,int playerNum)
{
	// �v���X
	return m_State[playerNum].Gamepad.wButtons & button;
}

//=================================================================================================
//
// TRIGGER�ŃL�[�̎擾
//
//=================================================================================================
bool CXinput::GetTrigger(int button,int playerNum)
{
	// �g���K�[�֐����Ă�
	return KeyTrigger( m_State[playerNum].Gamepad.wButtons & button, m_Oldstate[playerNum].Gamepad.wButtons & button);
}

//=================================================================================================
//
// RELEASE�ŃL�[�̎擾
//
//=================================================================================================
bool CXinput::GetRelease(int button,int playerNum)
{
	// �����[�X�֐����Ă�
	return KeyRelease( m_State[playerNum].Gamepad.wButtons & button, m_Oldstate[playerNum].Gamepad.wButtons & button);
}

//=================================================================================================
//
// �A�i���O�X�e�B�b�N���̎擾
//
//=================================================================================================
bool CXinput::GetAnalogL(int playerNum)
{
		// ���X�e�B�b�N��
	if( m_State[playerNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ){ return true;}
	else{ return false; }
}

//=================================================================================================
//
// �A�i���O�X�e�B�b�N�E�̎擾
//
//=================================================================================================
bool CXinput::GetAnalogR(int playerNum)
{
	// �E�X�e�B�b�N
	if( m_State[playerNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_State[playerNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ){ return true;}
	else{ return false; }
}

//=================================================================================================
//
// �A�i���O�X�e�B�b�N���̐��K�����ꂽ�x�N�g�����擾
//
//=================================================================================================
D3DXVECTOR3 CXinput::GetAnalogLDir(int playerNum)
{
	D3DXVECTOR3 dir;
	dir = D3DXVECTOR3(CXinput::GetState(playerNum)->Gamepad.sThumbLX, 0.0f, CXinput::GetState(playerNum)->Gamepad.sThumbLY);
	D3DXVec3Normalize(&dir,&dir);
	return dir;
}

//=================================================================================================
//
// �A�i���O�X�e�B�b�N�E�̐��K�����ꂽ�x�N�g�����擾
//
//=================================================================================================
D3DXVECTOR3 CXinput::GetAnalogRDir(int playerNum)
{
	D3DXVECTOR3 dir;
	dir = D3DXVECTOR3(CXinput::GetState(playerNum)->Gamepad.sThumbRX, 0.0f, CXinput::GetState(playerNum)->Gamepad.sThumbRY);
	D3DXVec3Normalize(&dir,&dir);
	return dir;
}

//=================================================================================================
//
// �A�i���O�X�e�B�b�N�E�̐��K�����ꂽ�x�N�g�����擾
//
//=================================================================================================
bool CXinput::GetLT(int playerNum)
{
	if(m_State[playerNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return true ;}
	else{ return false; }
}

//=================================================================================================
//
// �A�i���O�X�e�B�b�N�E�̐��K�����ꂽ�x�N�g�����擾
//
//=================================================================================================
bool CXinput::GetRT(int playerNum)
{
	if(m_State[playerNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD){ return true; }
	else{ return false; }
}

//=================================================================================================
//
// �g���K�[����i�g���K�[�j
//
//=================================================================================================
bool CXinput::KeyTrigger ( bool bComand, bool bOldComand )			// �R���g���[���̃L�[�g���K�[
{
	bool trigger = false;
	trigger = (bOldComand ^ bComand) & bComand ;			// &���D�悳��Čv�Z�����
	return trigger;
}

//=================================================================================================
//
// �����[�X����i�����[�X�j
//
//=================================================================================================
bool CXinput::KeyRelease ( bool bComand, bool bOldComand )	// �R���g���[���̃L�[�����[�X
{
	bool release = false;
	release = bOldComand ^ bComand & bOldComand;
	return release;
}

//=================================================================================================
//
// �R���g���[���̏��n��
//
//=================================================================================================
XINPUT_STATE* CXinput::GetState(int playerNum)
{
	return &m_State[playerNum];
}