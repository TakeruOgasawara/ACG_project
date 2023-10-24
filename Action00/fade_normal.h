//======================================================================================
//
//�t�F�[�h�̏���[explosion.h]
//Author;���}���@�V
//
//======================================================================================
#ifndef _FADE_NORMAL_H_
#define _FADE_NORMAL_H_

#include "main.h"
#include "object2D.h"

class CFadeNormal : CObject2D
{
private:
	//�t�F�[�h�̏��
	typedef enum
	{
		STATE_NONE = 0,			//�������Ă��Ȃ����
		STATE_IN,				//�t�F�[�h�C�����
		STATE_OUT,				//�t�F�[�h�A�E�g���
		STATE_MAX
	} STATE;

public:
	CFadeNormal(int nPriority = (NUM_PRIORITY - 1));			//�R���X�g���N�^
	~CFadeNormal();			//�f�X�g���N�^

	static CFadeNormal *Create(void);

	//�v���g�^�C�v�錾
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(STATE state);
	STATE GetState(void) { return m_state; }

private:
	STATE m_state;	//�t�F�[�h�̏��
	D3DXCOLOR m_col;
};

#endif