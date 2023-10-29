//===============================================================================
//
// [break_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _BREAK_BLOCK_H_	//���̃}�N����`������Ă��Ȃ�������
#define _BREAK_BLOCK_H_	//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "object.h"

//�O���錾
class CObjectX;
class CPlayer;

//�v���C���[�N���X
class CBreakBlock : public CObject
{
public:

	enum TYPE
	{
		TYPE_BLOCK = 0,
		TYPE_FRAME,
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,	//�Ȃ�
		STATE_BREAK,	//�j��
		STATE_RECREATE,	//�Đ�
		STATE_MAX
	};

public:
	CBreakBlock(int nPriority = 4);
	~CBreakBlock();

	static CBreakBlock* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�p
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//�����ݒ�
	void SetState(STATE state) { m_state = state; }

	//�擾�p
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//�����擾
	CBreakBlock* GetBreakBlock(void) { return this; }

	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float size);

private:
	void Break(void);
	void ReCeate(void);

	CObjectX* m_pObjectX[TYPE_MAX];
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_SavePos;
	D3DXVECTOR3 m_rot;	//����
	STATE m_state;
	int m_nDestroyCnt;	//���ł܂ł̃J�E���g
	int m_nReCreateCnt;
	bool m_bBreak;	//�j��t���O
};

#endif