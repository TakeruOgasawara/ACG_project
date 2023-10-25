//======================================================================================
//
// ステージ処理[stage.cpp]
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

#include "camera.h"
#include "player.h"
#include "edit.h"
#include "objectX.h"
#include "input.h"

#include "fade_death.h"

// 定数宣言
const int nNowArea = 2;

//静的メンバ変数宣言
CStage0* CStage0::m_pStage0 = nullptr;

//オブジェクトファイル名
const char* c_stage0FileList[3] =
{
	"data\\TXT\\stage\\0.0.txt",
	"data\\TXT\\stage\\0.1.txt",
	"data\\TXT\\stage\\0.2.txt",
};

//========================================================================
// コンストラクタ
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
}

//========================================================================
// デストラクタ
//========================================================================
CStage0::~CStage0()
{

}

//========================================================================
// シングルトン
//========================================================================
CStage0* CStage0::GetInstance(void)
{
	if (m_pStage0 == nullptr)
	{//nullだった場合

		m_pStage0 = new CStage0;

		m_pStage0->Init();

		return m_pStage0;
	}
	else
	{
		return m_pStage0;
	}
}

//========================================================================
// 初期化処理
//========================================================================
HRESULT CStage0::Init()
{
	//情報の取得
	m_pCamera = CManager::GetInstance()->GetCamera();

	m_pPlayer = CGame::GetPlayer();

	m_pNextStep = CNextStep::Create();

	//テキストの読み込み
	m_pEdit = CEdit::Create();
	m_pEdit->CEdit::Load(c_stage0FileList[nNowArea]);

	m_bLoad = true;

	return S_OK;
}

//========================================================================
// 終了処理
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
// 更新処理
//========================================================================
void CStage0::Update()
{
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_R) == true)
	{
		m_bLoad = true;
		CFadeDeath::Create();
	}

	if (m_pEdit != nullptr)
	{
		m_pEdit->Update();
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
		assert(false);
		break;
	}
}

//========================================================================
// 描画処理
//========================================================================
void CStage0::Draw()
{
	if (m_pEdit != nullptr)
	{
		m_pEdit->Draw();
	}
}

//========================================================================
// エリア0
//========================================================================
void CStage0::Area0(void)
{
	if (m_bLoad == true)
	{
		//エリアゴールの位置
		m_pNextStep->SetPosition(D3DXVECTOR3(640.0f, -0.0f, 0.0f));

		//プレイヤーの初期位置
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

		//カメラの設定
		m_pCamera->SetLength(500.0f);
		
		m_bLoad = false;
	}

	if (m_pNextStep != nullptr)
	{
		if (m_pNextStep->GetTach() == true && m_bNext == false)
		{
			////特定のオブジェクトの削除
			//CObject::ParticularRelease(CObject::TYPE_OBJECTX);

			////ステージ読み込み
			//m_pEdit->CEdit::Load(c_stage0FileList[AREA_1]);

			//エリア番号を変更
			m_area = AREA_1;

			//読み込みを開始状態へ
			m_bLoad = true;

			//次へ
			m_bNext = true;
		}
	}
}

//========================================================================
// エリア1
//========================================================================
void CStage0::Area1(void)
{
	if (m_bLoad == true)
	{
		//特定のオブジェクトの削除
		CObject::ParticularRelease(CObject::TYPE_OBJECTX);

		//ステージ読み込み
		m_pEdit->CEdit::Load(c_stage0FileList[AREA_1]);

		//エリアゴールの位置
		m_pNextStep->SetPosition(D3DXVECTOR3(2940.0f, -125.0f, 0.0f));	

		//プレイヤーの初期位置
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

		//カメラ設定
		m_pCamera->SetLength(500.0f);
		m_pCamera->SetHeight(200.0f, 200.0f);

		m_bLoad = false;
	}
	else
	{
		//次へ
		m_bNext = false;
	}

	if (m_pPlayer->GetPosition().x >= 0.0f && m_pPlayer->GetPosition().x <= 2300.0f)
	{
		m_pCamera->Follow2D_x_axisDedicated(m_pPlayer->GetPosition());
	}
	
	if (m_pNextStep->GetTach() == true && m_bNext == false)
	{
		//特定のオブジェクトの削除
		CObject::ParticularRelease(CObject::TYPE_OBJECTX);

		//ステージの読み込み
		m_pEdit->CEdit::Load(c_stage0FileList[AREA_1]);

		//エリア番号を変更
		m_area = AREA_1;

		//読み込みを開始状態へ
		m_bLoad = true;

		//次へ
		m_bNext = true;
	}
}

//========================================================================
// エリア2
//========================================================================
void CStage0::Area2(void)
{
	if (m_bLoad == true)
	{
		//エリアゴールの位置
		m_pNextStep->SetPosition(D3DXVECTOR3(2940.0f, -125.0f, 0.0f));

		//プレイヤーの初期位置
		m_pPlayer->SetPosition(D3DXVECTOR3(-400.0f, 25.0f, 0.0f));

		//カメラ設定
		m_pCamera->SetLength(500.0f);
		m_pCamera->SetHeight(200.0f, 200.0f);

		CBreakBlock::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));

		m_bLoad = false;
	}
	else
	{
		//次へ
		m_bNext = false;
	}

	if (m_pPlayer->GetPosition().x >= 0.0f && m_pPlayer->GetPosition().x <= 2300.0f)
	{
		m_pCamera->Follow2D_x_axisDedicated(m_pPlayer->GetPosition());
	}

	if (m_pNextStep->GetTach() == true && m_bNext == false)
	{
		//特定のオブジェクトの削除
		CObject::ParticularRelease(CObject::TYPE_OBJECTX);

		//ステージの読み込み
		m_pEdit->CEdit::Load(c_stage0FileList[AREA_2]);

		//エリア番号を変更
		m_area = AREA_2;

		//読み込みを開始状態へ
		m_bLoad = true;

		//次へ
		m_bNext = true;
	}
}
