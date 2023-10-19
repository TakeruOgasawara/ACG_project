//======================================================================================
//
// ステージ処理[stage.cpp]
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

//オブジェクトファイル名
const char* c_stageFileList[1] =
{
	"data\\TXT\\stage\\stage0.txt",
};


//========================================================================
// コンストラクタ
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
// デストラクタ
//========================================================================
CStage::~CStage()
{

}

//========================================================================
// 生成
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
// 初期化処理
//========================================================================
HRESULT CStage::Init()
{
	m_data.area = AREA_0;
	m_data.stage = STAGE_0;

	//情報の取得
	m_pCamera = CManager::GetInstance()->GetCamera();

	//プレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エディット
	m_pEdit = CEdit::Create();

	//テキストの読み込み
	//m_pEdit->CEdit::Load(c_stageFileList[0]);d

	return S_OK;
}

//========================================================================
// 終了処理
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
// 更新処理
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

		//assert(false, "指定外のステージが選択されました");
		break;
	}
}

//========================================================================
// 描画処理
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
