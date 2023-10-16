//===========================================================================================
//
// [light.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"

//===========================================================================================
// �R���X�g���N
//===========================================================================================
CLight::CLight()
{

}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CLight::~CLight()
{

}

//===========================================================================================
// ����������
//===========================================================================================
HRESULT CLight::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�ݒ�p�����x�N�g��
	D3DXVECTOR3 vecDir;	

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

		switch (nCntLight)
		{
		case 0:
			//���C�g1�̎�ނ�ݒ�
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			//���C�g1�̊g�U����ݒ�
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g1�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			D3DXVec3Normalize(&vecDir, &vecDir);			//�x�N�g���𐳋K������
			m_aLight[nCntLight].Direction = vecDir;
			break;

		case 1:
			//���C�g2�̎�ނ�ݒ�
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			//���C�g2�̊g�U����ݒ�
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			//���C�g2�̕�����ݒ�
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			D3DXVec3Normalize(&vecDir, &vecDir);			//�x�N�g���𐳋K������
			m_aLight[nCntLight].Direction = vecDir;
			break;

		case 2:
			//���C�g3�̎�ނ�ݒ�
			m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			//���C�g3�̊g�U����ݒ�
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

			//���C�g3�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			D3DXVec3Normalize(&vecDir, &vecDir);			//�x�N�g���𐳋K������
			m_aLight[nCntLight].Direction = vecDir;
			break;
		}

		//���C�g��ݒ�
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		//���C�g��L��������
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//===========================================================================================
// �I������
//===========================================================================================
void CLight::Uninit(void)
{

}

//===========================================================================================
// �X�V����
//===========================================================================================
void CLight::Update(void)
{
	//CManager::GetDebugProc()->Print("\n[���C�g���]\n");

}
