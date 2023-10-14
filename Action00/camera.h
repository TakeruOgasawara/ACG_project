//===============================================================================
//
// [camera.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _CAMERA_H_				//���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//�J�����N���X
class CCamera
{
private:
	struct Circle
	{
		float m_PosX;		// �`����WX
		float m_PosY;		// �`����WY
		float m_Radius;		// ���a(�`��p)
		float m_CenterX;	// ���S���WX
		float m_CenterY;	// ���S���WY
		float m_Angle;		// �p�x
		float m_Length;		// ���a�̒���
	};

public:
	CCamera();
	~CCamera();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//�Ǐ]
	void Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeightV, float fHeightR);			//�Ǐ]
	void Back(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//�w��

	void V_Move(void);
	void R_Move(void);
	void Zoom(void);			//�Y�[��

	void SetCamera(void);
	void SetLength(float fLength) { m_fLength = fLength; }
	void SetPosition_V(D3DXVECTOR3 pos) { m_posV = pos; }
	void SetPosition_R(D3DXVECTOR3 pos) { m_posR = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetValue(float fDistance, float fPosV, float fPosR);

	D3DXVECTOR3 GetPosition_V(void) { return m_posV; }
	D3DXVECTOR3 GetPosition_R(void) { return m_posR; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:
	void V_Move_Mouse(void);			//���_�ړ�(�}�E�X)
	void R_Move_Mouse(void);			//�����_�ړ�(�}�E�X)
	void FixOrientation(void);		//�����C��

	//�ϐ�
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_vecU;				//������x�N�g��
	D3DXVECTOR3 m_rot;				//����
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_posVDest;			//���_�̍���
	D3DXVECTOR3 m_posRDest;			//�����_�̍���
	float m_fLength;
	float m_fHeightV;
	float m_fHeightR;
	Circle m_circle;
};

#endif