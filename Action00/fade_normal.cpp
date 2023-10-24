//======================================================================================
//
// フェード処理[fade.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "fade_normal.h"

//マクロ定義
#define FADE_TIME		(0.025f)			//フェードの間隔

//========================================================================
// コンストラクタ
//========================================================================
CFadeNormal::CFadeNormal(int nPriority) : CObject2D(nPriority)
{
	m_state = STATE_NONE;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//========================================================================
// デストラクタ
//========================================================================
CFadeNormal::~CFadeNormal()
{

}

//========================================================================
// 生成
//========================================================================
CFadeNormal *CFadeNormal::Create(void)
{
	CFadeNormal *pFade = nullptr;

	if (pFade == nullptr)
	{
		pFade = new CFadeNormal;

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
HRESULT CFadeNormal::Init(void)
{
	//生成
	CObject2D::Init();

	//位置・サイズ・色の設定
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSize_center(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	//SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	SetState(STATE_IN);

	return S_OK;
}

//========================================================================
// 終了処理
//========================================================================
void CFadeNormal::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================================================
// 更新処理
//========================================================================
void CFadeNormal::Update(void)
{
	if (m_state != STATE_NONE)
	{
		if (m_state == STATE_IN)
		{//フェードイン状態

			m_col.a -= FADE_TIME;			//ポリゴンを透明にしていく

			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_state = STATE_NONE;				//何もしていない状態
			}
		}
		else if (m_state == STATE_OUT)
		{//フェードアウト状態
			m_col.a += FADE_TIME;			//ポリゴンを不透明にしていく

			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;

				return;
			}
		}
		
		//色の反映
		SetColor(m_col);
	}
}

//========================================================================
// 描画処理
//========================================================================
void CFadeNormal::Draw(void)
{
	if (m_state != STATE_NONE)
	{
		CObject2D::Draw();
	}
}

//========================================================================
// 設定処理
//========================================================================
//void CFadeNormal::Set(CScene::MODE modeNext)
//{
//	if (m_state != STATE_OUT)
//	{
//		m_state = STATE_OUT;			//フェードアウト状態
//		m_modeNext = modeNext;			//次の画面(モード)を設定
//		m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//}

//========================================================================
//フェード状態の設定
//========================================================================
void CFadeNormal::SetState(STATE state)
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