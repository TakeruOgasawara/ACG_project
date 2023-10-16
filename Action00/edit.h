//===============================================================================
//
// [edit.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _EDIT_H_				//このマクロ定義がされていなかったら
#define _EDIT_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "object.h"

//前方宣言
class CObjectX;

//プレイヤークラス
class CEdit
{
private:	//定数用プライベート

	static const int NUM_OBJECT = 100;
	static const int MAX_NAME = 254;

public:
	////種類
	// enum STATE
	//{
	//	STATE_OFF = 0,
	//	STATE_OFF,
	//	STATE_MAX
	//};

	CEdit();
	~CEdit();

	static CEdit* Create(void);

	static HRESULT Load(void);
	void Save(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObjectX *m_pObjectX;
	D3DXVECTOR3 m_pos;
	int m_nTypeIdx;
	int m_nIdx;
	bool m_bUse;
};

#endif