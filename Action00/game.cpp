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
#include "player.h"

#include "input.h"
#include "texture.h"
#include "fade.h"
#include "pause.h"
#include "edit.h"
#include "xfile.h"

#include "player.h"

#include "stage_manager.h"

//静的メンバ変数宣言
CPlayer* CGame::m_pPlayer = nullptr;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CGame::CGame()
{
	m_pUIManager = nullptr;
	m_pPause = nullptr;
	m_pXfile = nullptr;
	m_pSound = nullptr;
	m_pPlayer = false;
	m_bEdit = false;

	m_pStageManager = nullptr;
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
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-400.0f, 0.0f, 0.0f));
	
	m_pStageManager = CStageManager::GetInstance();

	return E_NOTIMPL;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CGame::Uninit()
{
	if (m_pStageManager != nullptr)
	{
		m_pStageManager->Uninit();
		delete m_pStageManager;
		m_pStageManager = nullptr;
	}

	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	if (m_pXfile != nullptr)
	{
		m_pXfile->Unload();
		delete m_pXfile;
		m_pXfile = nullptr;
	}
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CGame::Update()
{
	//ポインタの取得
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CFade *pFade = CManager::GetInstance()->GetFade();

	if (m_pStageManager != nullptr)
	{
		m_pStageManager->Update();
	}

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
			CManager::GetInstance()->GetFade()->Update();

			return;
		}
	}*/
	
	//if (pInputKey->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::GetInstance()->GetFade()->Set(MODE_RESULT);
	//}

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

	if (m_pStageManager != nullptr)
	{
		m_pStageManager->Draw();
	}
}