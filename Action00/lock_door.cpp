//===========================================================================================
//
// [lock_door.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include "lock_door.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"

#include "player.h"
#include "game.h"

#include "collision.h"

#include "texture.h"

static float SPEED = 0.2f;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CLockDoor::CLockDoor()
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_state = STATE_STOP;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CLockDoor::~CLockDoor()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CLockDoor* CLockDoor::Create(void)
{
	CLockDoor* pLOckDoor = nullptr;

	if (pLOckDoor == nullptr)
	{
		pLOckDoor = new CLockDoor;

		pLOckDoor->Init();

		pLOckDoor->SetType(TYPE_LOCKDOOR);

		return pLOckDoor;
	}

	return nullptr;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CLockDoor::Init(void)
{
	CObjectX::Init("data\\MODEL\\object\\lockdoor.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_state = STATE_DOWN;

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CLockDoor::Uninit(void)
{
	CObjectX::Uninit();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CLockDoor::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posOld = pos;

	if (m_state == STATE_DOWN)
	{
		m_move.y -= SPEED;

		/*if (CollisionObjectX(&pos, &posOld, GetVtxMax().y) == true)
		{
			m_state = STATE_STOP;
		}*/

		if (pos.y < 0.0f)
		{
			m_state = STATE_STOP;
			m_move.y = 0.0f;
		}

		//移動量を加算
		pos += m_move;
	}

	//位置設定
	SetPosition(pos);

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("\n\n【LockDoorオブジェクト情報】");
	CManager::GetInstance()->GetDebugProc()->Print("\n位置： x:%f y:%f z:%f\n", pos.x, pos.y, pos.z);
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CLockDoor::Draw(void)
{
	CObjectX::Draw();
}