//===============================================================================
//
// [player3D.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _PLAYER_H_				//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "billboard.h"

//�O���錾
class CCollision;
class CCamera;
class CArrowAround;
class CObject2D;

//�v���C���[�N���X
class CPlayer : public CBillboard
{
public:
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_RUN,
		STATE_DEATH,
		STATE_RETRY,
		STATE_MAX
	};

public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer *Create(D3DXVECTOR3 pos);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�p
	void SetState(STATE state) { m_state = state; }
	void SetMovement(D3DXVECTOR3 move) { m_move = move; }
	void SetMoveX(float x) { m_move.x = x; }
	void SetMoveY(float y) { m_move.y = y; }
	void SetMoveZ(float z) { m_move.z = z; }
	void SetFirstJamp(bool bJamp) { m_bFirstJump = bJamp; }
	void SetSecondJamp(bool bJamp) { m_bSecondJump = bJamp; }

	//�擾�p
	D3DXVECTOR3 GetPosisionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	STATE GetState(void) { return m_state; }
	bool GetFirstJamp(void) { return m_bFirstJump; }
	bool GetSecondJamp(void) { return m_bSecondJump; }

private:
	//�֐�
	void InputMove(void);	//�s������
	void Jump(void);	//�W�����v���܂Ƃ߂�
	void Arrow(D3DXVECTOR3 pos);	//���
	D3DXVECTOR3 GetScreenPosition(void);	//�X�N���[����̈ʒu

	//�ϐ�
	D3DXVECTOR3 m_posOld;	//�ߋ��ʒu
	D3DXVECTOR3 m_move;	//�ړ���
	bool m_bFirstJump;	//���ڂ̃W�����v��������
	bool m_bSecondJump;	//���ڂ̃W�����v��������
	STATE m_state;	//���

	//���v���W�F�N�g����
	CCollision *m_pCollision;	//�����蔻��
	CCamera *m_pCamera;	//�J����
	CArrowAround *m_pArrowAround;	//���
	CObject2D* m_pObject2D;	//2D�|���S��
};

#endif