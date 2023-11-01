//===========================================================================================
// 
// [texture.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdlib.h>
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//�ÓI�����o�ϐ��錾
int CTexture::m_nNumAll = 0;
CTexture::Tex CTexture::m_Texture[MAX_TEXTURE] = {};

//===========================================================================================
// �R���X�g���N�^
//===========================================================================================
CTexture::CTexture()
{
	m_nTextureIdx = 0;
	ZeroMemory(&m_Texture[0], sizeof(Tex) * MAX_TEXTURE);
}

//===========================================================================================
// �f�X�g���N�^
//===========================================================================================
CTexture::~CTexture()
{

}

//===========================================================================================
// �e�N�X�`����S�ēǂݍ���(����������)
//===========================================================================================
HRESULT CTexture::Load(void)
{
	//�t�@�C����
	const char *c_apTexName[MAX_TEXTURE] =
	{
		"data\\TEXTURE\\none.png",
		"data\\TEXTURE\\murabito.png",
	};

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (c_apTexName[nCntTex] != nullptr)
		{
			Regist(c_apTexName[nCntTex]);
		}
		else
		{
			return NULL;
		}
	}

	return S_OK;
}

//===========================================================================================
// �e�N�X�`����S�Ĕj������(�I������)
//===========================================================================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (m_Texture[nCntTex].pTexture != nullptr)
		{
			m_Texture[nCntTex].pTexture->Release();
			m_Texture[nCntTex].pTexture = nullptr;
		}
		if (m_Texture[nCntTex].aName != "")
		{
			ZeroMemory(&m_Texture[nCntTex].aName[0], sizeof(m_Texture[nCntTex].aName));
		}
	}
}

//===========================================================================================
// �g���e�N�X�`��
//===========================================================================================
int CTexture::Regist(const char *pTextureName)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�ϐ��錾
	int nCntTex = 0;			//for�J�E���g�p
	
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{//�e�N�X�`���̍ő吔���܂��

		if (pTextureName != nullptr)
		{
			if (m_Texture[nCntTex].pTexture != nullptr && m_Texture[nCntTex].aName != "")
			{//nullptr�ł͂Ȃ������ꍇ

				if (strcmp(&m_Texture[nCntTex].aName[0], pTextureName) == 0)
				{//���炩���ߗp�ӂ��ꂽ�t�@�C�����ƈ����̃t�@�C�����������������ꍇ

					return nCntTex;			//�ԍ���Ԃ�
				}
			}
			else
			{
				if (&m_Texture[nCntTex].aName[0] == pTextureName)
				{//����nullptr�������ꍇ

					return nCntTex;
				}
				else
				{
					//�e�N�X�`���̓ǂݍ���
					if (FAILED(D3DXCreateTextureFromFile(pDevice, pTextureName, &m_Texture[nCntTex].pTexture)))
					{
						return -1;
					}

					//�e�N�X�`��������������
					strcpy(&m_Texture[nCntTex].aName[0], pTextureName);

					m_nNumAll++;			//�e�N�X�`�������̃J�E���g�A�b�v

					return nCntTex;
				}
			}
		}
	}
	
	return -1;			//nullptr
}

//===========================================================================================
// �e�N�X�`���ԍ�
//===========================================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_Texture[nIdx].pTexture;
}
