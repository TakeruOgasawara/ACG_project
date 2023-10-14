//======================================================================================
//
//�t�F�[�h����[Bg.cpp]
//Author;���}���@�V
//
//======================================================================================
#include "game.h"
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "texture.h"

//�}�N����`
#define SIZE_X			(100.0f)
#define SIZE_Y			(50.0f)

//======================================================================================
// 
//======================================================================================
CPause::CPause()
{
	m_menu = MENU_CONTINUE;
	for (int nCntMenu = 0; nCntMenu < MENU_MAX; nCntMenu++)
	{
		m_aMenuInfo[nCntMenu] = {};
	}
	m_fColor_a = 0.0f;
	m_nSelect = 0;
	m_bUse = false;
}

//======================================================================================
// 
//======================================================================================
CPause::~CPause()
{

}

//======================================================================================
// 
//======================================================================================
CPause * CPause::Create(void)
{
	CPause *pPause = nullptr;

	pPause = new CPause;

	if (pPause != nullptr)
	{
		pPause->Init();

		return pPause;
	}
	else
	{
		return nullptr;
	}

	return pPause;
}

//======================================================================================
// 
//======================================================================================
void CPause::Init()
{
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{

		m_aMenuInfo[nCnt].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		// 2D�I�u�W�F�N�g�̐���
		m_aMenuInfo[nCnt].pObject2D = CObject2D::Create(NUM_PRIORITY - 1);

		if (m_aMenuInfo[nCnt].pObject2D != nullptr)
		{
			switch (nCnt)
			{
			case MENU_CONTINUE:
				m_aMenuInfo[nCnt].pObject2D->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\pause_0.png"));
				break;

			case MENU_RETRY:
				m_aMenuInfo[nCnt].pObject2D->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\pause_1.png"));
				break;

			case MENU_QUIT:
				m_aMenuInfo[nCnt].pObject2D->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\pause_2.png"));
				break;
			}
		
			m_aMenuInfo[nCnt].pObject2D->SetPosition(D3DXVECTOR3(640.0f, 200.0f + nCnt * 110.0f, 0.0f));
			m_aMenuInfo[nCnt].pObject2D->SetSize_center(SIZE_X, SIZE_Y);
		}
	}

	m_nSelect = m_menu;

	SelectMenu();
}

//======================================================================================
// �I������
//======================================================================================
void CPause::Uninit()
{
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_aMenuInfo[nCnt].pObject2D != nullptr)
		{
			m_aMenuInfo[nCnt].pObject2D->Uninit();
			m_aMenuInfo[nCnt].pObject2D = nullptr;
		}
	}
}

//======================================================================================
// �X�V
//======================================================================================
void CPause::Update()
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CInputJoyPad *pjoyPad = CManager::GetInputJoyPad();
	CFade *pFade = CManager::GetFade();

	if (pFade->GetState() != CFade::STATE_NONE)
	{// �����ꂽ��Ԃ̏ꍇ
		return;
	}

	if (pInputKey->GetTrigger(DIK_P) == true)
	{
		m_bUse = m_bUse ? false : true;
	}

	if (m_bUse == false)	//�`�F�b�N
	{
		return;
	}

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
	else if (pInputKey->GetTrigger(DIK_RETURN) == true)
	{
		if (pFade == nullptr)
		{
			return;
		}

		switch (m_menu)
		{
		case MENU_CONTINUE:
			m_bUse = false;
			break;
		case MENU_RETRY:
			//SetFadeMode(FADEMODE_NORMAL);
			pFade->Set(CScene::MODE_GAME);
			break;
		case MENU_QUIT:
			//SetFadeMode(FADEMODE_NORMAL);
			pFade->Set(CScene::MODE_TITLE);
			break;
		}
	}

}

//======================================================================================
// 
//======================================================================================
void CPause::Draw()
{

}

//======================================================================================
// �I�����Ă��郁�j���[
//======================================================================================
void CPause::SelectMenu(void)
{
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_menu == nCnt)
		{//�I�����Ă��郁�j���ƍ����Ă�����

			m_aMenuInfo[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			m_aMenuInfo[nCnt].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		}

		m_aMenuInfo[nCnt].pObject2D->SetColor(m_aMenuInfo[nCnt].col);
	}
}
