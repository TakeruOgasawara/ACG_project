//======================================================================================
//
// �p�[�e�B�N��3D����[particle3D.h]
// Author : Takeru Ogasawara
//
//======================================================================================
#ifndef _PARTICLE3D_H_			//���̃}�N����`������Ă��Ȃ�������
#define _PARTICLE3D_H_			//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "effect3D.h"

//*****************************
//�}�N����`
//*****************************
#define MAX_PARTICLE			(100)			//�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�N���X
class CParticle3D : public CEffect3D
{
public:
	//���
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_EXPLOSION,
		TYPE_MAX
	} TYPE;

public:

	CParticle3D();
	~CParticle3D();

	static CParticle3D *Create(D3DXVECTOR3 pos, TYPE type);
	void Uninit(void);

	void Set(D3DXVECTOR3 pos, TYPE type);

private:
	
};

#endif