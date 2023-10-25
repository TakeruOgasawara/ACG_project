//===============================================================================
//
// [edit.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _EDITOR_H_				//このマクロ定義がされていなかったら
#define _EDITOR_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "objectX.h"

//前方宣言
class CObjectX;

//プレイヤークラス
class CEditor
{
private:	//定数用プライベート

	static const int NUM_OBJECT = 100;
	static const int MAX_NAME = 254;

public:
	struct SObjectX
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//バッファへの頂点情報
		D3DXMATRIX mtxWorld;	//ワールドマトリックス
		LPD3DXMESH pMesh;	//使用されているモデル数
		LPD3DXBUFFER BuffMat;	//頂点カラー情報
		DWORD dwNumMat;		//カラーの数
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	};

public:

	CEditor();
	~CEditor();

	static CEditor* Create(void);

	void Load(const char* pFilename);
	void Save(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObjectX* m_pObjectX;
	SObjectX m_object;
	int m_nTypeIdx;
	int m_nIdx;
	bool m_bUse;
};

#endif