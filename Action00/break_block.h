//===============================================================================
//
// [break_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _BREAK_BLOCK_H_	//���̃}�N����`������Ă��Ȃ�������
#define _BREAK_BLOCK_H_	//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "objectX.h"

//�O���錾
//class CObjectX;

//�v���C���[�N���X
class CBreakBlock : public CObjectX
{
private:

	enum TYPE
	{
		TYPE_BLOCK = 0,
		TYPE_FRAME,
		TYPE_MAX
	};

public:
	CBreakBlock();
	~CBreakBlock();

	static CBreakBlock* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	////�ݒ�p
	//void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	//void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//�����ݒ�

	////�擾�p
	//D3DXVECTOR3 GetPosition(void) { return m_pos; }	//�ʒu�擾
	//D3DXVECTOR3 GetRotation(void) { return m_rot; }	//�����擾

private:
	CObjectX* m_pObjectX[TYPE_MAX];
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	int m_nDestroyTime;	//���ł܂ł̃J�E���g
};

#endif