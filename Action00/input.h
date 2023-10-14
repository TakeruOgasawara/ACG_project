//===============================================================================
//
// 入力処理[input.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _INPUT_H_				//このマクロ定義がされていなかったら
#define _INPUT_H_				//2重インクルード防止のマクロを定義

#include "main.h"

//パッドを使うために必要
#include "Xinput.h"
#pragma comment(lib, "xinput.lib")

//*****************************
//マクロ定義
//*****************************
#define NUM_KEY_MAX			(256)			//キーの最大数
#define NUM_MOUCE_MAX		(8)				//マウスボタンの最大数
#define NUM_PLAYER			(1)				//プレイヤー数

//入力クラス
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボードクラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aState[NUM_KEY_MAX];
	BYTE m_aStateTrigger[NUM_KEY_MAX];
	BYTE m_aStateRelease[NUM_KEY_MAX];
};

//ジョイパッドクラス
class CInputJoyPad : public CInput
{
public:
	//ボタンの種類 20以内
	enum JOYKEY
	{
		BUTTON_0 = 0,				// 十字↑ 
		BUTTON_1,					// 十字↓
		BUTTON_2,					// 十字←
		BUTTON_3,					// 十字→
		BUTTON_START,				// start
		BUTTON_BACK,				// back
		BUTTON_LS,					// 左スティック押し込み
		BUTTON_RS,					// 右スティック押し込み
		BUTTON_LB,					// LB/5
		BUTTON_RB,					// RB/6
		BUTTON_10,					// ?
		BUTTON_11,					// ?
		BUTTON_A,					// A/3 
		BUTTON_B,					// B/4
		BUTTON_X,					// X/1
		BUTTON_Y,					// Y/2
		BUTTON_16,					// ?
		BUTTON_17,					// ?
		BUTTON_18,					// ?
		BUTTON_19,					// ?
		BUTTON_20,					// ?
		BUTTON_MAX
	};

public:
	CInputJoyPad();
	~CInputJoyPad();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool GetPress(JOYKEY nKey, int nPlayer);
	bool GetTrigger(JOYKEY nKey, int nPlayer);
	bool GetRelease(JOYKEY nKey, int nPlayer);

	float GetJoyStickLX(int nPlayer);
	float GetJoyStickLY(int nPlayer);
	float GetJoyStickRX(int nPlayer);
	float GetJoyStickRY(int nPlayer);

private:
	XINPUT_STATE m_aState[NUM_PLAYER];						//プレス
	XINPUT_STATE m_aStateTrigger[NUM_PLAYER];				//トリガー
	XINPUT_STATE m_aStateRelease[NUM_PLAYER];				//リリース
	XINPUT_STATE m_aStateRepeat[NUM_PLAYER];				//リピート

};

//マウスクラス
class CInputMouse : CInput
{
public:
	//マウスボタンの種類
	typedef enum
	{
		MOUSE_LEFT = 0,
		MOUSE_RIGHT,
		MOUSE_HWEEL,
		MOUSE_SIDE1,
		MOUSE_SIDE2,
		MOUSE_6,
		MOUSE_7,
		MOUSE_8,
		MOUSE_9,
		MOUSE_10,
		MOUSE_11,
		MOUSE_12,
		MOUSE_13,
		MOUSE_14,
		MOUSE_15,
		MOUSE_16,
		MOUSE_17,
		MOUSE_18,
		MOUSE_MAX
	} MOUSE_BUTTON;

	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	D3DXVECTOR3 GetMovement(void);
	POINT GetPoint(void);

private:
	DIMOUSESTATE2 m_state;			//全入力情報の保管
	DIMOUSESTATE2 m_statePress;		//プレス
	DIMOUSESTATE2 m_stateTrigger;	//トリガー
	DIMOUSESTATE2 m_stateRelease;	//リリース
	BYTE m_aOldState;				//前回の入力情報を保存
	POINT m_point;
};

#endif