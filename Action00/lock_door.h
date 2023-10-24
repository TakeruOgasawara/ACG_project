//===============================================================================
//
// [lock_door.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _LOCK_DOOR_H_	//このマクロ定義がされていなかったら
#define _LOCK_DOOR_H_	//2重インクルード防止のマクロを定義

#include "main.h"
#include "objectX.h"

//プレイヤークラス
class CLockDoor : public CObjectX
{
public:

	enum STATE	//ドア状態
	{
		STATE_STOP = 0,
		STATE_DOWN,
		STATE_MAX
	};

public:
	CLockDoor();
	~CLockDoor();

	static CLockDoor* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_move;
	STATE m_state;
};

#endif