//======================================================================================
//
// �t�F�[�h����[fade.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "fade_normal.h"

//�}�N����`
#define FADE_TIME		(0.025f)			//�t�F�[�h�̊Ԋu

//========================================================================
// �R���X�g���N�^
//========================================================================
CFadeNormal::CFadeNormal(int nPriority) : CObject2D(nPriority)
{
	m_state = STATE_NONE;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CFadeNormal::~CFadeNormal()
{

}

//========================================================================
// ����
//========================================================================
CFadeNormal *CFadeNormal::Create(void)
{
	CFadeNormal *pFade = nullptr;

	if (pFade == nullptr)
	{
		pFade = new CFadeNormal;

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
HRESULT CFadeNormal::Init(void)
{
	//����
	CObject2D::Init();

	//�ʒu�E�T�C�Y�E�F�̐ݒ�
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSize_center(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	//SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	SetState(STATE_IN);

	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CFadeNormal::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================================
// �X�V����
//========================================================================
void CFadeNormal::Update(void)
{
	if (m_state != STATE_NONE)
	{
		if (m_state == STATE_IN)
		{//�t�F�[�h�C�����

			m_col.a -= FADE_TIME;			//�|���S���𓧖��ɂ��Ă���

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_state = STATE_NONE;				//�������Ă��Ȃ����
			}
		}
		else if (m_state == STATE_OUT)
		{//�t�F�[�h�A�E�g���
			m_col.a += FADE_TIME;			//�|���S����s�����ɂ��Ă���

			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;

				return;
			}
		}
		
		//�F�̔��f
		SetColor(m_col);
	}
}

//========================================================================
// �`�揈��
//========================================================================
void CFadeNormal::Draw(void)
{
	if (m_state != STATE_NONE)
	{
		CObject2D::Draw();
	}
}

//========================================================================
// �ݒ菈��
//========================================================================
//void CFadeNormal::Set(CScene::MODE modeNext)
//{
//	if (m_state != STATE_OUT)
//	{
//		m_state = STATE_OUT;			//�t�F�[�h�A�E�g���
//		m_modeNext = modeNext;			//���̉��(���[�h)��ݒ�
//		m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//}

//========================================================================
//�t�F�[�h��Ԃ̐ݒ�
//========================================================================
void CFadeNormal::SetState(STATE state)
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