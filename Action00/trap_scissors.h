//===============================================================================
//
// [damage_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TRAP_SCISSORS_H_	//このマクロ定義がされていなかったら
#define _TRAP_SCISSORS_H_	//2重インクルード防止のマクロを定義

#include "main.h"
#include "object.h"

#include "objectX.h"

//プレイヤークラス
class CTrapScissors : public CObject
{
private:
	enum MODEL
	{
		MODEL_MAIN = 0,
		MODEL_BLADE1,
		MODEL_BLADE2,
		MODEL_MAX
	};

	enum STATE
	{
		STATE_WAIT = 0,	//待ち
		STATE_ATTACK,
		STATE_END,
		STATE_MAX
	};

	struct Model
	{
		CObjectX* pModel;
		D3DXVECTOR3 rot;
	};

public:
	CTrapScissors();
	~CTrapScissors();

	static CTrapScissors* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定用
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//向き設定

	//取得用
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//位置取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//向き取得
	CTrapScissors* GetTrapScissors(void) { return this; }

	bool Collision(D3DXVECTOR3 pos, float size);

private:
	void BladeMove(void);

	Model m_aModel[MODEL_MAX];
	CObjectX* m_pFlagObject;
	STATE m_state;

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
};

#endif