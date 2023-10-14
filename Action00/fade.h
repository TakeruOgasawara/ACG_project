//======================================================================================
//
//フェードの処理[explosion.h]
//Author;小笠原　彪
//
//======================================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "object2D.h"

//前方宣言
class CObject2D;

class CFade : CObject2D
{
public:
	//フェードの状態
	typedef enum
	{
		STATE_NONE = 0,			//何もしていない状態
		STATE_IN,				//フェードイン状態
		STATE_OUT,				//フェードアウト状態
		STATE_MAX
	} STATE;

public:
	CFade(int nPriority = (NUM_PRIORITY - 1));			//コンストラクタ
	~CFade();			//デストラクタ

	static CFade *Create(CScene::MODE mode);

	//プロトタイプ宣言
	HRESULT Init(CScene::MODE modeNext);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(CScene::MODE modeNext);
	void SetState(STATE state);
	STATE GetState(void) { return m_state; }

private:
	STATE m_state;						//フェードの状態
	CScene::MODE m_modeNext;			//次の画面(モード)
	D3DXCOLOR m_col;
};

#endif