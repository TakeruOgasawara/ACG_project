//===============================================================================
//
// [edit.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _EDITOR_H_				//���̃}�N����`������Ă��Ȃ�������
#define _EDITOR_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "objectX.h"

//�O���錾
class CObjectX;

//�v���C���[�N���X
class CEditor
{
private:	//�萔�p�v���C�x�[�g

	static const int NUM_OBJECT = 100;
	static const int MAX_NAME = 254;

public:
	struct SObjectX
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//�o�b�t�@�ւ̒��_���
		D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
		LPD3DXMESH pMesh;	//�g�p����Ă��郂�f����
		LPD3DXBUFFER BuffMat;	//���_�J���[���
		DWORD dwNumMat;		//�J���[�̐�
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	};

public:

	CEditor();
	~CEditor();

	static CEditor* Create(void);

	void Load(const char* pFilename);
	void Save(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObjectX* m_pObjectX;
	SObjectX m_object;
	int m_nTypeIdx;
	int m_nIdx;
	bool m_bUse;
};

#endif