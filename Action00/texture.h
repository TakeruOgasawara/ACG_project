//===============================================================================
//
// [texture.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TEXTURE_H_				//このマクロ定義がされていなかったら
#define _TEXTURE_H_				//2重インクルード防止のマクロを定義

#include "main.h"

//マクロ定義
#define MAX_TEXTURE			(256)

//テクスチャクラス
class CTexture
{
public:
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_MURABITO,
		TYPE_BULLET,
		TYPE_CHAINBULLET,
	};

private:
	struct Tex
	{
		LPDIRECT3DTEXTURE9 pTexture;
		char aName[MAX_TEXTURE];
	};

public:
	CTexture();
	~CTexture();

	HRESULT Load(void);
	void Unload(void);

	int Regist(const char *pTextureName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
	int m_nTextureIdx;

private:
	static Tex m_Texture[MAX_TEXTURE];
	TYPE m_type;
	static int m_nNumAll;
};

#endif