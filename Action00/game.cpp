//===========================================================================================
//
// �Q�[�����[game.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdlib.h>

#include "game.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectX.h"

#include "debugproc.h"
#include "sound.h"
#include "camera.h"
#include "billboard.h"

#include "input.h"
#include "texture.h"
#include "fade.h"
#include "pause.h"
#include "edit.h"
#include "xfile.h"

#include "player.h"

#include "stage.h"

//�ÓI�����o�ϐ��錾
CGame* CGame::m_pGame = nullptr;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CGame::CGame()
{
	m_pUIManager = nullptr;
	m_pPause = nullptr;
	m_pXfile = nullptr;
	m_pSound = nullptr;
	m_bEdit = false;

	m_pStage = nullptr;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CGame::~CGame()
{

}

//===========================================================================================
// �V���O���g��
//===========================================================================================
CGame* CGame::GetInstance(void)
{
	if (m_pGame == nullptr)
	{//null�������ꍇ

		return m_pGame = new CGame;
	}
	else
	{
		return m_pGame;
	}
}

//===========================================================================================
// �j��
//===========================================================================================
void CGame::Release(void)
{
	if (m_pGame == nullptr)
	{//null�������ꍇ

		return;
	}
	else
	{
		delete	m_pGame;
		m_pGame = nullptr;
	}
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CGame::Init()
{
	m_pStage = CStage::Create();
	
	return E_NOTIMPL;
}

//===========================================================================================
// �I������
//===========================================================================================
void CGame::Uninit()
{
	if (m_pGame != nullptr)
	{
		m_pGame->Release();
	}

	if (m_pStage != nullptr)
	{
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = nullptr;
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	if (m_pXfile != nullptr)
	{
		m_pXfile->Unload();
		delete m_pXfile;
		m_pXfile = nullptr;
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CGame::Update()
{
	//�|�C���^�̎擾
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CFade *pFade = CManager::GetInstance()->GetFade();

	if (m_pStage != nullptr)
	{
		m_pStage->Update();
	}

	/*if (pInputKey->GetTrigger(DIK_P) == true)
	{
		if (m_pPause == nullptr)
		{
			m_pPause = CPause::Create();
		}
		else
		{
			m_pPause->Uninit();
			delete m_pPause;
			m_pPause = nullptr;
		}
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Update();

		if (m_pPause->GetPause() == true)
		{
			CManager::GetInstance()->GetFade()->Update();

			return;
		}
	}*/
	
	if (pInputKey->GetTrigger(DIK_RETURN) == true)
	{
		CManager::GetInstance()->GetFade()->Set(MODE_RESULT);
	}

	CScene::Update();
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CGame::Draw()
{
	CScene::Draw();

	if (m_pPause != nullptr)
	{
		m_pPause->Draw();
	}

	if (m_pStage != nullptr)
	{
		m_pStage->Draw();
	}
}