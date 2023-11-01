//===============================================================================
//
// [time.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TIME_H_				//このマクロ定義がされていなかったら
#define _TIME_H_				//2重インクルード帽子のマクロを定義

#include "main.h"

//**********************************
// 前方宣言
//**********************************
class CNumber;
class CObject2D;

//ナンバークラス
class CTime
{
public:

	enum STATE
	{
		STATE_NONE = 0,
		STATE_COUNT,
		STATE_STOP,
		STATE_END,
		STATE_MAX
	};

private:	//定数(マクロ的な役割)

	static const int NUM_TIME = 5;

public:
	CTime();	//コンストラクタ
	~CTime();	//デストラクタ

	static CTime* Create(D3DXVECTOR3 pos);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	void SetTime(void);
	void AddTime(int nMinute, int nSecond);

	int GetTime(void);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	STATE GetState(void) { return m_state; }

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetState(STATE state) { m_state = state; }

private:
	CNumber* m_apNumber[NUM_TIME];
	CObject2D* m_pPeriod;
	CObject2D* m_pColon;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nSecondCount;
	int m_nMinuteCount;
	DWORD m_dwGameStartTime;	//ゲーム開始時間
	DWORD m_dwGameTime;	//ゲーム経過時間
	STATE m_state;
};

#endif