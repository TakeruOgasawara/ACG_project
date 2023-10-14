//===============================================================================
//
// タイトル画面[title.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TITLE_H_				//このマクロ定義がされていなかったら
#define _TITLE_H_				//2重インクルード帽子のマクロを定義

#include "main.h"
#include "manager.h"

//前方宣言
class CObject2D;
class CMap;

//タイトルクラス
class CTitle : public CScene
{
private:

	enum STATE
	{
		STATE_NONE = 0,
		STATE_IN,
		STATE_OUT,
		STATE_MAX
	};

public:
	CTitle();
	~CTitle();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw(); 

private:
	int m_nTextureIdx;			//テクスチャへの頂点情報
	static CObject2D *m_apObject2D[2];
	static CMap *m_pMap;
	STATE m_state;
	float col_a;
};

#endif