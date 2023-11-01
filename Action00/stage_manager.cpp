//======================================================================================
//
// �X�e�[�W����[stage.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "stage_manager.h"
#include <stdio.h>
#include <assert.h>
#include "manager.h"
#include "fade.h"
#include "scene.h"

#include "game.h"
#include "object_next_step.h"

#include "stage0.h"

#include "camera.h"
#include "player.h"
#include "edit.h"
#include "objectX.h"
#include "input.h"

//�ÓI�����o�ϐ��錾
CStageManager* CStageManager::m_pStageManager = nullptr;

//========================================================================
// �R���X�g���N�^
//========================================================================
CStageManager::CStageManager()
{
	m_stage = STAGE_0;
	m_state = STATE_START;
	nProgress = 0;

	m_pStage0 = nullptr;
	m_bEnd = false;
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CStageManager::~CStageManager()
{

}

//========================================================================
// �V���O���g��
//========================================================================
//CStageManager* CStageManager::GetInstance(void)
//{
//	if (m_pStageManager == nullptr)
//	{//null�������ꍇ
//
//		m_pStageManager = new CStageManager;
//
//		m_pStageManager->Init();
//
//		return m_pStageManager;
//	}
//	else
//	{
//		return m_pStageManager;
//	}
//}


//========================================================================
// ����
//========================================================================
CStageManager* CStageManager::Create(void)
{
	CStageManager* pStageManager = nullptr;

	if (pStageManager == nullptr)
	{
		pStageManager = new CStageManager;

		if (pStageManager != nullptr)
		{
			//����������
			pStageManager->Init();

			return pStageManager;
		}
		else
		{
			return nullptr;
		}
	}

	return pStageManager;
}

//========================================================================
// ����������
//========================================================================
HRESULT CStageManager::Init()
{
	m_stage = STAGE_0;

	m_pStage0 = CStage0::Create();

	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CStageManager::Uninit()
{
	if (m_pStage0 != nullptr)
	{
		m_pStage0->Uninit();
		delete m_pStage0;
		m_pStage0 = nullptr;
	}
}

//========================================================================
// �X�V����
//========================================================================
void CStageManager::Update()
{
	switch (m_stage)
	{
	case STAGE_0:
		m_pStage0->Update();
		break;

	case STAGE_1:

		break;

	case STAGE_2:

		break;

	case STAGE_3:

		break;

	case STAGE_4:

		break;

	default:
		assert(false);
		break;
	}

	if (m_bEnd == false)
	{
		if (m_pStage0->GetArea() == m_pStage0->AREA_2 && m_pStage0->GetAreaEnd() == true)
		{
			CManager::GetInstance()->GetFade()->SetMode(CScene::MODE_RESULT);

			m_bEnd = true;
		}
	}
}

//========================================================================
// �`�揈��
//========================================================================
void CStageManager::Draw()
{

}