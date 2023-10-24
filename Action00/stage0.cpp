//======================================================================================
//
// �X�e�[�W����[stage.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "stage0.h"
#include <stdio.h>
#include <assert.h>
#include "manager.h"
#include "scene.h"
#include "fade.h"

#include "game.h"
#include "object_next_step.h"
#include "object.h"
#include "lock_door.h"

#include "camera.h"
#include "player.h"
#include "edit.h"
#include "objectX.h"
#include "input.h"

// �萔�錾
const int nNowArea = 0;

//�ÓI�����o�ϐ��錾
CStage0* CStage0::m_pStage0 = nullptr;

//�I�u�W�F�N�g�t�@�C����
const char* c_stage0FileList[3] =
{
	"data\\TXT\\stage\\0.0.txt",
	"data\\TXT\\stage\\0.1.txt",
	"data\\TXT\\stage\\0.2.txt",
};

//========================================================================
// �R���X�g���N�^
//========================================================================
CStage0::CStage0()
{
	m_area = AREA_0;
	m_bLoad = false;
	m_pCamera = nullptr;
	m_pPlayer = nullptr;
	m_pEdit = nullptr;
	m_pNextStep = nullptr;
	m_bNext = false;
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CStage0::~CStage0()
{

}

//========================================================================
// �V���O���g��
//========================================================================
CStage0* CStage0::GetInstance(void)
{
	if (m_pStage0 == nullptr)
	{//null�������ꍇ

		m_pStage0 = new CStage0;

		m_pStage0->Init();

		return m_pStage0;
	}
	else
	{
		return m_pStage0;
	}
}

//========================================================================
// ����������
//========================================================================
HRESULT CStage0::Init()
{
	//���̎擾
	m_pCamera = CManager::GetInstance()->GetCamera();

	m_pPlayer = CGame::GetPlayer();

	m_pEdit = CEdit::Create();

	m_pNextStep = CNextStep::Create();

	//�e�L�X�g�̓ǂݍ���
	m_pEdit->CEdit::Load(c_stage0FileList[nNowArea]);

	m_bLoad = true;

	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CStage0::Uninit()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}
	if (m_pCamera != nullptr)
	{
		m_pCamera = nullptr;
	}
	if (m_pEdit != nullptr)
	{
		delete m_pEdit;
		m_pEdit = nullptr;
	}
}

//========================================================================
// �X�V����
//========================================================================
void CStage0::Update()
{
	if (m_pEdit != nullptr)
	{
		m_pEdit->Update();
	}

	switch (m_area)
	{
	case AREA_0:
		Area0();
		break;

	case AREA_1:
		Area1();
		break;

	case AREA_2:
		Area2();
		break;

	default:
		assert(false);
		break;
	}
}

//========================================================================
// �`�揈��
//========================================================================
void CStage0::Draw()
{
	if (m_pEdit != nullptr)
	{
		m_pEdit->Draw();
	}
}

//========================================================================
// �G���A0
//========================================================================
void CStage0::Area0(void)
{
	if (m_bLoad == true)
	{
		m_pNextStep->SetPosition(D3DXVECTOR3(640.0f, -0.0f, 0.0f));
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

		m_bLoad = false;
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->SetLength(500.0f);
	}

	if (m_pNextStep != nullptr)
	{
		if (m_pNextStep->GetTach() == true)
		{
			//����̃I�u�W�F�N�g�̍폜
			CObject::ParticularRelease(CObject::TYPE_OBJECTX);

			m_pEdit->CEdit::Load(c_stage0FileList[1]);

			m_area = AREA_1;

			m_bLoad = true;
		}
	}
}

//========================================================================
// �G���A1
//========================================================================
void CStage0::Area1(void)
{
	if (m_bLoad == true)
	{
		m_pNextStep->SetPosition(D3DXVECTOR3(2940.0f, -125.0f, 0.0f));
		
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

		m_bLoad = false;
	}

	if (m_pPlayer->GetPosition().x >= 0.0f && m_pPlayer->GetPosition().x <= 2300.0f)
	{
		m_pCamera->Follow2D_x_axisDedicated(m_pPlayer->GetPosition());
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->SetLength(500.0f);
		m_pCamera->SetHeight(200.0f, 200.0f);
	}
	
	//if (m_pNextStep->GetTach() == true)
	//{
	//	m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 0.0f, 0.0f));
	//	m_pPlayer->SetMovement(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	//m_pEdit->CEdit::Load(c_stage0FileList[2]);

	//	m_area = AREA_2;

	//	//CManager::GetInstance()->GetFade()->Set(CScene::MODE_RESULT);
	//}
}

//========================================================================
// �G���A2
//========================================================================
void CStage0::Area2(void)
{

}
