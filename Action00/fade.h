//======================================================================================
//
//�t�F�[�h�̏���[explosion.h]
//Author;���}���@�V
//
//======================================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "object2D.h"

//�O���錾
class CObject2D;

class CFade : CObject2D
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		STATE_NONE = 0,			//�������Ă��Ȃ����
		STATE_IN,				//�t�F�[�h�C�����
		STATE_OUT,				//�t�F�[�h�A�E�g���
		STATE_MAX
	} STATE;

public:
	CFade(int nPriority = (NUM_PRIORITY - 1));			//�R���X�g���N�^
	~CFade();			//�f�X�g���N�^

	static CFade *Create(CScene::MODE mode);

	//�v���g�^�C�v�錾
	HRESULT Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CScene::MODE modeNext);
	void SetState(STATE state);
	STATE GetState(void) { return m_state; }

private:
	STATE m_state;						//�t�F�[�h�̏��
	CScene::MODE m_modeNext;			//���̉��(���[�h)
	D3DXCOLOR m_col;
};

#endif