//===========================================================================================
//
// [objectX.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "object.h"

//===========================================================================================
// コンストラクタ
//===========================================================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_dwNumMat = NULL;
	
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	m_vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nModelIdx = 0;
	m_nTextureIdx = 0;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CObjectX::~CObjectX()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CObjectX * CObjectX::Create(void)
{
	CObjectX *pObjX = NULL;

	if (pObjX == NULL)
	{
		pObjX = new CObjectX;

		if (pObjX != NULL)
		{
			pObjX->Init();

			return pObjX;
		}
		else
		{
			return NULL;
		}
	}

	return S_OK;
}

//===========================================================================================
// 生成
//===========================================================================================
CObjectX *CObjectX::Create(const char *c_pFileName, D3DXVECTOR3 pos)
{
	CObjectX *pObjX = NULL;

	if (pObjX == NULL)
	{
		pObjX = new CObjectX;

		if (pObjX != NULL)
		{
			//初期化処理
			pObjX->Init(c_pFileName, pos);

			//位置設定
			pObjX->SetPosition(pos);
			pObjX->m_pos = pos;

			return pObjX;
		}
		else
		{
			return NULL;
		}
	}

	return S_OK;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CObjectX::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	//種類設定
	//SetType(TYPE_OBJECTX);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\murabito\\atama.x",
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &m_pBuffMat,
		NULL, &m_dwNumMat,
		&m_pMesh);

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//ファイルからテクスチャを読み込む
			m_nTextureIdx = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	return S_OK;
}

//===========================================================================================
// 初期化処理(オーバーロード)
//===========================================================================================
HRESULT CObjectX::Init(const char *c_pFileName, D3DXVECTOR3 pos)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATERIAL *pMat;			//マテリアルへのポインタ

	//種類設定
	SetType(TYPE_OBJECTX);

	//Xファイルの読み込み
	D3DXLoadMeshFromX(c_pFileName,
		D3DXMESH_SYSTEMMEM, pDevice,
		NULL, &m_pBuffMat,
		NULL, &m_dwNumMat,
		&m_pMesh);

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//ファイルからテクスチャを読み込む
			m_nTextureIdx = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	DWORD dwSizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ
	int nNumVtx;			//頂点数

	//頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//頂点座標の代入

		if (m_vtxMax.x < vtx.x)
		{//xが大きかったら
			m_vtxMax.x = vtx.x;
		}
		if (m_vtxMax.z < vtx.z)
		{//zの値が大きかったら
			m_vtxMax.z = vtx.z;
		}

		if (m_vtxMin.x > vtx.x)
		{//xが小さかったら
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMin.z > vtx.z)
		{//zの値が大きかったら
			m_vtxMin.z = vtx.z;
		}

		if (m_vtxMax.y < vtx.y)
		{//xが大きかったら
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMin.y > vtx.y)
		{//xが小さかったら
			m_vtxMin.y = vtx.y;
		}

		pVtxBuff += dwSizeFVF;			//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CObjectX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}		

	//マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	//該当するオブジェクトの破棄
	Release();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CObjectX::Update(void)
{
	m_pos = GetPosition();
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CObjectX::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat[nCntMat].pTextureFilename != NULL && m_nTextureIdx > 0)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, pTexture->GetAddress(m_nTextureIdx));
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}

		//オブジェクト(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存されていたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================
// 当たり判定
//===========================================================================================
bool CObjectX::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pVtxMax, D3DXVECTOR3 pVtxMin)
{
	bool bUse = false;

	//オブジェクトとの当たり判定
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			CObjectX *pObjectX = CObject::GetObjectX();

			if (pObjectX == nullptr)
			{
				continue;
			}

			D3DXVECTOR3 pos = pObjectX->GetPosition();
			D3DXVECTOR3 vtxMax = pObjectX->GetVtxMax();
			D3DXVECTOR3 vtxMin = pObjectX->GetVtxMin();

			if (pPos->y + pVtxMax.y > pos.y + vtxMin.y &&
				pPos->y + pVtxMin.y < pos.y + vtxMax.y)
			{//上下の当たり判定
				if (pPos->x + pVtxMax.x > pos.x + vtxMin.x &&
					pPos->x + pVtxMin.x < pos.x + vtxMax.x)
				{//左右の当たり幅の指定
					if (pPosOld->z + pVtxMax.z <= pos.z + vtxMin.z &&
						pPos->z + pVtxMax.z >= pos.z + vtxMin.z)
					{//前の当たり判定
						pPos->z = pos.z + vtxMin.z - pVtxMax.z;
						pMove->z = 0.0f;			//移動量を0へ
						bUse = true;
					}
					if (pPosOld->z + pVtxMin.z >= pos.z + vtxMax.z &&
						pPos->z + pVtxMin.z < pos.z + vtxMax.z)
					{//後の当たり判定
						pPos->z = pos.z + vtxMax.z - pVtxMin.z;
						pMove->z = 0.0f;			//移動量を0へ
						bUse = true;
					}
				}

				if (pPos->z + pVtxMax.z > pos.z + vtxMin.z &&
					pPos->z + pVtxMin.z < pos.z + vtxMax.z)
				{//上下の当たり幅の指定
					if (pPosOld->x + pVtxMax.x + SIZE <= pos.x + vtxMin.x &&
						pPos->x + pVtxMax.x + SIZE >= pos.x + vtxMin.x)
					{//左の当たり判定
						pPos->x = pos.x + vtxMin.x + pVtxMin.x - SIZE;
						pMove->x = 0.0f;			//移動量を0へ
						bUse = true;
					}
					if (pPosOld->x + pVtxMin.x - SIZE >= pos.x + vtxMax.x &&
						pPos->x + pVtxMin.x - SIZE <= pos.x + vtxMax.x)
					{//右の当たり判定
						pPos->x = pos.x + vtxMax.x + pVtxMax.x + SIZE;
						pMove->x = 0.0f;			//移動量を0へ
						bUse = true;
					}
				}
			}
		}
	}

	return bUse;
}