//======================================================================================
//
//フェードの処理[explosion.h]
//Author;小笠原　彪
//
//======================================================================================
#ifndef _FADE_NORMAL_H_
#define _FADE_NORMAL_H_

#include "main.h"
#include "object2D.h"

class CFadeNormal : CObject2D
{
private:
	//フェードの状態
	typedef enum
	{
		STATE_NONE = 0,			//何もしていない状態
		STATE_IN,				//フェードイン状態
		STATE_OUT,				//フェードアウト状態
		STATE_MAX
	} STATE;

public:
	CFadeNormal(int nPriority = (NUM_PRIORITY - 1));			//コンストラクタ
	~CFadeNormal();			//デストラクタ

	static CFadeNormal *Create(void);

	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetState(STATE state);
	STATE GetState(void) { return m_state; }

private:
	STATE m_state;	//フェードの状態
	D3DXCOLOR m_col;
};

#endif