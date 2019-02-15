//=====================================================================================================
// 
// XInput(�R���g���[���[)
//	Author:	Masaki Kuboki
//
//=====================================================================================================
#ifndef _MYXINPUT_H_
#define _MYXINPUT_H_
#pragma comment (lib, "xinput.lib")				// ���C�u�����̃C���|�[�g

#include <Windows.h>
#include <XInput.h>

// �v���C���[�l��(Init�����ł̎g�p)
typedef enum 
{
	PLAYER_ONE,		// �P�l �l�͂O
	PLAYER_TWO,		// �Q�l �l�͂P
	PLAYER_TREE,	// �R�l �l�͂Q
	PLAYER_MAX		// �S�l �l�͂R
}PLAYER_NUM;

//=====================================================================================================
//
// class
//
//=====================================================================================================
class CXinput
{
public:
	CXinput() { m_nRegisterNum = 0; };
	~CXinput() {};

	// ��{�֐�(�K�������)
	static void Init(PLAYER_NUM playerNum, HWND hWnd);	
	static void Uninit(void);			
	static void Update(void);	

	// �{�^������̎��
	static bool GetPress(int button, int playerNum);		// �v���X
	static bool GetTrigger(int button, int playerNum);		// �g���K�[
	static bool GetRelease(int button, int playerNum);		// �����[�X
	
	// �A�i���O�X�e�B�b�N�̏��擾
	// �����F�R���g���[���i���o�[�@�߂�l�Fbool�^��	������Ă�����true�A������Ă��Ȃ�������false ��Ԃ�
	static bool GetAnalogL(int playerNum);				// �A�i���O�X�e�B�b�N���̓��̗͂L��
	static bool GetAnalogR(int playerNum);				// �A�i���O�X�e�B�b�N�E�̓��̗͂L��

	static D3DXVECTOR3 GetAnalogLDir(int playerNum);			// �A�i���O�X�e�B�b�N���̐��K�����ꂽ�x�N�g�����擾
	static D3DXVECTOR3 GetAnalogRDir(int playerNum);			// �A�i���O�X�e�B�b�N�E�̐��K�����ꂽ�x�N�g�����擾

	// �g���K�[�{�^��(LT�ART�ALB�ARB)���̎擾
	// �����F�R���g���[���i���o�[�@�߂�l�Fbool�^��	������Ă�����true�A������Ă��Ȃ�������false ��Ԃ�
	static bool GetLT(int playerNum);				// �g���K�[�{�^����
	static bool GetRT(int playerNum);				// �g���K�[�{�^���E

	// �R���g���[���̏��̎擾
	// �����F�R���g���[���i���o�[�@ �߂�l�FXINPUT_STATE�^�̃A�h���X���Ԃ��Ă���
	static XINPUT_STATE* GetState(int playerNum);

	// �ȉ��͎g��Ȃ�
	static bool KeyTrigger(bool bComand, bool bOldComand);	// �R���g���[���̃L�[�g���K�[
	static bool KeyRelease(bool bComand, bool bOldComand);	// �R���g���[���̃L�[�����[�X

private:
	static XINPUT_STATE m_State[PLAYER_MAX];				// �C���X�^���X�쐬
	static XINPUT_STATE m_Oldstate[PLAYER_MAX];				// �ߋ��̏�Ԃ��擾

	static int m_nRegisterNum;					// �v���C���[�̓o�^��

	static DWORD m_dwResult;				// �擾�̌���

};

//=====================================================================================================
//
// ��{�֐��i�K�������j
//
//=====================================================================================================
//void InitXInput(PLAYER_NUM playerNum, HWND hWnd);	// �R���g���[���ڑ����̏�����
//void UninitXInput(void);				// 
//void UpdateXInput(void);				// �A�i���O�X�e�B�b�N�̃f�b�h�]�[������

//=====================================================================================================
// �{�^���g�p�̗L���̊m�F�֐�
//=====================================================================================================
//
// �����F�i���j�m�F����{�^���A�i���j�R���g���[���i���o�[
//		 <xinput.h>���̂���		int�^�łO����R�͈̔͂ŃZ�b�g
//
// �߂�l�Fbool�^��	������Ă�����true		������Ă��Ȃ�������false ��Ԃ�
//
// �g�p��FGetXInputTrigger(XINPUT_GAMEPAD_DPAD_UP,0);
// XINPUT_GAMEPAD_DPAD_UP			��
// XINPUT_GAMEPAD_DPAD_DOWN			��
// XINPUT_GAMEPAD_DPAD_LEFT			��
// XINPUT_GAMEPAD_DPAD_RIGHT		��
// XINPUT_GAMEPAD_START				START�{�^��
// XINPUT_GAMEPAD_BACK				BACK�{�^��
// XINPUT_GAMEPAD_LEFT_THUMB		���X�e�B�b�N��������
// XINPUT_GAMEPAD_RIGHT_THUMB		�E�X�e�B�b�N��������
// XINPUT_GAMEPAD_LEFT_SHOULDER		���g���K�[
// XINPUT_GAMEPAD_RIGHT_SHOULDER	�E�g���K�[
// XINPUT_GAMEPAD_A					A�{�^��
// XINPUT_GAMEPAD_B					B�{�^��
// XINPUT_GAMEPAD_X					X�{�^��
// XINPUT_GAMEPAD_Y					Y�{�^��
//=====================================================================================================
//bool GetXInputPress(int button,int playerNum);			// �v���X
//bool GetXInputTrigger(int button,int playerNum);		// �g���K�[
//bool GetXInputRelease(int button,int playerNum);		// �����[�X

//=====================================================================================================
// �A�i���O�X�e�B�b�N���̎擾
//=====================================================================================================
//
// �����F�R���g���[���i���o�[
//
// �߂�l�Fbool�^��	������Ă�����true		������Ă��Ȃ�������false ��Ԃ�
//=====================================================================================================
//bool GetXInputAnalogL(int playerNum);				// �A�i���O�X�e�B�b�N���̓��̗͂L��
//bool GetXInputAnalogR(int playerNum);				// �A�i���O�X�e�B�b�N�E�̓��̗͂L��
//
//D3DXVECTOR3 GetAnalogLDir(int playerNum);			// �A�i���O�X�e�B�b�N���̐��K�����ꂽ�x�N�g�����擾
//D3DXVECTOR3 GetAnalogRDir(int playerNum);			// �A�i���O�X�e�B�b�N�E�̐��K�����ꂽ�x�N�g�����擾

//=====================================================================================================
// �g���K�[�{�^���iLT�ART�{�^���j���̎擾
//=====================================================================================================
//
// �����F�R���g���[���i���o�[
//
// �߂�l�Fbool�^��	������Ă�����true		������Ă��Ȃ�������false ��Ԃ�
//=====================================================================================================
//bool GetXInputLT(int playerNum);				// �g���K�[�{�^����
//bool GetXInputRT(int playerNum);				// �g���K�[�{�^���E

//=====================================================================================================
// �R���g���[���̏��̎擾
//=====================================================================================================
//
// �����F�R���g���[���i���o�[
//
// �߂�l�FXINPUT_STATE�^�̃A�h���X���Ԃ��Ă���
//=====================================================================================================
//XINPUT_STATE* GetXInputState(int playerNum);

//=====================================================================================================
// �����͎g��Ȃ�
//=====================================================================================================
//bool KeyTrigger ( bool bComand, bool bOldComand );	// �R���g���[���̃L�[�g���K�[
//bool KeyRelease ( bool bComand, bool bOldComand );	// �R���g���[���̃L�[�����[�X

#endif