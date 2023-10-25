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

	if (Collision() == true)
	{
		m_state = STATE_BREAK;
	}
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
bool CBreakBlock::Collision(void)
{
	bool bLand = false;

	CPlayer* pPlayer = CGame::GetPlayer();

	if (pPlayer == nullptr)
	{
		assert(false);
		return false;
	}

	if (m_pObjectX[TYPE_BLOCK] == false)
	{
		return false;
	}

	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	D3DXVECTOR3 playerPosOld = pPlayer->GetPosisionOld();
	D3DXVECTOR3 playerMove = pPlayer->GetMovement();
	bool bFirst = pPlayer->GetFirstJamp();
	bool bSecond = pPlayer->GetSecondJamp();
	float size = 25.0f;

	D3DXVECTOR3 pos = m_pObjectX[TYPE_BLOCK]->GetPosition();
	D3DXVECTOR3 vtxMax = m_pObjectX[TYPE_BLOCK]->GetVtxMax();
	D3DXVECTOR3 vtxMin = m_pObjectX[TYPE_BLOCK]->GetVtxMin();

	if (bFirst == false || bSecond == false)
	{
		//yの当たり判定
		if (playerPos.z + size > pos.z + vtxMin.z && playerPos.z - size < pos.z + vtxMax.z &&
			playerPos.x + size > pos.x + vtxMin.x && playerPos.x - size < pos.x + vtxMax.x)
		{//ブロックの範囲ないの場合
			if (playerPosOld.y + size <= pos.y + vtxMin.y && playerPos.y + size >= pos.y + vtxMin.y)
			{//上の当たり判定
				pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, pos.y + vtxMin.y - size, playerPos.z));
				pPlayer->SetMoveY(0.0f);
			}
			if (playerPosOld.y - size >= pos.y + vtxMax.y && playerPos.y - size <= pos.y + vtxMax.y)
			{//下の当たり判定
				playerPos.y = pos.y + vtxMax.y + size;

				pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
				pPlayer->SetMoveY(0.0f);

				pPlayer->SetFirstJamp(false);
				pPlayer->SetSecondJamp(false);
				
				bLand = true;
			}
		}
		if (playerPos.y + size > pos.y + vtxMin.y && playerPos.y - size < pos.y + vtxMax.y)
		{//オブジェクトの幅(y)に入った場合
			if (playerPos.x + size > pos.x + vtxMin.x && playerPos.x - size < pos.x + vtxMax.x)
			{//左右の当たり幅の指定
				if (playerPosOld.z + size <= pos.z + vtxMin.z && playerPos.z + size >= pos.z + vtxMin.z)
				{//前の当たり判定
					playerPos.z = pos.z + vtxMin.z - size;

					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveZ(0.0f);
				}
				if (playerPosOld.z - size >= pos.z + vtxMax.z && playerPos.z - size <= pos.z + vtxMax.z)
				{//後の当たり判定
					playerPos.z = pos.z + vtxMax.z + size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveZ(0.0f);
				}
			}
			if (playerPos.z + size > pos.z + vtxMin.z && playerPos.z - size < pos.z + vtxMax.z)
			{//オブジェクトの幅(z)に入った場合
				if (playerPosOld.x + size <= pos.x + vtxMin.x && playerPos.x + size >= pos.x + vtxMin.x)
				{//左の当たり判定
					playerPos.x = pos.x + vtxMin.x - size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveX(0.0f);
				}
				if (playerPosOld.x - size >= pos.x + vtxMax.x && playerPos.x - size <= pos.x + vtxMax.x)
				{//右の当たり判定
					playerPos.x = pos.x + vtxMax.x + size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveX(0.0f);
				}
			}
		}
	}
	else
	{
		if (playerPos.y + size > pos.y + vtxMin.y && playerPos.y - size < pos.y + vtxMax.y)
		{//オブジェクトの幅(y)に入った場合
			if (playerPos.x + size > pos.x + vtxMin.x && playerPos.x - size < pos.x + vtxMax.x)
			{//左右の当たり幅の指定
				if (playerPosOld.z + size <= pos.z + vtxMin.z && playerPos.z + size >= pos.z + vtxMin.z)
				{//前の当たり判定
					playerPos.z = pos.z + vtxMin.z - size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveZ(0.0f);
				}
				if (playerPosOld.z - size >= pos.z + vtxMax.z && playerPos.z - size <= pos.z + vtxMax.z)
				{//後の当たり判定
					playerPos.z = pos.z + vtxMax.z + size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveZ(0.0f);
				}
			}
			if (playerPos.z + size > pos.z + vtxMin.z && playerPos.z - size < pos.z + vtxMax.z)
			{//オブジェクトの幅(z)に入った場合
				if (playerPosOld.x + size <= pos.x + vtxMin.x && playerPos.x + size >= pos.x + vtxMin.x)
				{//左の当たり判定
					playerPos.x = pos.x + vtxMin.x - size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));

					pPlayer->SetMoveX(0.0f);
				}
				if (playerPosOld.x - size >= pos.x + vtxMax.x && playerPos.x - size <= pos.x + vtxMax.x)
				{//右の当たり判定
					playerPos.x = pos.x + vtxMax.x + size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveX(0.0f);
				}
			}

			//yの当たり判定
			if (playerPos.z + size > pos.z + vtxMin.z && playerPos.z - size < pos.z + vtxMax.z &&
				playerPos.x + size > pos.x + vtxMin.x && playerPos.x - size < pos.x + vtxMax.x)
			{//ブロックの範囲ないの場合
				if (playerPosOld.y + size <= pos.y + vtxMin.y && playerPos.y + size >= pos.y + vtxMin.y)
				{//上の当たり判定
					playerPos.y = pos.y + vtxMin.y - size;
					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveY(0.0f);
				}
				if (playerPosOld.y - size >= pos.y + vtxMax.y && playerPos.y - size <= pos.y + vtxMax.y)
				{//下の当たり判定
					playerPos.y = pos.y + vtxMax.y + size;

					pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
					pPlayer->SetMoveY(0.0f);
					pPlayer->SetFirstJamp(false);
					pPlayer->SetSecondJamp(false);

					bLand = true;

				}
			}
		}
	}

	return bLand;
}
