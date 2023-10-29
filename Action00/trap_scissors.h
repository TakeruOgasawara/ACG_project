//===============================================================================
//
// [damage_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TRAP_SCISSORS_H_	//���̃}�N����`������Ă��Ȃ�������
#define _TRAP_SCISSORS_H_	//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "object.h"

#include "objectX.h"

//�v���C���[�N���X
class CTrapScissors : public CObject
{
private:
	enum MODEL
	{
		MODEL_MAIN = 0,
		MODEL_BLADE1,
		MODEL_BLADE2,
		MODEL_MAX
	};

	enum STATE
	{
		STATE_WAIT = 0,	//�҂�
		STATE_ATTACK,
		STATE_END,
		STATE_MAX
	};

	struct Model
	{
		CObjectX* pModel;
		D3DXVECTOR3 rot;
	};

public:
	CTrapScissors();
	~CTrapScissors();

	static CTrapScissors* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�p
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//�����ݒ�

	//�擾�p
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//�����擾
	CTrapScissors* GetTrapScissors(void) { return this; }

	bool Collision(D3DXVECTOR3 pos, float size);

private:
	void BladeMove(void);

	Model m_aModel[MODEL_MAX];
	CObjectX* m_pFlagObject;
	STATE m_state;

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
};

#endif