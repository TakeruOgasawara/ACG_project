//===========================================================================================
//
// [time.cpp]m_aChain[0]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "time.h"
#include "object2D.h"
#include "number.h"
#include "manager.h"
#include "texture.h"

#include <assert.h>

//マクロ定義
#define AIDA			(30.0f)
#define START_MINUT		(3)
#define START_TIME		(0)

//===========================================================================================
// コンストラクタ
//===========================================================================================
CTime::CTime()
{
	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
	m_pPeriod = nullptr;
	m_pColon = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSecondCount = 0;
	m_nMinuteCount = 0;
	m_dwGameStartTime = 0;	//ゲーム開始時間
	m_dwGameTime = 0;	//ゲーム経過時間
	m_state = STATE_NONE;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CTime::~CTime()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CTime* CTime::Create(D3DXVECTOR3 pos)
{
	CTime* pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;

		if (pTime != NULL)
		{
			pTime->Init(pos);

			return pTime;
		}
		else
		{
			return NULL;
		}
	}

	return NULL;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
	m_pPeriod = nullptr;
	m_pColon = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSecondCount = 0;
	m_nMinuteCount = 0;
	m_dwGameStartTime = 0;	//ゲーム開始時間
	m_dwGameTime = 0;	//ゲーム経過時間
	m_state = STATE_NONE;

	m_pos = pos;

	m_nMinuteCount = START_MINUT * 10000;
	m_nSecondCount = START_TIME;

	m_state = STATE_COUNT;

	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(pos);

		switch (nCnt)
		{
		case 0:	//分
			m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + ((AIDA) * nCnt), m_pos.y, 0.0f));

			m_pColon = CObject2D::Create(D3DXVECTOR3(m_pos.x + ((AIDA) * nCnt + 27.0f), m_pos.y + 7.0f, 0.0f));
			m_pColon->SetSizeCenter(3.0f, 13.0f);
			m_pColon->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\colon.png"));

			break;

		case 1:	//秒
			m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + ((AIDA) * nCnt + 25.0f), m_pos.y, 0.0f));
			break;

		case 2:
			m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + ((AIDA) * nCnt + 25.0f), m_pos.y, 0.0f));
			break;

		case 3:	//コンマ秒
			m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + ((AIDA) * nCnt + 50.0f), m_pos.y, 0.0f));

			m_pPeriod = CObject2D::Create(D3DXVECTOR3(m_pos.x + ((AIDA)*nCnt + 25.0f), m_pos.y + 20.0f, 0.0f));
			m_pPeriod->SetSizeCenter(3.0f, 3.0f);
			m_pPeriod->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\period.png"));

			break;

		case 4:
			m_apNumber[nCnt]->SetPosition(D3DXVECTOR3(m_pos.x + ((AIDA) * nCnt + 50.0f), m_pos.y, 0.0f));
			break;
		default:

			break;
		}

		m_apNumber[nCnt]->SetSize(15.0f, 20.0f);
	}

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CTime::Uninit()
{
	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = nullptr;
		}
	}

	if (m_pColon != nullptr)
	{
		//m_pColon->Uninit();
		m_pColon = nullptr;
	}

	if (m_pPeriod != nullptr)
	{
		//m_pPeriod->Uninit();
		m_pPeriod = nullptr;
	}

	//今回のゲームの秒数を取得(ここに置くのヤバいかも)
	CManager::GetInstance()->SetCurrentTime(m_nMinuteCount, m_nSecondCount);
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CTime::Update()
{
	SetTime();
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CTime::Draw()
{
	for (int nCnt = 0; nCnt < NUM_TIME; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//===========================================================================================
// タイムの設定
//===========================================================================================
void CTime::SetTime(void)
{
	int aTexU[NUM_TIME];			//各桁の数字を格納

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	if (m_state == STATE_COUNT)
	{
		//経過時間の算出
		m_dwGameTime = timeGetTime() - m_dwGameStartTime;

		if (m_dwGameTime %= 1000)
		{
			m_nSecondCount--;
		}
	}

	//分
	aTexU[0] = m_nMinuteCount % 100000 / 10000;

	// 秒
	aTexU[1] = m_nSecondCount % 10000 / 1000;
	aTexU[2] = m_nSecondCount % 1000 / 100;

	// コンマ秒
	aTexU[3] = m_nSecondCount % 100 / 10;
	aTexU[4] = m_nSecondCount % 10 / 1;

	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{
		if (m_apNumber[nCntTime] != nullptr)
		{
			//頂点バッファをロック
			m_apNumber[nCntTime]->GetObject2D()->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(aTexU[nCntTime] * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(aTexU[nCntTime] * 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(aTexU[nCntTime] * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(aTexU[nCntTime] * 0.1f + 0.1f, 1.0f);

			//頂点バッファをアンロックする
			m_apNumber[nCntTime]->GetObject2D()->GetVtxBuff()->Unlock();
		}
	}

	//終了
	if (m_state == STATE_COUNT)
	{
		if (m_nMinuteCount <= 0 && m_nSecondCount <= 0)
		{
			m_nMinuteCount = 0;
			m_nSecondCount = 0;
			m_state = STATE_END;
			return;
		}
		if (m_nSecondCount <= 0)
		{
			m_nSecondCount = 6000;
			m_nMinuteCount -= (1 * 10000);
		}
	}
}

//===========================================================================================
// タイムの加算(アイテムを取った時など今は使わん)
//===========================================================================================
void CTime::AddTime(int nMinute, int nSecond)
{
	m_nMinuteCount = nMinute * 10000;
	m_nSecondCount = nSecond /** 100*/;
}

//===========================================================================================
// タイムの取得
//===========================================================================================
int CTime::GetTime(void)
{
	return m_nSecondCount;
}
