//===========================================================================================
//
// [edit.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include "edit.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "object.h"
#include "objectX.h"
#include "debugproc.h"

#include "texture.h"
#include "xfile.h"

//�}�N����`
static const int MAX_TYPE = 3;
#define SPEED			(50.0f)

static char* FILENAME = "data\\TXT\\stage\\stage0.txt";

//�I�u�W�F�N�g�t�@�C����
const char *c_Obj[MAX_TYPE] =
{
	"data\\MODEL\\object\\floor00.x",
	"data\\MODEL\\object\\blockTile00.x",
	"data\\MODEL\\object\\bigTV.x",
};

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CEdit::CEdit()
{
	m_nTypeIdx = 0;
	m_bUse = false;
	m_object.BuffMat = nullptr;
	m_object.dwNumMat = NULL;
	m_object.rot = { 0.0f, 0.0f, 0.0f };
	m_object.pos = { 0.0f, 0.0f, 0.0f };
	m_pObjectX = nullptr;
	m_nIdx = 0;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CEdit::~CEdit()
{

}

//===========================================================================================
// ����
//===========================================================================================
CEdit* CEdit::Create(void)
{
	CEdit* pEdit = nullptr;

	if (pEdit == nullptr)
	{
		pEdit = new CEdit;

		return pEdit;
	}

	return nullptr;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CEdit::Init(void)
{
	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CEdit::Uninit(void)
{
	if (m_pObjectX != nullptr)
	{
		delete m_pObjectX;
		m_pObjectX = nullptr;
	}
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CEdit::Update(void)
{
	//�L�[�{�[�h���̎擾
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();
	CXfile* pXfile = CManager::GetInstance()->GetXfile();

	if (pInputKey->GetTrigger(DIK_F3))
	{
		m_bUse = m_bUse ? false : true;
	}

	if (m_bUse == false)
	{
		return;
	}

	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y�f�o�b�O���[�h���z\n\n");

	//�ړ�
	if (pInputKey->GetTrigger(DIK_UP))
	{
		m_object.pos.y += SPEED;
	}
	if (pInputKey->GetTrigger(DIK_DOWN))
	{
		m_object.pos.y -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_LEFT))
	{
		m_object.pos.x -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_RIGHT))
	{
		m_object.pos.x += SPEED;
	}

	if (pInputKey->GetTrigger(DIK_LSHIFT))
	{
		m_object.pos.z += SPEED;
	}

	if (pInputKey->GetTrigger(DIK_LCONTROL))
	{
		m_object.pos.z -= SPEED;
	}

	//�I�u�W�F�N�g��ނ̕ύX
	if (pInputKey->GetTrigger(DIK_1))
	{
		m_nTypeIdx++;

		m_nTypeIdx %= pXfile->GetNumAll();			//�J��Ԃ�
	}

	//�I�u�W�F�N�g�̐ݒu
	if (pInputKey->GetTrigger(DIK_RETURN))
	{
		m_pObjectX = CObjectX::Create(c_Obj[m_nTypeIdx], m_object.pos);
		m_pObjectX->SetModelIdx(m_nTypeIdx);
	}

	//�t�@�C����������(�Z�[�u)
	if (pInputKey->GetTrigger(DIK_F9))
	{
		Save();
	}
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CEdit::Draw(void)
{
	if (m_bUse == false)
	{
		return;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	CXfile *pXfile = CManager::GetInstance()->GetXfile();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_object.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_object.rot.y, m_object.rot.x, m_object.rot.z);
	D3DXMatrixMultiply(&m_object.mtxWorld, &m_object.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_object.pos.x, m_object.pos.y, m_object.pos.z);
	D3DXMatrixMultiply(&m_object.mtxWorld, &m_object.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_object.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pXfile->GetAdrress(m_nTypeIdx)->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXfile->GetAdrress(m_nTypeIdx)->dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat[nCntMat].pTextureFilename != NULL && pXfile->GetAdrress(m_nTypeIdx)->pTextureIdx > 0)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAddress(pXfile->GetAdrress(m_nTypeIdx)->pTextureIdx));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}

		//�I�u�W�F�N�g(�p�[�c)�̕`��
		pXfile->GetAdrress(m_nTypeIdx)->pMesh->DrawSubset(nCntMat);
	}

	//�ۑ�����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================
// �ǂݍ���
//===========================================================================================
void CEdit::Load(const char* pFilename)
{
	char Dast[128] = {};		//������̃S�~��
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	FILE* pFile = nullptr;			//�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(pFilename, "r");

	if (pFile == nullptr)
	{
		return;
	}

	while (strcmp("END_SCRIPT", &Dast[0]) != 0)
	{
		fscanf(pFile, "%s", &Dast[0]);

		if (strcmp("OBJECTSET", &Dast[0]) == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &Dast[0]);

				if (strcmp("TYPE", &Dast[0]) == 0)
				{
					fscanf(pFile, "%s", &Dast[0]);
					fscanf(pFile, "%d", &nType);			//�ʒux
				}
				if (strcmp("POS", &Dast[0]) == 0)
				{
					fscanf(pFile, "%s", &Dast[0]);
					fscanf(pFile, "%f", &pos.x);			//�ʒux
					fscanf(pFile, "%f", &pos.y);			//�ʒuy
					fscanf(pFile, "%f", &pos.z);			//�ʒuz
				}
				if (strcmp("ROT", &Dast[0]) == 0)
				{
					fscanf(pFile, "%s", &Dast[0]);
					fscanf(pFile, "%f", &rot.x);			//�ʒux
					fscanf(pFile, "%f", &rot.y);			//�ʒuy
					fscanf(pFile, "%f", &rot.z);			//�ʒuz

					break;
				}

				if (strcmp("ROT", &Dast[0]) == 0)
				{
					fscanf(pFile, "%s", &Dast[0]);
					fscanf(pFile, "%f", &rot.x);			//�ʒux
					fscanf(pFile, "%f", &rot.y);			//�ʒuy
					fscanf(pFile, "%f", &rot.z);			//�ʒuz

					break;
				}
			}
		}
		else if (strcmp("END_OBJECTSET", &Dast[0]) == 0)
		{
			m_pObjectX = CObjectX::Create(c_Obj[nType], pos);
		}
	}
}

//===========================================================================================
// ��������
//===========================================================================================
void CEdit::Save(void)
{
	FILE* pFile = NULL;			//�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("data\\TXT\\stage\\stage0.txt", "w");

	if (pFile == nullptr)
	{
		return;
	}

	fprintf(pFile, "SCRIPT\n\n");

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			CObject* pObj = CObject::GetCObject(nCntPriority, nCnt);

			if (pObj != NULL && pObj->GetType() == CObject::TYPE_OBJECTX)
			{
				CObjectX* pObjectX = pObj->GetObjectX();

				D3DXVECTOR3 pos = pObjectX->GetPosition();
				D3DXVECTOR3 rot = pObjectX->GetRotation();
				int nTypeIdx = pObjectX->GetModelIndx();

				fprintf(pFile, "OBJECTSET\n");
				fprintf(pFile, "	TYPE = %d\n", nTypeIdx);
				fprintf(pFile, "	POS = %0.2f %0.2f %0.2f\n", pos.x, pos.y, pos.z);
				fprintf(pFile, "	ROT = %0.2f %0.2f %0.2f\n", rot.x, rot.y, rot.z);
				fprintf(pFile, "END_OBJECTSET\n\n");
			}
		}
	}

	//�I���̍��}
	fprintf(pFile, "END_SCRIPT");

	//�t�@�C�������
	fclose(pFile);
	
}

