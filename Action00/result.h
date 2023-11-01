//===============================================================================
//
// リザルト画面[result.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _RESULT_H_				//このマクロ定義がされていなかったら
#define _RESULT_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "manager.h"

//前方宣言
class CObject2D;
class CScore;
class CTime;

//タイトルクラス
class CResult : public CScene
{
private:

	enum EUI	//UIの種類
	{
		YOUR_NAME = 0,
		RANK_FONT,
		RANK,
		TIME,
		UI_MAX
	};

public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Save(int* pTime);
	void Load(int* pTime);
	void Sort(int* pTime);
	void RankingIn(int* pTime, int nResult);
	int m_nRank;

	int m_nTextureIdx;	//テクスチャへの頂点情報
	int m_nResultCnt;
	CObject2D* m_pBg2D;
	CObject2D* m_pUi2D[UI_MAX];
	CTime* m_pScore;
	CTime* m_pRanking[5];
};

#endif