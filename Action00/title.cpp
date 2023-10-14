//===========================================================================================
//
// �^�C�g�����[title.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "fade.h"

//�ÓI�����o�ϐ��錾
CObject2D *CTitle::m_apObject2D[2] = {};
CMap *CTitle::m_pMap = nullptr;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CTitle::CTitle()
{
	m_state = STATE_NONE;
	col_a = 0.0f;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CTitle::~CTitle()
{

}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CTitle::Init()
{
	col_a = 0.0f;

	CTexture *pTexture = CManager::GetTexture();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apObject2D[nCnt] = CObject2D::Create(3);

		switch (nCnt)
		{
		case 0:
			m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
			m_apObject2D[nCnt]->SetSize_center(300.0f, 100.0f);
			m_apObject2D[nCnt]->BindTexture(pTexture->Regist("data\\TEXTURE\\TITLE\\title-1.png"));
			break;

		case 1:
			m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(640.0f, 600.0f, 0.0f));
			m_apObject2D[nCnt]->SetSize_center(130.0f, 40.0f);
			m_apObject2D[nCnt]->BindTexture(pTexture->Regist("data\\TEXTURE\\tutorial_ENTER.png"));
			break;
		default:
			break;
		}
	}

	m_state = STATE_IN;

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CTitle::Uninit()
{

}

//===========================================================================================
// �X�V����
//===========================================================================================
void CTitle::Update()
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CInputJoyPad *pJoyPad = CManager::GetInputJoyPad();

	if (m_state == STATE_IN)
	{//�t�F�[�h�C�����

		col_a -= 0.02f;			//�|���S���𓧖��ɂ��Ă���

		if (col_a <= 0.4f)
		{
			col_a = 0.0f;
			m_state = STATE_OUT;				//�������Ă��Ȃ����
		}
	}
	else if (m_state == STATE_OUT)
	{//�t�F�[�h�A�E�g���

		col_a += 0.02f;			//�|���S����s�����ɂ��Ă���

		if (col_a >= 1.0f)
		{
			col_a = 1.0f;
			m_state = STATE_IN;				//�������Ă��Ȃ����
		}
	}

	m_apObject2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, col_a));

	if (pInputKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->BUTTON_A, 0))
	{
		CManager::GetFade()->Set(MODE_GAME);
	}

	CScene::Update();
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CTitle::Draw()
{
	CScene::Draw();
}

