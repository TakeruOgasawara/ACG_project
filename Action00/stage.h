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
class CObject2D;

//タイトルクラス
class CStage : public CScene
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

	static HRESULT Load(void);

private:
	SData m_data;
};

#endif