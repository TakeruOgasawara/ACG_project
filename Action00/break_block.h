//===============================================================================
//
// [break_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _BREAK_BLOCK_H_	//このマクロ定義がされていなかったら
#define _BREAK_BLOCK_H_	//2重インクルード防止のマクロを定義

#include "main.h"
#include "object.h"

//前方宣言
class CObjectX;
class CPlayer;

//プレイヤークラス
class CBreakBlock : public CObject
{
public:

	enum TYPE
	{
		TYPE_BLOCK = 0,
		TYPE_FRAME,
		TYPE_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,	//なし
		STATE_BREAK,	//破壊
		STATE_RECREATE,	//再生
		STATE_MAX
	};

public:
	CBreakBlock(int nPriority = 4);
	~CBreakBlock();

	static CBreakBlock* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定用
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//向き設定
	void SetState(STATE state) { m_state = state; }

	//取得用
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//位置取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//向き取得
	CBreakBlock* GetBreakBlock(void) { return this; }

	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float size);

private:
	void Break(void);
	void ReCeate(void);

	CObjectX* m_pObjectX[TYPE_MAX];
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_SavePos;
	D3DXVECTOR3 m_rot;	//向き
	STATE m_state;
	int m_nDestroyCnt;	//消滅までのカウント
	int m_nReCreateCnt;
	bool m_bBreak;	//破壊フラグ
};

#endif