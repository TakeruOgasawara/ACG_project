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
class CUI_Manager;
class CPause;
class CSound;
class CEdit;
class CXfile;

class CStage;

//タイトルクラス
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	static CGame* GetInstance(void);
	static void Release(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	CPause* GetPause(void) { return m_pPause; }
	CXfile* GetXfile(void) { return m_pXfile; }

private:
	void Edit(void);

	static CGame* m_pGame;

	CUI_Manager* m_pUIManager;
	CPause* m_pPause;
	CXfile* m_pXfile;
	CSound* m_pSound;

	CStage* m_pStage;

	bool m_bEdit;
};

#endif