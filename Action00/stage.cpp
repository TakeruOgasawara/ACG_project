//======================================================================================
//
// �X�e�[�W����[stage.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "stage.h"
#include <stdio.h>
#include <assert.h>

#include "game.h"

#include "camera.h"
#include "player.h"
#include "edit.h"
#include "objectX.h"
#include "input.h"

//�I�u�W�F�N�g�t�@�C����
const char* c_stageFileList[1] =
{
	"data\\TXT\\stage\\stage0.txt",
};


//========================================================================
// �R���X�g���N�^
//========================================================================
CStage::CStage()
{
	m_data.area = AREA_0;
	m_data.stage = STAGE_0;

	m_pCamera = nullptr;
	m_pEdit = nullptr;
	m_pPlayer = nullptr;
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CStage::~CStage()
{

}

//========================================================================
// ����
//========================================================================
CStage* CStage::Create(void)
{
	CStage* pStage = nullptr;

	if (pStage == nullptr)
	{
		pStage = new CStage;

		if (pStage != nullptr)
		{
			pStage->Init();

			return pStage;
		}
	}

	return nullptr;
}

//========================================================================
// ����������
//========================================================================
HRESULT CStage::Init()
{
	m_data.area = AREA_0;
	m_data.stage = STAGE_0;

	//���̎擾
	m_pCamera = CManager::GetInstance()->GetCamera();

	//�v���C���[
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�G�f�B�b�g
	m_pEdit = CEdit::Create();

	//�e�L�X�g�̓ǂݍ���
	//m_pEdit->CEdit::Load(c_stageFileList[0]);d

	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CStage::Uninit()
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
void CStage::Update()
{
	if (m_pEdit != nullptr)
	{
		m_pEdit->Update();
	}

	switch (m_data.stage)
	{
	case STAGE_0:

		Stage0();

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

		//assert(false, "�w��O�̃X�e�[�W���I������܂���");
		break;
	}
}

//========================================================================
// �`�揈��
//========================================================================
void CStage::Draw()
{
	if (m_pEdit != nullptr)
	{
		m_pEdit->Draw();
	}
}

//========================================================================
// 
//========================================================================
void CStage::Stage0(void)
{
	if (m_pCamera != nullptr)
	{
		m_pCamera->SetLength(700.0f);
		m_pCamera->SetHeight(200.0f, 200.0f);
		m_pCamera->Follow2D_x_axisDedicated(m_pPlayer->GetPosition());
	}
}
