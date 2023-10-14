//===========================================================================================
// 
// [texture.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdlib.h>
#include "xfile.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//�ÓI�����o�ϐ��錾
int CXfile::m_nNumAll = 0;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CXfile::CXfile()
{
	for (int nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{
		m_apXFileInfo[nCntFile] = nullptr;
	}
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CXfile::~CXfile()
{

}

//===========================================================================================
// X�t�@�C����S�ēǂݍ���(����������)
//===========================================================================================
HRESULT CXfile::Load(int nIdx)
{
	//�|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetTexture();

	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^
	DWORD dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	int nNumVtx;			//���_��
	
	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(&m_apXFileInfo[nIdx]->aXfileName[0],
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_apXFileInfo[nIdx]->XFileData.m_pBuffMat,
		NULL,
		&m_apXFileInfo[nIdx]->XFileData.m_dwNumMat,
		&m_apXFileInfo[nIdx]->XFileData.m_pMesh)))
	{
		return E_FAIL;		//�ǂݍ��ݎ��s
	}

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_apXFileInfo[nIdx]->XFileData.m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_apXFileInfo[nIdx]->XFileData.m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			//�t�@�C������e�N�X�`����ǂݍ���
			pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	//���_�����擾
	nNumVtx = m_apXFileInfo[nIdx]->XFileData.m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_apXFileInfo[nIdx]->XFileData.m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_apXFileInfo[nIdx]->XFileData.m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//���_���W�̑��

		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMax.x < vtx.x)
		{//x���傫��������
			m_apXFileInfo[nIdx]->XFileData.m_vtxMax.x = vtx.x;
		}
		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMax.z < vtx.z)
		{//z�̒l���傫��������
			m_apXFileInfo[nIdx]->XFileData.m_vtxMax.z = vtx.z;
		}

		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMin.x > vtx.x)
		{//x��������������
			m_apXFileInfo[nIdx]->XFileData.m_vtxMin.x = vtx.x;
		}
		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMin.z > vtx.z)
		{//z�̒l���傫��������
			m_apXFileInfo[nIdx]->XFileData.m_vtxMin.z = vtx.z;
		}

		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMax.y < vtx.y)
		{//x���傫��������
			m_apXFileInfo[nIdx]->XFileData.m_vtxMax.y = vtx.y;
		}
		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMin.y > vtx.y)
		{//x��������������
			m_apXFileInfo[nIdx]->XFileData.m_vtxMin.y = vtx.y;
		}

		pVtxBuff += dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_apXFileInfo[nIdx]->XFileData.	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//===========================================================================================
// �S�Ĕj������(�I������)
//===========================================================================================
void CXfile::Unload(void)
{
	for (int nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{
		if (m_apXFileInfo[nCntFile] != nullptr)
		{
			if (m_apXFileInfo[nCntFile]->XFileData.m_pBuffMat != nullptr)
			{
				m_apXFileInfo[nCntFile]->XFileData.m_pBuffMat->Release();
				m_apXFileInfo[nCntFile]->XFileData.m_pBuffMat = nullptr;
			}

			if (m_apXFileInfo[nCntFile]->XFileData.m_pMesh != nullptr)
			{
				m_apXFileInfo[nCntFile]->XFileData.m_pMesh->Release();
				m_apXFileInfo[nCntFile]->XFileData.m_pMesh = nullptr;
			}
		}
	}
}

//===========================================================================================
// X�t�@�C���Ɋ��蓖�Ă�ꂽ�ԍ���Ԃ�
//===========================================================================================
int CXfile::Regist(const char *c_pXfileName)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	//�ϐ��錾
	int nCntFile = 0;			//for�J�E���g�p

	for (nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{//�e�N�X�`���̍ő吔���܂��

		if (m_apXFileInfo[nCntFile] == nullptr)
		{//NULL�̏ꍇ
			continue;
		}
		else if (strstr(c_pXfileName, &m_apXFileInfo[nCntFile]->aXfileName[0]))
		{
			return nCntFile;
		}
	}

	return -1;			//NULL
}