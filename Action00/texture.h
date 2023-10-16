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
private:
	struct Tex
	{
		LPDIRECT3DTEXTURE9 pTexture;
		char aName[MAX_TEXTURE];
	};

public:
	CTexture();
	~CTexture();

	//メンバ関数
	HRESULT Load(void);	//読み込み
	void Unload(void);	//削除
	int Regist(const char *pTextureName);	//登録

	//取得用メンバ関数
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	//アドレス取得

	//メンバ変数
	int m_nTextureIdx;

private:
	static Tex m_Texture[MAX_TEXTURE];
	static int m_nNumAll;
};

#endif