//===============================================================================
//
// [number.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _NUMBER_H_				//���̃}�N����`������Ă��Ȃ�������
#define _NUMBER_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "object.h"

//�O���錾
class CObject2D;

//�i���o�[�N���X
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static CNumber *Create(D3DXVECTOR3 pos);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(float fWidth, float fHeight);
	CObject2D *GetObject2D(void);

private:
	static int m_nTextureIdx;			//�e�N�X�`���ԍ�
	CObject2D *m_pObject2D;
};

#endif