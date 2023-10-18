//===============================================================================
//
// ステージ画面[stage.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _STAGE_H_				//このマクロ定義がされていなかったら
#define _STAGE_H_				//2重インクルード帽子のマクロを定義

#include "main.h"
#include "manager.h"

//前方宣言
class CPlayer;
class CEdit;
class CCamera;

//タイトルクラス
class CStage
{
private:
	//ステージ列挙型
	enum STAGE
	{
		STAGE_0 = 0,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		STAGE_5,
		STAGE_MAX
	};

	//エリア列挙型
	enum AREA
	{
		AREA_0 = 0,
		AREA_1,
		AREA_2,
		AREA_MAX
	};

	struct SData
	{
		STAGE stage;
		AREA area;
	};

public:
	CStage();
	~CStage();

	static CStage* Create(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:	//メンバ関数
	void Stage0(void);
	/*void Stage1(void);
	void Stage2(void);
	void Stage3(void);
	void Stage4(void);
	void Stage5(void);*/

private:	//メンバ変数
	SData m_data;

	CCamera* m_pCamera;
	CEdit* m_pEdit;
	CPlayer* m_pPlayer;
};

#endif