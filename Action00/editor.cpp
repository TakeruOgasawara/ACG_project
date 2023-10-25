//===========================================================================================
//
// [edit.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include <assert.h>
#include "editor.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "object.h"
#include "objectX.h"
#include "debugproc.h"

#include "texture.h"
#include "xfile.h"

//マクロ定義
static const int MAX_TYPE = 3;
#define SPEED			(49.0f)

static char* FILENAME = "data\\TXT\\stage\\stage0.txt";

//===========================================================================================
// コンストラクタ
//===========================================================================================
CEditor::CEditor()
{
	m_nTypeIdx = 0;
	m_bUse = false;
	m_object.BuffMat = nullptr;
	m_object.dwNumMat = NULL;
	m_object.rot = { 0.0f, 0.0f, 0.0f };
	m_object.pos = { 0.0f, 0.0f, 0.0f };
	m_pObjectX = nullptr;
	m_nIdx = 0;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CEditor::~CEditor()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CEditor* CEditor::Create(void)
{
	CEditor* pEdit = nullptr;

	if (pEdit == nullptr)
	{
		pEdit = new CEditor;

		return pEdit;
	}

	return nullptr;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CEditor::Init(void)
{
	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CEditor::Uninit(void)
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
void CEditor::Update(void)
{
	//キーボード情報の取得
	CInputKeyboard* pInputKey = CManager::GetInstance()->GetInputKeyboard();
	CDebugProc* pDebug = CManager::GetInstance()->GetDebugProc();
	CXfile* pXfile = CManager::GetInstance()->GetXfile();

	if (pInputKey->GetTrigger(DIK_F3))
	{
		m_bUse = m_bUse ? false : true;
	}

	if (m_bUse == false)
	{
		return;
	}

	CManager::GetInstance()->GetDebugProc()->Print("\n\n【エディットモード中】\n");
	CManager::GetInstance()->GetDebugProc()->Print("位置： x:%f y:%f z:%f\n", m_object.pos.x, m_object.pos.y, m_object.pos.z);
	CManager::GetInstance()->GetDebugProc()->Print("向き： x:%f y:%f z:%f\n", m_object.rot.x, m_object.rot.y, m_object.rot.z);
	CManager::GetInstance()->GetDebugProc()->Print("種類： %d\n", m_nTypeIdx);

	//移動
	if (pInputKey->GetTrigger(DIK_UP))
	{
		m_object.pos.y += SPEED;
	}
	if (pInputKey->GetTrigger(DIK_DOWN))
	{
		m_object.pos.y -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_LEFT))
	{
		m_object.pos.x -= SPEED;
	}
	if (pInputKey->GetTrigger(DIK_RIGHT))
	{
		m_object.pos.x += SPEED;
	}

	if (pInputKey->GetTrigger(DIK_LSHIFT))
	{
		m_object.pos.z += SPEED;
	}

	if (pInputKey->GetTrigger(DIK_LCONTROL))
	{
		m_object.pos.z -= SPEED;
	}

	//オブジェクト種類の変更
	if (pInputKey->GetTrigger(DIK_1))
	{
		m_nTypeIdx++;

		int nCt = pXfile->GetNumAll();

		m_nTypeIdx %= pXfile->GetNumAll();			//繰り返し
	}

	//オブジェクトの設置
	if (pInputKey->GetTrigger(DIK_RETURN))
	{
		m_pObjectX = CObjectX::Create(pXfile->GetFileName(m_nTypeIdx), m_object.pos);
		m_pObjectX->SetModelIdx(m_nTypeIdx);
	}

	//ファイル書き込み(セーブ)
	if (pInputKey->GetTrigger(DIK_F9))
	{
		Save();
	}
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CEditor::Draw(void)
{
	if (m_bUse == false)
	{
		return;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	CXfile* pXfile = CManager::GetInstance()->GetXfile();
	CXfile::SXFile* pXfileData = pXfile->GetAdrress(m_nTypeIdx);

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;	//現在のマテリアル保存用
	D3DXMATERIAL* pMat;	//マテリアルデータへのポインタ

	if (pXfileData == nullptr)
	{
		assert(false);

		return;
	}

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_object.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_object.rot.y, m_object.rot.x, m_object.rot.z);
	D3DXMatrixMultiply(&m_object.mtxWorld, &m_object.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_object.pos.x, m_object.pos.y, m_object.pos.z);
	D3DXMatrixMultiply(&m_object.mtxWorld, &m_object.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_object.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)pXfileData->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXfileData->dwNumMat; nCntMat++)
	{
		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, pTexture->GetAddress(pXfileData->pTextureIdx));

		//オブジェクト(パーツ)の描画
		if (FAILED(pXfileData->pMesh->DrawSubset(nCntMat)))
		{
			assert(false);
		}
	}

	//保存されていたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===========================================================================================
// 読み込み
//===========================================================================================
void CEditor::Load(const char* pFilename)
{
	char Dast[128] = {};		//文字列のゴミ箱
	int nType = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CXfile* pXfile = CManager::GetInstance()->GetXfile();
	CXfile::SXFile* pXfileData = pXfile->GetAdrress(m_nTypeIdx);
	FILE* pFile = nullptr;			//ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(pFilename, "r");

	if (pFile == nullptr)
	{
		return;
	}

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
			m_pObjectX = CObjectX::Create(pXfile->GetFileName(nType), pos);
		}
	}
}

//===========================================================================================
// 書き込み
//===========================================================================================
void CEditor::Save(void)
{
	FILE* pFile = NULL;			//ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data\\TXT\\stage\\stage0.txt", "w");

	if (pFile == nullptr)
	{
		return;
	}

	fprintf(pFile, "SCRIPT\n\n");

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
		{
			CObject* pObj = CObject::GetCObject(nCntPriority, nCnt);

			if (pObj != NULL && pObj->GetType() == CObject::TYPE_OBJECTX)
			{
				CObjectX* pObjectX = pObj->GetObjectX();

				D3DXVECTOR3 pos = pObjectX->GetPosition();
				D3DXVECTOR3 rot = pObjectX->GetRotation();
				int nTypeIdx = pObjectX->GetModelIndx();

				fprintf(pFile, "OBJECTSET\n");
				fprintf(pFile, "	TYPE = %d\n", nTypeIdx);
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