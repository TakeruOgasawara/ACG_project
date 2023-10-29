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
	void AddTime(int nValue);

	int GetTime(void);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

private:
	CNumber* m_apNumber[NUM_TIME];
	CObject2D* m_pPeriod;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nTimeCount;
	int m_nTime;	
	DWORD m_dwGameStartTime;	//ゲーム開始時間
	DWORD m_dwGameTime;	//ゲーム経過時間
};

#endif