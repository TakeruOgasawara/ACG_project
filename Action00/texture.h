//===============================================================================
//
// [texture.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TEXTURE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _TEXTURE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//�}�N����`
#define MAX_TEXTURE			(256)

//�e�N�X�`���N���X
class CTexture
{
private:
	struct Tex
	{
		LPDIRECT3DTEXTURE9 pTexture;
		char aName[MAX_TEXTURE];
	};

public:
	CTexture();
	~CTexture();

	//�����o�֐�
	HRESULT Load(void);	//�ǂݍ���
	void Unload(void);	//�폜
	int Regist(const char *pTextureName);	//�o�^

	//�擾�p�����o�֐�
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	//�A�h���X�擾

	//�����o�ϐ�
	int m_nTextureIdx;

private:
	static Tex m_Texture[MAX_TEXTURE];
	static int m_nNumAll;
};

#endif