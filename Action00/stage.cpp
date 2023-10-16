//======================================================================================
//
// �X�e�[�W����[stage.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "stage.h"
#include <stdio.h>

#include "objectX.h"

//========================================================================
// �R���X�g���N�^
//========================================================================
CStage::CStage()
{
	m_data = {};
}

//========================================================================
// �f�X�g���N�^
//========================================================================
CStage::~CStage()
{

}

//========================================================================
// ����
//========================================================================
CStage* CStage::Create(void)
{
	CStage* pStage = nullptr;

	if (pStage == nullptr)
	{
		pStage = new CStage;

		if (pStage != nullptr)
		{
			pStage->Init();

			return pStage;
		}
	}

	return nullptr;
}

//========================================================================
// ����������
//========================================================================
HRESULT CStage::Init()
{
	m_data.area = AREA_0;
	m_data.stage = STAGE_0;

	return S_OK;
}

//========================================================================
// �I������
//========================================================================
void CStage::Uninit()
{

}

//========================================================================
// �X�V����
//========================================================================
void CStage::Update()
{

}

//========================================================================
// �`�揈��
//========================================================================
void CStage::Draw()
{

}

HRESULT CStage::Load(void)
{
	char Dast[128] = {};		//������̃S�~��
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	FILE* pFile = NULL;			//�t�@�C���|�C���^��錾

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
				//CObjectX::Create(c_Obj[nType], pos);
			}
		}
	}

	return S_OK;
}
