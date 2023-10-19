//===========================================================================================
//
// �^�C�g�����[title.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <assert.h>

#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "fade.h"

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CTitle::CTitle()
{
	pName2D = nullptr;

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_apMenu[nCnt].pMenu2D = nullptr;
		m_apMenu[nCnt].col = { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	m_nTextureIdx = 0;
	m_nSelect = 0;
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
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	pName2D = CObject2D::Create(3);
	pName2D->SetPosition(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
	pName2D->SetSize_center(300.0f, 60.0f);
	pName2D->BindTexture(pTexture->Regist("data\\TEXTURE\\TITLE\\name.png"));

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_apMenu[nCnt].pMenu2D = CObject2D::Create(3);

		switch (nCnt)
		{
		
		case MENU_START:
			m_apMenu[nCnt].pMenu2D->SetPosition(D3DXVECTOR3(640.0f, 400.0f, 0.0f));
			m_apMenu[nCnt].pMenu2D->SetSize_center(30.0f, 20.0f);
			m_apMenu[nCnt].pMenu2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apMenu[nCnt].pMenu2D->BindTexture(pTexture->Regist("data\\TEXTURE\\title\\start.png"));
			break;

		case MENU_END:
			m_apMenu[nCnt].pMenu2D->SetPosition(D3DXVECTOR3(640.0f, 450.0f, 0.0f));
			m_apMenu[nCnt].pMenu2D->SetSize_center(30.0f, 20.0f);
			m_apMenu[nCnt].pMenu2D->SetColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
			m_apMenu[nCnt].pMenu2D->BindTexture(pTexture->Regist("data\\TEXTURE\\title\\end.png"));
			break;

		default:
			assert(false);	//�G���[
			break;
		}
	}

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CTitle::Uninit()
{
	pName2D = nullptr;

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_apMenu[nCnt].pMenu2D = nullptr;
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CTitle::Update()
{
	//���̓|�C���^�̎擾
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pJoyPad = CManager::GetInstance()->GetInputJoyPad();

	if (pInputKey->GetTrigger(DIK_W) == true)
	{
		m_nSelect = (m_nSelect - 1 + MENU_MAX) % MENU_MAX;

		m_menu = (MENU)m_nSelect;

		SelectMenu();
	}
	else if (pInputKey->GetTrigger(DIK_S) == true)
	{
		m_nSelect = (m_nSelect + 1 + MENU_MAX) % MENU_MAX;

		m_menu = (MENU)m_nSelect;

		SelectMenu();
	}

	if (pInputKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->BUTTON_A, 0))
	{
		switch (m_menu)
		{
		case CTitle::MENU_START:
			CManager::GetInstance()->GetFade()->Set(MODE_GAME);
			break;

		case CTitle::MENU_END:
			//DestroyWindow();
			break;

		default:
			assert(false);
			break;
		}
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

//===========================================================================================
// �I������Ă��郁�j���[
//===========================================================================================
void CTitle::SelectMenu(void)
{
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_menu == nCnt)
		{//�I�����Ă��郁�j���ƍ����Ă�����

			m_apMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			m_apMenu[nCnt].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		}

		m_apMenu[nCnt].pMenu2D->SetColor(m_apMenu[nCnt].col);
	}
}

