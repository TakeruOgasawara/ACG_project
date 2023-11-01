//======================================================================================
//
// �G�t�F�N�g3D����[effect.h]
// Author : Takeru Ogasawara
//
//======================================================================================
#ifndef _EFFECT3D_H_			//���̃}�N����`������Ă��Ȃ�������
#define _EFFECT3D_H_			//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "billboard.h"

//*****************************
//�}�N����`
//*****************************
#define MAX_EFFECT			(100)			//�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�N���X
class CEffect3D : public CBillboard
{
public:
	CEffect3D(int nPriority = 5);
	~CEffect3D();

	static HRESULT Load(void);
	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int life);

private:
	D3DXVECTOR3 m_move;
	D3DXCOLOR m_col;			//�F
	int m_nLife;				//����
	int m_nMaxLife;				//�ő����
	static int m_nTextureIdx;
};

#endif