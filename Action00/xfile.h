////===============================================================================
////
//// [Xfile.h]
//// Author : Takeru Ogasawara
////
////===============================================================================
//#ifndef _XFILE_H_				//���̃}�N����`������Ă��Ȃ�������
//#define _XFILE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`
//
//#include "main.h"
//
////�e�N�X�`���N���X
//class CXfile
//{
//private:
//	static const int MAX_FILE = 64;
//	static const int MAX_NAME = 254;
//
//private:
//	//X�t�@�C�����̍\����
//	struct SXFile
//	{
//		LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//�o�b�t�@�ւ̒��_���
//		D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
//		LPD3DXMESH pMesh;					//�g�p����Ă��郂�f����
//		LPD3DXBUFFER pBuffMat;			//���_�J���[���
//		DWORD dwNumMat;					//�J���[�̐�
//		D3DXVECTOR3 vtxMin, vtxMax;		//�I�u�W�F�N�g�̍ő�l�E�ŏ��l
//		const char aXfileName[MAX_NAME];
//		int *nTextureIdx;					//�e�N�X�`���ԍ�
//	};
//
//public:
//	CXfile();
//	~CXfile();
//
//	static HRESULT Load(int nIdx);
//	void Unload(void);
//
//	int Regist(const char *pXfileName);
//
//	D3DXVECTOR3 GetMax(int nIdx) { return m_aXFile[nIdx].vtxMax; }
//	D3DXVECTOR3 GetMin(int nIdx) { return m_aXFile[nIdx].vtxMin; }
//
//private:
//	
//	SXFile m_aXFile[MAX_FILE];
//	static int m_nNumAll;
//};
//
//#endif