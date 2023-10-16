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
#define MAX_OBJ			(2) 
#define SPEED			(50.0f)

//オブジェクトファイル名
const char *c_Obj[MAX_OBJ] =
{
	"data\\MODEL\\object\\floor00.x",
	"data\\MODEL\\object\\blockTile00.x",
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
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_pObjectX = nullptr;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CEdit::~CEdit()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CEdit* CEdit::Create(void)
{
	CEdit* pEdit = nullptr;

	if (pEdit == nullptr)
	{
		pEdit = new CEdit;

		pEdit->Init();

		return pEdit;
	}

	return nullptr;
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
	pFile = fopen("data\\TXT\\stage\\stage.txt", "w");

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
HRESULT CEdit::Init(void)
{
	//オブジェクトの初期化
	m_pObjectX = CObjectX::Create(c_Obj[m_nTypeIdx], m_pos);

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CEdit::Uninit(void)
{
	if (m_pObjectX != nullptr)
	{
		delete m_pObjectX;
		m_pObjectX = nullptr;
	}
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CEdit::Update(void)
{
	//キーボード情報の取得
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();
	CDebugProc *pDebug = CManager::GetDebugProc();

	CManager::GetDebugProc()->Print("\n\nデバッグモード中\n\n");

	if (m_pObjectX == nullptr)
	{
		return;
	}

	//オブジェクト種類の変更
	if (pInputKey->GetTrigger(DIK_1))
	{
		m_nTypeIdx++;

		m_nTypeIdx %= MAX_OBJ;			//繰り返し

		//オブジェクトの初期化
		m_pObjectX->Init(c_Obj[m_nTypeIdx], m_pObjectX->GetPosition());
	}

	//移動
	if (pInputKey->GetTrigger(DIK_UP))
	{
		m_pos.y += SPEED;
	}
	if (pInputKey->GetTrigger(DIK_DOWN))
	{
		m_pos.y -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_LEFT))
	{
		m_pos.x -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_RIGHT))
	{
		m_pos.x += SPEED;
	}

	//位置の更新
	m_pObjectX->SetPosition(m_pos);

	//オブジェクトの設置
	if (pInputKey->GetTrigger(DIK_RETURN))
	{
		//生成
		m_pObjectX = CObjectX::Create(c_Obj[m_nTypeIdx], m_pos);

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
	if (m_pObjectX != nullptr)
	{
		m_pObjectX->Draw();
	}
}
