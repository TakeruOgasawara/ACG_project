//===============================================================================
//
// ステージ画面[stage.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _STAGE0_H_	//このマクロ定義がされていなかったら
#define _STAGE0_H_	//2重インクルード帽子のマクロを定義

#include "main.h"
#include "manager.h"

//前方宣言
class CPlayer;
class CCamera;
class CNextStep;
class CLockDoor;

class CEdit;
class CEditor;

//タイトルクラス
class CStage0
{
private:
	//エリア列挙型
	enum EArea
	{
		AREA_0 = 0,
		AREA_1,
		AREA_2,
		AREA_MAX
	};

public:
	CStage0();
	~CStage0();

	//static CStage0* Create(void);
	static CStage0* GetInstance(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	CPlayer* GetPlayer(void) { return m_pPlayer; }

private:
	void Area0(void);
	void Area1(void);
	void Area2(void);

private:	//メンバ変数
	static CStage0* m_pStage0;
	EArea m_area;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CEdit* m_pEdit;
	CNextStep* m_pNextStep;

	bool m_bNext;	//次へ進むか
	bool m_bLoad;	//初期読み込みフラグ
};

#endif