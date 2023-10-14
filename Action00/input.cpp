//======================================================================================
//
// ���͏���[input.cpp]
// Author:Takeru Ogasawara
//
//======================================================================================
#include "input.h"
#include <stdio.h>

//�ÓI�����o�ϐ��錾
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//========================================================================
// �R���X�g���N�^
//========================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CInput::~CInput()
{

}

//========================================================================
// ����������
//========================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̏�����
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();			//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//Directinput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//========================================================================
// �L�[�{�[�h�̃R���X�g���N�^
//========================================================================
CInputKeyboard::CInputKeyboard()
{
	
}

//========================================================================
// �L�[�{�[�h�̃f�X�g���N�^
//========================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//========================================================================
// �L�[�{�[�h����������
//========================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���͂̏�����
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//========================================================================
// �L�[�{�[�h�I������
//========================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//========================================================================
// �L�[�{�[�h�X�V����
//========================================================================
void CInputKeyboard::Update(void)
{
	int nCntKey = 0;
	BYTE aState[256];

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aState), &aState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aState[nCntKey]) & aState[nCntKey];		//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aStateRelease[nCntKey] = (m_aState[nCntKey] | aState[nCntKey]) ^ aState[nCntKey];		//�L�[�{�[�h�̃����[�X����ۑ�

			m_aState[nCntKey] = aState[nCntKey];			//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();				//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//========================================================================
//�L�[�{�[�h�̃v���X�����擾
//========================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aState[nKey] & 0x80) ? true : false;
}

//========================================================================
//�L�[�{�[�h�̃g���K�[�����擾
//========================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================================================
//�L�[�{�[�h�̃����[�X�����擾
//========================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aStateRelease[nKey] & 0x80) ? true : false;
}

//========================================================================
// �R���X�g���N�^
//========================================================================
CInputMouse::CInputMouse()
{

}

//========================================================================
// �f�X�g���N�^
//========================================================================
CInputMouse::~CInputMouse()
{

}

//========================================================================
//�@�}�E�X�̏���������
//========================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���̓f�o�C�X(�}�E�X)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;			//���Βl���[�h�Őݒ� (��Βl��DIPROPAXISMODE_ABS)

	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		//�f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//========================================================================
// �}�E�X�̏I������
//========================================================================
void CInputMouse::Uninit(void)
{
	//���̓f�o�C�X(�}�E�X)�̔j��
	CInput::Uninit();
}

//========================================================================
// �}�E�X�̍X�V����
//========================================================================
void CInputMouse::Update(void)
{
	DIMOUSESTATE2 mouse;			//�}�E�X�̓��͏��

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
	{
		for (int nCnt = 0; nCnt < NUM_MOUCE_MAX; nCnt++)
		{
			//�g���K�[���̎擾
			m_stateTrigger.rgbButtons[nCnt] = (m_state.rgbButtons[nCnt] ^ mouse.rgbButtons[nCnt]) & mouse.rgbButtons[nCnt];		//�}�E�X�̃g���K�[����ۑ�

			m_statePress.rgbButtons[nCnt] = m_state.rgbButtons[nCnt];			//�}�E�X�̃v���X����ۑ�
		}

		//���̎擾
		m_statePress = mouse;

		//���͏��̕ۑ�
		m_state = mouse;
	}
	else
	{
		m_pDevice->Acquire();				//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//========================================================================
// �}�E�X�̃v���X�����擾
//========================================================================
bool CInputMouse::GetPress(int nKey)
{
	return (m_statePress.rgbButtons[nKey] & 0x80) ? true : false;
}

//========================================================================
// �}�E�X�̃g���K�[�����擾
//========================================================================
bool CInputMouse::GetTrigger(int nKey)
{
	return (m_stateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//========================================================================
// �}�E�X�̃����[�X�����擾
//========================================================================
bool CInputMouse::GetRelease(int nKey)
{
	return (m_stateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//========================================================================
// �}�E�X�̈ړ������擾
//========================================================================
D3DXVECTOR3 CInputMouse::GetMovement(void)
{
	//�ړ��ʂ�Ԃ�
	return D3DXVECTOR3((float)m_state.lX, (float)m_state.lY, (float)m_state.lZ);
}

//========================================================================
// �}�E�X�J�[�\���̃X�N���[�����W�̎擾
//========================================================================
POINT CInputMouse::GetPoint(void)
{
	//�X�N���[�����W�̎擾
	GetCursorPos(&m_point);

	//�X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &m_point);

	return m_point;
}

//========================================================================
// �R���X�g���N�^
//========================================================================
CInputJoyPad::CInputJoyPad()
{

}

//========================================================================
// �f�X�g���N�^
//========================================================================
CInputJoyPad::~CInputJoyPad()
{

}

//========================================================================
// ����������
//========================================================================
HRESULT CInputJoyPad::Init(void)
{
	//�ϐ��錾
	int nCntPad;

	//XInput�̃X�e�[�g(�g�����)
	XInputEnable(true);

	//�������̏�����(�v���C���[��)
	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		memset(&m_aState[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aStateTrigger[nCntPad], 0, sizeof(XINPUT_STATE));
		memset(&m_aStateRelease[nCntPad], 0, sizeof(XINPUT_STATE));
	}

	//�Ȃ��Ƃł��Ȃ�
	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CInputJoyPad::Uninit(void)
{
	//XInput�̃X�e�[�g(�g��Ȃ����)
	XInputEnable(false);
}

//========================================================================
// �X�V����
//========================================================================
void CInputJoyPad::Update(void)
{
	//�ϐ��錾
	int nCntPad;

	XINPUT_STATE aGamePadState;			//�Q�[���p�b�h�̓��͏��

	for (nCntPad = 0; nCntPad < NUM_PLAYER; nCntPad++)
	{
		//���̓f�o�C�X����f�[�^���擾
		if (XInputGetState(nCntPad, &aGamePadState) == ERROR_SUCCESS)
		{
			//�Q�[���p�b�h�̃g���K�[����ۑ�
			m_aStateTrigger[nCntPad].Gamepad.wButtons =
				(m_aState[nCntPad].Gamepad.wButtons ^ aGamePadState.Gamepad.wButtons) & aGamePadState.Gamepad.wButtons;

			//���s�[�g���
			m_aStateRepeat[nCntPad].Gamepad.wButtons =
				(m_aState[nCntPad].Gamepad.wButtons & aGamePadState.Gamepad.wButtons);

			//�����[�X���
			m_aStateRelease[nCntPad].Gamepad.wButtons =
				(m_aState[nCntPad].Gamepad.wButtons | aGamePadState.Gamepad.wButtons) ^ aGamePadState.Gamepad.wButtons;

			//�Q�[���p�b�h�̃v���X����ۑ�
			m_aState[nCntPad] = aGamePadState;
		}
	}
}

//========================================================================
// �v���X�����擾
//========================================================================
bool CInputJoyPad::GetPress(JOYKEY nKey, int nPlayer)
{
	return (m_aState[nPlayer].Gamepad.wButtons & 0x01 << nKey) ? true : false;
}

//========================================================================
// �g���K�[
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
