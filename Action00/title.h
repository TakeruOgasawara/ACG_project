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

//タイトルクラス
class CTitle : public CScene
{
private:	//構造体・列挙型用

	enum MENU
	{
		MENU_START = 0,
		MENU_END,
		MENU_MAX
	};

	struct SObject2D
	{
		CObject2D* pMenu2D;
		D3DXCOLOR col;
	};

public:
	CTitle();
	~CTitle();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw(); 

private:
	void SelectMenu(void);

	int m_nTextureIdx;
	CObject2D* pName2D;
	SObject2D m_apMenu[MENU_MAX];
	MENU m_menu;
	int m_nSelect;
};

#endif