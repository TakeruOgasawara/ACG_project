//===============================================================================
//
// [object2D.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _OBJECT2DANIM_H_				//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT2DANIM_H_				//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "object2D.h"

//�A�j���[�V�����N���X
class CObject2Danim : public CObject2D
{
public:
	CObject2Danim();
	~CObject2Danim();

	static HRESULT Load(void);
	static CObject2Danim *Create(void);
	static CObject2Danim *Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetAnimation(int nPttern);
	void SetTexture(float fTexU, float fTexV);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̒��_���
	int m_nPttern;
	int m_nCntPttern;
	float m_fTexSizeX;
	float m_fTexSizeY;
};

#endif