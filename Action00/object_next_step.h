//===============================================================================
//
// [break_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _NEXT_STEP_H_	//このマクロ定義がされていなかったら
#define _NEXT_STEP_H_	//2重インクルード防止のマクロを定義

#include "main.h"
#include "objectX.h"

//前方宣言
//class CObjectX;

//プレイヤークラス
class CNextStep : public CObjectX
{
public:
	CNextStep();
	~CNextStep();

	static CNextStep* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CNextStep* GetNextStep(void) { return this; }
	bool GetTach(void) { return m_bTach; }
	bool Collision(D3DXVECTOR3 pos, float size);

private:

	bool m_bTach;
};

#endif