//===========================================================================================
//
// [edit.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include "edit.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "object.h"
#include "objectX.h"
#include "debugproc.h"

//マクロ定義
#define MAX_OBJ			(6) 
#define SPEED			(5.0f)

//オブジェクトファイル名
const char *c_Obj[MAX_OBJ] =
{
	"data\\MODEL\\object\\kihon.x",
	"data\\MODEL\\object\\kihon1.x",
	"data\\MODEL\\object\\coin.x",
	"data\\MODEL\\object\\mitumisi.x",
	"data\\MODEL\\object\\TanukiShop.x",
	"data\\MODEL\\object\\tree.x",
};

//===========================================================================================
// コンストラクタ
//===========================================================================================
CEdit::CEdit()
{
	m_nIdx = 0;
	m_nTypeIdx = 0;
	m_bUse = false;
	//m_state = STATE_OFF;

	m_objectX = nullptr;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CEdit::~CEdit()
{

}

//===========================================================================================
// 読み込み
//===========================================================================================
HRESULT CEdit::Load(void)
{
	char Dast[128] = {};		//文字列のゴミ箱
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	FILE *pFile = NULL;			//ファイルポインタを宣言

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
				CObjectX::Create(c_Obj[nType], pos);
			}
		}
	}

	return S_OK;
}

//===========================================================================================
// 書き込み
//===========================================================================================
void CEdit::Save(void)
{
	FILE *pFile = NULL;			//ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data\\TXT\\MAP\\stage.txt", "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "SCRIPT\n\n");

		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{
			for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
			{
				CObject *pObj = CObject::GetCObject(nCntPriority, nCnt);

				if (pObj != NULL && pObj->GetType() == CObject::TYPE_OBJECTX)
				{
					D3DXVECTOR3 pos = pObj->GetPosition();
					D3DXVECTOR3 rot = pObj->GetRotation();

					fprintf(pFile, "OBJECTSET\n");
					fprintf(pFile, "	TYPE = %d\n", 0);
					fprintf(pFile, "	POS = %0.2f %0.2f %0.2f\n", pos.x, pos.y, pos.z);
					fprintf(pFile, "	ROT = %0.2f %0.2f %0.2f\n", rot.x, rot.y, rot.z);
					fprintf(pFile, "END_OBJECTSET\n\n");
				}
			}
		}

		//終了の合図
		fprintf(pFile, "END_SCRIPT");

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CEdit::Init(D3DXVECTOR3 pos)
{
	//オブジェクトの初期化
	m_objectX = CObjectX::Create(c_Obj[m_nTypeIdx], pos);

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CEdit::Uninit(void)
{
	//オブジェクトの終了処理
	//CObjectX::Uninit();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CEdit::Update(void)
{
	//キーボード情報の取得
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CDebugProc *pDebug = CManager::GetDebugProc();

	D3DXVECTOR3 pos;

	if (pInputKey->GetTrigger(DIK_F3))
	{
		m_bUse = m_bUse ? false : true;			//使用するかの有無
	}

	if (m_bUse == true)
	{
		//オブジェクトの初期化
		m_objectX->Init(c_Obj[m_nTypeIdx], m_objectX->GetPosition());
	}
	else
	{
		return;
	}

	//オブジェクト種類の変更
	if (pInputKey->GetTrigger(DIK_1))
	{
		m_nTypeIdx++;

		//オブジェクトの初期化
		m_objectX->Init(c_Obj[m_nTypeIdx], m_objectX->GetPosition());

		m_nTypeIdx %= MAX_OBJ;			//繰り返し
	}

	//移動
	if (pInputKey->GetPress(DIK_UP))
	{
		pos.z += 1.0f;
	}
	if (pInputKey->GetPress(DIK_DOWN))
	{
		pos.z -= 1.0f;
	}
	if (pInputKey->GetPress(DIK_LEFT))
	{
		pos.x -= 1.0f;
	}
	if (pInputKey->GetPress(DIK_RIGHT))
	{
		pos.x += 1.0f;
	}
	if (pInputKey->GetPress(DIK_LSHIFT))
	{
		pos.y += 1.0f;
	}
	if (pInputKey->GetPress(DIK_LCONTROL))
	{
		pos.y -= 1.0f;
	}

	//位置の更新
	m_objectX->SetPosition(pos);

	//オブジェクトの設置
	if (pInputKey->GetTrigger(DIK_RETURN))
	{
		//生成
		m_objectX = CObjectX::Create(c_Obj[m_nTypeIdx], pos);

		m_nIdx++;
	}

	//ファイル書き込み(セーブ)
	if (pInputKey->GetTrigger(DIK_0))
	{
		Save();
	}
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CEdit::Draw(void)
{
	//オブジェクトの描画
	if (m_objectX != nullptr)
	{
		m_objectX->Draw();
	}
}
