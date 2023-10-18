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
CXfile::SXFile *CXfile::m_aXFile[MAX_FILE] = {};
int CXfile::m_nNumAll = 0;	//�ǂݍ��񂾑���

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CXfile::CXfile()
{
	for (int nCntData = 0; nCntData < MAX_FILE; nCntData++)
	{
		m_aXFile[nCntData] = nullptr;
	}
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CXfile::~CXfile()
{

}

//===========================================================================================
// X�t�@�C����ǂݍ���(����������)
//===========================================================================================
HRESULT CXfile::Load(void)
{
	// �ŏ��ɓǂݍ���x�t�@�C���ꗗ
	const char *aFileList[MAX_FILE] =
	{
		"data\\MODEL\\object\\floor00.x",
		"data\\MODEL\\object\\blockTile00.x",
		"data\\MODEL\\object\\bigTV.x",
	};

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (aFileList[nCntTex] != nullptr)
		{
			Regist(aFileList[nCntTex]);
		}
		else
		{
			break;
		}
	}

	return S_OK;
}

//===========================================================================================
// �S�Ĕj������(�I������)
//===========================================================================================
void CXfile::Unload(void)
{
	for (int nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{
		if (m_aXFile[nCntFile] != nullptr)
		{
			//�t�@�C�������N���A
			ZeroMemory(&m_aXFile[nCntFile]->aXfileName, sizeof(m_aXFile[nCntFile]->aXfileName));
			
			if (m_aXFile[nCntFile]->pBuffMat != nullptr)
			{
				m_aXFile[nCntFile]->pBuffMat->Release();
				m_aXFile[nCntFile]->pBuffMat = nullptr;
			}

			if (m_aXFile[nCntFile]->pMesh != nullptr)
			{
				m_aXFile[nCntFile]->pMesh->Release();
				m_aXFile[nCntFile]->pMesh = nullptr;
			}

			delete m_aXFile[nCntFile];
			m_aXFile[nCntFile] = nullptr;

			m_nNumAll--;
		}
	}
}

//===========================================================================================
// X�t�@�C���Ɋ��蓖�Ă�ꂽ�ԍ���Ԃ�
//===========================================================================================
int CXfile::Regist(const char *c_pXfileName)
{
	//�|�C���^�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	CTexture* pTexture = CManager::GetInstance()->GetTexture();	//�e�N�X�`���|�C���^�̎擾
	D3DXMATERIAL *pMat;	//�}�e���A���|�C���^

	if (c_pXfileName == nullptr)
	{
		return -1;
	}

	for (int nCnt = 0; nCnt < MAX_FILE; nCnt++)
	{
		if (m_aXFile[nCnt] != nullptr)
		{
			if (strcmp(&m_aXFile[nCnt]->aXfileName[0], c_pXfileName) == 0)
			{//���炩���ߗp�ӂ��ꂽ�t�@�C�����ƈ����̃t�@�C�����������������ꍇ

				return nCnt;	//�ԍ���Ԃ�
			}

			continue;
		}

		//�|�C���^�𐶐�
		m_aXFile[nCnt] = new SXFile;

		//�l���N���A����
		ZeroMemory(m_aXFile[nCnt], sizeof(SXFile));

		if (m_aXFile[nCnt] != nullptr)
		{
			//X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(c_pXfileName,
				D3DXMESH_SYSTEMMEM, pDevice,
				NULL,
				&m_aXFile[nCnt]->pBuffMat,
				NULL,
				&m_aXFile[nCnt]->dwNumMat,
				&m_aXFile[nCnt]->pMesh)))
			{
				return E_FAIL;	//�ǂݍ��ݎ��s
			}

			//�e�N�X�`��������������
			strcpy(&m_aXFile[nCnt]->aXfileName[0], c_pXfileName);

			//�}�e���A���ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)m_aXFile[nCnt]->pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_aXFile[nCnt]->dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != nullptr)
				{
					//�t�@�C������e�N�X�`����ǂݍ���
					m_aXFile[nCnt]->pTextureIdx = pTexture->Regist(pMat[nCntMat].pTextureFilename);
				}
			}

			//�I�u�W�F�N�g�T�C�Y���Z�o����֐�
			VtxMaxMin(nCnt);

			m_nNumAll++;	//�����J�E���g�A�b�v

			return nCnt;
		}
	}

	return -1;	//NULL
}

//===========================================================================================
// �I�u�W�F�N�g�̃T�C�Y���Z�o
//===========================================================================================
void CXfile::VtxMaxMin(int nNowCount)
{
	DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	int nNumVtx;	//���_��

	//���_�����擾
	nNumVtx = m_aXFile[nNowCount]->pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_aXFile[nNowCount]->pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_aXFile[nNowCount]->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

	if (m_aXFile[nNowCount]->vtxMax.x < vtx.x)
	{//x���傫��������
		m_aXFile[nNowCount]->vtxMax.x = vtx.x;
	}
	if (m_aXFile[nNowCount]->vtxMax.z < vtx.z)
	{//z�̒l���傫��������
		m_aXFile[nNowCount]->vtxMax.z = vtx.z;
	}

	if (m_aXFile[nNowCount]->vtxMin.x > vtx.x)
	{//x��������������
		m_aXFile[nNowCount]->vtxMin.x = vtx.x;
	}
	if (m_aXFile[nNowCount]->vtxMin.z > vtx.z)
	{//z�̒l���傫��������
		m_aXFile[nNowCount]->vtxMin.z = vtx.z;
	}

	if (m_aXFile[nNowCount]->vtxMax.y < vtx.y)
	{//x���傫��������
		m_aXFile[nNowCount]->vtxMax.y = vtx.y;
	}
	if (m_aXFile[nNowCount]->vtxMin.y > vtx.y)
	{//x��������������
		m_aXFile[nNowCount]->vtxMin.y = vtx.y;
	}

	pVtxBuff += dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	
	//���_�o�b�t�@���A�����b�N
	m_aXFile[nNowCount]->pMesh->UnlockVertexBuffer();
}

//===========================================================================================
// �I�u�W�F�N�g�̃T�C�Y���Z�o
//===========================================================================================
CXfile::SXFile* CXfile::GetAdrress(int nIdx)
{
	if (nIdx < 0 && nIdx > m_nNumAll)
	{
		return nullptr;
	}

	return m_aXFile[nIdx];
}

