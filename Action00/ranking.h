//======================================================================================
//
// ランキングの処理[ranking.h]
// Author : Takeru Ogasawara
//
//======================================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene.h"

//前方宣言
class CScore;

class CRanking : public CScene
{
private:
	static const int MAX_RANKING = 5;

public:
	enum RANK
	{
		RANK_NONE = 0,
		RANK_IN,
		RANK_OUT,
		RANK_MAX
	};

public:
	CRanking();
	~CRanking();

	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Save(int* pTime);
	void Load(int* pTime);
	void Sort(int* pTime);

	static CScore* m_apScore[MAX_RANKING];
};

#endif