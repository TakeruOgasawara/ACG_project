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
class CXfile;

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
	MODE GetMode(void) { return m_mode; }

private:
	MODE m_mode;
};

// マネージャクラス(全体管理)
class CManager
{
public:
	CManager();
	~CManager();

	static CManager *GetInstance(void);
	static void Release(void);

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	CRenderer* GetRenderer(void) { return m_pRenderer; }
	CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	CInputJoyPad* GetInputJoyPad(void) { return m_pInputJoyPad; }
	CDebugProc* GetDebugProc(void) { return m_pDebugProc; }
	CSound* GetSound(void) { return m_pSound; }
	CCamera* GetCamera(void) { return m_pCamera; }
	CLight* GetLight(void) { return m_pLight; }
	CTexture* GetTexture(void) { return m_pTexture; }
	CScene* GetScene(void) { return m_pScene; }
	CFade* GetFade(void) { return m_pFade; }
	CXfile* GetXfile(void) { return m_pXfile; }

	void SetMode(CScene::MODE mode);
	CScene::MODE GetMode(void) { return m_pScene->GetMode(); }

private:
	static CManager *m_pManager;

	CRenderer* m_pRenderer;
	CInputKeyboard* m_pInputKeyboard;
	CInputMouse * m_pInputMouse;
	CInputJoyPad * m_pInputJoyPad;
	CDebugProc * m_pDebugProc;
	CSound* m_pSound;
	CCamera * m_pCamera;
	CLight * m_pLight;
	CTexture* m_pTexture;
	bool m_bUse;

	CTitle* m_pTitle;
	CGame* m_pGame;
	CResult* m_pResult;
	CFade* m_pFade;
	CScene* m_pScene;

	CXfile* m_pXfile;
};

#endif
