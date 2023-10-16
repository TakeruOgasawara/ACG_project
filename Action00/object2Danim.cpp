//===========================================================================================
//
// [object2Danim.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "renderer.h"
#include "manager.h"
#include "object2Danim.h"
#include "input.h"

//�}�N����`
#define SIZE_X		(100.0f)	//
#define SIZE_Y		(100.0f)	//
#define ANGLE_X		(10.0f)		//
#define ANGLE_Y		(10.0f)		//
//�A�j���[�V�����̏���
#define ANIM_FIRST			(5)					//���̐���ANIM_FIRST�ɂȂ������ŏ�����J��Ԃ�
#define ANIM_PTTERN			(8)					//�ǂݍ��ރA�j���̃p�^�[����
#define TEX_ANIM0			(4)						//�������A�j���̃p�^�[�����̔���
#define TEX_ANIM1			(0.125f)					//�������A�j��1�R�}�̉���(0.0�`1.0)
#define TEX_ANIM2			(0.5f)					//�������A�j��1�R�}�̏c��(0.0�`1.0)

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CObject2Danim::m_pTexture = NULL;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CObject2Danim::CObject2Danim()
{
	 m_pTexture = NULL;			//�e�N�X�`�����
	m_nCntPttern = 0;
	m_nPttern = 0;
	m_fTexSizeX = 0.0f;
	m_fTexSizeY = 0.0f;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CObject2Danim::~CObject2Danim()
{

}

//===========================================================================================
// �e�N�X�`���̓ǂݍ���
//===========================================================================================
HRESULT CObject2Danim::Load(void)
{
	return E_NOTIMPL;
}

//===========================================================================================
// ��������
//===========================================================================================
CObject2Danim * CObject2Danim::Create(void)
{
	CObject2Danim *pObject2Danim = NULL;

	if (pObject2Danim == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject2Danim = new CObject2Danim;

		if (pObject2Danim != NULL)
		{
			//����������
			pObject2Danim->Init();

			return pObject2Danim;
		}
		else
		{
			return NULL;
		}
	}

	return NULL;
}

//===========================================================================================
// ��������(�ʒu)
//===========================================================================================
CObject2Danim *CObject2Danim::Create(D3DXVECTOR3 pos)
{
	CObject2Danim *pObject2Danim = NULL;

	if (pObject2Danim == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject2Danim = new CObject2Danim;

		if (pObject2Danim != NULL)
		{
			//����������
			pObject2Danim->Init();

			pObject2Danim->SetPosition(pos);

			return pObject2Danim;
		}
		else
		{
			return NULL;
		}
	}

	return NULL;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CObject2Danim::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bomb0.png", &m_pTexture)))
	{
		return E_FAIL;
	}
	
	CObject2D::Init();

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CObject2Danim::Uninit(void)
{
	CObject2D::Uninit();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CObject2Danim::Update(void)
{
	
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CObject2Danim::Draw(void)
{
	CObject2D::Draw();
}

//===========================================================================================
// �A�j���[�V��������
//===========================================================================================
void CObject2Danim::SetAnimation(int nPttern)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	m_fTexSizeX = 1.0f / nPttern;
	
	if ((m_nCntPttern % ANIM_FIRST) == 0)
	{
		//�p�^�[��No.���X�V����
		m_nPttern = (m_nPttern + 1) % nPttern;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		CObject2D::GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((m_nPttern % nPttern / 2) * m_fTexSizeX, (m_nPttern / (nPttern / 2)) * TEX_ANIM2);
		pVtx[1].tex = D3DXVECTOR2((m_nPttern % nPttern / 2) * m_fTexSizeX + m_fTexSizeX, (m_nPttern / (nPttern / 2)) * TEX_ANIM2);
		pVtx[2].tex = D3DXVECTOR2((m_nPttern % nPttern / 2) * m_fTexSizeX, (m_nPttern / (nPttern / 2)) * TEX_ANIM2 + TEX_ANIM2);
		pVtx[3].tex = D3DXVECTOR2((m_nPttern % nPttern / 2) * m_fTexSizeX + m_fTexSizeX, (m_nPttern / (nPttern / 2)) * TEX_ANIM2 + TEX_ANIM2);

		//���_�o�b�t�@���A�����b�N����
		CObject2D::GetVtxBuff()->Unlock();

		if (m_nPttern == nPttern - 1)
		{
			Uninit();
		}
	}

	//�A�j���[�V�����J�E���g
	m_nCntPttern++;
}

//===========================================================================================
// �A�j���[�V��������
//===========================================================================================
void CObject2Danim::SetTexture(float fTexU, float fTexV)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	CObject2D::GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, fTexV);
	pVtx[3].tex = D3DXVECTOR2(fTexU, fTexV);

	//���_�o�b�t�@���A�����b�N����
	CObject2D::GetVtxBuff()->Unlock();
}
