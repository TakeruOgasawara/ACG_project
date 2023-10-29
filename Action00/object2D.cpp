//===========================================================================================
//
// [object2D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"

//�}�N����`
#define SIZE_X		(100.0f)	//���̒���
#define SIZE_Y		(100.0f)	//�c�̒���

//�ÓI�����o�ϐ��錾
int CObject2D::m_nNumObj2D = 0;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nTextureIdx = 0;

	m_nNumObj2D++;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CObject2D::~CObject2D()
{
	m_nNumObj2D--;
}

//===========================================================================================
// ��������(�����l)
//===========================================================================================
CObject2D *CObject2D::Create(void)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//����������
			pObject2D->Init();

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

//===========================================================================================
// ��������(�ʒu)
//===========================================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//����������
			pObject2D->Init();

			//�ʒu�̐ݒ菈��
			pObject2D->SetPosition(pos);

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

//===============================================
// ����
//===============================================
CObject2D *CObject2D::Create(const int nPriority)
{
	CObject2D *pObject2D = nullptr;

	// �I�u�W�F�N�g2D�̐���
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != NULL)
	{
		pObject2D->Init();

		pObject2D->SetType(TYPE_NONE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObject2D;
}
//===========================================================================================
// ��������(�ʒu�A��])
//===========================================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//����������
			pObject2D->Init();

			pObject2D->SetPosition(pos);
			pObject2D->SetRotation(rot);

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject2D;
}

//===========================================================================================
// ��������(�ʒu�A�e�N�X�`����)
//===========================================================================================
CObject2D * CObject2D::Create(D3DXVECTOR3 pos, const char *name)
{
	CObject2D *pObject2D = nullptr;
	CTexture *pTex = CManager::GetInstance()->GetTexture();

	if (pObject2D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//����������
			pObject2D->Init();

			pObject2D->SetPosition(pos);

			pObject2D->BindTexture(pTex->Regist(name));

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject2D;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CObject2D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�ʒu(�f�t�H���g)
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 0.0f);

	//�T�C�Y�ݒ�(�f�t�H���g)
	m_fWidth = SIZE_X;
	m_fHeight = SIZE_Y;

	//�Ίp���̒������Z�o(�f�t�H���g)
	m_fLength = sqrtf(SIZE_X * SIZE_X + SIZE_Y * SIZE_Y) * 0.5f;

	//�Ίp���̊p�x���Z�o����(�f�t�H���g)
	m_fAngle = atan2f(SIZE_X, SIZE_Y);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���̐ݒ�(�f�t�H���g)
	SetVertex();

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CObject2D::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�j��
	Release();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CObject2D::Update(void)
{

}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CObject2D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�e�N�X�`�����̎擾
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));			//���_���\���̂̃T�C�Y

	//�e�N�X�`���̐ݒ�
	if (pTexture != NULL)
	{
		pDevice->SetTexture(0, pTexture->GetAddress(m_nTextureIdx));
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
		0,			//�`�悷��ŏ��̃C���f�b�N�X(�厖)
		2);			//�v���~�e�B�u(�|���S��)��
}

//=======================================================
// ���_���̐ݒ�(�f�t�H���g&&)
//=======================================================
void CObject2D::SetVertex(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
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

//=======================================================
// ���_���̐ݒ�(�P���Ȃ��̗p)
//=======================================================
void CObject2D::SetVertex(D3DXVECTOR2 size)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y + size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=======================================================
// ���_���̐ݒ�(�X�N���[���p)
//=======================================================
void CObject2D::SetVertex(float fWidth, float fHeight, float fSpeedx, float fSpeedy)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth, m_pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth, m_pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y + fHeight, 0.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(fSpeedx, fSpeedy);
	pVtx[1].tex = D3DXVECTOR2(fSpeedx + 1.0f, fSpeedy);
	pVtx[2].tex = D3DXVECTOR2(fSpeedx, fSpeedy + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fSpeedx + 1.0f, fSpeedy + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=======================================================
// �ʒu�̐ݒ�
//=======================================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	//��������l���擾
	m_pos = pos;

	//���_���
	SetVertex();
}

//=======================================================
// �ʒu���̎擾
//=======================================================
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

//=======================================================
// �����̐ݒ�
//=======================================================
void CObject2D::SetRotation(D3DXVECTOR3 rot)
{
	//��������l���擾
	m_rot = rot;

	//���_���
	SetVertex();
}

//=======================================================
// �����̎擾
//=======================================================
D3DXVECTOR3 CObject2D::GetRotation(void)
{
	return m_rot;
}

//=======================================================
// �F�̐ݒ�
//=======================================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�F�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=======================================================
// �F�̎擾
//=======================================================
D3DXCOLOR CObject2D::GetColor(void)
{
	return m_col;
}

//=======================================================
// �|���S���T�C�Y�̎擾
//=======================================================
D3DXVECTOR2 CObject2D::GetSize(void)
{
	return D3DXVECTOR2(m_fWidth, m_fHeight);
}

//=======================================================
// �|���S���T�C�Y�̐ݒ�
//=======================================================
void CObject2D::SetSizeCenter(float fWidth, float fHeight)
{
	//�T�C�Y�̐ݒ�(�������g�p���Ȃ��ꍇ)
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=======================================================
// �|���S���T�C�Y�̐ݒ�
//=======================================================
void CObject2D::SetSize_lefteEnd(float fWidth, float fHeight)
{
	//�T�C�Y�̐ݒ�(�������g�p���Ȃ��ꍇ)
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=======================================================
// �|���S���T�C�Y�̐ݒ�
//=======================================================
void CObject2D::SetSizeLength(float fWidth, float fHeight)
{
	//�Ίp���̒������Z�o����(�������g�p����ꍇ)
	m_fLength = sqrtf(fWidth * fWidth + fHeight * fHeight) * 0.5f;

	//�Ίp���̊p�x���Z�o����(�������g�p����ꍇ)
	m_fAngle = atan2f(fWidth, fHeight);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=======================================================
// �|���S���T�C�Y�̐ݒ�
//=======================================================
float CObject2D::GetAngle(void)
{
	return m_fAngle;
}

//=======================================================
// �p�x�̎擾
//=======================================================
float CObject2D::GetLength(void)
{
	return m_fLength;
}

//=======================================================
// �e�N�X�`���̔ԍ����蓖��
//=======================================================
void CObject2D::BindTexture(int nIdx)
{
	m_nTextureIdx = nIdx;
}

//=======================================================
// ���_���̎擾
//=======================================================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetVtxBuff(void)
{
	return m_pVtxBuff;
}
