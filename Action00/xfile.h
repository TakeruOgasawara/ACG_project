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

private:
	//X�t�@�C�����̍\����
	struct SData
	{
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//�o�b�t�@�ւ̒��_���
		D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
		LPD3DXMESH m_pMesh;					//�g�p����Ă��郂�f����
		LPD3DXBUFFER m_pBuffMat;			//���_�J���[���
		DWORD m_dwNumMat;					//�J���[�̐�
		D3DXVECTOR3 m_vtxMin, m_vtxMax;		//�I�u�W�F�N�g�̍ő�l�E�ŏ��l
		int *nTextureIdx;					//�e�N�X�`���ԍ�
	};

	struct  Info
	{
		SData XFileData;
		const char aXfileName[MAX_NAME];
	};

public:
	CXfile();
	~CXfile();

	HRESULT Load(int nIdx);
	void Unload(void);

	int Regist(const char *c_pXfileName);

	D3DXVECTOR3 GetMax(int nIdx) { return m_apXFileInfo[nIdx]->XFileData.m_vtxMax; }
	D3DXVECTOR3 GetMin(int nIdx) { return m_apXFileInfo[nIdx]->XFileData.m_vtxMin; }

private:
	
	Info *m_apXFileInfo[MAX_FILE];
	static int m_nNumAll;
};

#endif