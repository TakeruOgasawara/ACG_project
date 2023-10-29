//===========================================================================================
//
// [time.cpp]m_aChain[0]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "time.h"
#include "object2D.h"
#include "number.h"

//�}�N����`
#define AIDA			(50.0f)
#define START_TIME		(30000)

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CTime::CTime()
{
	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
	m_pPeriod = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTimeCount = 0;
	m_nTime = 0;
	m_dwGameStartTime = 0;	//�Q�[���J�n����
	m_dwGameTime = 0;	//�Q�[���o�ߎ���
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CTime::~CTime()
{

}

//===========================================================================================
// ����
//===========================================================================================
CTime* CTime::Create(D3DXVECTOR3 pos)
{
	CTime* pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;

		if (pTime != NULL)
		{
			pTime->Init(pos);

			return pTime;
		}
		else
		{
			return NULL;
		}
	}

	return NULL;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	m_nTimeCount = START_TIME;

	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(pos);

		m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + (AIDA * nCnt), m_pos.y, 0.0f));
		m_apNumber[nCnt]->SetSize(20.0f, 30.0f);
	}

	/*m_pPeriod = CObject2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f));
	m_pPeriod->SetSizeCenter(10.0f, 10.0f);
	m_pPeriod->BindTexture();*/

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CTime::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = nullptr;
		}
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CTime::Update()
{
	SetTime();
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CTime::Draw()
{
	/*for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}*/
}

//===========================================================================================
// �^�C���̐ݒ�
//===========================================================================================
void CTime::SetTime(void)
{
	int aTexU[NUM_TIME];			//�e���̐������i�[

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//�o�ߎ��Ԃ̎Z�o
	m_dwGameTime = timeGetTime() - m_dwGameStartTime;

	if (m_dwGameTime %= 1000)
	{
		m_nTimeCount--;
	}

	aTexU[0] = m_nTimeCount % 100000 / 10000;
	aTexU[1] = m_nTimeCount % 10000 / 1000;
	aTexU[2] = m_nTimeCount % 1000 / 100;
	aTexU[3] = m_nTimeCount % 100 / 10;
	aTexU[4] = m_nTimeCount % 10 / 1;

	for (int nCntScore = 0; nCntScore < NUM_TIME; nCntScore++)
	{
		if (m_apNumber[nCntScore] != NULL)
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
// �^�C���̉��Z(�A�C�e������������ȂǍ��͎g���)
//===========================================================================================
void CTime::AddTime(int nValue)
{
	m_nTimeCount += nValue;
}

//===========================================================================================
// �^�C���̎擾
//===========================================================================================
int CTime::GetTime(void)
{
	return m_nTimeCount;
}
