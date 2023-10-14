//===============================================================================
//
// [manager.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _MANAGER_H_				//このマクロ定義がされていなかったら
#define _MANAGER_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "object.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputJoyPad;
class CDebugProc;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CObjectX;
class CScene;

class CTitle;
class CGame;
class CResult;
class CFade;

//シーンクラス(画面遷移)
class CScene
{
public:
	//シーン種類
	typedef enum 
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CScene();
	~CScene();

	static CScene *Create(MODE mode);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetMode(MODE mode) { m_mode = mode; }
	static MODE GetMode(void) { return m_mode; }

private:
	static MODE m_mode;
};

// マネージャクラス(全体管理)
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return CScene::GetMode(); }
	
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }
	static CInputJoyPad *GetInputJoyPad(void) { return m_pInputJoyPad; }
	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	static CSound *GetSound(void) { return m_pSound; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CTexture *GetTexture(void) { return m_pTexture; }
	static CScene *GetScene(void) { return m_pScene; }
	static CFade *GetFade(void) { return m_pFade; }

private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;
	static CInputJoyPad *m_pInputJoyPad;
	static CDebugProc *m_pDebugProc;
	static CSound *m_pSound;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CTexture *m_pTexture;
	static bool m_bUse;

	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CFade *m_pFade;

	static CScene *m_pScene;
};

#endif
