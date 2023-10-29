//===========================================================================================
//
// [edit.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include <assert.h>
#include "trap_scissors.h"
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
CTrapScissors::CTrapScissors()
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aModel[nCnt].pModel = nullptr;
	}

	m_pFlagObject = nullptr;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = STATE_WAIT;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CTrapScissors::~CTrapScissors()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CTrapScissors* CTrapScissors::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTrapScissors* pBreakBlock = nullptr;

	if (pBreakBlock == nullptr)
	{
		pBreakBlock = new CTrapScissors;

		pBreakBlock->Init(pos, rot);

		pBreakBlock->SetType(CObject::TYPE_TRAPSCISSORS);

		return pBreakBlock;
	}

	return nullptr;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CTrapScissors::Init(void)
{
	return S_OK;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CTrapScissors::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_rot = rot;

	//本体
	m_aModel[MODEL_MAIN].pModel = CObjectX::Create("data\\MODEL\\object\\TrapScissors\\main.x", pos);
	m_aModel[MODEL_MAIN].pModel->SetRotation(m_rot);
	m_aModel[MODEL_MAIN].pModel->SetType(CObject::TYPE_TRAPSCISSORS);
	
	//刃１
	D3DXVECTOR3 pos1 = { 0.0f, 0.0f, 0.0f }, pos2{ 0.0f, 0.0f, 0.0f };

	pos1.x = pos.x + (sinf(m_rot.z + D3DX_PI * 1.57f) * 30.0f);
	pos1.y = pos.y + (cosf(m_rot.z + D3DX_PI * 1.57f) * 30.0f);
	pos2.x = pos.x + (sinf(m_rot.z + D3DX_PI * -1.57f) * 30.0f);
	pos2.y = pos.y + (cosf(m_rot.z + D3DX_PI * -1.57f) * 30.0f);

	m_aModel[MODEL_BLADE1].pModel = CObjectX::Create("data\\MODEL\\object\\TrapScissors\\blade1.x", D3DXVECTOR3(pos1.x, pos1.y, pos.z));
	m_aModel[MODEL_BLADE1].pModel->SetRotation(D3DXVECTOR3(0.0f, 0.0f, m_rot.z/* + 1.57f*/));
	m_aModel[MODEL_BLADE1].pModel->SetType(CObject::TYPE_TRAPSCISSORS);

	//刃２
	m_aModel[MODEL_BLADE2].pModel = CObjectX::Create("data\\MODEL\\object\\TrapScissors\\blade2.x", D3DXVECTOR3(pos2.x, pos2.y, pos.z));
	m_aModel[MODEL_BLADE2].pModel->SetRotation(D3DXVECTOR3(0.0f, 0.0f, m_rot.z /*- 1.57f*/));
	m_aModel[MODEL_BLADE2].pModel->SetType(CObject::TYPE_TRAPSCISSORS);
	
	//
	//m_pFlagObject = CObjectX::Create("data\\MODEL\\object\\TrapScissors\\flagObject.x", pos);

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CTrapScissors::Uninit(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		if (m_aModel[nCnt].pModel != nullptr)
		{
			//delete m_aModel[nCnt].pModel;
			m_aModel[nCnt].pModel = nullptr;
		}
	}


}

//===========================================================================================
// 更新処理
//===========================================================================================
void CTrapScissors::Update(void)
{
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad* pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	D3DXVECTOR3 pos = m_aModel[MODEL_MAIN].pModel->GetPosition();
	D3DXVECTOR3 rot = m_aModel[MODEL_MAIN].pModel->GetRotation();

	//D3DXVECTOR3 pos2 = m_aModel[MODEL_BLADE1].pModel->GetPosition();
	//D3DXVECTOR3 pos1 = m_aModel[MODEL_BLADE1].pModel->GetPosition();
	//pos1.x = pos.x + (sinf(m_rot.z + D3DX_PI * 1.57f) * 30.0f);
	//pos1.y = pos.y + (cosf(m_rot.z + D3DX_PI * 1.57f) * 30.0f);
	//pos2.x = pos.x + (sinf(m_rot.z + D3DX_PI * -1.57f) * 30.0f);
	//pos2.y = pos.y + (cosf(m_rot.z + D3DX_PI * -1.57f) * 30.0f);

	//if (pInputKeyboard->GetPress(DIK_L) == true)
	//{
	//	rot.z += 0.05f;
	//}

	//m_aModel[MODEL_MAIN].pModel->SetRotation(rot);

	//m_aModel[MODEL_BLADE1].pModel->SetPosition(pos1);
	//m_aModel[MODEL_BLADE2].pModel->SetPosition(pos2);

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("\n\n【トラばさみ情報】");
	CManager::GetInstance()->GetDebugProc()->Print("\n位置： x:%f y:%f z:%f", pos.x, pos.y, pos.z);
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CTrapScissors::Draw(void)
{
	//BladeMove();
}

//===========================================================================================
// 当たり判定
//===========================================================================================
bool CTrapScissors::Collision(D3DXVECTOR3 pos, float size)
{
	bool bTach = false;

	if (m_pFlagObject == nullptr)
	{
		return false;
	}

	D3DXVECTOR3 ObjectPos = m_pFlagObject->GetPosition();
	D3DXVECTOR3 vtxMax = m_pFlagObject->GetVtxMax();
	D3DXVECTOR3 vtxMin = m_pFlagObject->GetVtxMin();

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

//===========================================================================================
// 刃の動き
//===========================================================================================
void CTrapScissors::BladeMove(void)
{
	//if (m_state == STATE_ATTACK)
	{
		if (m_aModel[MODEL_BLADE1].rot.z <= 0.0f)
		{
			m_aModel[MODEL_BLADE1].rot.z -= 0.004f;
		}

		if (m_aModel[MODEL_BLADE1].rot.z >= 0.0f)
		{
			m_aModel[MODEL_BLADE2].rot.z += 0.004f;
		}

		if (m_aModel[MODEL_BLADE1].rot.z == 0.0f)
		{
			m_state = STATE_WAIT;
		}
		if (m_aModel[MODEL_BLADE2].rot.z == 0.0f)
		{
			m_state = STATE_WAIT;
		}

		m_aModel[MODEL_BLADE1].pModel->SetRotation(D3DXVECTOR3(0.0f, 0.0f, m_aModel[MODEL_BLADE1].rot.z));
		m_aModel[MODEL_BLADE2].pModel->SetRotation(D3DXVECTOR3(0.0f, 0.0f, m_aModel[MODEL_BLADE2].rot.z));
	}
}
