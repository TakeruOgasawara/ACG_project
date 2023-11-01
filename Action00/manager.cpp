//===========================================================================================
//
// [manager.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include"renderer.h"
#include "object.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "xfile.h"
#include "slow.h"

#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"

#include "object3D.h"

//�ÓI�����o�ϐ��錾
CManager* CManager::m_pManager = nullptr;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CManager::CManager()
{
	m_pRenderer = nullptr;
	m_pInputKeyboard = nullptr;
	m_pInputMouse = nullptr;
	m_pInputJoyPad = nullptr;
	m_pDebugProc = nullptr;
	m_pSound = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pTexture = nullptr;
	m_pScene = nullptr;
	m_pTitle = nullptr;
	m_pGame = nullptr;
	m_pResult = nullptr;
	m_pFade = nullptr;
	m_pXfile = nullptr;
	m_pSlow = nullptr;

	m_bUse = false;
	m_nCurrentMinute = 0;
	m_nCurrentSecond = 0;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CManager::~CManager()
{

}

//===========================================================================================
// �V���O���g��
//===========================================================================================
CManager *CManager::GetInstance(void)
{
	if (m_pManager == nullptr)
	{//null�������ꍇ

		return m_pManager = new CManager;
	}
	else
	{
		return m_pManager;
	}
}

//===========================================================================================
// �j��
//===========================================================================================
void CManager::Release(void)
{
	if (m_pManager == nullptr)
	{//null�������ꍇ

		return;
	}
	else
	{
		m_pManager->Uninit();

		delete m_pManager;
		m_pManager = nullptr;
	}
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//---------------------------
	// �C���X�^���X����
	//---------------------------
	//�����_���[
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;

		if (m_pRenderer != nullptr)
		{
			//�����_���[�̏���������
			if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
			{
				return E_FAIL;
			}
		}
	}
	//�L�[�{�[�h
	if (m_pInputKeyboard == nullptr)
	{
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != nullptr)
		{
			//�L�[�{�[�h�̏���������
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{
				return E_FAIL;
			}
		}
	}
	//�}�E�X
	if (m_pInputMouse == nullptr)
	{
		m_pInputMouse = new CInputMouse;

		if (m_pInputMouse != nullptr)
		{
			//�}�E�X�̏���������
			if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
			{
				return E_FAIL;
			}
		}
	}
	//�W���C�p�b�h
	if (m_pInputJoyPad == nullptr)
	{
		m_pInputJoyPad = new CInputJoyPad;

		if (m_pInputJoyPad != nullptr)
		{
			//�}�E�X�̏���������
			if (FAILED(m_pInputJoyPad->Init()))
			{
				return E_FAIL;
			}
		}
	}
	//�T�E���h
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound;

		if (m_pSound != nullptr)
		{
			//�}�E�X�̏���������
			m_pSound->Init(hWnd);
		}
	}
	// �f�o�b�O�\���̐���
	if (m_pDebugProc == nullptr)
	{
		m_pDebugProc = new CDebugProc;

		//����������
		if (m_pDebugProc != nullptr)
		{
			m_pDebugProc->Init();
		}
	}
	//�J�����̐���
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;

		//����������
		if (m_pCamera != nullptr)
		{
			m_pCamera->Init();
		}
	}
	//���C�g�̐���
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight;

		//����������
		if (m_pLight != nullptr)
		{
			m_pLight->Init();
		}
	}
	//�e�N�X�`���̐���
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;

		//����������
		if (m_pTexture != nullptr)
		{
			m_pTexture->Load();
		}
	}
	//x�t�@�C���̐���
	//if (m_pXfile == nullptr)
	//{
	//	m_pXfile = new CXfile;

	//	//����������
	//	if (m_pXfile != nullptr)
	//	{
	//		m_pXfile->Load();
	//	}
	//}

	// �X���[���̐���
	if (m_pSlow == nullptr)
	{
		m_pSlow = new CSlow;

		//����������
		if (m_pXfile != nullptr)
		{
			m_pSlow->Init();
		}
	}

	//���[�h�ݒ�
	SetMode(CScene::MODE_TITLE);
	
	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CManager::Uninit(void)
{
	//�S�I�u�W�F�N�g�̔j��(+�I������)
	CObject::ReleaseAll();

	//�L�[�{�[�h�̏I�������A�j��
	if (m_pInputKeyboard != nullptr)
	{
		//�L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();

		//�������̊J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	//�}�E�X�̏I�������A�j��
	if (m_pInputMouse != nullptr)
	{
		//�L�[�{�[�h�̏I������
		m_pInputMouse->Uninit();

		//�������̊J��
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}
	//�}�E�X�̏I�������A�j��
	if (m_pInputJoyPad != nullptr)
	{
		//�L�[�{�[�h�̏I������
		m_pInputJoyPad->Uninit();

		//�������̊J��
		delete m_pInputJoyPad;
		m_pInputJoyPad = nullptr;
	}
	//�f�o�b�O�v���b�N�̏I���A�j��
	if (m_pDebugProc != nullptr)
	{
		//�f�o�b�O�v���b�N�̏I������
		m_pDebugProc->Uninit();

		//�������̊J��
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
	//�����_���[�̏I�������A�j��
	if (m_pRenderer != nullptr)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();

		//�������̊J��
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//�T�E���h�̏I���A�j��
	if (m_pSound != nullptr)
	{
		//�T�E���h�̏I������
		m_pSound->Stop();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}
	//�J�����̏I���A�j��
	if (m_pCamera != nullptr)
	{
		//�J�����̏I������
		m_pCamera->Uninit();
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//���C�g�̏I���A�j��
	if (m_pLight != nullptr)
	{
		//���C�g�̏I������
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = nullptr;
	}
	//�e�N�X�`���̏I���A�j��
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̏I������
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = nullptr;
	}
	//�V�[���̏I���A�j��
	if (m_pScene != nullptr)
	{
		//�V�[���̏I������
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//X�t�@�C���̏I���A�j��
	if (m_pXfile != nullptr)
	{
		//�V�[���̏I������
		m_pXfile->Unload();
		delete m_pXfile;
		m_pXfile = nullptr;
	}

	//�X���[�̏I���A�j��
	if (m_pSlow != nullptr)
	{
		//�V�[���̏I������
		m_pSlow->Uninit();
		delete m_pSlow;
		m_pSlow = nullptr;
	}
	
	if (m_pFade != nullptr)
	{
		m_pFade = nullptr;
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CManager::Update(void)
{
	CManager::GetDebugProc()->Print("FPS[%d]\n", GetFps());
	CManager::GetDebugProc()->Print("�I�u�W�F�N�g����[%d]\n\n", CObject::GetNumAll());

	m_pDebugProc->Print("�y ������@ �z\n");
	m_pDebugProc->Print("F1 : �f�o�b�O�\��[ON/OFF]\nF2 : �@���\��[ON/OFF]\n");

	//�f�o�b�O�v���b�N�̍X�V����
	if (CManager::GetDebugProc() != nullptr)
	{
		CManager::GetDebugProc()->Update();
	}

	//�L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//�}�E�X�̍X�V����
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Update();
	}

	//�W���C�p�b�h�̍X�V����
	if (m_pInputJoyPad != nullptr)
	{
		m_pInputJoyPad->Update();
	}

	// �X���[�̍X�V����
	if (m_pSlow != NULL)
	{
		m_pSlow->Update();
	}

	//�V�[���̍X�V
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	} 
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
}

void CManager::SetCurrentTime(int nMinute, int nSecond)
{
	m_nCurrentMinute = nMinute;
	m_nCurrentSecond = nSecond;
}

void CManager::GetCurrentTim(int* nMinute, int* nSecond)
{
	*nMinute = m_nCurrentMinute;
	*nSecond = m_nCurrentSecond;
}

//===========================================================================================
// ���[�h�̐ݒ�
//===========================================================================================
void CManager::SetMode(CScene::MODE mode)
{
	//�T�E���h�̒�~
	if (m_pSound != nullptr)
	{
		m_pSound->Stop();
	}

	//���݂̃��[�h��j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//�S�I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	//�e�N�X�`���̏I���A�j��
	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̏I������
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = nullptr;

		//�e�N�X�`���̐���
		if (m_pTexture == nullptr)
		{
			m_pTexture = new CTexture;

			//����������
			if (m_pTexture != nullptr)
			{
				m_pTexture->Load();
			}
		}
	}
	
	//�t�F�[�h�̍폜
	m_pFade = nullptr;

	//�V�������[�h�̐���
	m_pScene = CScene::Create(mode);
	m_pScene->SetMode(mode);

	if (m_pScene != nullptr)
	{
		m_pScene->Init();
	}

	//�t�F�[�h�̐���
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(mode);
	}
}