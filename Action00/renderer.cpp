//===========================================================================================
//
// [renderer.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "object2D.h"
#include "debugproc.h"
#include "sound.h"
#include "input.h"

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;				//Directx3D�I�u�W�F�N�g�ւ̃|�C���^
	m_pD3DDevice = NULL;		//Directx3D�ւ̃f�o�C�X�ւ̃|�C���^
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CRenderer::~CRenderer()
{

}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;		//�v���[���e�[�V�����p�����[�^

	//DIrect3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�o�C�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));				//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//�Q�[���̉�ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;			//�o�b�N�o�b�t�@�`��
	d3dpp.BackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;			//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//�f�v�X�o�b�t�@�Ƃ���16bit����
	d3dpp.Windowed = bWindow;						//�E�C���h���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//�w�i
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�����̎���w��(rand�g�p���A���񐔒l��ς���)
	srand((unsigned int)time(0));

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CRenderer::Uninit(void)
{
	//Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CRenderer::Update(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();

#if DEBUG
	if (pInputKey->GetTrigger(DIK_F2) == true)
	{//���C���[�t���[���\������
		if (m_bWireframe == true)
		{
			m_bWireframe = false;
		}
		else
		{
			m_bWireframe = true;
		}
	}
#endif

	if (m_bWireframe == true)
	{//���C���[�t���[����\������
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else if (m_bWireframe == false)
	{//���C���[�t���[���̕\����߂�
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DRS_ZENABLE);
	}

	//�S�X�V����
	CObject::UpdateAll();
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CRenderer::Draw(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();

	//��ʂ��N���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�S�X�V����
		CObject::DrawAll();

		// �f�o�b�O�\��
		if (pDebugProc != NULL)
		{
			//�f�o�b�O�v���b�N�̕`�揈��
			pDebugProc->Draw();
		}

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================================================
// �f�o�C�X�̎擾
//===================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}