//===========================================================================================
//
// ���U���g���[title.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "fade.h"
#include "score.h"
#include "time.h"

#include <stdio.h>

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CResult::CResult()
{
	m_pBg2D = nullptr;

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		m_pUi2D[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pRanking[nCnt] = nullptr;
	}

	m_pScore = nullptr;
	m_nTextureIdx = 0;
	m_nRank = 0;
	m_nResultCnt = 0;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CResult::~CResult()
{

}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CResult::Init(void)
{
	int aTime[5] = {};
	int nMinute = 0, nSecond = 0;
	int nSum = 0;
	int nMinute1[5] = {};
	int nSecond1[5] = {};

	CManager::GetInstance()->GetCurrentTim(&nMinute, &nSecond);

	int nSumMinute = 20000 - nMinute;
	int nSumSecond = 6000 - nSecond;

	nSum = nSumMinute + nSumSecond;

	nMinute = 0;
	nSecond = 0;

	if (nSum >= 20000)
	{
		nMinute = 2;
		nSecond = nSum - 20000;
	}
	else if (nSum >= 10000)
	{
		nMinute = 1;
		nSecond = nSum - 10000;
	}
	else if (nSum >= 1)
	{
		nSecond = nSum;
	}
	else
	{
		nSecond = 0;
	}

	//�����L���O�ǂݍ���
	Load(&aTime[0]);

	//�~���\�[�g
	Sort(&aTime[0]);

	//�C��
	RankingIn(&aTime[0], nSum);

	//�Z�[�u
	Save(&aTime[0]);

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (aTime[nCnt] >= 20000)
		{
			nMinute1[nCnt] = 2;
			nSecond1[nCnt] = aTime[nCnt] - 20000;
		}
		else if (aTime[nCnt] >= 10000)
		{
			nMinute1[nCnt] = 1;
			nSecond1[nCnt] = aTime[nCnt] - 10000;
		}
		else if (aTime[nCnt] >= 1)
		{
			nSecond1[nCnt] = aTime[nCnt];
		}
		else
		{
			nSecond1[nCnt] = 0;
		}
	}

	/*m_pBg2D = CObject2D::Create(3);
	m_pBg2D->SetSizeCenter(640.0f, 360.0f);
	m_pBg2D->BindTexture(m_nTextureIdx);*/

	// UI : ���Ȃ��̃^�C��
	m_pUi2D[YOUR_NAME] = CObject2D::Create(D3DXVECTOR3(200.0f, 100.0f, 0.0f));
	m_pUi2D[YOUR_NAME]->SetSizeCenter(170.0f, 50.0f);
	m_pUi2D[YOUR_NAME]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\0_yourTime.png"));

	// UI : �����N
	m_pUi2D[RANK_FONT] = CObject2D::Create(D3DXVECTOR3(200.0f, 250.0f, 0.0f));
	m_pUi2D[RANK_FONT]->SetSizeCenter(60.0f, 30.0f);
	m_pUi2D[RANK_FONT]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\rankFont.png"));

	// UI : �����N�ԍ�
	m_pUi2D[RANK] = CObject2D::Create(D3DXVECTOR3(m_pUi2D[RANK_FONT]->GetPosition().x - 30.0f, m_pUi2D[RANK_FONT]->GetPosition().y + 250.0f, 0.0f));
	m_pUi2D[RANK]->SetSizeCenter(25.0f, 200.0f);
	m_pUi2D[RANK]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\rankingNumber.png"));

	// UI : �^�C��
	m_pUi2D[TIME] = CObject2D::Create(D3DXVECTOR3(1000.0f, 250.0f, 0.0f));
	m_pUi2D[TIME]->SetSizeCenter(60.0f, 30.0f);
	m_pUi2D[TIME]->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\timeFont.png"));

	// �X�R�A
	m_pScore = CTime::Create(D3DXVECTOR3(400.0f, 120.0f, 0.0f));
	m_pScore->AddTime(nMinute, nSecond);
	m_pScore->SetState(CTime::STATE_END);
	m_pScore->SetTime();

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pRanking[nCnt] = CTime::Create(D3DXVECTOR3(880.0f, 330.0f + (85.0f) * nCnt, 0.0f));
		m_pRanking[nCnt]->AddTime(nMinute1[nCnt], nSecond1[nCnt]);
		m_pRanking[nCnt]->SetState(CTime::STATE_END);
		m_pRanking[nCnt]->SetTime();

	/*	if (m_nRank == nCnt)
		{
			m_pRanking[nCnt]->Set
		}*/
	}

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CResult::Uninit(void)
{
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (m_pUi2D[nCnt] == nullptr)
		{
			m_pUi2D[nCnt]->Uninit();
			m_pUi2D[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pRanking[nCnt]->Uninit();
		delete m_pRanking[nCnt];
		m_pRanking[nCnt] = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pJoyPad = CManager::GetInstance()->GetInputJoyPad();

	// �^�C�g���ɖ߂�܂łɃJ�E���g
	m_nResultCnt++;

	if (pInputKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->BUTTON_A, 0) || m_nResultCnt > 600)
	{
		CManager::GetInstance()->GetFade()->SetMode(MODE_TITLE);
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
	}

	CScene::Update();
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CResult::Draw(void)
{
	if (m_pScore != nullptr)
	{
		m_pScore->Draw();
	}

	CScene::Draw();
}

//===========================================================================================
// �ǂݍ���
//===========================================================================================
void CResult::Load(int* pTime)
{
	FILE* pFile = nullptr;

	//�t�@�C�����J��
	pFile = fopen("data\\ranking.txt", "r");

	if (pFile == nullptr)
	{
		return;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++, pTime++)
	{
		fscanf(pFile, "%d", &pTime[0]);

	}

	//�t�@�C�������
	fclose(pFile);
}

//===========================================================================================
// �~���\�[�g
//===========================================================================================
void CResult::Sort(int* pTime)
{
	for (int nCnt1 = 0; nCnt1 < 5 - 1; nCnt1++)
	{
		int nTempNum = nCnt1;

		for (int nCnt2 = nCnt1 + 1; nCnt2 < 5; nCnt2++)
		{
			if (pTime[nCnt2] < pTime[nTempNum])
			{// �l���傫���ꍇ
				nTempNum = nCnt2;
			}
		}

		if (nTempNum != nCnt1)
		{// �ύX����ꍇ
			int nTemp = pTime[nCnt1];
			pTime[nCnt1] = pTime[nTempNum];
			pTime[nTempNum] = nTemp;
		}
	}
}

//===========================================================================================
// ��������
//===========================================================================================
void CResult::Save(int* pTime)
{
	FILE* pFile = nullptr;

	//�t�@�C�����J��
	pFile = fopen("data\\ranking.txt", "w");

	if (pFile == nullptr)
	{
		return;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		fprintf(pFile, "%d\n", pTime[nCnt]);
	}

	//�t�@�C�������
	fclose(pFile);
}

//===============================================
// �����L���O�C���m�F
//===============================================
void CResult::RankingIn(int* pTime, int nResult)
{
	if (nResult < pTime[5 - 1] || pTime[5 - 1] == 0)
	{
		pTime[5 - 1] = nResult;

		// �\�[�g����
		Sort(pTime);

		// �ۑ�����
		Save(pTime);

		//�����N�C���������ʂ��m�F����
		for (int nCntRank = 0; nCntRank < 5; nCntRank++)
		{
			if (pTime[nCntRank] == nResult)
			{
				m_nRank = nCntRank;	// �����N�C���������ʂ�ۑ�			
				break;
			}
		}
	}
}
