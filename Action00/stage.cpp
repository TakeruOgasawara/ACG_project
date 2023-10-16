//======================================================================================
//
// ステージ処理[stage.cpp]
// Author : Takeru Ogasawara
//
//======================================================================================
#include "stage.h"
#include <stdio.h>

#include "objectX.h"

//========================================================================
// コンストラクタ
//========================================================================
CStage::CStage()
{
	m_data = {};
}

//========================================================================
// デストラクタ
//========================================================================
CStage::~CStage()
{

}

//========================================================================
// 生成
//========================================================================
CStage* CStage::Create(void)
{
	CStage* pStage = nullptr;

	if (pStage == nullptr)
	{
		pStage = new CStage;

		if (pStage != nullptr)
		{
			pStage->Init();

			return pStage;
		}
	}

	return nullptr;
}

//========================================================================
// 初期化処理
//========================================================================
HRESULT CStage::Init()
{
	m_data.area = AREA_0;
	m_data.stage = STAGE_0;

	return S_OK;
}

//========================================================================
// 終了処理
//========================================================================
void CStage::Uninit()
{

}

//========================================================================
// 更新処理
//========================================================================
void CStage::Update()
{

}

//========================================================================
// 描画処理
//========================================================================
void CStage::Draw()
{

}

HRESULT CStage::Load(void)
{
	char Dast[128] = {};		//文字列のゴミ箱
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	FILE* pFile = NULL;			//ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data\\TXT\\MAP\\stage.txt", "r");

	if (pFile != NULL)
	{
		while (strcmp("END_SCRIPT", &Dast[0]) != 0)
		{
			fscanf(pFile, "%s", &Dast[0]);

			if (strcmp("OBJECTSET", &Dast[0]) == 0)
			{
				while (1)
				{
					fscanf(pFile, "%s", &Dast[0]);

					if (strcmp("TYPE", &Dast[0]) == 0)
					{
						fscanf(pFile, "%s", &Dast[0]);
						fscanf(pFile, "%d", &nType);			//位置x
					}
					if (strcmp("POS", &Dast[0]) == 0)
					{
						fscanf(pFile, "%s", &Dast[0]);
						fscanf(pFile, "%f", &pos.x);			//位置x
						fscanf(pFile, "%f", &pos.y);			//位置y
						fscanf(pFile, "%f", &pos.z);			//位置z
					}
					if (strcmp("ROT", &Dast[0]) == 0)
					{
						fscanf(pFile, "%s", &Dast[0]);
						fscanf(pFile, "%f", &rot.x);			//位置x
						fscanf(pFile, "%f", &rot.y);			//位置y
						fscanf(pFile, "%f", &rot.z);			//位置z

						break;
					}
				}
			}
			else if (strcmp("END_OBJECTSET", &Dast[0]) == 0)
			{
				//CObjectX::Create(c_Obj[nType], pos);
			}
		}
	}

	return S_OK;
}
