//===========================================================================================
//
// [object.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//�ÓI�����o�ϐ��̐錾
CObject *CObject::m_apObject[NUM_PRIORITY][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CObject::CObject(int nPriority)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == nullptr)
		{
			m_apObject[nPriority][nCntObject] = this;		//�������g����
			m_nID = nCntObject;		//�������g��ID��ۑ�
			m_nPriority = nPriority;
			m_type = TYPE_NONE;
			m_nNumAll++;		//�������J�E���g�A�b�v

			break;
		}
	}
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CObject::~CObject()
{

}

//===========================================================================================
// �S�ẴI�u�W�F�N�g�̔j��
//===========================================================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();		//�I������
			}
		}
	}
}

//===========================================================================================
// ����̃I�u�W�F�N�g�̍X�V
//===========================================================================================
void CObject::ParticularRelease(TYPE type)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr && m_apObject[nCntPriority][nCntObject]->m_type == type)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();		//�I������
			}
		}
	}
}

//===========================================================================================
// �S�ẴI�u�W�F�N�g�̍X�V
//===========================================================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_nID <= MAX_OBJECT && m_apObject[nCntPriority][nCntObject]->m_nID > -1)
				{
					m_apObject[nCntPriority][nCntObject]->Update();			//�X�V����
				}
			}
		}
	}
}

//===========================================================================================
// �S�ẴI�u�W�F�N�g�̕`��
//===========================================================================================
void CObject::DrawAll(void)
{
	//�J�������̎擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//�J�����̃Z�b�g
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_nID <= MAX_OBJECT && m_apObject[nCntPriority][nCntObject]->m_nID > -1)
				{
					m_apObject[nCntPriority][nCntObject]->Draw();		//�`�揈��
				}
			}
		}
	}
}

//===========================================================================================
// ����̑S�ẴI�u�W�F�N�g�̔j��
//===========================================================================================
void CObject::ReleaseAll_specified(TYPE type)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->GetType() == type)
				{
					m_apObject[nCntPriority][nCntObject]->Uninit();		//�I������
				}
			}
		}
	}
}

//===========================================================================================
// �I�u�W�F�N�g���̎擾
//===========================================================================================
CObject *CObject::GetCObject(int nPriority, int nIdx)
{
	if (m_apObject[nPriority][nIdx] != nullptr)
	{
		return m_apObject[nPriority][nIdx];
	}

	return nullptr;
}

//===========================================================================================
// �^�C�v����(���肷��I�u�W�F�N�g�A���肵�����^�C�v)
//===========================================================================================
bool CObject::TypeCheck(CObject *pObject, TYPE type)
{
	if (pObject != nullptr && pObject->GetType() == type)
	{
		return TRUE;
	}

	return FALSE;
}

//===================================================
// �I�u�W�F�N�g�̔j��
//===================================================
void CObject::Release(void)
{
	int nID = m_nID;
	int nPriority = m_nPriority;

	if (nID < MAX_OBJECT && nID > -1)
	{
		if (m_apObject[nPriority][nID] != nullptr)
		{
			delete m_apObject[nPriority][nID];
			m_apObject[nPriority][nID] = nullptr;

			m_nNumAll--;		//�������J�E���g�_�E��
		}
	}
}

