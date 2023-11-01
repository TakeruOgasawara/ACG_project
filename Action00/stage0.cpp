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
#include "break_block.h"
#include "damage_block .h"
#include "trap_scissors.h"

#include "game.h"
#include "time.h"
#include "camera.h"
#include "player.h"
#include "edit.h"
#include "objectX.h"
#include "input.h"

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
	m_area = AREA_2;
	m_bLoad = false;
	m_pCamera = nullptr;
	m_pPlayer = nullptr;
	m_pEdit = nullptr;
	m_pNextStep = nullptr;
	m_bNext = false;
	m_bAreaEnd = false;
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
CStage0* CStage0::Create(void)
{
	CStage0* pStage0 = nullptr;

	if (pStage0 == nullptr)
	{
		pStage0 = new CStage0;

		if (pStage0 != nullptr)
		{
			//����������
			pStage0->Init();

			return pStage0;
		}
		else
		{
			return nullptr;
		}
	}

	return pStage0;
}

//========================================================================
// ����������
//========================================================================
HRESULT CStage0::Init()
{
	//���̎擾
	m_pCamera = CManager::GetInstance()->GetCamera();

	//�v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

	//�J�ڃI�u�W�F�N�g����
	m_pNextStep = CNextStep::Create();

	//�e�L�X�g�̓ǂݍ���
	m_area = AREA_0;

	m_pEdit = CEdit::Create();
	//m_pEdit->CEdit::Load(c_stage0FileList[AREA_2]);

	CDamageBlock::Create(D3DXVECTOR3(-50.0f, 125.0f, 0.0f));

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
	if (m_bAreaEnd == true)
	{
		return;
	}

	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad* pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	if (m_pPlayer == nullptr)
	{
		if (pInputKeyboard->GetTrigger(DIK_X) == true || pInpuJoyPad->GetTrigger(pInpuJoyPad->BUTTON_A, 0) == true)
		{
			m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			m_bLoad = true;
		}
		else
		{
			//return;
		}
	}

	if (m_pEdit != nullptr)
	{
		m_pEdit->Update();
	}

	if (m_pPlayer == nullptr)
	{
		return;
	}

	if (m_pPlayer->GetState() == CPlayer::STATE_DEATH)
	{
		m_pPlayer->Uninit();
		m_pPlayer = nullptr;
		return;
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
		//assert(false);
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
// �G���A0 (�`���[�g���A��)
//========================================================================
void CStage0::Area0(void)
{
	if (m_bLoad == true)
	{
		//����̃I�u�W�F�N�g�̍폜
		CObject::ReleaseAllSpecified(CObject::TYPE_OBJECTX);
		CObject::ReleaseAllSpecified(CObject::TYPE_BREAKBLOCK);
		CObject::ReleaseAllSpecified(CObject::TYPE_DAMAGEBLOCK);

		//�X�e�[�W�ǂݍ���
		m_pEdit->CEdit::Load(c_stage0FileList[AREA_0]);

		//�G���A�S�[���̈ʒu
		m_pNextStep->SetPosition(D3DXVECTOR3(640.0f, 0.0f, 0.0f));

		//�v���C���[�̏����ʒu
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

		//�J�����̐ݒ�
		m_pCamera->SetPosition_V(D3DXVECTOR3(0.0f, 200.0f, -500.0f));
		m_pCamera->SetPosition_R(D3DXVECTOR3(0.0f, 200.0f, 0.0f));
		m_pCamera->SetLength(500.0f);
		
		m_bLoad = false;
	}

	if (m_pNextStep != nullptr)
	{
		if (m_pNextStep->GetTach() == true && m_bNext == false)
		{
			//�G���A�ԍ���ύX
			m_area = AREA_1;

			//�ǂݍ��݂��J�n��Ԃ�
			m_bLoad = true;

			//����
			m_bNext = true;

			CGame::GetTime()->SetState(CTime::STATE_COUNT);
		}
	}
}

//========================================================================
// �G���A1 (�`���[�g���A��)
//========================================================================
void CStage0::Area1(void)
{
	if (m_bLoad == true)
	{
		//����̃I�u�W�F�N�g�̍폜
		CObject::ReleaseAllSpecified(CObject::TYPE_OBJECTX);
		CObject::ReleaseAllSpecified(CObject::TYPE_BREAKBLOCK);
		CObject::ReleaseAllSpecified(CObject::TYPE_DAMAGEBLOCK);

		//�X�e�[�W�ǂݍ���
		m_pEdit->CEdit::Load(c_stage0FileList[AREA_1]);

		//�G���A�S�[���̈ʒu
		m_pNextStep->SetPosition(D3DXVECTOR3(2940.0f, 0.0f, 0.0f));	

		//�v���C���[�̏����ʒu
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

		//�J�����ݒ�
		m_pCamera->SetPosition_V(D3DXVECTOR3(0.0f, 200.0f, -500.0f));
		m_pCamera->SetPosition_R(D3DXVECTOR3(0.0f, 200.0f, 0.0f));
		m_pCamera->SetLength(500.0f);
		m_pCamera->SetHeight(200.0f, 200.0f);

		m_bLoad = false;
	}
	else
	{
		//����
		m_bNext = false;
	}

	if (m_pPlayer->GetPosition().x >= 0.0f && m_pPlayer->GetPosition().x <= 2300.0f)
	{
		m_pCamera->Follow2D_x_axisDedicated(m_pPlayer->GetPosition());
	}
	
	if (m_pNextStep != nullptr)
	{
		if (m_pNextStep->GetTach() == true && m_bNext == false)
		{
			//�G���A�ԍ���ύX
			m_area = AREA_2;

			//�ǂݍ��݂��J�n��Ԃ�
			m_bLoad = true;

			//����
			m_bNext = true;
		}
	}
}

//========================================================================
// �G���A2 (�`���[�g���A��)
//========================================================================
void CStage0::Area2(void)
{
	if (m_bLoad == true)
	{
		//����̃I�u�W�F�N�g�̍폜
		CObject::ReleaseAllSpecified(CObject::TYPE_OBJECTX);
		CObject::ReleaseAllSpecified(CObject::TYPE_BREAKBLOCK);
		CObject::ReleaseAllSpecified(CObject::TYPE_DAMAGEBLOCK);

		//�X�e�[�W�̓ǂݍ���
		m_pEdit->CEdit::Load(c_stage0FileList[AREA_2]);

		//�G���A�S�[���̈ʒu
		m_pNextStep->SetPosition(D3DXVECTOR3(2800.0f, 0.0f, 0.0f));

		//�v���C���[�̏����ʒu
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));
	
		//�J�����ݒ�
		m_pCamera->SetPosition_V(D3DXVECTOR3(0.0f, 200.0f, -500.0f));
		m_pCamera->SetPosition_R(D3DXVECTOR3(0.0f, 200.0f, 0.0f));
		m_pCamera->SetLength(500.0f);
		m_pCamera->SetHeight(200.0f, 200.0f);

		CBreakBlock::Create(D3DXVECTOR3(350.0f, 225.0f, 0.0f));

		CBreakBlock::Create(D3DXVECTOR3(1275.0f, -100.0f, 0.0f));

		CBreakBlock::Create(D3DXVECTOR3(1600.0f, 225.0f, 0.0f));

		CDamageBlock::Create(D3DXVECTOR3(-50.0f, 125.0f, 0.0f));
		CDamageBlock::Create(D3DXVECTOR3(0.0f, 125.0f, 1.0f));

		CDamageBlock::Create(D3DXVECTOR3(1100.0f, -100.0f, 0.0f));

		m_bLoad = false;
	}
	else
	{
		//����
		m_bNext = false;
	}

	if (m_pPlayer->GetPosition().x >= 0.0f && m_pPlayer->GetPosition().x <= 2200.0f)
	{
		m_pCamera->Follow2D_x_axisDedicated(m_pPlayer->GetPosition());
	}

	if (m_pNextStep->GetTach() == true && m_bNext == false)
	{
		//�G���A�ԍ���ύX
		m_area = AREA_2;

		//�ǂݍ��݂��J�n��Ԃ�
		m_bLoad = true;

		//����
		m_bNext = true;

		m_bAreaEnd = true;

		//����̃I�u�W�F�N�g�̍폜
		CObject::ReleaseAllSpecified(CObject::TYPE_OBJECTX);
		CObject::ReleaseAllSpecified(CObject::TYPE_BREAKBLOCK);
		CObject::ReleaseAllSpecified(CObject::TYPE_DAMAGEBLOCK);
	}
}
