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

#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"

#include "object3D.h"

//�ÓI�����o�ϐ��錾
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CInputMouse *CManager::m_pInputMouse = nullptr;
CInputJoyPad *CManager::m_pInputJoyPad = nullptr;
CDebugProc *CManager::m_pDebugProc = nullptr;
CSound *CManager::m_pSound = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CLight *CManager::m_pLight = nullptr;
CTexture *CManager::m_pTexture = nullptr;
bool CManager::m_bUse = false;
CScene *CManager::m_pScene = nullptr;

CScene::MODE CScene::m_mode = CScene::MODE_GAME;
CFade *CManager::m_pFade = nullptr;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CManager::CManager()
{

}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CManager::~CManager()
{

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
			if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
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
	//if (m_pSound == nullptr)
	//{
	//	m_pSound = new CSound;

	//	if (m_pSound != nullptr)
	//	{
	//		//�}�E�X�̏���������
	//		m_pSound->Init(hWnd);
	//	}
	//}
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

	//m_pSound->PlaySound(CSound::LABEL_BGM000);

	//���[�h�ݒ�
	SetMode(GetMode());
	
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
	//if (m_pSound != nullptr)
	//{
	//	//�T�E���h�̏I������
	//	m_pSound->Stop();
	//	m_pSound->Uninit();

	//	delete m_pSound;
	//	m_pSound = nullptr;
	//}
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
	m_pScene->Draw();
}

//===========================================================================================
// ���[�h�̐ݒ�
//===========================================================================================
void CManager::SetMode(CScene::MODE mode)
{
	//�T�E���h�̒�~
	//if (m_pSound != nullptr)
	//{
	//	m_pSound->Stop();
	//}

	//���݂̃��[�h��j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

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

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CScene::CScene()
{
	
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CScene::~CScene()
{

}

//===========================================================================================
// �V�[���̐���
//===========================================================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = nullptr;

	if (pScene == nullptr)
	{
		//���[�h�ʂ̐���
		switch (mode)
		{
		case MODE_TITLE:
			pScene = new CTitle;
			break;

		case MODE_GAME:
			pScene = new CGame;
			break;

		case MODE_RESULT:
			pScene = new CResult;
			break;
		}
	}

	return pScene;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CScene::Init(void)
{
	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CScene::Uninit(void)
{

}

//===========================================================================================
// �X�V����
//===========================================================================================
void CScene::Update(void)
{
	//�J�����̍X�V����
	if (CManager::GetCamera() != nullptr)
	{
		CManager::GetCamera()->Update();
	}

	//�����_���[�̍X�V����
	if (CManager::GetRenderer() != nullptr)
	{
		CManager::GetRenderer()->Update();
	}
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CScene::Draw(void)
{
	if (CManager::GetRenderer() != nullptr)
	{
		CManager::GetRenderer()->Draw();
	}
}