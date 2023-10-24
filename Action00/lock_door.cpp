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
// �R���X�g���N�^
//===========================================================================================
CLockDoor::CLockDoor()
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_state = STATE_STOP;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CLockDoor::~CLockDoor()
{

}

//===========================================================================================
// ����
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
// ����������
//===========================================================================================
HRESULT CLockDoor::Init(void)
{
	CObjectX::Init("data\\MODEL\\object\\lockdoor.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_state = STATE_DOWN;

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CLockDoor::Uninit(void)
{
	CObjectX::Uninit();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CLockDoor::Update(void)
{
	//�ʒu�擾
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

		//�ړ��ʂ����Z
		pos += m_move;
	}

	//�ʒu�ݒ�
	SetPosition(pos);

	//�f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print("\n\n�yLockDoor�I�u�W�F�N�g���z");
	CManager::GetInstance()->GetDebugProc()->Print("\n�ʒu�F x:%f y:%f z:%f\n", pos.x, pos.y, pos.z);
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CLockDoor::Draw(void)
{
	CObjectX::Draw();
}