//===========================================================================================
//
// [effect3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "effect3D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define DEC_COL			(0.04f)
#define DEC_SIZE		(0.05f)

//静的メンバ変数宣言
int CEffect3D::m_nTextureIdx = 0;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CEffect3D::CEffect3D(int nPriority) : CBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 0;
	m_nMaxLife = 0;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CEffect3D::~CEffect3D()
{

}

//===========================================================================================
// テクスチャ読み込み
//===========================================================================================
HRESULT CEffect3D::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//使いたいテクスチャ名を指定
	m_nTextureIdx = CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\effect000.jpg");

	return S_OK;
}

//===========================================================================================
// 生成
//===========================================================================================
CEffect3D *CEffect3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife)
{
	CEffect3D *pEffect3D = NULL;

	if (pEffect3D == NULL)
	{
		pEffect3D = new CEffect3D;

		if (pEffect3D != NULL)
		{
			//初期化処理
			pEffect3D->Init();

			//生成位置の設定
			pEffect3D->SetPosition(pos);

			//サイズ設定
			pEffect3D->SetRadius(D3DXVECTOR2(fRadius, fRadius));

			//移動量設定
			pEffect3D->m_move = move;

			//色設定
			pEffect3D->SetColor(col);

			//体力設定
			pEffect3D->SetLife(nLife);

			//テクスチャ割り当て
			pEffect3D->BindTexture(m_nTextureIdx);

			return pEffect3D;
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
HRESULT CEffect3D::Init(void)
{
	//初期化処理
	CBillboard::Init();

	m_nLife = 100;
	m_nMaxLife = 100;

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CEffect3D::Uninit(void)
{
	//終了処理
	CBillboard::Uninit();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CEffect3D::Update(void)
{
	float fLength = 0.0f/* = GetLength()*/;
	m_col = GetColor();

	//体力の減算
	m_nLife--;

	//エフェクトの破棄
	if (m_nLife <= 0 || fLength <= 0.0f || m_col.a <= 0.0f)
	{//いずれかの数値が0以下になったら

		//破棄
		Uninit();
	}
	else
	{
		//位置情報の取得
		D3DXVECTOR3 pos = GetPosition();

		//位置に移動量を加算
		pos += m_move;

		//位置の設定
		SetPosition(pos);

		//カラーの減算//今の寿命わるマックスの寿命
		m_col.a -= DEC_COL;

		//半径の減算//今の寿命わるマックスの寿命
		fLength -= DEC_SIZE;

		//頂点設定
		SetSize(D3DXVECTOR2(fLength, fLength));

		//色設定
		SetColor(m_col);
	}
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CEffect3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//aブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===========================================================================================
// 体力設定
//===========================================================================================
void CEffect3D::SetLife(int life)
{
	m_nLife = life;
	m_nMaxLife = life;
}
