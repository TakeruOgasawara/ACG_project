//===============================================================================
//
// ���͏���[input.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _INPUT_H_				//���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//�p�b�h���g�����߂ɕK�v
#include "Xinput.h"
#pragma comment(lib, "xinput.lib")

//*****************************
//�}�N����`
//*****************************
#define NUM_KEY_MAX			(256)			//�L�[�̍ő吔
#define NUM_MOUCE_MAX		(8)				//�}�E�X�{�^���̍ő吔
#define NUM_PLAYER			(1)				//�v���C���[��

//���̓N���X
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

//�L�[�{�[�h�N���X
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

//�W���C�p�b�h�N���X
class CInputJoyPad : public CInput
{
public:
	//�{�^���̎�� 20�ȓ�
	enum JOYKEY
	{
		BUTTON_0 = 0,				// �\���� 
		BUTTON_1,					// �\����
		BUTTON_2,					// �\����
		BUTTON_3,					// �\����
		BUTTON_START,				// start
		BUTTON_BACK,				// back
		BUTTON_LS,					// ���X�e�B�b�N��������
		BUTTON_RS,					// �E�X�e�B�b�N��������
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
	XINPUT_STATE m_aState[NUM_PLAYER];						//�v���X
	XINPUT_STATE m_aStateTrigger[NUM_PLAYER];				//�g���K�[
	XINPUT_STATE m_aStateRelease[NUM_PLAYER];				//�����[�X
	XINPUT_STATE m_aStateRepeat[NUM_PLAYER];				//���s�[�g

};

//�}�E�X�N���X
class CInputMouse : CInput
{
public:
	//�}�E�X�{�^���̎��
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
	DIMOUSESTATE2 m_state;			//�S���͏��̕ۊ�
	DIMOUSESTATE2 m_statePress;		//�v���X
	DIMOUSESTATE2 m_stateTrigger;	//�g���K�[
	DIMOUSESTATE2 m_stateRelease;	//�����[�X
	BYTE m_aOldState;				//�O��̓��͏���ۑ�
	POINT m_point;
};

#endif