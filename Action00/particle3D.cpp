//===========================================================================================
//
// [particle3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "particle3D.h"
#include "effect3D.h"

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CParticle3D::CParticle3D()
{

}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CParticle3D::~CParticle3D()
{

}

//===========================================================================================
// ����
//===========================================================================================
CParticle3D *CParticle3D::Create(D3DXVECTOR3 pos, TYPE type)
{
	CParticle3D *pParticle = nullptr;

	if (pParticle == nullptr)
	{
		pParticle = new CParticle3D;

		if (pParticle != nullptr)
		{
			pParticle->Set(pos, type);

			return pParticle;
		}
		else
		{
			return nullptr;
		}
	}

	return pParticle;
}

//===========================================================================================
// �I������
//===========================================================================================
void CParticle3D::Uninit(void)
{
	Release();
}

//===========================================================================================
// �^�C�v
//===========================================================================================
void CParticle3D::Set(D3DXVECTOR3 pos, TYPE type)
{
	//�ϐ��錾
	float fRot;
	float fMove;
	float fRadius;
	int nLife;
	D3DXVECTOR3 move;
	D3DXCOLOR col;

	switch (type)
	{
	case TYPE_EXPLOSION:
		for (int nCnt = 0; nCnt < 100; nCnt++)
		{
			//x
			fRot = (float)(rand() % 629 - 314) / 100.0f;			//�p�x�̐ݒ�
			fMove = (float)(rand() % 60) / 10;			//�ړ��ʂ̐ݒ�
			move.x = sinf(fRot) * fMove;			//�ړ��ʂ̐ݒ�

			//y
			fRot = (float)(rand() % 629 - 314) / 100.0f;			//�p�x�̐ݒ�
			fMove = (float)(rand() % 45) / 10;			//�ړ��ʂ̐ݒ�
			move.y = cosf(fRot) * fMove;			//�ړ��ʂ̐ݒ�

			//z
			fRot = (float)(rand() % 629 - 314) / 100.0f;			//�p�x�̐ݒ�
			fMove = (float)(rand() % 45) / 10;			//�ړ��ʂ̐ݒ�
			move.z = cosf(fRot) * fMove;			//�ړ��ʂ̐ݒ�

			//�F�̐ݒ�
			col = D3DXCOLOR(0.3f, 0.6f, 0.4f, 1.0f);

			//���a�̐ݒ�
			fRadius = 10.0f;

			//�̗͂̐ݒ�
			nLife = 100;

			//�G�t�F�N�g�ݒ�
			CEffect3D::Create(pos, move, col, fRadius, nLife);
		}

		break;
	}
}
