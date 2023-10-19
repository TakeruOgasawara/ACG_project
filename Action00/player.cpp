//===========================================================================================
//
// [player3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include "player.h"
#include "arrow_around.h"

#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "collision.h"

//�}�N����`
#define SIZE			(D3DXVECTOR2(5.0f, 10.0f))

#define MOVE			(3.5f)			//�ړ���
#define ATT				(0.3f)			//����
#define GRAVITY			(1.0f)			//�d��

//���̈ʒu
#define ARROW_POS		(70.0f)

//�W�����v
#define FILSTJUMP_POWER		(20.4f)			//�W�����v��
#define SECONDJUMP_POWER	(30.0f)			//

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CPlayer::CPlayer(int nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = STATE_NORMAL;
	m_pCamera = nullptr;
	m_pArrowAround = nullptr;
	m_bFirstJump = false;
	m_bSecondJump = false;
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

	// �r���{�[�h(�v���C���[�{��
	CBillboard::Init();
 	SetSize(D3DXVECTOR2(SIZE.x, SIZE.y));
	BindTexture("data\\TEXTURE\\player.png");

	// ���
	// ���ڂ̃W�����v���������߂���
	m_pArrowAround = CArrowAround::Create();	//����
	m_pArrowAround->BindTexture("data\\TEXTURE\\game\\arrow1.png");
	//m_pArrowAround->SetSize(D3DXVECTOR2(10.0f, 20.0f));
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
		m_pArrowAround = nullptr;
	}

	CBillboard::Uninit();

	//�������g�̔j��
	Release();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posOld = pos;
	D3DXVECTOR3 rot = GetRotation();

	//�d��
	m_move.y -= GRAVITY;

	//�n��(0.0f)��艺�ɍs���Ȃ��悤��
	if (pos.y <= SIZE.y)
	{
		pos.y = SIZE.y;
		m_move.y = 0.0f;
		m_bFirstJump = false;
		m_bSecondJump = false;
	}

	if (m_bSecondJump == false)
	{//���ڂ̃W�����v�����ĂȂ��ꍇ

		//�ړ��ʂ��X�V(����������)
		m_move.x += (0.0f - m_move.x) * ATT;

		//����
		InputMove();
	}

	//�ړ��ʂ̑��
	pos += m_move;

	
	if (CollisionObjectX(&pos, &posOld, &m_move, SIZE.y) == true)
	{
		m_bFirstJump = false;
		m_bSecondJump = false;
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

	CBillboard::Draw();

	//���C�e�B���O�̗L��/�����̐ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
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

	//�W�����v���܂Ƃ߂��֐�
	Jump();
}

//===========================================================================================
// �W�����v
//===========================================================================================
void CPlayer::Jump(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//�W�����v�ł��邩�m�F
	if (m_bFirstJump == false && m_bSecondJump == false)
	{//�W�����v���Ă��Ȃ���Ԃ̏ꍇ
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{//�L�[�������ꂽ

			//�ړ��ʂ̏�����
			m_move.y = 0.0f;
			m_move.x = 0.0f;

			m_move.y += FILSTJUMP_POWER;			//���l�����

			m_bFirstJump = true;	//���ڂ̃W�����v���������Ƃɂ���

		}
	}
	if (pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT))
	{//�L�[�������ꂽ

		//�v���C���[�̃X�N���[�����W���擾
		D3DXVECTOR3 screemPos = GetScreenPosition();

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

		m_bSecondJump = true;	//���ڂ̃W�����v���������Ƃɂ���
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
