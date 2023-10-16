//===========================================================================================
//
// [camera.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

//�}�N����`
#define VIEWING_ANGLE		(45.0f)			//����p

#define LENGTH				(500.0f)			//�J�����Ƃ̋���
#define V_POSITION			(D3DXVECTOR3(0.0f, 1020.0f, 0.0f))			//���_�̍���
#define R_POSITION			(D3DXVECTOR3(0.0f, 540.0f, 0.0f))			//�����_�̍���
#define ROTATION			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//����

//�Ǐ]�֌W�}�N��
#define V_FOLLOW_HEIGHT		(200.0f)			//���_�̍���(�Ǐ])
#define R_FOLLOW_HEIGHT		(100.0f)			//�����_�̍���(�Ǐ])
#define R_FOLLOW_MAE		(D3DXVECTOR3(20.0f, 100.0f, 20.0f))			//�Ǐ]���ɒ����_���ǂ̂��炢�O�ɏo����

#define OFFSET_V			(0.3f)				//���_�̕␳
#define OFFSET_R			(0.3f)				//�����_�̕␳

#define MOUSE_SENSITIVITY	(0.004f)			//�}�E�X���x
#define PAD_SENSITIVITY		(0.045f)			//�p�b�h���x

#define CAMERA_ROT_LIMIT_UP		(0.35f)			//�J�����̏��
#define CAMERA_ROT_LIMIT_DOWN	(0.01f)			//�J�����̏��

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fHeightV = 0.0f;
	m_fHeightR = 0.0f;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CCamera::~CCamera()
{

}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(V_POSITION.x, V_POSITION.y, V_POSITION.z);
	m_posR = D3DXVECTOR3(R_POSITION.x, R_POSITION.y, R_POSITION.z);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(ROTATION.x, ROTATION.y, ROTATION.z);
	m_fLength = LENGTH;
	m_fHeightV = V_FOLLOW_HEIGHT;
	m_fHeightR = R_FOLLOW_HEIGHT;

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CCamera::Uninit(void)
{

}

//===========================================================================================
// �X�V����
//===========================================================================================
void CCamera::Update(void)
{
	//V_Move_Mouse();
	R_Move_Mouse();

	V_Move();
	R_Move();

	//�J�����̌������C������
	FixOrientation();

	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y�J�������z");
	CManager::GetInstance()->GetDebugProc()->Print("\n���_�F x:%f y:%f z:%f", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n�����_�F x:%f y:%f z:%f", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n�����F x:%f, y:%f z:%f\n", m_rot.z, m_rot.y, m_rot.z);
}

//===========================================================================================
// �J�����ݒ�
//===========================================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	//D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
	//	D3DXToRadian(VIEWING_ANGLE),					//����p
	//	(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//��ʂ̃A�X�y�N�g��
	//	10.0f,				//z�l�̍ŏ��l
	//	10000.0f);			//z�l�̍ő�l

	//�v���W�F�N�V�����}�g���b�N�X���쐬[���s���e]
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH,				//����p
		(float)SCREEN_HEIGHT,				//��ʂ̃A�X�y�N�g��
		1.0f,				//z�l�̍ŏ��l
		1000.0f);			//z�l�̍ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,			//���_
		&m_posR,			//�����_
		&m_vecU);			//���x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//===========================================================================================
// �J�����̌����𒼂�
//===========================================================================================
void CCamera::FixOrientation(void)
{
	//������3.14�ȏ�-3.14�ȉ��ɍs���Ȃ��悤�ɂ���
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z = -D3DX_PI;
	}
	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z = D3DX_PI;
	}
}

//===========================================================================================
// ���_(�}�E�X)
//===========================================================================================
void CCamera::V_Move_Mouse(void)
{
	//�C���v�b�g���̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	//���_�̈ړ�
	if (pInputMouse->GetPress(pInputMouse->MOUSE_LEFT))
	{
		m_rot.z += -pInputMouse->GetMovement().y * MOUSE_SENSITIVITY;
		m_rot.y += pInputMouse->GetMovement().x * MOUSE_SENSITIVITY;

		//�}�E�X�̈ړ��ʂ��王�_�𓮂���
		V_Move();
	}

	//�p�b�h
	/*m_rot.z += pInpuJoyPad->GetJoyStickRY(0) * PAD_SENSITIVITY;
	m_rot.y += pInpuJoyPad->GetJoyStickRX(0) * PAD_SENSITIVITY;*/
}

//===========================================================================================
// �����_(�}�E�X)
//===========================================================================================
void CCamera::R_Move_Mouse(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//���_�̈ړ�
	if (pInputMouse->GetPress(pInputMouse->MOUSE_RIGHT))
	{
		//�}�E�X�̈ړ��ʂ��璍���_�𓮂���
		m_rot.z += -pInputMouse->GetMovement().y * MOUSE_SENSITIVITY;
		m_rot.y += pInputMouse->GetMovement().x * MOUSE_SENSITIVITY;

		//�����_�̈ړ�
		R_Move();
	}
}

//===========================================================================================
// ���_
//===========================================================================================
void CCamera::V_Move(void)
{
	m_posV.x = m_posR.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength;
	m_posV.y = m_posR.y + sinf(m_rot.z) * -m_fLength;
	m_posV.z = m_posR.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength;
}

//===========================================================================================
// �����_
//===========================================================================================
void CCamera::R_Move(void)
{
	m_posR.x = m_posV.x + (cosf(m_rot.z) * sinf(m_rot.y)) * m_fLength;
	m_posR.y = m_posV.y + sinf(m_rot.z) * m_fLength;
	m_posR.z = m_posV.z + (cosf(m_rot.z) * cosf(m_rot.y)) * m_fLength;
}

//===========================================================================================
// �Y�[��
//===========================================================================================
void CCamera::Zoom(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//if (pInputMouse->GetPress(pInputMouse->MOUSE_HWEEL) == true)
	//{
	//	//�����_�̈ړ�
	//	m_posR.x += (-pInputMouse->GetMovement.x * sinf(m_rot.x)) * 0.1f;
	//	m_posR.y += (pInputMouse->GetMovement.y * sinf(m_rot.y)) * 0.1f;
	//	m_posR.z += (pInputMouse->GetMovement.z * sinf(m_rot.z)) * 0.1f;

	//	//�����_�̍X�V����
	//	V_Move();

	//	//���_�̈ړ�
	//	m_posV.x += (-pInputMouse->GetMovement.x * cosf(m_rot.x)) * 0.1f;
	//	m_posV.y += (pInputMouse->GetMovement.y * cosf(m_rot.y)) * 0.1f;
	//	m_posV.z += (pInputMouse->GetMovement.z * cosf(m_rot.z)) * 0.1f;

	//	//���_�̍X�V����
	//	R_Move();
	//}
}

//-------------------------------------------------------------------------------------------
// �J�����̒Ǐ]���� : Follow(�ʒu�A����)
//-------------------------------------------------------------------------------------------
void CCamera::Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ړI�̎��_/�����_��ݒ�(�����l)
	//�����_
	m_posRDest =
	{
		pos.x + sinf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.x,
		pos.y + m_fHeightR,
		pos.z + cosf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.z
	};

	//���_
	m_posVDest =
	{
		m_posRDest.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength,
		pos.y + m_fHeightV,
		m_posRDest.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength
	};

	m_posR += (m_posRDest - m_posR) * OFFSET_R;			//�����_��␳
	m_posV += (m_posVDest - m_posV) * OFFSET_R;			//���_��␳
}

//-------------------------------------------------------------------------------------------
// �J�����̒Ǐ]���� : Follow(�ʒu�A�����A���_�����A�����_����)
//-------------------------------------------------------------------------------------------
void CCamera::Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeightV, float fHeightR)
{
	m_fHeightV = fHeightV;
	m_fHeightR = fHeightR;

	//�ړI�̎��_/�����_��ݒ�(�����l)
	//�����_
	m_posRDest =
	{
		pos.x + sinf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.x,
		m_fHeightR,
		pos.z + cosf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.z
	};

	//���_
	m_posVDest =
	{
		m_posRDest.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength,
		m_fHeightV,
		m_posRDest.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength
	};

	m_posR += (m_posRDest - m_posR) * OFFSET_R;			//�����_��␳
	m_posV += (m_posVDest - m_posV) * OFFSET_R;			//���_��␳
}

//====================================================================
// ���X�N(x��)��p�Ǐ]����
//====================================================================
void CCamera::Follow2D_x_axisDedicated(D3DXVECTOR3 pos)
{
	//�ړI�̎��_/�����_��ݒ�(�����l)
//�����_
	m_posRDest =
	{
		pos.x + sinf(m_rot.y - D3DX_PI),
		/*pos.y + */m_fHeightR,
		pos.z + cosf(m_rot.y - D3DX_PI)
	};

	//���_
	m_posVDest =
	{
		m_posRDest.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength,
		/*pos.y + */m_fHeightV,
		m_posRDest.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength
	};

	m_posR += (m_posRDest - m_posR) * OFFSET_R;			//�����_��␳
	m_posV += (m_posVDest - m_posV) * OFFSET_R;			//���_��␳
}

//====================================================================
// �J�����̈ʒu�������I�Ɍ�둤��
//====================================================================
void  CCamera::Back(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ϐ��錾
	float fRotDiff = 0.0f;			//�����ۑ��p

	fRotDiff = (rot.y + D3DX_PI) - m_rot.y;			//�������v�Z

	//�ڕW�̊p�x�̕␳
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= (D3DX_PI * 2);
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	m_rot.y += fRotDiff * 0.045f;			//�␳����

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= 6.28f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += 6.28f;
	}

	//�J�������X�V����
	m_posVDest.x = pos.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength;
	m_posVDest.y = pos.y + sinf(m_rot.z) * -m_fLength;			//���_Y
	m_posVDest.z = pos.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength;
}

//===========================================================================================
// �J�����̐ݒ�(���l) : SetValue(���_�ƒ����_�̋����A���_�̍����A�����_�̍���)
//===========================================================================================
void CCamera::SetValue(float fDistance, D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_fLength = fDistance;
	m_posV = posV;
	m_fHeightV = posV.y;
	m_posR = posR;
}