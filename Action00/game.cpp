//===========================================================================================
//
// ゲーム画面[game.cpp]
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

#include "player.h"

//静的メンバ変数宣言
CPlayer3D *CGame::m_pPlayer3D = nullptr;
CMap *CGame::m_pMap = nullptr;
CUI_Manager *CGame::m_pUIManager = nullptr;
CPause *CGame::m_pPause = nullptr;
CEdit *CGame::m_pEdit = nullptr;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CGame::CGame()
{
	m_pSound = nullptr;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CGame::~CGame()
{

}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CGame::Init()
{
	//床
	CObject3D::Create(D3DXVECTOR3(0.0f, -5.0f, 0.0f), "data\\TEXTURE\\floor.png");

	CObjectX::Create("data\\MODEL\\object\\floor00.x", D3DXVECTOR3(0.0f, 30.0f, 0.0f));

	//プレイヤー
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return E_NOTIMPL;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CGame::Uninit()
{
	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CGame::Update()
{
	//ポインタの取得
	CDebugProc *pDebug = CManager::GetDebugProc();
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CFade *pFade = CManager::GetFade();
	int pos_x = 0, pos_z = 0;
	int Rand_If = 0;
	int RandPosx = 0;
	int RadPosz = 0;

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
			CManager::GetFade()->Update();

			return;
		}
	}*/

	if (pInputKey->GetTrigger(DIK_RETURN) == true)
	{
		CScene::SetMode(CScene::MODE_RESULT);
	}

	CScene::Update();
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CGame::Draw()
{
	CScene::Draw();

	if (m_pPause != nullptr)
	{
		m_pPause->Draw();
	}

	
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CGame::Edit(void)
{
	if (m_pEdit == nullptr)
	{
		m_pEdit = new CEdit;
	}

	if (m_pEdit != nullptr)
	{
		m_pEdit->Update();
	}
}
