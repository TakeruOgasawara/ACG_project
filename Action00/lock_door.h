//===============================================================================
//
// [lock_door.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _LOCK_DOOR_H_	//���̃}�N����`������Ă��Ȃ�������
#define _LOCK_DOOR_H_	//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "objectX.h"

//�v���C���[�N���X
class CLockDoor : public CObjectX
{
public:

	enum STATE	//�h�A���
	{
		STATE_STOP = 0,
		STATE_DOWN,
		STATE_MAX
	};

public:
	CLockDoor();
	~CLockDoor();

	static CLockDoor* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_move;
	STATE m_state;
};

#endif