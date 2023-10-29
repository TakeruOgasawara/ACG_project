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

//マクロ定義
#define MAX_NUMSCORE			(8)

//ナンバークラス
class CScore
{
public:
	CScore();
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void SetScore(void);
	void AddScore(int nValue);

private:
	static CNumber *m_apNumber[MAX_NUMSCORE];
	static D3DXVECTOR3 m_pos;
	static int m_nScore;
};

#endif