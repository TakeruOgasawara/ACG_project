//===============================================================================
//
// [Xfile.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _XFILE_H_				//このマクロ定義がされていなかったら
#define _XFILE_H_				//2重インクルード防止のマクロを定義

#include "main.h"

//テクスチャクラス
class CXfile
{
private:
	static const int MAX_FILE = 64;
	static const int MAX_NAME = 254;

private:
	//Xファイル情報の構造体
	struct SXFile
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//バッファへの頂点情報
		D3DXMATRIX mtxWorld;	//ワールドマトリックス
		LPD3DXMESH pMesh;	//使用されているモデル数
		LPD3DXBUFFER pBuffMat;	//頂点カラー情報
		DWORD dwNumMat;	//カラーの数
		D3DXVECTOR3 vtxMin, vtxMax;	//オブジェクトの最大値・最小値
		char aXfileName[MAX_NAME];
		int pTextureIdx;	//テクスチャ番号
	};

public:
	CXfile();
	~CXfile();

	HRESULT Load(void);
	void Unload(void);

	int Regist(const char *pXfileName);

	SXFile* GetAdrress(int nIdx);
	D3DXVECTOR3 GetMax(int nIdx) { return m_aXFile[nIdx]->vtxMax; }
	D3DXVECTOR3 GetMin(int nIdx) { return m_aXFile[nIdx]->vtxMin; }
	int GetNumAll(void) { return m_nNumAll; }

private:
	void VtxMaxMin(int nNowCount);
	static SXFile *m_aXFile[MAX_FILE];
	static int m_nNumAll;
};

#endif