//===========================================================================================
//
// [effect3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "effect3D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//�}�N����`
#define DEC_COL			(0.04f)
#define DEC_SIZE		(0.05f)

//�ÓI�����o�ϐ��錾
int CEffect3D::m_nTextureIdx = 0;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CEffect3D::CEffect3D(int nPriority) : CBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 0;
	m_nMaxLife = 0;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CEffect3D::~CEffect3D()
{

}

//===========================================================================================
// �e�N�X�`���ǂݍ���
//===========================================================================================
HRESULT CEffect3D::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�g�������e�N�X�`�������w��
	m_nTextureIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\effect000.jpg");

	return S_OK;
}

//===========================================================================================
// ����
//===========================================================================================
CEffect3D *CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	CEffect3D *pEffect3D = NULL;

	if (pEffect3D == NULL)
	{
		pEffect3D = new CEffect3D;

		if (pEffect3D != NULL)
		{
			//����������
			pEffect3D->Init();

			//�����ʒu�̐ݒ�
			pEffect3D->SetPosition(pos);

			//�T�C�Y�ݒ�
			pEffect3D->SetRadius(D3DXVECTOR2(fRadius, fRadius));

			//�ړ��ʐݒ�
			pEffect3D->m_move = move;

			//�F�ݒ�
			pEffect3D->SetColor(col);

			//�̗͐ݒ�
			pEffect3D->SetLife(nLife);

			//�e�N�X�`�����蓖��
			pEffect3D->BindTexture(m_nTextureIdx);

			return pEffect3D;
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
HRESULT CEffect3D::Init(void)
{
	//����������
	CBillboard::Init();

	m_nLife = 100;
	m_nMaxLife = 100;

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CEffect3D::Uninit(void)
{
	//�I������
	CBillboard::Uninit();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CEffect3D::Update(void)
{
	float fLength = 0.0f/* = GetLength()*/;
	m_col = GetColor();

	//�̗͂̌��Z
	m_nLife--;

	//�G�t�F�N�g�̔j��
	if (m_nLife <= 0 || fLength <= 0.0f || m_col.a <= 0.0f)
	{//�����ꂩ�̐��l��0�ȉ��ɂȂ�����

		//�j��
		Uninit();
	}
	else
	{
		//�ʒu���̎擾
		D3DXVECTOR3 pos = GetPosition();

		//�ʒu�Ɉړ��ʂ����Z
		pos += m_move;

		//�ʒu�̐ݒ�
		SetPosition(pos);

		//�J���[�̌��Z//���̎������}�b�N�X�̎���
		m_col.a -= DEC_COL;

		//���a�̌��Z//���̎������}�b�N�X�̎���
		fLength -= DEC_SIZE;

		//���_�ݒ�
		SetSize(D3DXVECTOR2(fLength, fLength));

		//�F�ݒ�
		SetColor(m_col);
	}
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CEffect3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//a�u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================================================================================
// �̗͐ݒ�
//===========================================================================================
void CEffect3D::SetLife(int life)
{
	m_nLife = life;
	m_nMaxLife = life;
}
