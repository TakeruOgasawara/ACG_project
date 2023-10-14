//===========================================================================================
// 
// [texture.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdlib.h>
#include "xfile.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//静的メンバ変数宣言
int CXfile::m_nNumAll = 0;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CXfile::CXfile()
{
	for (int nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{
		m_apXFileInfo[nCntFile] = nullptr;
	}
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CXfile::~CXfile()
{

}

//===========================================================================================
// Xファイルを全て読み込む(初期化処理)
//===========================================================================================
HRESULT CXfile::Load(int nIdx)
{
	//ポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetTexture();

	D3DXMATERIAL *pMat;			//マテリアルへのポインタ
	DWORD dwSizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ
	int nNumVtx;			//頂点数
	
	//Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(&m_apXFileInfo[nIdx]->aXfileName[0],
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL,
		&m_apXFileInfo[nIdx]->XFileData.m_pBuffMat,
		NULL,
		&m_apXFileInfo[nIdx]->XFileData.m_dwNumMat,
		&m_apXFileInfo[nIdx]->XFileData.m_pMesh)))
	{
		return E_FAIL;		//読み込み失敗
	}

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)m_apXFileInfo[nIdx]->XFileData.m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_apXFileInfo[nIdx]->XFileData.m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			//ファイルからテクスチャを読み込む
			pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	//頂点数を取得
	nNumVtx = m_apXFileInfo[nIdx]->XFileData.m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_apXFileInfo[nIdx]->XFileData.m_pMesh->GetFVF());

	//頂点バッファをロック
	m_apXFileInfo[nIdx]->XFileData.m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//頂点座標の代入

		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMax.x < vtx.x)
		{//xが大きかったら
			m_apXFileInfo[nIdx]->XFileData.m_vtxMax.x = vtx.x;
		}
		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMax.z < vtx.z)
		{//zの値が大きかったら
			m_apXFileInfo[nIdx]->XFileData.m_vtxMax.z = vtx.z;
		}

		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMin.x > vtx.x)
		{//xが小さかったら
			m_apXFileInfo[nIdx]->XFileData.m_vtxMin.x = vtx.x;
		}
		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMin.z > vtx.z)
		{//zの値が大きかったら
			m_apXFileInfo[nIdx]->XFileData.m_vtxMin.z = vtx.z;
		}

		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMax.y < vtx.y)
		{//xが大きかったら
			m_apXFileInfo[nIdx]->XFileData.m_vtxMax.y = vtx.y;
		}
		if (m_apXFileInfo[nIdx]->XFileData.m_vtxMin.y > vtx.y)
		{//xが小さかったら
			m_apXFileInfo[nIdx]->XFileData.m_vtxMin.y = vtx.y;
		}

		pVtxBuff += dwSizeFVF;			//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_apXFileInfo[nIdx]->XFileData.	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//===========================================================================================
// 全て破棄する(終了処理)
//===========================================================================================
void CXfile::Unload(void)
{
	for (int nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{
		if (m_apXFileInfo[nCntFile] != nullptr)
		{
			if (m_apXFileInfo[nCntFile]->XFileData.m_pBuffMat != nullptr)
			{
				m_apXFileInfo[nCntFile]->XFileData.m_pBuffMat->Release();
				m_apXFileInfo[nCntFile]->XFileData.m_pBuffMat = nullptr;
			}

			if (m_apXFileInfo[nCntFile]->XFileData.m_pMesh != nullptr)
			{
				m_apXFileInfo[nCntFile]->XFileData.m_pMesh->Release();
				m_apXFileInfo[nCntFile]->XFileData.m_pMesh = nullptr;
			}
		}
	}
}

//===========================================================================================
// Xファイルに割り当てられた番号を返す
//===========================================================================================
int CXfile::Regist(const char *c_pXfileName)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	//変数宣言
	int nCntFile = 0;			//forカウント用

	for (nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{//テクスチャの最大数分まわる

		if (m_apXFileInfo[nCntFile] == nullptr)
		{//NULLの場合
			continue;
		}
		else if (strstr(c_pXfileName, &m_apXFileInfo[nCntFile]->aXfileName[0]))
		{
			return nCntFile;
		}
	}

	return -1;			//NULL
}