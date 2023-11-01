//===========================================================================================
//
// [player3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "arrow_around.h"
#include "object2D.h"
#include "objectX.h"

#include "break_block.h"
#include "damage_block .h"
#include "object_next_step.h"
#include "trap_scissors.h"

#include "sound.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "collision.h"
#include "fade_death.h"

//�}�N����`
#define SIZE			(D3DXVECTOR2(5.0f, 10.0f))

#define MOVE			(2.5f)			//�ړ���
#define ATT				(0.3f)			//����
#define GRAVITY			(1.0f)			//�d��
#define LIFE			(1)				//�̗�
#define JUMPEND			(10)


//���̈ʒu
#define ARROW_POS		(70.0f)

//�W�����v
#define FILSTJUMP_POWER		(20.0f)			//�W�����v��
#define SECONDJUMP_POWER	(15.0f)			//

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CPlayer::CPlayer(int nPriority)
{
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = STATE_NORMAL;
	m_nLife = 0;
	m_nNormalJumpCount = 0;
	m_nSecondJumpCount = 0;
	m_pCamera = nullptr;
	m_pCollision = nullptr;
	m_pArrowAround = nullptr;
	m_pObject2D = nullptr;
	m_bNormalJump = false;
	m_bSecondJump = false;
	m_bJumpFlag = false;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CPlayer::~CPlayer()
{

}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���
//===========================================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			pPlayer->Init();

			pPlayer->SetPosition(pos);

			pPlayer->SetType(CObject::TYPE_PLAYER);

			return pPlayer;
		}
		else
		{
			return nullptr;
		}
	}

	return pPlayer;
}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���
//===========================================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			//����������
			pPlayer->Init();

			//�ʒu�ݒ�
			pPlayer->SetPosition(pos);

			//�����ݒ�
			pPlayer->SetRotation(rot);

			pPlayer->SetType(CObject::TYPE_PLAYER);

			return pPlayer;
		}
		else
		{
			return nullptr;
		}
	}

	return pPlayer;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CPlayer::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	CObject::SetType(CObject::TYPE_PLAYER);

	m_nLife = LIFE;

	// �r���{�[�h(�v���C���[�{��
	CBillboard::Init();
 	SetSize(D3DXVECTOR2(SIZE.x, SIZE.y));
	BindTexture("data\\TEXTURE\\player.png");

	// ���
	// ���ڂ̃W�����v���������߂���
	m_pArrowAround = CArrowAround::Create();	//����
	m_pArrowAround->BindTexture("data\\TEXTURE\\game\\arrow1.png");
	m_pArrowAround->SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y + 50.0f, 0.0f));

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CPlayer::Uninit(void)
{
	if (m_pArrowAround != nullptr)
	{
		m_pArrowAround->Uninit();
		m_pArrowAround = nullptr;
	}

	CBillboard::Uninit();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	//�ߋ��ʒu�̕ۑ�
	m_posOld = pos;

	if (m_state == STATE_DEATH)
	{//���S��Ԃ̏ꍇ
		return;
	}

	if (m_bSecondJump == false)
	{
		//�d�͂�������
		m_move.y -= GRAVITY;

		//�ړ��ʂ��X�V(����������)
		m_move.x += (0.0f - m_move.x) * ATT;

		//����
		InputMove();

		//�W�����v���܂Ƃ߂��֐�
		NormalJump();
	}

	if (m_bSecondJump == true)
	{
		m_nSecondJumpCount++;

		if (m_nSecondJumpCount > JUMPEND)
		{
			m_bSecondJump = false;
			m_nSecondJumpCount = 0;
		}
	}

	//��ʊO�ɏo�����̔���
	if (GetScreenPosition().y > SCREEN_HEIGHT)
	{
		Hit(10);
		return;
	}

	//if (GetScreenPosition().y < 0)
	//{
	//	m_move.y = 0.0f;
	//	pos.y = SIZE.y + 15.0f;
	//}

	//�ړ��ʂ̑��
	pos += m_move;

	//�I�u�W�F�N�g�Ƃ̓����蔻��֐�
	if (CollisionObjectX1(&pos, &m_posOld, &m_move, m_bNormalJump, SIZE.y + 15.0f) == true)
	{
		m_bNormalJump = false;
		m_bSecondJump = false;
		m_bJumpFlag = false;
	}
	if (CollisionObjectX1(&pos, &m_posOld, &m_move, m_bSecondJump, SIZE.y + 15.0f) == true)
	{
		m_bNormalJump = false;
		m_bSecondJump = false;
		m_bJumpFlag = false;
	}	
	//�����u���b�N�Ƃ̓����蔻��
	if (CollisionBreakBlock(&pos, &m_posOld, &m_move, SIZE.y + 15.0f) == true)
	{
		m_bNormalJump = false;
		m_bSecondJump = false;
		m_bJumpFlag = false;
	}
	//�_���[�W�u���b�N�Ƃ̓����蔻��
	if (CollisionDamageBlock(pos, SIZE.y + 15.0f) == true)
	{
		Hit(10);
		return;
	}
	//���Ƃ̓����蔻��
	if (CollisionNextStep(pos, SIZE.y + 15.0f) == true)
	{
		return;
	}

	//���
	Arrow(pos);

	//�ʒu�̐ݒ�
	SetPosition(pos);

	//�f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y�v���C���[���z");
	CManager::GetInstance()->GetDebugProc()->Print("\n�ʒu�F x:%f y:%f z:%f", pos.x, pos.y, pos.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n�����F x:%f y:%f z:%f", rot.x, rot.y, rot.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n�ړ��ʁF x:%f y:%f z:%f\n", m_move.x, m_move.y, m_move.z);
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CPlayer::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O�̗L��/�����̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (m_state != STATE_DEATH)
	{
		CBillboard::Draw();
	}

	//���C�e�B���O�̗L��/�����̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===========================================================================================
// �q�b�g����
//===========================================================================================
void CPlayer::Hit(int nDamage)
{
	//�̗͂����炷
	m_nLife -= nDamage;

	if (m_nLife < 0 && m_state != STATE_DEATH)
	{
		CFadeDeath::Create();
		m_state = STATE_DEATH;
		m_nLife = 0;

		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DEATH);
	}
}

//===========================================================================================
// �������
//===========================================================================================
void CPlayer::InputMove(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	//�L�[���͂ňړ����鏈��
	if (pInputKeyboard->GetPress(DIK_A) == true || pInpuJoyPad->GetJoyStickLX(0) < 0)
	{//A�L�[�������ꂽ

		m_move.x -= MOVE;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true || pInpuJoyPad->GetJoyStickLX(0) > 0)
	{//D�L�[�������ꂽ

		m_move.x += MOVE;	
	}
}

//===========================================================================================
// �m�[�}���W�����v
//===========================================================================================
void CPlayer::NormalJump(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	if (m_bNormalJump == false && m_bSecondJump == false)
	{//�W�����v���Ă��Ȃ���Ԃ̏ꍇ

		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pInpuJoyPad->GetPress(pInpuJoyPad->BUTTON_RB, 0) == true)
		{//�L�[�������ꂽ

			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_JUMP);

			m_move.y += FILSTJUMP_POWER;

			m_bNormalJump = true;
		}
	}

	//�u�[�X�g�W�����v
	SecondJump();

	if (pInpuJoyPad->GetJoyStickLX(0) < 0)
	{//��
		//�ړ��ʂ̏�����
		m_move.y = 0.0f;
		m_move.x = 0.0f;
	}
	if (pInpuJoyPad->GetJoyStickLX(0) > 0)
	{//�E
		//�ړ��ʂ̏�����
		m_move.y = 0.0f;
		m_move.x = 0.0f;
	}
}

//===========================================================================================
// �W�����v
//===========================================================================================
void CPlayer::SecondJump(void)
{
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad* pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();
	CInputMouse* pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�v���C���[�̃X�N���[�����W���擾
	D3DXVECTOR3 screemPos = GetScreenPosition();

	if (m_bJumpFlag == false)
	{//�W�����v���Ă��Ȃ���Ԃ̏ꍇ

		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT))
		{//�L�[�������ꂽ

			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BOOST);

			//�v���C���[����}�E�X�J�[�\���̊p�x���Z�o
			float fAngle = atan2f((screemPos.x - pInputMouse->GetPoint().x) + D3DX_PI, (screemPos.y - pInputMouse->GetPoint().y) + D3DX_PI);

			//�ړ��ʂ̏�����
			m_move.y = 0.0f;
			m_move.x = 0.0f;

			//�ړ��ʂɉ�����
			m_move +=
			{
				sinf(fAngle + D3DX_PI) * SECONDJUMP_POWER,
				cosf(fAngle) * SECONDJUMP_POWER,
				0.0f
			};

			m_bNormalJump = true;
			m_bSecondJump = true;	//���ڂ̃W�����v���������Ƃɂ���
			m_bJumpFlag = true;
		}
	}
}

//===========================================================================================
// ���
//===========================================================================================
void CPlayer::Arrow(D3DXVECTOR3 pos)
{
	CInputMouse* pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�v���C���[�̃X�N���[�����W���擾
	D3DXVECTOR3 screemPos = GetScreenPosition();

	//�v���C���[����}�E�X�J�[�\���̊p�x���Z�o
	float fAngle = atan2f((screemPos.x - pInputMouse->GetPoint().x) + D3DX_PI, (screemPos.y - pInputMouse->GetPoint().y) + D3DX_PI);

	//null�`�F�b�N
	if (m_pArrowAround != nullptr)
	{
		//�ʒu�ݒ�
		m_pArrowAround->SetPosition(D3DXVECTOR3(pos.x + sinf(-fAngle) * ARROW_POS, pos.y + cosf(-fAngle) * ARROW_POS, 0.0f));

		//����
		m_pArrowAround->SetRotation(D3DXVECTOR3(0.0f, 0.0f, fAngle));
	}

	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y���z\n");
	CManager::GetInstance()->GetDebugProc()->Print("�ʒu x:%f y:%f z%f\n", m_pArrowAround->GetPosition().x, m_pArrowAround->GetPosition().y, m_pArrowAround->GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("���� x:%f y:%f z%f\n", m_pArrowAround->GetRotation().x, m_pArrowAround->GetRotation().y, m_pArrowAround->GetRotation().z);
}

//===========================================================================================
// �X�N���[����̃v���C���[�̈ʒu
//===========================================================================================
D3DXVECTOR3 CPlayer::GetScreenPosition(void)
{
	//�ϐ��錾
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 playerPos = GetPosition();
	D3DXVECTOR3 screenPos;
	D3DVIEWPORT9 viewport;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetViewport(&viewport);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�X�N���[�����W�ɕϊ�
	D3DXVec3Project(&screenPos, &playerPos, &viewport, &mtxProjection, &mtxView, &mtxWorld);

	return screenPos;
}

//===========================================================================================
// �����u���b�N�Ƃ̓����蔻��
//===========================================================================================
bool CPlayer::CollisionBreakBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float size)
{
	bool bLand = false;	//���n������

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject* pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			if (pObject->GetType() != pObject->TYPE_BREAKBLOCK)
			{
				continue;
			}

			CBreakBlock* pBreakBlock = pObject->GetBreakBlock();	//�q�N���X�A����u���b�N�̏��擾

			if (pBreakBlock == nullptr)
			{
				continue;
			}

			if (pBreakBlock->Collision(pPos, pPosOld, pMove, size) == true)
			{
				bLand = true;
			}
		}
	}
	return bLand;	//bLand�̌��ʂ��֐��ɕԂ�
}

//===========================================================================================
// �_���[�W�u���b�N�Ƃ̓����蔻��
//===========================================================================================
bool CPlayer::CollisionDamageBlock(D3DXVECTOR3 pos, float size)
{
	bool bTouch = false;	//�ڐG������

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject* pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			if (pObject->GetType() != pObject->TYPE_DAMAGEBLOCK)
			{
				continue;
			}

			CDamageBlock* pDamageBlock = pObject->GetDamageBlock();	//�q�N���X�A����u���b�N�̏��擾

			if (pDamageBlock == nullptr)
			{
				continue;
			}

			if (pDamageBlock->Collision(pos, size) == true)
			{
				bTouch = true;
			}
		}
	}

	return bTouch;			//bLand�̌��ʂ��֐��ɕԂ�
}

//===========================================================================================
// �X�e�[�W�؂�ւ��̓����蔻��
//===========================================================================================
bool CPlayer::CollisionNextStep(D3DXVECTOR3 pos, float size)
{
	bool bTouch = false;	//�ڐG������

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject* pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			if (pObject->GetType() != pObject->TYPE_NEXTSTEP)
			{
				continue;
			}

			CNextStep* pNextStep = pObject->GetNextStep();	//�q�N���X�A����u���b�N�̏��擾

			if (pNextStep == nullptr)
			{
				continue;
			}

			if (pNextStep->Collision(pos, size) == true)
			{
				bTouch = true;
			}
		}
	}

	return bTouch;			//bLand�̌��ʂ��֐��ɕԂ�
}
