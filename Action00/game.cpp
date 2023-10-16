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
#include "xfile.h"

#include "player.h"

//静的メンバ変数宣言
CPlayer3D *CGame::m_pPlayer3D = nullptr;
CMap *CGame::m_pMap = nullptr;
CUI_Manager *CGame::m_pUIManager = nullptr;
CPause *CGame::m_pPause = nullptr;
CEdit *CGame::m_pEdit = nullptr;
CXfile* CGame::m_pXfile = nullptr;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CGame::CGame()
{
	m_pSound = nullptr;
	m_bEdit = false;
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
	if (m_pXfile == nullptr)
	{
		m_pXfile = new CXfile;

		//	xファイルの読み込み
		m_pXfile->Load();
	}

	/*CObject3D *pObject3D = CObject3D::Create(D3DXVECTOR3(0.0f, 200.0f, 10.0f), CObject3D::TYPE_WALL);
	pObject3D->SetSize_wall(640.0f, 360.0f);*/

	//床
	CObject3D::Create(D3DXVECTOR3(0.0f, -5.0f, 0.0f), "data\\TEXTURE\\floor.png");

	//CObjectX::Create("data\\MODEL\\object\\floor00.x", D3DXVECTOR3(0.0f, 250.0f, 0.0f));

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

	//エディット
	Edit();



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

	if (m_pEdit != nullptr)
	{
		m_pEdit->Draw();
	}
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CGame::Edit(void)
{
	CInputKeyboard* pInputKey = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKey->GetTrigger(DIK_F3) == true)
	{
		m_bEdit = m_bEdit ? false : true;

		if (m_bEdit == true)
		{
			if (m_pEdit == nullptr)
			{
				m_pEdit = CEdit::Create();
			}
		}
		else
		{
			if (m_pEdit != nullptr)
			{
				delete m_pEdit;
				m_pEdit = nullptr;

			}
		}
	}

	if (m_pEdit != nullptr)
	{
		m_pEdit->Update();

		return;
	}
}
