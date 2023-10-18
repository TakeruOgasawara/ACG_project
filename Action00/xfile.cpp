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
CXfile::SXFile *CXfile::m_aXFile[MAX_FILE] = {};
int CXfile::m_nNumAll = 0;	//読み込んだ総数

//===========================================================================================
// コンストラクタ
//===========================================================================================
CXfile::CXfile()
{
	for (int nCntData = 0; nCntData < MAX_FILE; nCntData++)
	{
		m_aXFile[nCntData] = nullptr;
	}
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CXfile::~CXfile()
{

}

//===========================================================================================
// Xファイルを読み込む(初期化処理)
//===========================================================================================
HRESULT CXfile::Load(void)
{
	// 最初に読み込むxファイル一覧
	const char *aFileList[MAX_FILE] =
	{
		"data\\MODEL\\object\\floor00.x",
		"data\\MODEL\\object\\blockTile00.x",
		"data\\MODEL\\object\\bigTV.x",
	};

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (aFileList[nCntTex] != nullptr)
		{
			Regist(aFileList[nCntTex]);
		}
		else
		{
			break;
		}
	}

	return S_OK;
}

//===========================================================================================
// 全て破棄する(終了処理)
//===========================================================================================
void CXfile::Unload(void)
{
	for (int nCntFile = 0; nCntFile < MAX_FILE; nCntFile++)
	{
		if (m_aXFile[nCntFile] != nullptr)
		{
			//ファイル名をクリア
			ZeroMemory(&m_aXFile[nCntFile]->aXfileName, sizeof(m_aXFile[nCntFile]->aXfileName));
			
			if (m_aXFile[nCntFile]->pBuffMat != nullptr)
			{
				m_aXFile[nCntFile]->pBuffMat->Release();
				m_aXFile[nCntFile]->pBuffMat = nullptr;
			}

			if (m_aXFile[nCntFile]->pMesh != nullptr)
			{
				m_aXFile[nCntFile]->pMesh->Release();
				m_aXFile[nCntFile]->pMesh = nullptr;
			}

			delete m_aXFile[nCntFile];
			m_aXFile[nCntFile] = nullptr;

			m_nNumAll--;
		}
	}
}

//===========================================================================================
// Xファイルに割り当てられた番号を返す
//===========================================================================================
int CXfile::Regist(const char *c_pXfileName)
{
	//ポインタ取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();	//テクスチャポインタの取得
	D3DXMATERIAL *pMat;	//マテリアルポインタ

	if (c_pXfileName == nullptr)
	{
		return -1;
	}

	for (int nCnt = 0; nCnt < MAX_FILE; nCnt++)
	{
		if (m_aXFile[nCnt] != nullptr)
		{
			if (strcmp(&m_aXFile[nCnt]->aXfileName[0], c_pXfileName) == 0)
			{//あらかじめ用意されたファイル名と引数のファイル名が同じだった場合

				return nCnt;	//番号を返す
			}

			continue;
		}

		//ポインタを生成
		m_aXFile[nCnt] = new SXFile;

		//値をクリアする
		ZeroMemory(m_aXFile[nCnt], sizeof(SXFile));

		if (m_aXFile[nCnt] != nullptr)
		{
			//Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(c_pXfileName,
				D3DXMESH_SYSTEMMEM, pDevice,
				NULL,
				&m_aXFile[nCnt]->pBuffMat,
				NULL,
				&m_aXFile[nCnt]->dwNumMat,
				&m_aXFile[nCnt]->pMesh)))
			{
				return E_FAIL;	//読み込み失敗
			}

			//テクスチャ名を書き込む
			strcpy(&m_aXFile[nCnt]->aXfileName[0], c_pXfileName);

			//マテリアルへのポインタを取得
			pMat = (D3DXMATERIAL*)m_aXFile[nCnt]->pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_aXFile[nCnt]->dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != nullptr)
				{
					//ファイルからテクスチャを読み込む
					m_aXFile[nCnt]->pTextureIdx = pTexture->Regist(pMat[nCntMat].pTextureFilename);
				}
			}

			//オブジェクトサイズを算出する関数
			VtxMaxMin(nCnt);

			m_nNumAll++;	//総数カウントアップ

			return nCnt;
		}
	}

	return -1;	//NULL
}

//===========================================================================================
// オブジェクトのサイズを算出
//===========================================================================================
void CXfile::VtxMaxMin(int nNowCount)
{
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE* pVtxBuff;	//頂点バッファへのポインタ
	int nNumVtx;	//頂点数

	//頂点数を取得
	nNumVtx = m_aXFile[nNowCount]->pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_aXFile[nNowCount]->pMesh->GetFVF());

	//頂点バッファをロック
	m_aXFile[nNowCount]->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

	if (m_aXFile[nNowCount]->vtxMax.x < vtx.x)
	{//xが大きかったら
		m_aXFile[nNowCount]->vtxMax.x = vtx.x;
	}
	if (m_aXFile[nNowCount]->vtxMax.z < vtx.z)
	{//zの値が大きかったら
		m_aXFile[nNowCount]->vtxMax.z = vtx.z;
	}

	if (m_aXFile[nNowCount]->vtxMin.x > vtx.x)
	{//xが小さかったら
		m_aXFile[nNowCount]->vtxMin.x = vtx.x;
	}
	if (m_aXFile[nNowCount]->vtxMin.z > vtx.z)
	{//zの値が大きかったら
		m_aXFile[nNowCount]->vtxMin.z = vtx.z;
	}

	if (m_aXFile[nNowCount]->vtxMax.y < vtx.y)
	{//xが大きかったら
		m_aXFile[nNowCount]->vtxMax.y = vtx.y;
	}
	if (m_aXFile[nNowCount]->vtxMin.y > vtx.y)
	{//xが小さかったら
		m_aXFile[nNowCount]->vtxMin.y = vtx.y;
	}

	pVtxBuff += dwSizeFVF;			//頂点フォーマットのサイズ分ポインタを進める
	
	//頂点バッファをアンロック
	m_aXFile[nNowCount]->pMesh->UnlockVertexBuffer();
}

//===========================================================================================
// オブジェクトのサイズを算出
//===========================================================================================
CXfile::SXFile* CXfile::GetAdrress(int nIdx)
{
	if (nIdx < 0 && nIdx > m_nNumAll)
	{
		return nullptr;
	}

	return m_aXFile[nIdx];
}

