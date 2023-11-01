//===============================================================================
//
// [score.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _SCORE_H_				//このマクロ定義がされていなかったら
#define _SCORE_H_				//2重インクルード帽子のマクロを定義

#include "main.h"
#include "number.h"

//スコアクラス
class CScore
{
public:
	static const int MAX_SCORE = 5;

public:
	CScore();
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void AddScore(int nValue);

private:
	void SetScore(void);

	CNumber *m_apNumber[MAX_SCORE];
	D3DXVECTOR3 m_pos;
	int m_nScore;
};

#endif