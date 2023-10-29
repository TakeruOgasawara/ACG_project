//======================================================================================
//
// フェード処理[fade.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "fade_death.h"

//マクロ定義
#define FADE_TIME		(0.02f)			//フェードの間隔
#define START	(30)

//========================================================================
// コンストラクタ
//========================================================================
CFadeDeath::CFadeDeath(int nPriority) : CObject2D(nPriority)
{
	m_state = STATE_NONE;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nStartCnt = 0;
}

//========================================================================
// デストラクタ
//========================================================================
CFadeDeath::~CFadeDeath()
{

}

//========================================================================
// 生成
//========================================================================
CFadeDeath *CFadeDeath::Create(void)
{
	CFadeDeath *pFade = nullptr;

	if (pFade == nullptr)
	{
		pFade = new CFadeDeath;

		if (pFade != nullptr)
		{
			pFade->Init();
			return pFade;
		}
	}

	return pFade;
}

//========================================================================
// 初期化処理(オーバーロード)
//========================================================================
HRESULT CFadeDeath::Init(void)
{
	m_nStartCnt = 0;

	//生成
	CObject2D::Init();

	//位置・サイズ・色の設定
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSizeCenter(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	SetState(STATE_IN);

	return S_OK;
}

//========================================================================
// 終了処理
//========================================================================
void CFadeDeath::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================================
// 更新処理
//========================================================================
void CFadeDeath::Update(void)
{
	if (m_state != STATE_NONE)
	{
		m_nStartCnt++;

		if (m_nStartCnt < START)
		{
			return;
		}

		if (m_state == STATE_IN)
		{//フェードイン状態

			m_col.a -= FADE_TIME;			//ポリゴンを透明にしていく

			if (m_col.a <= 0.0f)
			{
				m_nStartCnt = 0;
				m_col.a = 0.0f;
				m_state = STATE_NONE;				//何もしていない状態
			}
		}

		//色の反映
		SetColor(m_col);
	}
}

//========================================================================
// 描画処理
//========================================================================
void CFadeDeath::Draw(void)
{
	if (m_state != STATE_NONE)
	{
		CObject2D::Draw();
	}
}

//========================================================================
//フェード状態の設定
//========================================================================
void CFadeDeath::SetState(STATE state)
{
	m_state = state;

	switch (m_state)
	{
	case STATE_NONE:
		m_col.a = 0.0f;
		break;

	case STATE_IN:
		m_col.a = 1.0f;
		break;

	case STATE_OUT:
		m_col.a = 0.0f;
		break;

	default:

		break;
	}

	SetColor(m_col);
}