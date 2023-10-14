//===============================================================================
//
// ���U���g���[result.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _RESULT_H_				//���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "manager.h"

//�O���錾
class CObject2D;

//�^�C�g���N���X
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	static HRESULT Load(void);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
private:
	static int m_nTextureIdx;			//�e�N�X�`���ւ̒��_���
	static CObject2D *m_pObject2D;
};

#endif