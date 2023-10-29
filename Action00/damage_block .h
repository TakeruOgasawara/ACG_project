//===============================================================================
//
// [damage_block.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _DAMAGE_BLOCK_H_	//このマクロ定義がされていなかったら
#define _DAMAGE_BLOCK_H_	//2重インクルード防止のマクロを定義

#include "main.h"
#include "objectX.h"

//プレイヤークラス
class CDamageBlock : public CObjectX
{
public:
	CDamageBlock();
	~CDamageBlock();

	static CDamageBlock* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定用
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//向き設定

	//取得用
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//位置取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//向き取得
	CDamageBlock* GetDamageBlock(void) { return this; }

	bool Collision(D3DXVECTOR3 pos, float size);

private:

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
};

#endif