//===============================================================================
//
// [Xfile.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _XFILE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _XFILE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//�e�N�X�`���N���X
class CXfile
{
private:
	static const int MAX_FILE = 64;
	static const int MAX_NAME = 254;

public:
	//X�t�@�C�����̍\����
	struct SXFile
	{
		LPD3DXMESH pMesh;	//�g�p����Ă��郂�f����
		LPD3DXBUFFER pBuffMat;	//���_�J���[���
		DWORD dwNumMat;	//�J���[�̐�
		D3DXVECTOR3 vtxMin, vtxMax;	//�I�u�W�F�N�g�̍ő�l�E�ŏ��l
		char aXfileName[MAX_NAME];
		int pTextureIdx;	//�e�N�X�`���ԍ�
	};

public:
	CXfile();
	~CXfile();

	HRESULT Load(void);
	void Unload(void);

	int Regist(const char *pXfileName);

	SXFile* GetAdrress(int nIdx);
	D3DXVECTOR3 GetMax(int nIdx) { return m_aXFile[nIdx]->vtxMax; }
	D3DXVECTOR3 GetMin(int nIdx) { return m_aXFile[nIdx]->vtxMin; }
	char* GetFileName(int nIdx) { return &m_aXFile[nIdx]->aXfileName[0]; }
	int GetNumAll(void) { return m_nNumAll; }

private:
	void VtxMaxMin(int nNowCount);
	static SXFile *m_aXFile[MAX_FILE];
	static int m_nNumAll;
};

#endif