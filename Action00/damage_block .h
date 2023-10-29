//===============================================================================
//
// [damage_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _DAMAGE_BLOCK_H_	//���̃}�N����`������Ă��Ȃ�������
#define _DAMAGE_BLOCK_H_	//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "objectX.h"

//�v���C���[�N���X
class CDamageBlock : public CObjectX
{
public:
	CDamageBlock();
	~CDamageBlock();

	static CDamageBlock* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�p
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//�����ݒ�

	//�擾�p
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//�����擾
	CDamageBlock* GetDamageBlock(void) { return this; }

	bool Collision(D3DXVECTOR3 pos, float size);

private:

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
};

#endif