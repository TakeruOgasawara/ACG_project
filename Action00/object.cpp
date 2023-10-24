//===========================================================================================
//
// [object.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//静的メンバ変数の宣言
CObject *CObject::m_apObject[NUM_PRIORITY][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//===========================================================================================
// コンストラクタ
//===========================================================================================
CObject::CObject(int nPriority)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == nullptr)
		{
			m_apObject[nPriority][nCntObject] = this;		//自分自身を代入
			m_nID = nCntObject;		//自分自身のIDを保存
			m_nPriority = nPriority;
			m_type = TYPE_NONE;
			m_nNumAll++;		//総数をカウントアップ

			break;
		}
	}
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CObject::~CObject()
{

}

//===========================================================================================
// 全てのオブジェクトの破棄
//===========================================================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();		//終了処理
			}
		}
	}
}

//===========================================================================================
// 特定のオブジェクトの更新
//===========================================================================================
void CObject::ParticularRelease(TYPE type)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr && m_apObject[nCntPriority][nCntObject]->m_type == type)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();		//終了処理
			}
		}
	}
}

//===========================================================================================
// 全てのオブジェクトの更新
//===========================================================================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_nID <= MAX_OBJECT && m_apObject[nCntPriority][nCntObject]->m_nID > -1)
				{
					m_apObject[nCntPriority][nCntObject]->Update();			//更新処理
				}
			}
		}
	}
}

//===========================================================================================
// 全てのオブジェクトの描画
//===========================================================================================
void CObject::DrawAll(void)
{
	//カメラ情報の取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//カメラのセット
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_nID <= MAX_OBJECT && m_apObject[nCntPriority][nCntObject]->m_nID > -1)
				{
					m_apObject[nCntPriority][nCntObject]->Draw();		//描画処理
				}
			}
		}
	}
}

//===========================================================================================
// 特定の全てのオブジェクトの破棄
//===========================================================================================
void CObject::ReleaseAll_specified(TYPE type)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->GetType() == type)
				{
					m_apObject[nCntPriority][nCntObject]->Uninit();		//終了処理
				}
			}
		}
	}
}

//===========================================================================================
// オブジェクト情報の取得
//===========================================================================================
CObject *CObject::GetCObject(int nPriority, int nIdx)
{
	if (m_apObject[nPriority][nIdx] != nullptr)
	{
		return m_apObject[nPriority][nIdx];
	}

	return nullptr;
}

//===========================================================================================
// タイプ判定(判定するオブジェクト、判定したいタイプ)
//===========================================================================================
bool CObject::TypeCheck(CObject *pObject, TYPE type)
{
	if (pObject != nullptr && pObject->GetType() == type)
	{
		return TRUE;
	}

	return FALSE;
}

//===================================================
// オブジェクトの破棄
//===================================================
void CObject::Release(void)
{
	int nID = m_nID;
	int nPriority = m_nPriority;

	if (nID < MAX_OBJECT && nID > -1)
	{
		if (m_apObject[nPriority][nID] != nullptr)
		{
			delete m_apObject[nPriority][nID];
			m_apObject[nPriority][nID] = nullptr;

			m_nNumAll--;		//総数をカウントダウン
		}
	}
}

