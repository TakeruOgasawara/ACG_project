//======================================================================================
//
// �����L���O����[ranking.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "main.h"
#include "ranking.h"
#include "time.h"
#include "input.h"
#include "fade.h"
#include "score.h"

#include <stdio.h>
#include <assert.h>

//*****************************
// �}�N����`
//*****************************
#define RANKING_FILE	"ranking.bin"
#define MAX_TEX				(2)				//�e�N�X�`���\�̍ő吔
#define NUM_PLACE			(8)				//�X�R�A�̌���
#define MAX_RANK			(5)				//�\�����郉���L���O�̍ő吔

#define RANK_AIDA_WIDTH		(40.0f)			//�����̉��Ԋu
#define RANK_AIDA_HEIGHT	(80.0f)			//�����̏c�Ԋu
#define RANK_SIZE_WIDTH		(40.0f)			//�����̑傫��(x)
#define RANK_SIZE_HEIGHT	(60.0f)			//�����̑傫��(y)

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CScore* CRanking::m_apScore[MAX_RANKING] = {};

//========================================================================
// �R���X�g���N�^
//========================================================================
CRanking::CRanking()
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_apScore[nCnt] = nullptr;
	}
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CRanking::~CRanking()
{
}
//========================================================================
// ������
//========================================================================
HRESULT CRanking::Init(void)
{
	D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };
	int aTime[MAX_RANKING] = {};

	Load(&aTime[0]);

	Sort(&aTime[0]);

	//�X�R�A�̕\��
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x , pos.y + (10 * nCnt), 0.0f));
		m_apScore[nCnt]->AddScore(aTime[nCnt]);
	}

	return S_OK;
}

//========================================================================
// �I��
//========================================================================
void CRanking::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_apScore[nCnt]->Uninit();
		m_apScore[nCnt] = nullptr;
	}
}

//========================================================================
// �X�V
//========================================================================
void CRanking::Update(void)
{

}

//========================================================================
// �`��
//========================================================================
void CRanking::Draw(void)
{

}

//========================================================================
// ��������
//========================================================================
void CRanking::Save(int* pTime)
{
	////�t�@�C���|�C���^��錾
	//FILE* pFile;

	//pFile = fopen(RANKING_FILE, "wb");

	//if (pFile != NULL)
	//{//�t�@�C�����J�����ꍇ
	//	//�o�C�i���t�@�C���ɃZ�[�u
	//	fwrite(&pTime[0], sizeof(int), MAX_RANK, pFile);

	//	//�t�@�C�������
	//	fclose(pFile);
	//}
	FILE* pFile = nullptr;

	//�t�@�C�����J��
	pFile = fopen("data\\ranking.txt", "r");

	if (pFile == nullptr)
	{
		return;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		fscanf(pFile, "%d", &pTime[nCnt]);
	}

	//�t�@�C�������
	fclose(pFile);
}

//========================================================================
// �ǂݍ���
//========================================================================
void CRanking::Load(int* pTime)
{
	////�t�@�C���|�C���^��錾
	//FILE* pFile;

	//pFile = fopen(RANKING_FILE, "rb");

	//if (pFile != nullptr)
	//{//�t�@�C�����J�����ꍇ
	//	//�o�C�i���t�@�C�����烍�[�h

	//	fread(&pTime[0], sizeof(int), MAX_RANK, pFile);

	//	//�t�@�C�������
	//	fclose(pFile);
	//}
	//else
	//{
	//	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	//	{
	//		pTime[nCnt] = 0;
	//	}
	//}

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

//========================================================================
// �~���\�[�g
//========================================================================
void CRanking::Sort(int* pTime)
{
	for (int nCntFst = 0; nCntFst < MAX_RANKING - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// ���̈�ԑ傫���ԍ�

		for (int nCntSec = nCntFst + 1; nCntSec < MAX_RANKING; nCntSec++)
		{
			if (pTime[nCntSec] > pTime[nTempNum])
			{// �l���傫���ꍇ
				nTempNum = nCntSec;	// �傫���ԍ���ύX
			}
		}

		if (nTempNum != nCntFst)
		{// �ύX����ꍇ
			int nTemp = pTime[nCntFst];
			pTime[nCntFst] = pTime[nTempNum];
			pTime[nTempNum] = nTemp;
		}
	}
}
