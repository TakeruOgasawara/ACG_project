//===========================================================================================
//
// [billboard.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "billboard.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"

//マクロ定義
#define SIZE			(D3DXVECTOR2(60.0f, 60.0f))

//===========================================================================================
// コンストラクタ
//===========================================================================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority), m_pTexture(nullptr)			//これ処理が少し速いらしい
{
	//m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nTextureIdx = 0;
	m_bUseLighting = false;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CBillboard::~CBillboard()
{
	
}

//===========================================================================================
// オブジェクト3Dの生成
//===========================================================================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard = NULL;

	if (pBillboard == NULL)
	{
		pBillboard = new CBillboard;

		if (pBillboard != NULL)
		{
			pBillboard->Init();

			return pBillboard;
		}
		else
		{
			return NULL;
		}
	}

	return pBillboard;
}

//===========================================================================================
// オブジェクト3Dの生成
//===========================================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos)
{
	CBillboard *pBillboard = nullptr;

	if (pBillboard == nullptr)
	{
		pBillboard = new CBillboard;

		if (pBillboard != nullptr)
		{
			pBillboard->Init();

			pBillboard->SetPosition(pos);

			return pBillboard;
		}
		else
		{
			return nullptr;
		}
	}

	return pBillboard;
}

//===========================================================================================
// 生成
//===========================================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, const char *pTexName)
{
	CBillboard *pBillboard = nullptr;
	CTexture *pTexture = nullptr;

	if (pBillboard == nullptr)
	{
		pBillboard = new CBillboard;

		if (pBillboard != nullptr)
		{
			pBillboard->Init();

			pBillboard->SetPosition(pos);
			
			pBillboard->BindTexture(pTexture->Regist(pTexName));

			return pBillboard;
		}
		
		return nullptr;
	}

	return pBillboard;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CBillboard::Init(void)
{
	m_size = D3DXVECTOR2(SIZE.x, SIZE.y);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (m_pVtxBuff == nullptr)
	{
		return S_FALSE;
	}

	//頂点設定
	SetverTex();

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CBillboard::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//破棄
	Release();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CBillboard::Update(void)
{
	
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//テクスチャポインタの取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス
	D3DXMATRIX mtxView;				//ビューマトリックスの取得用

	//zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		//比較方法
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			//zバッファ更新の有効無効設定

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);					//基準値

	if (m_bUseLighting == true)
	{
		//ライティングの有効/無効の設定
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0,
		sizeof(VERTEX_3D));			//頂点情報構造体のサイズ

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTextureIdx));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,			//描画する最初のインデックス(大事)
		2);			//プリミティブ(ポリゴン)数

	//zバッファを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			//zバッファ更新の有効無効設定

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//アルファテストの有効/無効の設定
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);	//比較方法
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);				//基準値

	if (m_bUseLighting == true)
	{
		//ライティングの有効/無効の設定
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//===========================================================================================
// 頂点情報の設定
//===========================================================================================
void CBillboard::SetverTex(void)
{
	//対角線の長さを算出(デフォルト)
	float fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;

	//対角線の角度を算出する(デフォルト)
	float fAngle = atan2f(m_size.x, m_size.y);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI + fAngle) * fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z  + fAngle) * fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - fAngle) * fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + fAngle) * fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - fAngle) * fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - fAngle) * fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + fAngle) * fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI + fAngle) * fLength;
	pVtx[3].pos.z = 0.0f;

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー(0.0f～1.0f内で設定)
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================================================================================
// テクスチャの割り当て
//===========================================================================================
void CBillboard::BindTexture(int nIdx)
{
	m_nTextureIdx = nIdx;
}

//===========================================================================================
// テクスチャの割り当て(テクスチャ名からテクスチャ番号に変換)
//===========================================================================================
void CBillboard::BindTexture(const char *texName)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//テクスチャ番号に変換
	m_nTextureIdx = pTexture->Regist(texName);
}
