////===========================================================================================
//// 
//// [texture.cpp]
//// Author : Takeru Ogasawara
////
////===========================================================================================
//#include <stdlib.h>
//#include "xfile.h"
//#include "renderer.h"
//#include "manager.h"
//#include "texture.h"
//
////�ÓI�����o�ϐ��錾
//int CXfile::m_nNumAll = 0;	//�ǂݍ��񂾑���
//
////===========================================================================================
//// �R���X�g���N�^
////===========================================================================================
//CXfile::CXfile()
//{
//	for (int nCntData = 0; nCntData < MAX_FILE; nCntData++)
//	{
//		m_aXFile[nCntData].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���f���̍ŏ��l
//		m_aXFile[nCntData].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���f���̍ő�l
//		m_aXFile[nCntData].pVtxBuff = nullptr;								// ���_�o�b�t�@�̃|�C���^
//		m_aXFile[nCntData].pMesh = nullptr;								// ���b�V��(���_���)�ւ̃|�C���^
//		m_aXFile[nCntData].pBuffMat = nullptr;								// �}�e���A���ւ̃|�C���^
//		m_aXFile[nCntData].dwNumMat = 0;								// �}�e���A���̐�
//		m_aXFile[nCntData].nTextureIdx = nullptr;							// �e�N�X�`���̃C���f�b�N�X�ԍ�
//	}
//}
//
////===========================================================================================
//// �f�X�g���N�^
////===========================================================================================
//CXfile::~CXfile()
//{
//
//}
//
////===========================================================================================
//// X�t�@�C����S�ēǂݍ���(����������)
////===========================================================================================
//HRESULT CXfile::Load(int nIdx)
//{
//	//�|�C���^�擾
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer().GetDevice();
//	CTexture *pTexture = CManager::GetTexture();
//
//	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^
//	DWORD dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
//	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
//	int nNumVtx;			//���_��
//	
//	//X�t�@�C���̓ǂݍ���
//	if (FAILED(D3DXLoadMeshFromX(m_aXFile[nIdx].aXfileName[0],
//		D3DXMESH_SYSTEMMEM, pDevice,
//		NULL,
//		m_aXFile[nIdx].XFileData.m_pBuffMat,
//		NULL,
//		m_aXFile[nIdx].XFileData.m_dwNumMat,
//		m_aXFile[nIdx].XFileData.m_pMesh)))
//	{
//		return E_FAIL;		//�ǂݍ��ݎ��s
//	}
//
//	//�}�e���A���ւ̃|�C���^���擾
//	pMat = (D3DXMATERIAL*)m_aXFile[nIdx].XFileData.m_pBuffMat.GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)m_aXFile[nIdx].XFileData.m_dwNumMat; nCntMat++)
//	{
//		if (pMat[nCntMat].pTextureFilename != nullptr)
//		{
//			//�t�@�C������e�N�X�`����ǂݍ���
//			pTexture.Regist(pMat[nCntMat].pTextureFilename);
//		}
//	}
//
//	//���_�����擾
//	nNumVtx = m_aXFile[nIdx].XFileData.m_pMesh.GetNumVertices();
//
//	//���_�t�H�[�}�b�g�̃T�C�Y���擾
//	dwSizeFVF = D3DXGetFVFVertexSize(m_aXFile[nIdx].XFileData.m_pMesh.GetFVF());
//
//	//���_�o�b�t�@�����b�N
//	m_aXFile[nIdx].XFileData.m_pMesh.LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
//	{
//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//���_���W�̑��
//
//		if (m_aXFile[nIdx].XFileData.m_vtxMax.x < vtx.x)
//		{//x���傫��������
//			m_aXFile[nIdx].XFileData.m_vtxMax.x = vtx.x;
//		}
//		if (m_aXFile[nIdx].XFileData.m_vtxMax.z < vtx.z)
//		{//z�̒l���傫��������
//			m_aXFile[nIdx].XFileData.m_vtxMax.z = vtx.z;
//		}
//
//		if (m_aXFile[nIdx].XFileData.m_vtxMin.x > vtx.x)
//		{//x��������������
//			m_aXFile[nIdx].XFileData.m_vtxMin.x = vtx.x;
//		}
//		if (m_aXFile[nIdx].XFileData.m_vtxMin.z > vtx.z)
//		{//z�̒l���傫��������
//			m_aXFile[nIdx].XFileData.m_vtxMin.z = vtx.z;
//		}
//
//		if (m_aXFile[nIdx].XFileData.m_vtxMax.y < vtx.y)
//		{//x���傫��������
//			m_aXFile[nIdx].XFileData.m_vtxMax.y = vtx.y;
//		}
//		if (m_aXFile[nIdx].XFileData.m_vtxMin.y > vtx.y)
//		{//x��������������
//			m_aXFile[nIdx].XFileData.m_vtxMin.y = vtx.y;
//		}
//
//		pVtxBuff += dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	m_aXFile[nIdx].XFileData.	m_pMesh.UnlockVertexBuffer();
//
//	return S_OK;
//}
//
////===========================================================================================
//// �S�Ĕj������(�I������)
////===========================================================================================
//void CXfile::Unload(void)
//{
//	for (int nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
//	{
//		if (m_aXFile[nCntFile] != nullptr)
//		{
//			if (m_aXFile[nCntFile].XFileData.m_pBuffMat != nullptr)
//			{
//				m_aXFile[nCntFile].XFileData.m_pBuffMat.Release();
//				m_aXFile[nCntFile].XFileData.m_pBuffMat = nullptr;
//			}
//
//			if (m_aXFile[nCntFile].XFileData.m_pMesh != nullptr)
//			{
//				m_aXFile[nCntFile].XFileData.m_pMesh.Release();
//				m_aXFile[nCntFile].XFileData.m_pMesh = nullptr;
//			}
//		}
//	}
//}
//
////===========================================================================================
//// X�t�@�C���Ɋ��蓖�Ă�ꂽ�ԍ���Ԃ�
////===========================================================================================
//int CXfile::Regist(const char *c_pXfileName)
//{
//	//�f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer().GetDevice();
//
//	//D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^
//
//	//�ϐ��錾
//	int nCntFile = 0;			//for�J�E���g�p
//
//	for (nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
//	{//�e�N�X�`���̍ő吔���܂��
//
//		if (m_aXFile[nCntFile] == nullptr)
//		{//NULL�̏ꍇ
//			continue;
//		}
//		else if (strstr(c_pXfileName, &m_aXFile[nCntFile].aXfileName[0]))
//		{
//			return nCntFile;
//		}
//	}
//
//	return -1;			//NULL
//}