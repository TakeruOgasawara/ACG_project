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
// �R���X�g���N�^
//===========================================================================================
CDamageBlock::CDamageBlock()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CDamageBlock::~CDamageBlock()
{

}

//===========================================================================================
// ����
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
// ����������
//===========================================================================================
HRESULT CDamageBlock::Init(void)
{
	return S_OK;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CDamageBlock::Init(D3DXVECTOR3 pos)
{
	CObjectX::Init("data\\MODEL\\object\\damageBlock.x", pos);
	SetPosition(pos);

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CDamageBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CDamageBlock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//�f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y�_���[�W�����z");
	CManager::GetInstance()->GetDebugProc()->Print("\n�ʒu�F x:%f y:%f z:%f", pos.x, pos.y, pos.z);
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CDamageBlock::Draw(void)
{
	CObjectX::Draw();
}

//===========================================================================================
// �����蔻��
//===========================================================================================
bool CDamageBlock::Collision(D3DXVECTOR3 pos, float size)
{
	bool bTach = false;

	D3DXVECTOR3 ObjectPos = GetPosition();
	D3DXVECTOR3 vtxMax = GetVtxMax();
	D3DXVECTOR3 vtxMin = GetVtxMin();

	if (pos.y + size > ObjectPos.y + vtxMin.y && pos.y - size < ObjectPos.y + vtxMax.y)
	{//�I�u�W�F�N�g�̕�(y)�ɓ������ꍇ
		if (pos.x + size > ObjectPos.x + vtxMin.x &&
			pos.x - size < ObjectPos.x + vtxMax.x)
		{//���E�̓����蕝�̎w��
			if (pos.z + size >= ObjectPos.z + vtxMin.z)
			{//�O�̓����蔻��
				bTach = true;
			}
			if (pos.z - size <= ObjectPos.z + vtxMax.z)
			{//��̓����蔻��
				bTach = true;
			}
		}
	}

	return bTach;
}
