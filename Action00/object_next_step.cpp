//===========================================================================================
//
// [edit.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include "object_next_step.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"

#include "fade_normal.h"
#include "player.h"
#include "game.h"

#include "texture.h"
#include "xfile.h"

//===========================================================================================
// コンストラクタ
//===========================================================================================
CNextStep::CNextStep()
{
	m_bTach = false;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CNextStep::~CNextStep()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CNextStep* CNextStep::Create(void)
{
	CNextStep* pNextStep = nullptr;

	if (pNextStep == nullptr)
	{
		pNextStep = new CNextStep;

		pNextStep->Init();

		pNextStep->SetType(TYPE_NEXTSTEP);

		return pNextStep;
	}

	return nullptr;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CNextStep::Init(void)
{
	CObjectX::Init("data\\MODEL\\object\\nextStepObject.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CNextStep::Uninit(void)
{
	CObjectX::Uninit();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CNextStep::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	TachObject(pos);

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("\n\n【NextStepオブジェクト情報】");
	CManager::GetInstance()->GetDebugProc()->Print("\n位置： x:%f y:%f z:%f\n", pos.x, pos.y, pos.z);
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CNextStep::Draw(void)
{
	CObjectX::Draw();
}

//===========================================================================================
// 触れた判定
//===========================================================================================
bool CNextStep::TachObject(D3DXVECTOR3 pos)
{
	m_bTach = false;
	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer == nullptr)
	{
		return false;
	}

	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	D3DXVECTOR3 playerPosOld = pPlayer->GetPosisionOld();
	float size = 10.0f;
	D3DXVECTOR3 vtxMax = GetVtxMax();
	D3DXVECTOR3 vtxMin = GetVtxMin();

	if (playerPos.y + size > pos.y + vtxMin.y && playerPos.y - size < pos.y + vtxMax.y)
	{//オブジェクトの幅(y)に入った場合
		if (playerPos.x + size > pos.x + vtxMin.x &&
			playerPos.x - size < pos.x + vtxMax.x)
		{//左右の当たり幅の指定
			if (playerPos.z + size >= pos.z + vtxMin.z)
			{//前の当たり判定
				m_bTach = true;
				CFadeNormal::Create();
			}
			if (playerPos.z - size <= pos.z + vtxMax.z)
			{//後の当たり判定
				m_bTach = true;
				CFadeNormal::Create();
			}
		}
	}

	return m_bTach;
}
