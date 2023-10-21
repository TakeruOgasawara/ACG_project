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
////===========================================================================================
//// �R���X�g���N�^
////===========================================================================================
//CBreakBlock::CBreakBlock()
//{
//	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
//	{
//		m_pObjectX[nCnt] = nullptr;
//	}
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_nDestroyTime = 0;
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
//		pEdit->Init(pos);
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
//	return S_OK;
//}
//
////===========================================================================================
//// ����������
////===========================================================================================
//HRESULT CBreakBlock::Init(D3DXVECTOR3 pos)
//{
//	m_pObjectX[TYPE_BLOCK] = CObjectX::Create();
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
//	m_pObjectX->Draw();
//}