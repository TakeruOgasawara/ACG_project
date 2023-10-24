//======================================================================================
//
// ステージ処理[stage.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "stage_manager.h"
#include <stdio.h>
#include <assert.h>

#include "game.h"
#include "object_next_step.h"

#include "stage0.h"

#include "camera.h"
#include "player.h"
#include "edit.h"
#include "objectX.h"
#include "input.h"

//静的メンバ変数宣言
CStageManager* CStageManager::m_pStageManager = nullptr;

//========================================================================
// コンストラクタ
//========================================================================
CStageManager::CStageManager()
{
	m_stage = STAGE_0;
	nProgress = 0;

	m_pStage0 = nullptr;
}

//========================================================================
// デストラクタ
//========================================================================
CStageManager::~CStageManager()
{

}

//========================================================================
// シングルトン
//========================================================================
CStageManager* CStageManager::GetInstance(void)
{
	if (m_pStageManager == nullptr)
	{//nullだった場合

		m_pStageManager = new CStageManager;

		m_pStageManager->Init();

		return m_pStageManager;
	}
	else
	{
		return m_pStageManager;
	}
}

//========================================================================
// 初期化処理
//========================================================================
HRESULT CStageManager::Init()
{
	m_stage = STAGE_0;

	m_pStage0 = CStage0::GetInstance();

	return S_OK;
}

//========================================================================
// 終了処理
//========================================================================
void CStageManager::Uninit()
{
	if (m_pStage0 != nullptr)
	{
		m_pStage0->Uninit();
		delete m_pStage0;
		m_pStage0 = nullptr;
	}
}

//========================================================================
// 更新処理
//========================================================================
void CStageManager::Update()
{
	switch (m_stage)
	{
	case STAGE_0:
		m_pStage0->Update();
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

		assert(false);
		break;
	}
}

//========================================================================
// 描画処理
//========================================================================
void CStageManager::Draw()
{
	
}