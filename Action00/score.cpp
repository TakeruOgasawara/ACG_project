//===========================================================================================
//
// [score.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "score.h"
#include "object2D.h"

//�}�N����`
#define SPACE	(30.0f)
#define SIZE_X	(20.0f)
#define SIZE_Y	(25.0f)

//�ÓI�����o�ϐ��錾
CNumber *CScore::m_apNumber[MAX_NUMSCORE] = {};
D3DXVECTOR3 CScore::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CScore::m_nScore = 0;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CScore::CScore()
{
	m_nScore = 0;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CScore::~CScore()
{

}

//===========================================================================================
// ����
//===========================================================================================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = nullptr;

	if (pScore == nullptr)
	{
		pScore = new CScore;

		if (pScore != nullptr)
		{
			m_pos = pos;

			pScore->Init();

			return pScore;
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CScore::Init()
{
	for (int nCnt = 0; nCnt < MAX_NUMSCORE; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(m_pos.x + (SPACE * nCnt), m_pos.y, 0.0f));
		m_apNumber[nCnt]->SetSize(SIZE_X, SIZE_Y);
	}

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CScore::Uninit()
{
	for (int nCnt = 0; nCnt < MAX_NUMSCORE; nCnt++)
	{
		m_apNumber[nCnt]->Uninit();
		delete m_apNumber[nCnt];
		m_apNumber[nCnt] = nullptr;
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CScore::Update()
{
	SetScore();
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CScore::Draw()
{
	for (int nCnt = 0; nCnt < m_nScore; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//===========================================================================================
// 
//===========================================================================================
void CScore::SetScore(void)
{
	int aTexU[MAX_NUMSCORE];			//�e���̐������i�[

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	aTexU[0] = m_nScore % 100000000 / 100000;
	aTexU[1] = m_nScore % 10000000 / 100000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10 / 1;

	for (int nCntScore = 0; nCntScore < MAX_NUMSCORE; nCntScore++)
	{
		if (m_apNumber[nCntScore] != nullptr)
		{
			//���_�o�b�t�@�����b�N
			m_apNumber[nCntScore]->GetObject2D()->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(aTexU[nCntScore] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(aTexU[nCntScore] * 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(aTexU[nCntScore] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(aTexU[nCntScore] * 0.1f + 0.1f, 1.0f);

			//���_�o�b�t�@���A�����b�N����
			m_apNumber[nCntScore]->GetObject2D()->GetVtxBuff()->Unlock();
		}
	}
}

//===========================================================================================
// �X�R�A���Z
//===========================================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}