//===============================================================================
//
// ゲーム画面[game.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _GAME_H_				//このマクロ定義がされていなかったら
#define _GAME_H_				//2重インクルード帽子のマクロを定義

#include "main.h"
#include "manager.h"

//前方宣言
class CPlayer3D;
class CMap;
class CUI_Manager;
class CPause;
class CSound;
class CEdit;
class CXfile;

//タイトルクラス
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CPlayer3D *GetPlayer3D(void) { return m_pPlayer3D; }
	static CPause *GetPause(void) { return m_pPause; }
	static CXfile* GetXfile(void) { return m_pXfile; }

private:
	void Edit(void);

	static CPlayer3D *m_pPlayer3D;
	static CMap *m_pMap;
	static CUI_Manager *m_pUIManager;
	static CPause *m_pPause;
	static CEdit *m_pEdit;
	static CXfile* m_pXfile;
	CSound *m_pSound;

	bool m_bEdit;
};

#endif