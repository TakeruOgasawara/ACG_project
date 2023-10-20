////===========================================================================================
////
//// [edit.cpp]
//// Author : Takeru Ogasawara
////
////===========================================================================================
//#include <stdio.h>
//#include "break_block.h"
//#include "manager.h"
//#include "renderer.h"
//#include "input.h"
//#include "objectX.h"
//#include "debugproc.h"
//
//#include "texture.h"
//#include "xfile.h"
//
////�}�N����`
//static const int MAX_TYPE = 4;
//
////===========================================================================================
//// �R���X�g���N�^
////===========================================================================================
//CBreakBlock::CBreakBlock()
//{
//
//}
//
////===========================================================================================
//// �f�X�g���N�^
////===========================================================================================
//CBreakBlock::~CBreakBlock()
//{
//
//}
//
////===========================================================================================
//// ����
////===========================================================================================
//CBreakBlock* CBreakBlock::Create(D3DXVECTOR3 pos)
//{
//	CBreakBlock* pEdit = nullptr;
//
//	if (pEdit == nullptr)
//	{
//		pEdit = new CBreakBlock;
//
//		pEdit->Init();
//		pEdit->SetPosition(pos);
//
//		return pEdit;
//	}
//
//	return nullptr;
//}
//
////===========================================================================================
//// ����������
////===========================================================================================
//HRESULT CBreakBlock::Init(void)
//{
//
//	CObjectX::Init();
//
//	return S_OK;
//}
//
////===========================================================================================
//// �I������
////===========================================================================================
//void CBreakBlock::Uninit(void)
//{
//	if (m_pObjectX != nullptr)
//	{
//		delete m_pObjectX;
//		m_pObjectX = nullptr;
//	}
//}
//
////===========================================================================================
//// �X�V����
////===========================================================================================
//void CBreakBlock::Update(void)
//{
//	//�L�[�{�[�h���̎擾
//	CInputKeyboard* pInputKey = CManager::GetInstance()->GetInputKeyboard();
//	CDebugProc* pDebug = CManager::GetInstance()->GetDebugProc();
//	CXfile* pXfile = CManager::GetInstance()->GetXfile();
//
//	if (pInputKey->GetTrigger(DIK_F3))
//	{
//		m_bUse = m_bUse ? false : true;
//	}
//
//	if (m_bUse == false)
//	{
//		return;
//	}
//
//	CManager::GetInstance()->GetDebugProc()->Print("\n\n�y�G�f�B�b�g���[�h���z\n\n");
//	CManager::GetInstance()->GetDebugProc()->Print("�ʒu�F x:%f y:%f z:%f\n", m_object.pos.x, m_object.pos.y, m_object.pos.z);
//	CManager::GetInstance()->GetDebugProc()->Print("�����F x:%f y:%f z:%f\n", m_object.rot.x, m_object.rot.y, m_object.rot.z);
//	CManager::GetInstance()->GetDebugProc()->Print("��ށF %d\n", m_nTypeIdx);
//
//	//�ړ�
//	if (pInputKey->GetTrigger(DIK_UP))
//	{
//		m_object.pos.y += SPEED;
//	}
//	if (pInputKey->GetTrigger(DIK_DOWN))
//	{
//		m_object.pos.y -= SPEED;
//	}
//	if (pInputKey->GetTrigger(DIK_LEFT))
//	{
//		m_object.pos.x -= SPEED;
//	}
//	if (pInputKey->GetTrigger(DIK_RIGHT))
//	{
//		m_object.pos.x += SPEED;
//	}
//
//	if (pInputKey->GetTrigger(DIK_LSHIFT))
//	{
//		m_object.pos.z += SPEED;
//	}
//
//	if (pInputKey->GetTrigger(DIK_LCONTROL))
//	{
//		m_object.pos.z -= SPEED;
//	}
//
//	m_pObjectX->SetPosition(m_object.pos);
//
//	//�I�u�W�F�N�g��ނ̕ύX
//	if (pInputKey->GetTrigger(DIK_1))
//	{
//		m_nTypeIdx++;
//
//		int nCt = pXfile->GetNumAll();
//
//		m_nTypeIdx %= pXfile->GetNumAll();			//�J��Ԃ�
//
//		m_pObjectX->Init(c_Obj[m_nTypeIdx], m_object.pos);
//		m_pObjectX->SetModelIdx(m_nTypeIdx);
//	}
//
//	//�I�u�W�F�N�g�̐ݒu
//	if (pInputKey->GetTrigger(DIK_RETURN))
//	{
//		CObjectX::Create(c_Obj[m_nTypeIdx], m_object.pos);
//		m_pObjectX->SetModelIdx(m_nTypeIdx);
//	}
//
//	//�t�@�C����������(�Z�[�u)
//	if (pInputKey->GetTrigger(DIK_F9))
//	{
//		Save();
//	}
//}
//
////===========================================================================================
//// �`�揈��
////===========================================================================================
//void CBreakBlock::Draw(void)
//{
//	if (m_bUse == false)
//	{
//		return;
//	}
//
//	m_pObjectX->Draw();
//}
//
////===========================================================================================
//// �ǂݍ���
////===========================================================================================
//void CBreakBlock::Load(const char* pFilename)
//{
//	char Dast[128] = {};		//������̃S�~��
//	int nType = 0;
//	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	FILE* pFile = nullptr;			//�t�@�C���|�C���^��錾
//
//	//�t�@�C�����J��
//	pFile = fopen(pFilename, "r");
//
//	if (pFile == nullptr)
//	{
//		return;
//	}
//
//	while (strcmp("END_SCRIPT", &Dast[0]) != 0)
//	{
//		fscanf(pFile, "%s", &Dast[0]);
//
//		if (strcmp("OBJECTSET", &Dast[0]) == 0)
//		{
//			while (1)
//			{
//				fscanf(pFile, "%s", &Dast[0]);
//
//				if (strcmp("TYPE", &Dast[0]) == 0)
//				{
//					fscanf(pFile, "%s", &Dast[0]);
//					fscanf(pFile, "%d", &nType);			//�ʒux
//				}
//				if (strcmp("POS", &Dast[0]) == 0)
//				{
//					fscanf(pFile, "%s", &Dast[0]);
//					fscanf(pFile, "%f", &pos.x);			//�ʒux
//					fscanf(pFile, "%f", &pos.y);			//�ʒuy
//					fscanf(pFile, "%f", &pos.z);			//�ʒuz
//				}
//				if (strcmp("ROT", &Dast[0]) == 0)
//				{
//					fscanf(pFile, "%s", &Dast[0]);
//					fscanf(pFile, "%f", &rot.x);			//�ʒux
//					fscanf(pFile, "%f", &rot.y);			//�ʒuy
//					fscanf(pFile, "%f", &rot.z);			//�ʒuz
//
//					break;
//				}
//
//				if (strcmp("ROT", &Dast[0]) == 0)
//				{
//					fscanf(pFile, "%s", &Dast[0]);
//					fscanf(pFile, "%f", &rot.x);			//�ʒux
//					fscanf(pFile, "%f", &rot.y);			//�ʒuy
//					fscanf(pFile, "%f", &rot.z);			//�ʒuz
//
//					break;
//				}
//			}
//		}
//		else if (strcmp("END_OBJECTSET", &Dast[0]) == 0)
//		{
//			m_pObjectX = CObjectX::Create(c_Obj[nType], pos);
//		}
//	}
//}
//
////===========================================================================================
//// ��������
////===========================================================================================
//void CBreakBlock::Save(void)
//{
//	FILE* pFile = NULL;			//�t�@�C���|�C���^��錾
//
//	//�t�@�C�����J��
//	pFile = fopen("data\\TXT\\stage\\stage0.txt", "w");
//
//	if (pFile == nullptr)
//	{
//		return;
//	}
//
//	fprintf(pFile, "SCRIPT\n\n");
//
//	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
//	{
//		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
//		{
//			CObject* pObj = CObject::GetCObject(nCntPriority, nCnt);
//
//			if (pObj != NULL && pObj->GetType() == CObject::TYPE_OBJECTX)
//			{
//				CObjectX* pObjectX = pObj->GetObjectX();
//
//				D3DXVECTOR3 pos = pObjectX->GetPosition();
//				D3DXVECTOR3 rot = pObjectX->GetRotation();
//				int nTypeIdx = pObjectX->GetModelIndx();
//
//				fprintf(pFile, "OBJECTSET\n");
//				fprintf(pFile, "	TYPE = %d\n", nTypeIdx);
//				fprintf(pFile, "	POS = %0.2f %0.2f %0.2f\n", pos.x, pos.y, pos.z);
//				fprintf(pFile, "	ROT = %0.2f %0.2f %0.2f\n", rot.x, rot.y, rot.z);
//				fprintf(pFile, "END_OBJECTSET\n\n");
//			}
//		}
//	}
//
//	//�I���̍��}
//	fprintf(pFile, "END_SCRIPT");
//
//	//�t�@�C�������
//	fclose(pFile);
//
//}
//
