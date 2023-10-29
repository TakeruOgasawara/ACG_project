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

//�}�N����`
#define BREAK	(80)
#define RECREATE	(80)

//===========================================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//===========================================================================================
CBreakBlock::~CBreakBlock()
{

}

//===========================================================================================
// ����
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
// ����������
//===========================================================================================
HRESULT CBreakBlock::Init(void)
{
	return S_OK;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CBreakBlock::Init(D3DXVECTOR3 pos)
{
	m_pObjectX[TYPE_BLOCK] = CObjectX::Create("data\\MODEL\\object\\breakBlock.x", pos);

	m_pObjectX[TYPE_BLOCK]->SetType(CObject::TYPE_BREAKBLOCK);

	m_SavePos = pos;

	return S_OK;
}

//===========================================================================================
// �I������
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
// �X�V����
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

	//�ʒu�ݒ�
	D3DXVECTOR3 pos = GetPosition();

	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y�������z");
	CManager::GetInstance()->GetDebugProc()->Print("\n�ʒu�F x:%f y:%f z:%f", pos.x, pos.y, pos.z);
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CBreakBlock::Draw(void)
{
	
}

//===========================================================================================
// �j��
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
// �Đ���
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
// �����蔻��
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

	//y�̓����蔻��
	if (pPos->z + size > pos.z + vtxMin.z && pPos->z - size < pos.z + vtxMax.z &&
		pPos->x + size > pos.x + vtxMin.x && pPos->x - size < pos.x + vtxMax.x)
	{//�u���b�N�͈̔͂Ȃ��̏ꍇ
		if (pPosOld->y + size <= pos.y + vtxMin.y &&
			pPos->y + size >= pos.y + vtxMin.y)
		{//��̓����蔻��
			pPos->y = pos.y + vtxMin.y - size;
			pMove->y = 0.0f;
		}
		if (pPosOld->y - size >= pos.y + vtxMax.y &&
			pPos->y - size <= pos.y + vtxMax.y)
		{//���̓����蔻��
			pPos->y = pos.y + vtxMax.y + size;
			pMove->y = 0.0f;
			m_state = STATE_BREAK;
			bLand = true;
		}
	}
	if (pPos->y + size > pos.y + vtxMin.y && pPos->y - size < pos.y + vtxMax.y)
	{//�I�u�W�F�N�g�̕�(y)�ɓ������ꍇ
		if (pPos->x + size > pos.x + vtxMin.x &&
			pPos->x - size < pos.x + vtxMax.x)
		{//���E�̓����蕝�̎w��
			if (pPosOld->z + size <= pos.z + vtxMin.z &&
				pPos->z + size >= pos.z + vtxMin.z)
			{//�O�̓����蔻��
				pPos->z = pos.z + vtxMin.z - size;
				pMove->z = 0.0f;
			}
			if (pPosOld->z - size >= pos.z + vtxMax.z &&
				pPos->z - size <= pos.z + vtxMax.z)
			{//��̓����蔻��
				pPos->z = pos.z + vtxMax.z + size;
				pMove->z = 0.0f;
			}
		}
		if (pPos->z + size > pos.z + vtxMin.z && pPos->z - size < pos.z + vtxMax.z)
		{//�I�u�W�F�N�g�̕�(z)�ɓ������ꍇ
			if (pPosOld->x + size <= pos.x + vtxMin.x &&
				pPos->x + size >= pos.x + vtxMin.x)
			{//���̓����蔻��
				pPos->x = pos.x + vtxMin.x - size;
				pMove->x = 0.0f;
			}
			if (pPosOld->x - size >= pos.x + vtxMax.x &&
				pPos->x - size <= pos.x + vtxMax.x)
			{//�E�̓����蔻��
				pPos->x = pos.x + vtxMax.x + size;
				pMove->x = 0.0f;
			}
		}
	}

	return bLand;
}
