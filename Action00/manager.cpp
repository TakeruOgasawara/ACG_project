//===========================================================================================
//
// [manager.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include"renderer.h"
#include "object.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "xfile.h"
#include "slow.h"

#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"

#include "object3D.h"

//静的メンバ変数宣言
CManager* CManager::m_pManager = nullptr;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CManager::CManager()
{
	m_pRenderer = nullptr;
	m_pInputKeyboard = nullptr;
	m_pInputMouse = nullptr;
	m_pInputJoyPad = nullptr;
	m_pDebugProc = nullptr;
	m_pSound = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pTexture = nullptr;
	m_pScene = nullptr;
	m_pTitle = nullptr;
	m_pGame = nullptr;
	m_pResult = nullptr;
	m_pFade = nullptr;
	m_pXfile = nullptr;
	m_pSlow = nullptr;

	m_bUse = false;
	m_nCurrentMinute = 0;
	m_nCurrentSecond = 0;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CManager::~CManager()
{

}

//===========================================================================================
// シングルトン
//===========================================================================================
CManager *CManager::GetInstance(void)
{
	if (m_pManager == nullptr)
	{//nullだった場合

		return m_pManager = new CManager;
	}
	else
	{
		return m_pManager;
	}
}

//===========================================================================================
// 破棄
//===========================================================================================
void CManager::Release(void)
{
	if (m_pManager == nullptr)
	{//nullだった場合

		return;
	}
	else
	{
		m_pManager->Uninit();

		delete m_pManager;
		m_pManager = nullptr;
	}
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//---------------------------
	// インスタンス生成
	//---------------------------
	//レンダラー
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;

		if (m_pRenderer != nullptr)
		{
			//レンダラーの初期化処理
			if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
			{
				return E_FAIL;
			}
		}
	}
	//キーボード
	if (m_pInputKeyboard == nullptr)
	{
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != nullptr)
		{
			//キーボードの初期化処理
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{
				return E_FAIL;
			}
		}
	}
	//マウス
	if (m_pInputMouse == nullptr)
	{
		m_pInputMouse = new CInputMouse;

		if (m_pInputMouse != nullptr)
		{
			//マウスの初期化処理
			if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
			{
				return E_FAIL;
			}
		}
	}
	//ジョイパッド
	if (m_pInputJoyPad == nullptr)
	{
		m_pInputJoyPad = new CInputJoyPad;

		if (m_pInputJoyPad != nullptr)
		{
			//マウスの初期化処理
			if (FAILED(m_pInputJoyPad->Init()))
			{
				return E_FAIL;
			}
		}
	}
	//サウンド
	if (m_pSound == nullptr)
	{
		m_pSound = new CSound;

		if (m_pSound != nullptr)
		{
			//マウスの初期化処理
			m_pSound->Init(hWnd);
		}
	}
	// デバッグ表示の生成
	if (m_pDebugProc == nullptr)
	{
		m_pDebugProc = new CDebugProc;

		//初期化処理
		if (m_pDebugProc != nullptr)
		{
			m_pDebugProc->Init();
		}
	}
	//カメラの生成
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CCamera;

		//初期化処理
		if (m_pCamera != nullptr)
		{
			m_pCamera->Init();
		}
	}
	//ライトの生成
	if (m_pLight == nullptr)
	{
		m_pLight = new CLight;

		//初期化処理
		if (m_pLight != nullptr)
		{
			m_pLight->Init();
		}
	}
	//テクスチャの生成
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;

		//初期化処理
		if (m_pTexture != nullptr)
		{
			m_pTexture->Load();
		}
	}
	//xファイルの生成
	//if (m_pXfile == nullptr)
	//{
	//	m_pXfile = new CXfile;

	//	//初期化処理
	//	if (m_pXfile != nullptr)
	//	{
	//		m_pXfile->Load();
	//	}
	//}

	// スロー情報の生成
	if (m_pSlow == nullptr)
	{
		m_pSlow = new CSlow;

		//初期化処理
		if (m_pXfile != nullptr)
		{
			m_pSlow->Init();
		}
	}

	//モード設定
	SetMode(CScene::MODE_TITLE);
	
	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CManager::Uninit(void)
{
	//全オブジェクトの破棄(+終了処理)
	CObject::ReleaseAll();

	//キーボードの終了処理、破棄
	if (m_pInputKeyboard != nullptr)
	{
		//キーボードの終了処理
		m_pInputKeyboard->Uninit();

		//メモリの開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	//マウスの終了処理、破棄
	if (m_pInputMouse != nullptr)
	{
		//キーボードの終了処理
		m_pInputMouse->Uninit();

		//メモリの開放
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}
	//マウスの終了処理、破棄
	if (m_pInputJoyPad != nullptr)
	{
		//キーボードの終了処理
		m_pInputJoyPad->Uninit();

		//メモリの開放
		delete m_pInputJoyPad;
		m_pInputJoyPad = nullptr;
	}
	//デバッグプロックの終了、破棄
	if (m_pDebugProc != nullptr)
	{
		//デバッグプロックの終了処理
		m_pDebugProc->Uninit();

		//メモリの開放
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
	//レンダラーの終了処理、破棄
	if (m_pRenderer != nullptr)
	{
		//レンダラーの終了処理
		m_pRenderer->Uninit();

		//メモリの開放
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//サウンドの終了、破棄
	if (m_pSound != nullptr)
	{
		//サウンドの終了処理
		m_pSound->Stop();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}
	//カメラの終了、破棄
	if (m_pCamera != nullptr)
	{
		//カメラの終了処理
		m_pCamera->Uninit();
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//ライトの終了、破棄
	if (m_pLight != nullptr)
	{
		//ライトの終了処理
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = nullptr;
	}
	//テクスチャの終了、破棄
	if (m_pTexture != nullptr)
	{
		//テクスチャの終了処理
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = nullptr;
	}
	//シーンの終了、破棄
	if (m_pScene != nullptr)
	{
		//シーンの終了処理
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//Xファイルの終了、破棄
	if (m_pXfile != nullptr)
	{
		//シーンの終了処理
		m_pXfile->Unload();
		delete m_pXfile;
		m_pXfile = nullptr;
	}

	//スローの終了、破棄
	if (m_pSlow != nullptr)
	{
		//シーンの終了処理
		m_pSlow->Uninit();
		delete m_pSlow;
		m_pSlow = nullptr;
	}
	
	if (m_pFade != nullptr)
	{
		m_pFade = nullptr;
	}
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CManager::Update(void)
{
	CManager::GetDebugProc()->Print("FPS[%d]\n", GetFps());
	CManager::GetDebugProc()->Print("オブジェクト総数[%d]\n\n", CObject::GetNumAll());

	m_pDebugProc->Print("【 操作方法 】\n");
	m_pDebugProc->Print("F1 : デバッグ表示[ON/OFF]\nF2 : 法線表示[ON/OFF]\n");

	//デバッグプロックの更新処理
	if (CManager::GetDebugProc() != nullptr)
	{
		CManager::GetDebugProc()->Update();
	}

	//キーボードの更新処理
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	//マウスの更新処理
	if (m_pInputMouse != nullptr)
	{
		m_pInputMouse->Update();
	}

	//ジョイパッドの更新処理
	if (m_pInputJoyPad != nullptr)
	{
		m_pInputJoyPad->Update();
	}

	// スローの更新処理
	if (m_pSlow != NULL)
	{
		m_pSlow->Update();
	}

	//シーンの更新
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	} 
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CManager::Draw(void)
{
	//レンダラーの描画処理
	if (m_pScene != nullptr)
	{
		m_pScene->Draw();
	}
}

void CManager::SetCurrentTime(int nMinute, int nSecond)
{
	m_nCurrentMinute = nMinute;
	m_nCurrentSecond = nSecond;
}

void CManager::GetCurrentTim(int* nMinute, int* nSecond)
{
	*nMinute = m_nCurrentMinute;
	*nSecond = m_nCurrentSecond;
}

//===========================================================================================
// モードの設定
//===========================================================================================
void CManager::SetMode(CScene::MODE mode)
{
	//サウンドの停止
	if (m_pSound != nullptr)
	{
		m_pSound->Stop();
	}

	//現在のモードを破棄
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//全オブジェクトの破棄
	CObject::ReleaseAll();

	//テクスチャの終了、破棄
	if (m_pTexture != nullptr)
	{
		//テクスチャの終了処理
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = nullptr;

		//テクスチャの生成
		if (m_pTexture == nullptr)
		{
			m_pTexture = new CTexture;

			//初期化処理
			if (m_pTexture != nullptr)
			{
				m_pTexture->Load();
			}
		}
	}
	
	//フェードの削除
	m_pFade = nullptr;

	//新しいモードの生成
	m_pScene = CScene::Create(mode);
	m_pScene->SetMode(mode);

	if (m_pScene != nullptr)
	{
		m_pScene->Init();
	}

	//フェードの生成
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(mode);
	}
}