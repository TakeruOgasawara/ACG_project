//===============================================================================
//
// ステージ画面[stage.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _STAGE_MANAGER_H_	//このマクロ定義がされていなかったら
#define _STAGE_MANAGER_H_	//2重インクルード防止のマクロを定義

#include "main.h"
#include "manager.h"

//前方宣言
class CStage0;

//タイトルクラス
class CStageManager
{
private:
	//ステージ列挙型
	enum ESTAGE
	{
		STAGE_0 = 0,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		STAGE_5,
		STAGE_MAX
	};

public:
	CStageManager();
	~CStageManager();

	static CStageManager* GetInstance(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:	//メンバ変数
	static CStageManager* m_pStageManager;

	ESTAGE m_stage;
	CStage0* m_pStage0;

	int nProgress;	//進行度
};

#endif