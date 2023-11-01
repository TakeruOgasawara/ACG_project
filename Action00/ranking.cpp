//======================================================================================
//
// ランキング処理[ranking.cpp]
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
// マクロ定義
//*****************************
#define RANKING_FILE	"ranking.bin"
#define MAX_TEX				(2)				//テクスチャ―の最大数
#define NUM_PLACE			(8)				//スコアの桁数
#define MAX_RANK			(5)				//表示するランキングの最大数

#define RANK_AIDA_WIDTH		(40.0f)			//数字の横間隔
#define RANK_AIDA_HEIGHT	(80.0f)			//数字の縦間隔
#define RANK_SIZE_WIDTH		(40.0f)			//数字の大きさ(x)
#define RANK_SIZE_HEIGHT	(60.0f)			//数字の大きさ(y)

//*****************************
// 静的メンバ変数宣言
//*****************************
CScore* CRanking::m_apScore[MAX_RANKING] = {};

//========================================================================
// コンストラクタ
//========================================================================
CRanking::CRanking()
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_apScore[nCnt] = nullptr;
	}
}

//========================================================================
// デストラクタ
//========================================================================
CRanking::~CRanking()
{
}
//========================================================================
// 初期化
//========================================================================
HRESULT CRanking::Init(void)
{
	D3DXVECTOR3 pos = { 0.0f, 0.0f, 0.0f };
	int aTime[MAX_RANKING] = {};

	Load(&aTime[0]);

	Sort(&aTime[0]);

	//スコアの表示
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(pos.x , pos.y + (10 * nCnt), 0.0f));
		m_apScore[nCnt]->AddScore(aTime[nCnt]);
	}

	return S_OK;
}

//========================================================================
// 終了
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
// 更新
//========================================================================
void CRanking::Update(void)
{

}

//========================================================================
// 描画
//========================================================================
void CRanking::Draw(void)
{

}

//========================================================================
// 書き込み
//========================================================================
void CRanking::Save(int* pTime)
{
	////ファイルポインタを宣言
	//FILE* pFile;

	//pFile = fopen(RANKING_FILE, "wb");

	//if (pFile != NULL)
	//{//ファイルが開けた場合
	//	//バイナリファイルにセーブ
	//	fwrite(&pTime[0], sizeof(int), MAX_RANK, pFile);

	//	//ファイルを閉じる
	//	fclose(pFile);
	//}
	FILE* pFile = nullptr;

	//ファイルを開く
	pFile = fopen("data\\ranking.txt", "r");

	if (pFile == nullptr)
	{
		return;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		fscanf(pFile, "%d", &pTime[nCnt]);
	}

	//ファイルを閉じる
	fclose(pFile);
}

//========================================================================
// 読み込み
//========================================================================
void CRanking::Load(int* pTime)
{
	////ファイルポインタを宣言
	//FILE* pFile;

	//pFile = fopen(RANKING_FILE, "rb");

	//if (pFile != nullptr)
	//{//ファイルが開けた場合
	//	//バイナリファイルからロード

	//	fread(&pTime[0], sizeof(int), MAX_RANK, pFile);

	//	//ファイルを閉じる
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

	//ファイルを開く
	pFile = fopen("data\\ranking.txt", "r");

	if (pFile == nullptr)
	{
		return;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++, pTime++)
	{
		fscanf(pFile, "%d", &pTime[0]);

	}

	//ファイルを閉じる
	fclose(pFile);
}

//========================================================================
// 降順ソート
//========================================================================
void CRanking::Sort(int* pTime)
{
	for (int nCntFst = 0; nCntFst < MAX_RANKING - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// 仮の一番大きい番号

		for (int nCntSec = nCntFst + 1; nCntSec < MAX_RANKING; nCntSec++)
		{
			if (pTime[nCntSec] > pTime[nTempNum])
			{// 値が大きい場合
				nTempNum = nCntSec;	// 大きい番号を変更
			}
		}

		if (nTempNum != nCntFst)
		{// 変更する場合
			int nTemp = pTime[nCntFst];
			pTime[nCntFst] = pTime[nTempNum];
			pTime[nTempNum] = nTemp;
		}
	}
}
