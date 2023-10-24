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

class CStageManager;
class CPlayer;

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

	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	CPause* GetPause(void) { return m_pPause; }
	CXfile* GetXfile(void) { return m_pXfile; }

private:
	CUI_Manager* m_pUIManager;
	CPause* m_pPause;
	CXfile* m_pXfile;
	CSound* m_pSound;
	static CPlayer* m_pPlayer;
	CStageManager* m_pStageManager;

	bool m_bEdit;
};

#endif