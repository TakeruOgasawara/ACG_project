//===========================================================================================
//
// タイトル画面[title.cpp]
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

//静的メンバ変数宣言
CObject2D *CTitle::m_apObject2D[2] = {};
CMap *CTitle::m_pMap = nullptr;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CTitle::CTitle()
{
	m_state = STATE_NONE;
	col_a = 0.0f;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CTitle::~CTitle()
{

}

//===========================================================================================
// 初期化処理
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
// 終了処理
//===========================================================================================
void CTitle::Uninit()
{

}

//===========================================================================================
// 更新処理
//===========================================================================================
void CTitle::Update()
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CInputJoyPad *pJoyPad = CManager::GetInputJoyPad();

	if (m_state == STATE_IN)
	{//フェードイン状態

		col_a -= 0.02f;			//ポリゴンを透明にしていく

		if (col_a <= 0.4f)
		{
			col_a = 0.0f;
			m_state = STATE_OUT;				//何もしていない状態
		}
	}
	else if (m_state == STATE_OUT)
	{//フェードアウト状態

		col_a += 0.02f;			//ポリゴンを不透明にしていく

		if (col_a >= 1.0f)
		{
			col_a = 1.0f;
			m_state = STATE_IN;				//何もしていない状態
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
// 描画処理
//===========================================================================================
void CTitle::Draw()
{
	CScene::Draw();
}

