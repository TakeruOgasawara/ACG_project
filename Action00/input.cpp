//======================================================================================
//
// 入力処理[input.cpp]
// Author:Takeru Ogasawara
//
//======================================================================================
#include "input.h"
#include <stdio.h>

//静的メンバ変数宣言
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//========================================================================
// コンストラクタ
//========================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//========================================================================
// デストラクタ
//========================================================================
CInput::~CInput()
{

}

//========================================================================
// 初期化処理
//========================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInputオブジェクトの初期化
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//========================================================================
// 終了処理
//========================================================================
void CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();			//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//Directinputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//========================================================================
// キーボードのコンストラクタ
//========================================================================
CInputKeyboard::CInputKeyboard()
{
	
}

//========================================================================
// キーボードのデストラクタ
//========================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//========================================================================
// キーボード初期化処理
//========================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//入力の初期化
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//強調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//========================================================================
// キーボード終了処理
//========================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//========================================================================
// キーボード更新処理
//========================================================================
void CInputKeyboard::Update(void)
{
	int nCntKey = 0;
	BYTE aState[256];

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aState), &aState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aState[nCntKey]) & aState[nCntKey];		//キーボードのトリガー情報を保存
			m_aStateRelease[nCntKey] = (m_aState[nCntKey] | aState[nCntKey]) ^ aState[nCntKey];		//キーボードのリリース情報を保存

			m_aState[nCntKey] = aState[nCntKey];			//キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();				//キーボードへのアクセス権を獲得
	}
}

//========================================================================
//キーボードのプレス情報を取得
//========================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aState[nKey] & 0x80) ? true : false;
}

//========================================================================
//キーボードのトリガー情報を取得
//========================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================================================
//キーボードのリリース情報を取得
//========================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aStateRelease[nKey] & 0x80) ? true : false;
}

//========================================================================
// コンストラクタ
//========================================================================
CInputMouse::CInputMouse()
{

}

//========================================================================
// デストラクタ
//========================================================================
CInputMouse::~CInputMouse()
{

}

//========================================================================
//　マウスの初期化処理
//========================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//入力デバイス(マウス)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}
	//強調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;			//相対値モードで設定 (絶対値はDIPROPAXISMODE_ABS)

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		//デバイスの設定に失敗
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//========================================================================
// マウスの終了処理
//========================================================================
void CInputMouse::Uninit(void)
{
	//入力デバイス(マウス)の破棄
	CInput::Uninit();
}

//========================================================================
// マウスの更新処理
//========================================================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 mouse;			//マウスの入力情報

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (int nCnt = 0; nCnt < NUM_MOUCE_MAX; nCnt++)
		{
			//トリガー情報の取得
			m_stateTrigger.rgbButtons[nCnt] = (m_state.rgbButtons[nCnt] ^ mouse.rgbButtons[nCnt]) & mouse.rgbButtons[nCnt];		//マウスのトリガー情報を保存

			m_statePress.rgbButtons[nCnt] = m_state.rgbButtons[nCnt];			//マウスのプレス情報を保存
		}

		//情報の取得
		m_statePress = mouse;

		//入力情報の保存
		m_state = mouse;
	}
	else
	{
		m_pDevice->Acquire();				//キーボードへのアクセス権を獲得
	}
}

//========================================================================
// マウスのプレス情報を取得
//========================================================================
bool CInputMouse::GetPress(int nKey)
{
	return (m_statePress.rgbButtons[nKey] & 0x80) ? true : false;
}

//========================================================================
// マウスのトリガー情報を取得
//========================================================================
bool CInputMouse::GetTrigger(int nKey)
{
	return (m_stateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//========================================================================
// マウスのリリース情報を取得
//========================================================================
bool CInputMouse::GetRelease(int nKey)
{
	return (m_stateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//========================================================================
// マウスの移動情報を取得
//========================================================================
D3DXVECTOR3 CInputMouse::GetMovement(void)
{
	//移動量を返す
	return D3DXVECTOR3((float)m_state.lX, (float)m_state.lY, (float)m_state.lZ);
}

//========================================================================
// マウスカーソルのスクリーン座標の取得
//========================================================================
POINT CInputMouse::GetPoint(void)
{
	//スクリーン座標の取得
	GetCursorPos(&m_point);

	//スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &m_point);

	return m_point;
}

//========================================================================
// コンストラクタ
//========================================================================
CInputJoyPad::CInputJoyPad()
{

}

//========================================================================
// デストラクタ
//========================================================================
CInputJoyPad::~CInputJoyPad()
{

}

//========================================================================
// 初期化処理
//========================================================================
HRESULT CInputJoyPad::Init(void)
{
	//変数宣言
	int nCntPad;

	//XInputのステート(使う状態)
	XInputEnable(true);

	//メモリの初期化(プレイヤー分)
	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		memset(&m_aState[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aStateTrigger[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aStateRelease[nCntPad], 0, sizeof(XINPUT_STATE));
	}

	//ないとできない
	return S_OK;
}

//========================================================================
// 終了処理
//========================================================================
void CInputJoyPad::Uninit(void)
{
	//XInputのステート(使わない状態)
	XInputEnable(false);
}

//========================================================================
// 更新処理
//========================================================================
void CInputJoyPad::Update(void)
{
	//変数宣言
	int nCntPad;

	XINPUT_STATE aGamePadState;			//ゲームパッドの入力情報

	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		//入力デバイスからデータを取得
		if (XInputGetState(nCntPad, &aGamePadState) == ERROR_SUCCESS)
		{
			//ゲームパッドのトリガー情報を保存
			m_aStateTrigger[nCntPad].Gamepad.wButtons =
				(m_aState[nCntPad].Gamepad.wButtons ^ aGamePadState.Gamepad.wButtons) & aGamePadState.Gamepad.wButtons;

			//リピート情報
			m_aStateRepeat[nCntPad].Gamepad.wButtons =
				(m_aState[nCntPad].Gamepad.wButtons & aGamePadState.Gamepad.wButtons);

			//リリース情報
			m_aStateRelease[nCntPad].Gamepad.wButtons =
				(m_aState[nCntPad].Gamepad.wButtons | aGamePadState.Gamepad.wButtons) ^ aGamePadState.Gamepad.wButtons;

			//ゲームパッドのプレス情報を保存
			m_aState[nCntPad] = aGamePadState;
		}
	}
}

//========================================================================
// プレス情報を取得
//========================================================================
bool CInputJoyPad::GetPress(JOYKEY nKey, int nPlayer)
{
	return (m_aState[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//========================================================================
// トリガー
//========================================================================
bool CInputJoyPad::GetTrigger(JOYKEY nKey, int nPlayer)
{
	return (m_aStateTrigger[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//========================================================================
// 
//========================================================================
bool CInputJoyPad::GetRelease(JOYKEY nKey, int nPlayer)
{
	return (m_aStateRelease[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//========================================================================
// 
//========================================================================
float CInputJoyPad::GetJoyStickLX(int nPlayer)
{
	return m_aState[nPlayer].Gamepad.sThumbLX / (float)SHRT_MAX;
}

//========================================================================
// 
//========================================================================
float CInputJoyPad::GetJoyStickLY(int nPlayer)
{
	return m_aState[nPlayer].Gamepad.sThumbLY / (float)SHRT_MAX;
}

//========================================================================
// 
//========================================================================
float CInputJoyPad::GetJoyStickRX(int nPlayer)
{
	return m_aState[nPlayer].Gamepad.sThumbRX / (float)SHRT_MAX;
}

//========================================================================
// 
//========================================================================
float CInputJoyPad::GetJoyStickRY(int nPlayer)
{
	return m_aState[nPlayer].Gamepad.sThumbRY / (float)SHRT_MAX;
}
