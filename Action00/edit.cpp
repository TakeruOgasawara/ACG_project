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
static const int MAX_TYPE = 6;
#define SPEED	(25.0f)

static char* FILENAME = "data\\TXT\\stage\\0.1.txt";		//�������ރX�e�[�W�t�@�C����

//�I�u�W�F�N�g�t�@�C����
const char* c_Obj[MAX_TYPE] =
{ 
	"data\\MODEL\\object\\squareMin.x",
	"data\\MODEL\\object\\squareMax.x",
	"data\\MODEL\\object\\blockTileMin.x",
	"data\\MODEL\\object\\bigTV.x",
	"data\\MODEL\\object\\fence.x",
	"data\\MODEL\\object\\lockdoor.x",
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

		pEdit->Init();

		return pEdit;
	}

	return nullptr;
}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CEdit::Init(void)
{
#ifdef _DEBUG	//�f�o�b�N�����s

	m_pObjectX = CObjectX::Create(c_Obj[m_nTypeIdx], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_pObjectX->Init(c_Obj[m_nTypeIdx], D3DXVECTOR3(0.0f, 0.0f, 0.0f));

#endif
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
#ifdef _DEBUG	//�f�o�b�N�����s

	//�L�[�{�[�h���̎擾
	CInputKeyboard* pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CDebugProc* pDebug = CManager::GetInstance()->GetDebugProc();
	CXfile* pXfile = CManager::GetInstance()->GetXfile();

	if (pInputKey->GetTrigger(DIK_F3))
	{
		m_bUse = m_bUse ? false : true;
	}

	if (m_bUse == false)
	{
		return;
	}

	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y�G�f�B�b�g���[�h���z\n\n");
	CManager::GetInstance()->GetDebugProc()->Print("�ʒu�F x:%f y:%f z:%f\n", m_object.pos.x, m_object.pos.y, m_object.pos.z);
	CManager::GetInstance()->GetDebugProc()->Print("�����F x:%f y:%f z:%f\n", m_object.rot.x, m_object.rot.y, m_object.rot.z);
	CManager::GetInstance()->GetDebugProc()->Print("��ށF %d\n", m_nTypeIdx);

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

	m_pObjectX->SetPosition(m_object.pos);

	//�I�u�W�F�N�g��ނ̕ύX
	if (pInputKey->GetTrigger(DIK_1))
	{
		m_nTypeIdx++;

		m_nTypeIdx %= MAX_TYPE;			//�J��Ԃ�

		m_pObjectX->Init(c_Obj[m_nTypeIdx], m_object.pos);
		m_pObjectX->SetModelIdx(m_nTypeIdx);
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

#endif
}

//===========================================================================================
// �`�揈��
//===========================================================================================
void CEdit::Draw(void)
{
#ifdef _DEBUG	//�f�o�b�N�����s


	if (m_bUse == false)
	{
		return;
	}

	m_pObjectX->Draw();

#endif
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
			CObjectX::Create(c_Obj[nType], pos);
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
	pFile = fopen(FILENAME, "w");

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

