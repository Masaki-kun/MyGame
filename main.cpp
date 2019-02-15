//=====================================================================================================================
//	
//  [main.cpp]  Author : Masaki Kuboki
//
//=====================================================================================================================
#include "main.h"
#include "Manager.h"

//=====================================================================================================================
//
// �v���g�^�C�v�錾
//
//=====================================================================================================================
//�߂�l window���L���� �N���X�ō쐬�������O( , �ǂ�ȃ��b�Z�[�W��, ����msg�̕t���̏��)
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//=====================================================================================================================
//
// �O���[�o���ϐ�
//
//=====================================================================================================================
HWND hWnd;

//====================================================================================================
//
// Winproc�֐�
//
//======================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLime, int nShowCmd)
{
	int w_width, w_height = 0;							// �N���C�A���g�̈�ł̎g�p
	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };		// �N���C�A���g�̈�ł̎g�p
	RECT dr;											// �N���C�A���g�̈�ł̎g�p
	DWORD bStyle = (WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME;// �N���C�A���g�̈�ł̎g�p

	DWORD dwExecLastTime = 0;				// �Q�[���������I���������
	DWORD dwCurrentTime = 0;				// ���݂̎���


											//�\���̂��̇@ �\���̕ϐ��̏������œ���� *����* �ł����݂̗ʂ����Ȃ�
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// �\���̂̃T�C�Y,�\���̂̃T�C�Y�ɑ��N���X�������Ă��邱�Ƃ�����
		CS_VREDRAW | CS_HREDRAW,		// CS_VREDRAW == �����ACS_REDRAW == �����Bwindow�̃T�C�Y�ω��ɑΉ����čĕ`�������
		WndProc,						// window�v���V�[�W�� �֐��̃|�C���^�^�B�֐������ꂾ�����A�h���X�ɂȂ�B�E�B���h�E��ł̔��������C�x���g�̏���
		0,								// �g��Ȃ� �N���X�\���̂̒ǉ��̈� �o�C�g�P�ʂŗ\��
		0,								// �g��Ȃ� �E�B���h�E�\���̂̒ǉ��̈� �o�C�g�P�ʂŗ\��
		hInstance,						// �d�v�I�I WinMain���� �������̂悤�Ȃ��� �C���X�^���X�̃n���h��
		NULL,							// �A�v���P�[�V�����̃A�C�R�� 
		LoadCursor(NULL, IDC_ARROW),	// �J�[�\���̕ύX
		(HBRUSH)(COLOR_WINDOW + 1),	    // �N���C�A���g�̈�̃f�t�H���g�̔w�i�F�̐ݒ�
		NULL,							// �N���X���j���[�n���h��
		CLASS_NAME,						// �p�[�c�� �N���X�� ���͂Ȃ�ł��悢
		NULL							// �~�j�A�C�R���̐ݒ�	
	};

	RegisterClassEx(&wcex);			// window�N���X�̓o�^

	//----------------------------------------------------------------
	// �N���C�A���g�̈�̃T�C�Y�ݒ�
	//----------------------------------------------------------------

	AdjustWindowRect(&wr, bStyle, false);	// �N���C�A���g�T�C�Y�����߂�֐�
	w_width = (wr.right - wr.left);		// �N���C�A���g�T�C�Y�̕�
	w_height = (wr.bottom - wr.top);		// �N���C�A���g�T�C�Y�̍���
	GetWindowRect(GetDesktopWindow(), &dr);
	HWND hWnd = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, /*WS_POPUP*/bStyle, CW_USEDEFAULT, CW_USEDEFAULT, w_width, w_height, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nShowCmd);		// �\��
	UpdateWindow(hWnd);				// �X�V

	MSG msg;

	//=====================================================================================================================
	//
	// �Q�[�����[�v�̍쐬
	//
	//=====================================================================================================================
	CManager::Init(hInstance, hWnd, true);	// ������ ShouWindow�̑O�ɒu����...
	if (!CManager::Init)
	{
		MessageBox(hWnd, "�������Ɏ��s���܂���", "���s", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	//	����\��ݒ�
	timeBeginPeriod(1);

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else { // �Q�[������
			dwCurrentTime = timeGetTime();
			CManager::Update();	// �X�V����
			CManager::Draw();		// �`�揈��
		}
	} while (msg.message != WM_QUIT);

	CManager::Uninit();	// �I������

				// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;

}

//======================================================================================================
//
// WndProc�֐�
//
//======================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);		//WM_QUIT���b�Z�[�W�̑��M
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:			//�G�X�P�[�v�{�^��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
				break;
			}
			break;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //�d�v�I�I ��{�͂������������Ă���� ���ʂȓ�����case��return���g��������ʂ��Ȃ��悤�ɂ���

}

//======================================================================================================
//
// hWnd
//
//======================================================================================================
HWND GethWnd()
{
	return hWnd;
}