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
#define MAX_OBJ			(6) 
#define SPEED			(5.0f)

//�I�u�W�F�N�g�t�@�C����
const char *c_Obj[MAX_OBJ] =
{
	"data\\MODEL\\object\\kihon.x",
	"data\\MODEL\\object\\kihon1.x",
	"data\\MODEL\\object\\coin.x",
	"data\\MODEL\\object\\mitumisi.x",
	"data\\MODEL\\object\\TanukiShop.x",
	"data\\MODEL\\object\\tree.x",
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

	m_objectX = nullptr;
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CEdit::~CEdit()
{

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
	pFile = fopen("data\\TXT\\MAP\\stage.txt", "w");

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
HRESULT CEdit::Init(D3DXVECTOR3 pos)
{
	//�I�u�W�F�N�g�̏�����
	m_objectX = CObjectX::Create(c_Obj[m_nTypeIdx], pos);

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CEdit::Uninit(void)
{
	//�I�u�W�F�N�g�̏I������
	//CObjectX::Uninit();
}

//===========================================================================================
// �X�V����
//===========================================================================================
void CEdit::Update(void)
{
	//�L�[�{�[�h���̎擾
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CDebugProc *pDebug = CManager::GetDebugProc();

	D3DXVECTOR3 pos;

	if (pInputKey->GetTrigger(DIK_F3))
	{
		m_bUse = m_bUse ? false : true;			//�g�p���邩�̗L��
	}

	if (m_bUse == true)
	{
		//�I�u�W�F�N�g�̏�����
		m_objectX->Init(c_Obj[m_nTypeIdx], m_objectX->GetPosition());
	}
	else
	{
		return;
	}

	//�I�u�W�F�N�g��ނ̕ύX
	if (pInputKey->GetTrigger(DIK_1))
	{
		m_nTypeIdx++;

		//�I�u�W�F�N�g�̏�����
		m_objectX->Init(c_Obj[m_nTypeIdx], m_objectX->GetPosition());

		m_nTypeIdx %= MAX_OBJ;			//�J��Ԃ�
	}

	//�ړ�
	if (pInputKey->GetPress(DIK_UP))
	{
		pos.z += 1.0f;
	}
	if (pInputKey->GetPress(DIK_DOWN))
	{
		pos.z -= 1.0f;
	}
	if (pInputKey->GetPress(DIK_LEFT))
	{
		pos.x -= 1.0f;
	}
	if (pInputKey->GetPress(DIK_RIGHT))
	{
		pos.x += 1.0f;
	}
	if (pInputKey->GetPress(DIK_LSHIFT))
	{
		pos.y += 1.0f;
	}
	if (pInputKey->GetPress(DIK_LCONTROL))
	{
		pos.y -= 1.0f;
	}

	//�ʒu�̍X�V
	m_objectX->SetPosition(pos);

	//�I�u�W�F�N�g�̐ݒu
	if (pInputKey->GetTrigger(DIK_RETURN))
	{
		//����
		m_objectX = CObjectX::Create(c_Obj[m_nTypeIdx], pos);

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
	if (m_objectX != nullptr)
	{
		m_objectX->Draw();
	}
}
