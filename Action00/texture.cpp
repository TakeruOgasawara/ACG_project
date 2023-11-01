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

//静的メンバ変数宣言
int CTexture::m_nNumAll = 0;
CTexture::Tex CTexture::m_Texture[MAX_TEXTURE] = {};

//===========================================================================================
// コンストラクタ
//===========================================================================================
CTexture::CTexture()
{
	m_nTextureIdx = 0;
	ZeroMemory(&m_Texture[0], sizeof(Tex) * MAX_TEXTURE);
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CTexture::~CTexture()
{

}

//===========================================================================================
// テクスチャを全て読み込む(初期化処理)
//===========================================================================================
HRESULT CTexture::Load(void)
{
	//ファイル名
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
// テクスチャを全て破棄する(終了処理)
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
// 使うテクスチャ
//===========================================================================================
int CTexture::Regist(const char *pTextureName)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//変数宣言
	int nCntTex = 0;			//forカウント用
	
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{//テクスチャの最大数分まわる

		if (pTextureName != nullptr)
		{
			if (m_Texture[nCntTex].pTexture != nullptr && m_Texture[nCntTex].aName != "")
			{//nullptrではなかった場合

				if (strcmp(&m_Texture[nCntTex].aName[0], pTextureName) == 0)
				{//あらかじめ用意されたファイル名と引数のファイル名が同じだった場合

					return nCntTex;			//番号を返す
				}
			}
			else
			{
				if (&m_Texture[nCntTex].aName[0] == pTextureName)
				{//もしnullptrだった場合

					return nCntTex;
				}
				else
				{
					//テクスチャの読み込み
					if (FAILED(D3DXCreateTextureFromFile(pDevice, pTextureName, &m_Texture[nCntTex].pTexture)))
					{
						return -1;
					}

					//テクスチャ名を書き込む
					strcpy(&m_Texture[nCntTex].aName[0], pTextureName);

					m_nNumAll++;			//テクスチャ総数のカウントアップ

					return nCntTex;
				}
			}
		}
	}
	
	return -1;			//nullptr
}

//===========================================================================================
// テクスチャ番号
//===========================================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_Texture[nIdx].pTexture;
}
