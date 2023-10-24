//===========================================================================================
//
// [object3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "object3D.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"

//�}�N����`
#define SIZE			(D3DXVECTOR3(500.0f, 0.0f, 500.0f))

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CObject3D::CObject3D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pVtxBuff = nullptr;
	m_nTextureIdx = 0;
	m_type = TYPE_NONE;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CObject3D::~CObject3D()
{

}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���
//===========================================================================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		pObject3D = new CObject3D;

		if (pObject3D != nullptr)
		{
			pObject3D->Init();

			return pObject3D;
		}
		else
		{
			return nullptr;
		}
	}

	return S_OK;
}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���[�I�o�[���[�h] : Create(�ʒu)
//===========================================================================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		pObject3D = new CObject3D;

		if (pObject3D != nullptr)
		{
			pObject3D->Init();

			pObject3D->SetPosition(pos);

			//�e�N�X�`���̊��蓖��
			//pObject3D->BindTexture(m_nTextureIdx);

			return pObject3D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject3D;
}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���[�I�o�[���[�h] : Create(�ʒu�A�^�C�v) 
//===========================================================================================
CObject3D * CObject3D::Create(D3DXVECTOR3 pos, TYPE type)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		pObject3D = new CObject3D;

		if (pObject3D != nullptr)
		{
			pObject3D->SetType(type);		//��ސݒ�

			pObject3D->Init();	//������

			pObject3D->SetPosition(pos);	//�ʒu�ݒ�

			return pObject3D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject3D;
}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���[�I�o�[���[�h] : Create(�ʒu�A�e�N�X�`����) 
//===========================================================================================
CObject3D * CObject3D::Create(D3DXVECTOR3 pos, const char *cTexName)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		pObject3D = new CObject3D;

		if (pObject3D != nullptr)
		{
			pObject3D->Init();	//������

			pObject3D->SetPosition(pos);	//�ʒu�ݒ�

			//�e�N�X�`���̊��蓖��
			pObject3D->BindTexture(pTexture->Regist(cTexName));

			return pObject3D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject3D;
}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���[�I�o�[���[�h] : Create(�ʒu�A�傫���A�e�N�X�`����) 
//===========================================================================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, const char * cTexName)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		pObject3D = new CObject3D;

		if (pObject3D != nullptr)
		{
			pObject3D->Init();	//������

			pObject3D->SetPosition(pos);	//�ʒu�ݒ�

			pObject3D->SetSize_field(size.x, size.y);

			//�e�N�X�`���̊��蓖��
			pObject3D->BindTexture(pTexture->Regist(cTexName));

			return pObject3D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject3D;
}

//===========================================================================================
// �I�u�W�F�N�g3D�̐���[�I�o�[���[�h] : Create(�ʒu�A�傫���A�F�A�e�N�X�`����) 
//===========================================================================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXCOLOR col, const char *cTexName)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	CObject3D *pObject3D = nullptr;

	if (pObject3D == nullptr)
	{
		pObject3D = new CObject3D;

		if (pObject3D != nullptr)
		{
			pObject3D->Init();	//������

			pObject3D->SetPosition(pos);	//�ʒu�ݒ�

			pObject3D->SetSize_field(size.x, size.y);	//�傫���ݒ�

			pObject3D->SetColor(col);

			//�e�N�X�`���̊��蓖��
			pObject3D->BindTexture(pTexture->Regist(cTexName));

			return pObject3D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject3D;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CObject3D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//��ނ̐ݒ�
	//CObject::SetType(CObject::TYPE_OBJECT3D);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//���_�ݒ�
	switch (m_type)
	{
	case TYPE_FIELD:
		m_size.x = SIZE.x;
		m_size.z = SIZE.z;
		SetVerTex_field();
		break;

	case TYPE_WALL:
		m_size.x = SIZE.x;
		m_size.z = SIZE.y;
		SetVerTex_wall();
		break;

	default:
		SetVerTex_field();
		break;
	}
	
	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�������g�̔j��
	Release();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CObject3D::Update(void)
{
	D3DXVECTOR3 pos = m_pos;

	//���_�ݒ�
	switch (m_type)
	{
	case TYPE_FIELD:
		SetVerTex_field();
		break;

	case TYPE_WALL:
		SetVerTex_wall();
		break;

	default:
		SetVerTex_field();
		break;
	}

	//�f�o�b�O�\��
	CManager::GetInstance()->GetDebugProc()->Print("\n\n[�I�u�W�F�N�g3D���]");
	CManager::GetInstance()->GetDebugProc()->Print("\n�ʒu�F x:%f y:%f z:%f", m_pos.x, m_pos.y, m_pos.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n�����F x:%f y:%f z:%f", m_rot.x, m_rot.y, m_rot.z);
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CObject3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	
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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0,
		sizeof(VERTEX_3D));			//���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTextureIdx));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
		0,						//�`�悷��ŏ��̃C���f�b�N�X
		2);						//�|���S����
}

//===========================================================================================
// ���_���̐ݒ�(�t�B�[���h�^)
//===========================================================================================
void CObject3D::SetVerTex_field(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, +m_size.z);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, 0.0f, +m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, 0.0f, -m_size.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[(0.0f�`1.0f���Őݒ�)
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================================================
// ���_���̐ݒ�(�E�H�[���^)
//===========================================================================================
void CObject3D::SetVerTex_wall(void)
{
	D3DXVECTOR3 pos = m_pos;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[(0.0f�`1.0f���Őݒ�)
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	pos = m_pos;
}

//===========================================================================================
// �傫���ݒ�(�t�B�[���h)
//===========================================================================================
void CObject3D::SetSize_field(float x, float z)
{
	m_size.x = x;
	m_size.z = z;
}

//===========================================================================================
// �傫���ݒ�(�E�H�[��)
//===========================================================================================
void CObject3D::SetSize_wall(float x, float y)
{
	m_size.x = x;
	m_size.y = y;
}

//===========================================================================================
// �F�̐ݒ�
//===========================================================================================
void CObject3D::SetColor(D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[(0.0f�`1.0f���Őݒ�)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================================================================
// �e�N�X�`���ԍ��̊��蓖��
//===========================================================================================
void CObject3D::BindTexture(int nIdx)
{
	m_nTextureIdx = nIdx;
}
