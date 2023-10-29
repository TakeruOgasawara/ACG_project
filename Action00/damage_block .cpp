//===========================================================================================
//
// [edit.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include <assert.h>
#include "damage_block .h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "objectX.h"
#include "debugproc.h"
#include "collision.h"

#include "game.h"
#include "player.h"
#include "texture.h"
#include "xfile.h"

//===========================================================================================
// コンストラクタ
//===========================================================================================
CDamageBlock::CDamageBlock()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CDamageBlock::~CDamageBlock()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CDamageBlock* CDamageBlock::Create(D3DXVECTOR3 pos)
{
	CDamageBlock* pBreakBlock = nullptr;

	if (pBreakBlock == nullptr)
	{
		pBreakBlock = new CDamageBlock;

		pBreakBlock->Init(pos);

		pBreakBlock->SetType(CObject::TYPE_DAMAGEBLOCK);

		return pBreakBlock;
	}

	return nullptr;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CDamageBlock::Init(void)
{
	return S_OK;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CDamageBlock::Init(D3DXVECTOR3 pos)
{
	CObjectX::Init("data\\MODEL\\object\\damageBlock.x", pos);
	SetPosition(pos);

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CDamageBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CDamageBlock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("\n\n【ダメージ物情報】");
	CManager::GetInstance()->GetDebugProc()->Print("\n位置： x:%f y:%f z:%f", pos.x, pos.y, pos.z);
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CDamageBlock::Draw(void)
{
	CObjectX::Draw();
}

//===========================================================================================
// 当たり判定
//===========================================================================================
bool CDamageBlock::Collision(D3DXVECTOR3 pos, float size)
{
	bool bTach = false;

	D3DXVECTOR3 ObjectPos = GetPosition();
	D3DXVECTOR3 vtxMax = GetVtxMax();
	D3DXVECTOR3 vtxMin = GetVtxMin();

	if (pos.y + size > ObjectPos.y + vtxMin.y && pos.y - size < ObjectPos.y + vtxMax.y)
	{//オブジェクトの幅(y)に入った場合
		if (pos.x + size > ObjectPos.x + vtxMin.x &&
			pos.x - size < ObjectPos.x + vtxMax.x)
		{//左右の当たり幅の指定
			if (pos.z + size >= ObjectPos.z + vtxMin.z)
			{//前の当たり判定
				bTach = true;
			}
			if (pos.z - size <= ObjectPos.z + vtxMax.z)
			{//後の当たり判定
				bTach = true;
			}
		}
	}

	return bTach;
}
