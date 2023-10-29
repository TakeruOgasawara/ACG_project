//======================================================================================
//
// �t�F�[�h����[fade.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "fade_death.h"

//�}�N����`
#define FADE_TIME		(0.02f)			//�t�F�[�h�̊Ԋu
#define START	(30)

//========================================================================
// �R���X�g���N�^
//========================================================================
CFadeDeath::CFadeDeath(int nPriority) : CObject2D(nPriority)
{
	m_state = STATE_NONE;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nStartCnt = 0;
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CFadeDeath::~CFadeDeath()
{

}

//========================================================================
// ����
//========================================================================
CFadeDeath *CFadeDeath::Create(void)
{
	CFadeDeath *pFade = nullptr;

	if (pFade == nullptr)
	{
		pFade = new CFadeDeath;

		if (pFade != nullptr)
		{
			pFade->Init();
			return pFade;
		}
	}

	return pFade;
}

//========================================================================
// ����������(�I�[�o�[���[�h)
//========================================================================
HRESULT CFadeDeath::Init(void)
{
	m_nStartCnt = 0;

	//����
	CObject2D::Init();

	//�ʒu�E�T�C�Y�E�F�̐ݒ�
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSizeCenter(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	SetState(STATE_IN);

	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CFadeDeath::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================================
// �X�V����
//========================================================================
void CFadeDeath::Update(void)
{
	if (m_state != STATE_NONE)
	{
		m_nStartCnt++;

		if (m_nStartCnt < START)
		{
			return;
		}

		if (m_state == STATE_IN)
		{//�t�F�[�h�C�����

			m_col.a -= FADE_TIME;			//�|���S���𓧖��ɂ��Ă���

			if (m_col.a <= 0.0f)
			{
				m_nStartCnt = 0;
				m_col.a = 0.0f;
				m_state = STATE_NONE;				//�������Ă��Ȃ����
			}
		}

		//�F�̔��f
		SetColor(m_col);
	}
}

//========================================================================
// �`�揈��
//========================================================================
void CFadeDeath::Draw(void)
{
	if (m_state != STATE_NONE)
	{
		CObject2D::Draw();
	}
}

//========================================================================
//�t�F�[�h��Ԃ̐ݒ�
//========================================================================
void CFadeDeath::SetState(STATE state)
{
	m_state = state;

	switch (m_state)
	{
	case STATE_NONE:
		m_col.a = 0.0f;
		break;

	case STATE_IN:
		m_col.a = 1.0f;
		break;

	case STATE_OUT:
		m_col.a = 0.0f;
		break;

	default:

		break;
	}

	SetColor(m_col);
}