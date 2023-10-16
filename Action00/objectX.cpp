//===========================================================================================
//
// [objectX.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "object.h"

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_dwNumMat = NULL;
	
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	m_vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nModelIdx = 0;
	m_nTextureIdx = 0;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CObjectX::~CObjectX()
{

}

//===========================================================================================
// ����
//===========================================================================================
CObjectX * CObjectX::Create(void)
{
	CObjectX *pObjX = NULL;

	if (pObjX == NULL)
	{
		pObjX = new CObjectX;

		if (pObjX != NULL)
		{
			pObjX->Init();

			return pObjX;
		}
		else
		{
			return NULL;
		}
	}

	return S_OK;
}

//===========================================================================================
// ����
//===========================================================================================
CObjectX *CObjectX::Create(const char *c_pFileName, D3DXVECTOR3 pos)
{
	CObjectX *pObjX = NULL;

	if (pObjX == NULL)
	{
		pObjX = new CObjectX;

		if (pObjX != NULL)
		{
			//����������
			pObjX->Init(c_pFileName, pos);

			//�ʒu�ݒ�
			pObjX->SetPosition(pos);
			pObjX->m_pos = pos;

			return pObjX;
		}
		else
		{
			return NULL;
		}
	}

	return S_OK;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CObjectX::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	//��ސݒ�
	//SetType(TYPE_OBJECTX);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\murabito\\atama.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &m_pBuffMat,
		NULL, &m_dwNumMat,
		&m_pMesh);

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�t�@�C������e�N�X�`����ǂݍ���
			m_nTextureIdx = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	return S_OK;
}

//===========================================================================================
// ����������(�I�[�o�[���[�h)
//===========================================================================================
HRESULT CObjectX::Init(const char *c_pFileName, D3DXVECTOR3 pos)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATERIAL *pMat;			//�}�e���A���ւ̃|�C���^

	//��ސݒ�
	SetType(TYPE_OBJECTX);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(c_pFileName,
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &m_pBuffMat,
		NULL, &m_dwNumMat,
		&m_pMesh);

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�t�@�C������e�N�X�`����ǂݍ���
			m_nTextureIdx = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	DWORD dwSizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	int nNumVtx;			//���_��

	//���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//���_���W�̑��

		if (m_vtxMax.x < vtx.x)
		{//x���傫��������
			m_vtxMax.x = vtx.x;
		}
		if (m_vtxMax.z < vtx.z)
		{//z�̒l���傫��������
			m_vtxMax.z = vtx.z;
		}

		if (m_vtxMin.x > vtx.x)
		{//x��������������
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMin.z > vtx.z)
		{//z�̒l���傫��������
			m_vtxMin.z = vtx.z;
		}

		if (m_vtxMax.y < vtx.y)
		{//x���傫��������
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y > vtx.y)
		{//x��������������
			m_vtxMin.y = vtx.y;
		}

		pVtxBuff += dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CObjectX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}		

	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	//�Y������I�u�W�F�N�g�̔j��
	Release();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CObjectX::Update(void)
{
	m_pos = GetPosition();
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CObjectX::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat[nCntMat].pTextureFilename != NULL && m_nTextureIdx > 0)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAddress(m_nTextureIdx));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}

		//�I�u�W�F�N�g(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ�����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================
// �����蔻��
//===========================================================================================
bool CObjectX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pVtxMax, D3DXVECTOR3 pVtxMin)
{
	bool bUse = false;

	//�I�u�W�F�N�g�Ƃ̓����蔻��
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			CObjectX *pObjectX = CObject::GetObjectX();

			if (pObjectX == nullptr)
			{
				continue;
			}

			D3DXVECTOR3 pos = pObjectX->GetPosition();
			D3DXVECTOR3 vtxMax = pObjectX->GetVtxMax();
			D3DXVECTOR3 vtxMin = pObjectX->GetVtxMin();

			if (pPos->y + pVtxMax.y > pos.y + vtxMin.y &&
				pPos->y + pVtxMin.y < pos.y + vtxMax.y)
			{//�㉺�̓����蔻��
				if (pPos->x + pVtxMax.x > pos.x + vtxMin.x &&
					pPos->x + pVtxMin.x < pos.x + vtxMax.x)
				{//���E�̓����蕝�̎w��
					if (pPosOld->z + pVtxMax.z <= pos.z + vtxMin.z &&
						pPos->z + pVtxMax.z >= pos.z + vtxMin.z)
					{//�O�̓����蔻��
						pPos->z = pos.z + vtxMin.z - pVtxMax.z;
						pMove->z = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
					if (pPosOld->z + pVtxMin.z >= pos.z + vtxMax.z &&
						pPos->z + pVtxMin.z < pos.z + vtxMax.z)
					{//��̓����蔻��
						pPos->z = pos.z + vtxMax.z - pVtxMin.z;
						pMove->z = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
				}

				if (pPos->z + pVtxMax.z > pos.z + vtxMin.z &&
					pPos->z + pVtxMin.z < pos.z + vtxMax.z)
				{//�㉺�̓����蕝�̎w��
					if (pPosOld->x + pVtxMax.x + SIZE <= pos.x + vtxMin.x &&
						pPos->x + pVtxMax.x + SIZE >= pos.x + vtxMin.x)
					{//���̓����蔻��
						pPos->x = pos.x + vtxMin.x + pVtxMin.x - SIZE;
						pMove->x = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
					if (pPosOld->x + pVtxMin.x - SIZE >= pos.x + vtxMax.x &&
						pPos->x + pVtxMin.x - SIZE <= pos.x + vtxMax.x)
					{//�E�̓����蔻��
						pPos->x = pos.x + vtxMax.x + pVtxMax.x + SIZE;
						pMove->x = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
				}
			}
		}
	}

	return bUse;
}