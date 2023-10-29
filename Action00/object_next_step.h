//===============================================================================
//
// [break_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _NEXT_STEP_H_	//���̃}�N����`������Ă��Ȃ�������
#define _NEXT_STEP_H_	//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "objectX.h"

//�O���錾
//class CObjectX;

//�v���C���[�N���X
class CNextStep : public CObjectX
{
public:
	CNextStep();
	~CNextStep();

	static CNextStep* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CNextStep* GetNextStep(void) { return this; }
	bool GetTach(void) { return m_bTach; }
	bool Collision(D3DXVECTOR3 pos, float size);

private:

	bool m_bTach;
};

#endif