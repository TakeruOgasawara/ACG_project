//===========================================================================================
//
// [object2D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "texture.h"

//マクロ定義
#define SIZE_X		(100.0f)	//横の長さ
#define SIZE_Y		(100.0f)	//縦の長さ

//静的メンバ変数宣言
int CObject2D::m_nNumObj2D = 0;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nTextureIdx = 0;

	m_nNumObj2D++;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CObject2D::~CObject2D()
{
	m_nNumObj2D--;
}

//===========================================================================================
// 生成処理(初期値)
//===========================================================================================
CObject2D *CObject2D::Create(void)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		//オブジェクト2Dの生成
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//初期化処理
			pObject2D->Init();

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

//===========================================================================================
// 生成処理(位置)
//===========================================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		//オブジェクト2Dの生成
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//初期化処理
			pObject2D->Init();

			//位置の設定処理
			pObject2D->SetPosition(pos);

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}

//===============================================
// 生成
//===============================================
CObject2D *CObject2D::Create(const int nPriority)
{
	CObject2D *pObject2D = nullptr;

	// オブジェクト2Dの生成
	pObject2D = new CObject2D(nPriority);

	if (pObject2D != NULL)
	{
		pObject2D->Init();

		pObject2D->SetType(TYPE_NONE);
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pObject2D;
}
//===========================================================================================
// 生成処理(位置、回転)
//===========================================================================================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObject2D *pObject2D = nullptr;

	if (pObject2D == nullptr)
	{
		//オブジェクト2Dの生成
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//初期化処理
			pObject2D->Init();

			pObject2D->SetPosition(pos);
			pObject2D->SetRotation(rot);

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject2D;
}

//===========================================================================================
// 生成処理(位置、テクスチャ名)
//===========================================================================================
CObject2D * CObject2D::Create(D3DXVECTOR3 pos, const char *name)
{
	CObject2D *pObject2D = nullptr;
	CTexture *pTex = CManager::GetInstance()->GetTexture();

	if (pObject2D == nullptr)
	{
		//オブジェクト2Dの生成
		pObject2D = new CObject2D;

		if (pObject2D != nullptr)
		{
			//初期化処理
			pObject2D->Init();

			pObject2D->SetPosition(pos);

			pObject2D->BindTexture(pTex->Regist(name));

			return pObject2D;
		}
		else
		{
			return nullptr;
		}
	}

	return pObject2D;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CObject2D::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//位置(デフォルト)
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 0.0f);

	//サイズ設定(デフォルト)
	m_fWidth = SIZE_X;
	m_fHeight = SIZE_Y;

	//対角線の長さを算出(デフォルト)
	m_fLength = sqrtf(SIZE_X * SIZE_X + SIZE_Y * SIZE_Y) * 0.5f;

	//対角線の角度を算出する(デフォルト)
	m_fAngle = atan2f(SIZE_X, SIZE_Y);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報の設定(デフォルト)
	SetVertex();

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CObject2D::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != nullptr)
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
void CObject2D::Update(void)
{

}

//===========================================================================================
// 描画処理
//===========================================================================================
void CObject2D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//テクスチャ情報の取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));			//頂点情報構造体のサイズ

	//テクスチャの設定
	if (pTexture != NULL)
	{
		pDevice->SetTexture(0, pTexture->GetAddress(m_nTextureIdx));
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//プリミティブの種類
		0,			//描画する最初のインデックス(大事)
		2);			//プリミティブ(ポリゴン)数
}

//=======================================================
// 頂点情報の設定(デフォルト&&)
//=======================================================
void CObject2D::SetVertex(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=======================================================
// 頂点情報の設定(単純なもの用)
//=======================================================
void CObject2D::SetVertex(D3DXVECTOR2 size)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y + size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=======================================================
// 頂点情報の設定(スクロール用)
//=======================================================
void CObject2D::SetVertex(float fWidth, float fHeight, float fSpeedx, float fSpeedy)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth, m_pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth, m_pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y + fHeight, 0.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(fSpeedx, fSpeedy);
	pVtx[1].tex = D3DXVECTOR2(fSpeedx + 1.0f, fSpeedy);
	pVtx[2].tex = D3DXVECTOR2(fSpeedx, fSpeedy + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fSpeedx + 1.0f, fSpeedy + 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=======================================================
// 位置の設定
//=======================================================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	//引数から値を取得
	m_pos = pos;

	//頂点情報
	SetVertex();
}

//=======================================================
// 位置情報の取得
//=======================================================
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

//=======================================================
// 向きの設定
//=======================================================
void CObject2D::SetRotation(D3DXVECTOR3 rot)
{
	//引数から値を取得
	m_rot = rot;

	//頂点情報
	SetVertex();
}

//=======================================================
// 向きの取得
//=======================================================
D3DXVECTOR3 CObject2D::GetRotation(void)
{
	return m_rot;
}

//=======================================================
// 色の設定
//=======================================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//色の設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=======================================================
// 色の取得
//=======================================================
D3DXCOLOR CObject2D::GetColor(void)
{
	return m_col;
}

//=======================================================
// ポリゴンサイズの取得
//=======================================================
D3DXVECTOR2 CObject2D::GetSize(void)
{
	return D3DXVECTOR2(m_fWidth, m_fHeight);
}

//=======================================================
// ポリゴンサイズの設定
//=======================================================
void CObject2D::SetSizeCenter(float fWidth, float fHeight)
{
	//サイズの設定(向きを使用しない場合)
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=======================================================
// ポリゴンサイズの設定
//=======================================================
void CObject2D::SetSize_lefteEnd(float fWidth, float fHeight)
{
	//サイズの設定(向きを使用しない場合)
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y + m_fHeight, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=======================================================
// ポリゴンサイズの設定
//=======================================================
void CObject2D::SetSizeLength(float fWidth, float fHeight)
{
	//対角線の長さを算出する(向きを使用する場合)
	m_fLength = sqrtf(fWidth * fWidth + fHeight * fHeight) * 0.5f;

	//対角線の角度を算出する(向きを使用する場合)
	m_fAngle = atan2f(fWidth, fHeight);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + -D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=======================================================
// ポリゴンサイズの設定
//=======================================================
float CObject2D::GetAngle(void)
{
	return m_fAngle;
}

//=======================================================
// 角度の取得
//=======================================================
float CObject2D::GetLength(void)
{
	return m_fLength;
}

//=======================================================
// テクスチャの番号割り当て
//=======================================================
void CObject2D::BindTexture(int nIdx)
{
	m_nTextureIdx = nIdx;
}

//=======================================================
// 頂点情報の取得
//=======================================================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetVtxBuff(void)
{
	return m_pVtxBuff;
}
