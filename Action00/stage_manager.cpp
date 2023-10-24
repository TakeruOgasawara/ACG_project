//======================================================================================
//
// �X�e�[�W����[stage.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "stage_manager.h"
#include <stdio.h>
#include <assert.h>

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
	nProgress = 0;

	m_pStage0 = nullptr;
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
CStageManager* CStageManager::GetInstance(void)
{
	if (m_pStageManager == nullptr)
	{//null�������ꍇ

		m_pStageManager = new CStageManager;

		m_pStageManager->Init();

		return m_pStageManager;
	}
	else
	{
		return m_pStageManager;
	}
}

//========================================================================
// ����������
//========================================================================
HRESULT CStageManager::Init()
{
	m_stage = STAGE_0;

	m_pStage0 = CStage0::GetInstance();

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
}

//========================================================================
// �`�揈��
//========================================================================
void CStageManager::Draw()
{
	
}