//===============================================================================
//
// [edit.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _EDIT_H_				//���̃}�N����`������Ă��Ȃ�������
#define _EDIT_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "object.h"

//�O���錾
class CObjectX;

//�v���C���[�N���X
class CEdit
{
private:	//�萔�p�v���C�x�[�g

	static const int NUM_OBJECT = 100;
	static const int MAX_NAME = 254;

public:
	////���
	// enum STATE
	//{
	//	STATE_OFF = 0,
	//	STATE_OFF,
	//	STATE_MAX
	//};

	CEdit();
	~CEdit();

	static CEdit* Create(void);

	static HRESULT Load(void);
	void Save(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObjectX *m_pObjectX;
	D3DXVECTOR3 m_pos;
	int m_nTypeIdx;
	int m_nIdx;
	bool m_bUse;
};

#endif