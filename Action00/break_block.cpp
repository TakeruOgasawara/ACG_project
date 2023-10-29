//===========================================================================================
//
// [edit.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include <assert.h>
#include "break_block.h"
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

//マクロ定義
#define BREAK	(80)
#define RECREATE	(80)

//===========================================================================================
// コンストラクタ
//===========================================================================================
CBreakBlock::CBreakBlock(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_pObjectX[nCnt] = nullptr;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nDestroyCnt = 0;
	m_nReCreateCnt = 0;
	m_bBreak = false;
	m_state = STATE_NONE;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CBreakBlock::~CBreakBlock()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CBreakBlock* CBreakBlock::Create(D3DXVECTOR3 pos)
{
	CBreakBlock* pBreakBlock = nullptr;

	if (pBreakBlock == nullptr)
	{
		pBreakBlock = new CBreakBlock;

		pBreakBlock->Init(pos);
		pBreakBlock->SetPosition(pos);

		pBreakBlock->SetType(CObject::TYPE_BREAKBLOCK);

		return pBreakBlock;
	}

	return nullptr;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CBreakBlock::Init(void)
{
	return S_OK;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CBreakBlock::Init(D3DXVECTOR3 pos)
{
	m_pObjectX[TYPE_BLOCK] = CObjectX::Create("data\\MODEL\\object\\breakBlock.x", pos);

	m_pObjectX[TYPE_BLOCK]->SetType(CObject::TYPE_BREAKBLOCK);

	m_SavePos = pos;

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CBreakBlock::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pObjectX[nCnt] != nullptr)
		{
			//m_pObjectX[nCnt]->Uninit();
			//delete m_pObjectX[nCnt];
			m_pObjectX[nCnt] = nullptr;
		}
	}
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CBreakBlock::Update(void)
{
	switch (m_state)
	{
	case STATE_NONE:
		break;

	case STATE_BREAK:
		Break();
		break;

	case STATE_RECREATE:
		ReCeate();
		break;

	default:
		assert(false);
		break;
	}

	//位置設定
	D3DXVECTOR3 pos = GetPosition();

	CManager::GetInstance()->GetDebugProc()->Print("\n\n【崩れる情報】");
	CManager::GetInstance()->GetDebugProc()->Print("\n位置： x:%f y:%f z:%f", pos.x, pos.y, pos.z);
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CBreakBlock::Draw(void)
{
	
}

//===========================================================================================
// 破壊
//===========================================================================================
void CBreakBlock::Break(void)
{
	m_nDestroyCnt++;

	if (m_nDestroyCnt > BREAK)
	{
		m_pObjectX[TYPE_BLOCK]->Uninit();
		m_pObjectX[TYPE_BLOCK] = nullptr;

		m_nDestroyCnt = 0;
		m_bBreak = false;
		m_state = STATE_RECREATE;
	}
}

//===========================================================================================
// 再生成
//===========================================================================================
void CBreakBlock::ReCeate(void)
{
	m_nReCreateCnt++;

	if (m_nReCreateCnt < RECREATE)
	{
		return;
	}

	if (m_pObjectX[TYPE_BLOCK] == nullptr)
	{
		m_pObjectX[TYPE_BLOCK] = CObjectX::Create("data\\MODEL\\object\\breakBlock.x", m_SavePos);
		m_pObjectX[TYPE_BLOCK]->SetType(CObject::TYPE_BREAKBLOCK);

		m_nReCreateCnt = 0;
		m_state = STATE_NONE;
	}
}

//===========================================================================================
// 当たり判定
//===========================================================================================
bool CBreakBlock::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float size)
{
	bool bLand = false;

	if (m_pObjectX[TYPE_BLOCK] == false)
	{
		return false;
	}

	D3DXVECTOR3 pos = m_pObjectX[TYPE_BLOCK]->GetPosition();
	D3DXVECTOR3 vtxMax = m_pObjectX[TYPE_BLOCK]->GetVtxMax();
	D3DXVECTOR3 vtxMin = m_pObjectX[TYPE_BLOCK]->GetVtxMin();

	//yの当たり判定
	if (pPos->z + size > pos.z + vtxMin.z && pPos->z - size < pos.z + vtxMax.z &&
		pPos->x + size > pos.x + vtxMin.x && pPos->x - size < pos.x + vtxMax.x)
	{//ブロックの範囲ないの場合
		if (pPosOld->y + size <= pos.y + vtxMin.y &&
			pPos->y + size >= pos.y + vtxMin.y)
		{//上の当たり判定
			pPos->y = pos.y + vtxMin.y - size;
			pMove->y = 0.0f;
		}
		if (pPosOld->y - size >= pos.y + vtxMax.y &&
			pPos->y - size <= pos.y + vtxMax.y)
		{//下の当たり判定
			pPos->y = pos.y + vtxMax.y + size;
			pMove->y = 0.0f;
			m_state = STATE_BREAK;
			bLand = true;
		}
	}
	if (pPos->y + size > pos.y + vtxMin.y && pPos->y - size < pos.y + vtxMax.y)
	{//オブジェクトの幅(y)に入った場合
		if (pPos->x + size > pos.x + vtxMin.x &&
			pPos->x - size < pos.x + vtxMax.x)
		{//左右の当たり幅の指定
			if (pPosOld->z + size <= pos.z + vtxMin.z &&
				pPos->z + size >= pos.z + vtxMin.z)
			{//前の当たり判定
				pPos->z = pos.z + vtxMin.z - size;
				pMove->z = 0.0f;
			}
			if (pPosOld->z - size >= pos.z + vtxMax.z &&
				pPos->z - size <= pos.z + vtxMax.z)
			{//後の当たり判定
				pPos->z = pos.z + vtxMax.z + size;
				pMove->z = 0.0f;
			}
		}
		if (pPos->z + size > pos.z + vtxMin.z && pPos->z - size < pos.z + vtxMax.z)
		{//オブジェクトの幅(z)に入った場合
			if (pPosOld->x + size <= pos.x + vtxMin.x &&
				pPos->x + size >= pos.x + vtxMin.x)
			{//左の当たり判定
				pPos->x = pos.x + vtxMin.x - size;
				pMove->x = 0.0f;
			}
			if (pPosOld->x - size >= pos.x + vtxMax.x &&
				pPos->x - size <= pos.x + vtxMax.x)
			{//右の当たり判定
				pPos->x = pos.x + vtxMax.x + size;
				pMove->x = 0.0f;
			}
		}
	}

	return bLand;
}
