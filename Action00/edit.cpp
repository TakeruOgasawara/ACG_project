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

//�}�N����`
#define MAX_OBJ			(2) 
#define SPEED			(50.0f)

//�I�u�W�F�N�g�t�@�C����
const char *c_Obj[MAX_OBJ] =
{
	"data\\MODEL\\object\\floor00.x",
	"data\\MODEL\\object\\blockTile00.x",
};

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CEdit::CEdit()
{
	m_nIdx = 0;
	m_nTypeIdx = 0;
	m_bUse = false;
	//m_state = STATE_OFF;
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pObjectX = nullptr;
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

		pEdit->Init();

		return pEdit;
	}

	return nullptr;
}

//===========================================================================================
// �ǂݍ���
//===========================================================================================
HRESULT CEdit::Load(void)
{
	char Dast[128] = {};		//������̃S�~��
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	FILE *pFile = NULL;			//�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("data\\TXT\\MAP\\stage.txt", "r");

	if (pFile != NULL)
	{
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
				}
			}
			else if (strcmp("END_OBJECTSET", &Dast[0]) == 0)
			{
				CObjectX::Create(c_Obj[nType], pos);
			}
		}
	}

	return S_OK;
}

//===========================================================================================
// ��������
//===========================================================================================
void CEdit::Save(void)
{
	FILE *pFile = NULL;			//�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("data\\TXT\\stage\\stage.txt", "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{
			for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
			{
				CObject *pObj = CObject::GetCObject(nCntPriority, nCnt);

				if (pObj != NULL && pObj->GetType() == CObject::TYPE_OBJECTX)
				{
					D3DXVECTOR3 pos = pObj->GetPosition();
					D3DXVECTOR3 rot = pObj->GetRotation();

					fprintf(pFile, "OBJECTSET\n");
					fprintf(pFile, "	TYPE = %d\n", 0);
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
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CEdit::Init(void)
{
	//�I�u�W�F�N�g�̏�����
	m_pObjectX = CObjectX::Create(c_Obj[m_nTypeIdx], m_pos);

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
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CDebugProc *pDebug = CManager::GetDebugProc();

	CManager::GetDebugProc()->Print("\n\n�f�o�b�O���[�h��\n\n");

	if (m_pObjectX == nullptr)
	{
		return;
	}

	//�I�u�W�F�N�g��ނ̕ύX
	if (pInputKey->GetTrigger(DIK_1))
	{
		m_nTypeIdx++;

		m_nTypeIdx %= MAX_OBJ;			//�J��Ԃ�

		//�I�u�W�F�N�g�̏�����
		m_pObjectX->Init(c_Obj[m_nTypeIdx], m_pObjectX->GetPosition());
	}

	//�ړ�
	if (pInputKey->GetTrigger(DIK_UP))
	{
		m_pos.y += SPEED;
	}
	if (pInputKey->GetTrigger(DIK_DOWN))
	{
		m_pos.y -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_LEFT))
	{
		m_pos.x -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_RIGHT))
	{
		m_pos.x += SPEED;
	}

	//�ʒu�̍X�V
	m_pObjectX->SetPosition(m_pos);

	//�I�u�W�F�N�g�̐ݒu
	if (pInputKey->GetTrigger(DIK_RETURN))
	{
		//����
		m_pObjectX = CObjectX::Create(c_Obj[m_nTypeIdx], m_pos);

		m_nIdx++;
	}

	//�t�@�C����������(�Z�[�u)
	if (pInputKey->GetTrigger(DIK_0))
	{
		Save();
	}
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CEdit::Draw(void)
{
	//�I�u�W�F�N�g�̕`��
	if (m_pObjectX != nullptr)
	{
		m_pObjectX->Draw();
	}
}
