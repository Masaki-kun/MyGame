//=====================================================================================================================
//
//  [Renderer.cpp] Author : Masaki Kuboki
//
//=====================================================================================================================
#include "main.h"
#include "RendererDX.h"

//=====================================================================================================================
//
// static�����o�ϐ�
//
//=====================================================================================================================
LPDIRECT3D9 CRendererDX::m_pD3D;
LPDIRECT3DDEVICE9 CRendererDX::m_pD3DDevice;

//=====================================================================================================================
//
//
//
//=====================================================================================================================
CRendererDX::CRendererDX()
{

}

//=====================================================================================================================
// 
//
//
//=====================================================================================================================
CRendererDX::~CRendererDX()
{

}

//=====================================================================================================================
//
//
//
//=====================================================================================================================
bool CRendererDX::Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	srand((unsigned)time(NULL));

	// Direct3D�C���^�[�t�F�[�X�̎擾
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);		// �G���h���[�U�[�����^�C��
	if (m_pD3D == NULL)
	{
		return false;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) { return false/*E_FAIL*/; }

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		// d3dpp���O�Ŗ��߂Ă�������

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[RGBA32bit
	d3dpp.BackBufferCount = 1;										// ����ʉ�������H
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//
	d3dpp.EnableAutoDepthStencil = TRUE;							// ��{�I��true�ɂ���@�f���M���ɓ������ăt���b�v
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//
	d3dpp.Windowed = !bWindow;										// window�ɂ���̂��t���X�N���[����	!bWindow�Ńt���X�N���[��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// �b�� ONE���ƈ��I������Ƃ������b�Z�[�W��������ĕ`�� ���ǂꂭ�炢�ŕ`��ł���̂����������Ƃ���IMMEDIATE
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		MessageBox(hWnd, "�f�o�C�X���쐬�ł��܂���ł���", "check", MB_OK);
		return false/*E_FAIL*/;
	}




	// �����_�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// ��1�����A���t�@�̃^�C�v    ��2���� �g�����ǂ����̔��f
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ��

																			// ���l�̏�Z���ł���悤��
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // ��2����   �|���S���ƃe�N�X�`�����ǂ��u�����h�����邩
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // ��2����   �|���S���ƃe�N�X�`�����ǂ��u�����h�����邩
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // ��2����   �|���S���ƃe�N�X�`�����ǂ��u�����h�����邩

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//=====================================================================================================================
	// �t�B���^�[
	//=====================================================================================================================
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);	
}

//=====================================================================================================================
//
//
//
//=====================================================================================================================
void CRendererDX::Uninit(void)
{
	if (m_pD3DDevice != NULL)					// ��������Ȃ��Ƒ��̐l�Ɉ��e���@�}�i�[�@�������͕K���Ԃ�
	{
		// �f�o�C�X�̊J��
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	if (m_pD3D != NULL)							// ��������Ȃ��Ƒ��̐l�Ɉ��e��
	{
		// Direct3D�I�u�W�F�N�g�̊J��
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=====================================================================================================================
//
// DrawBegin
//
//=====================================================================================================================
void CRendererDX::DrawBegin(void)
{
	//clear, Begin�V�[��,End�V�[��,present�͂P�t���[���Ɉ��
	// �J�E���g�A�͈̓N���A�i����͑S��ʁj�A�F�̂��ƁA���F�ŃN���A�AZBUFFER�̃N���A�l�A�X�e���V���o�b�t�@�[�̃N���A�[
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	m_pD3DDevice->BeginScene();
	//bDraw = true;
}

//=====================================================================================================================
//
// DrawEnd
//
//=====================================================================================================================
void CRendererDX::DrawEnd(void)
{
	m_pD3DDevice->EndScene();	// Direct3D�ɂ��`��̏I��
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);	// present �͑���@Draw�̍Ō�ɌĂ�
}

LPDIRECT3DDEVICE9 CRendererDX::GetD3DDevice(void)
{
	return m_pD3DDevice;
}

void CRendererDX::Drawing(void)
{

}