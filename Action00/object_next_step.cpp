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
// �R���X�g���N�^
//===========================================================================================
CNextStep::CNextStep()
{
	m_bTach = false;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CNextStep::~CNextStep()
{

}

//===========================================================================================
// ����
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
// ����������
//===========================================================================================
HRESULT CNextStep::Init(void)
{
	CObjectX::Init("data\\MODEL\\object\\nextStepObject.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CNextStep::Uninit(void)
{
	CObjectX::Uninit();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CNextStep::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	//�f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print("\n\n�yNextStep�I�u�W�F�N�g���z");
	CManager::GetInstance()->GetDebugProc()->Print("\n�ʒu�F x:%f y:%f z:%f\n", pos.x, pos.y, pos.z);
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CNextStep::Draw(void)
{
	//CObjectX::Draw();
}

//===========================================================================================
// �G�ꂽ����
//===========================================================================================
bool CNextStep::Collision(D3DXVECTOR3 pos, float size)
{
	m_bTach = false;
	
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
				m_bTach = true;
				CFadeNormal::Create();
			}
			if (pos.z - size <= ObjectPos.z + vtxMax.z)
			{//��̓����蔻��
				m_bTach = true;
				CFadeNormal::Create();
			}
		}
	}

	return m_bTach;
}
