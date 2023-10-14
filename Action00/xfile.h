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
	struct SData
	{
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファへの頂点情報
		D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
		LPD3DXMESH m_pMesh;					//使用されているモデル数
		LPD3DXBUFFER m_pBuffMat;			//頂点カラー情報
		DWORD m_dwNumMat;					//カラーの数
		D3DXVECTOR3 m_vtxMin, m_vtxMax;		//オブジェクトの最大値・最小値
		int *nTextureIdx;					//テクスチャ番号
	};

	struct  Info
	{
		SData XFileData;
		const char aXfileName[MAX_NAME];
	};

public:
	CXfile();
	~CXfile();

	HRESULT Load(int nIdx);
	void Unload(void);

	int Regist(const char *c_pXfileName);

	D3DXVECTOR3 GetMax(int nIdx) { return m_apXFileInfo[nIdx]->XFileData.m_vtxMax; }
	D3DXVECTOR3 GetMin(int nIdx) { return m_apXFileInfo[nIdx]->XFileData.m_vtxMin; }

private:
	
	Info *m_apXFileInfo[MAX_FILE];
	static int m_nNumAll;
};

#endif