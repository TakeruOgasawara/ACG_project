//===============================================================================
//
// [objectX.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _OBJECTX_H_				//このマクロ定義がされていなかったら
#define _OBJECTX_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "object.h"

//前方宣言
class CXfile;

class CObjectX : public CObject
{
private:
	const float SIZE = 20.0f;

public:
	CObjectX(int nPriority = 0);			//コンストラクタ
	~CObjectX();			//デストラクタ

	//生成
	static CObjectX *Create(void);
	static CObjectX *Create(const char *c_pFileName, D3DXVECTOR3 pos);

	HRESULT Init(void);
	HRESULT Init(const char *c_pFileName, D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pVtxMax, D3DXVECTOR3 pVtxMin);

	//設定用
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetModelIdx(int nIdx) { m_nModelIdx = nIdx; }

	//取得用
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }
	CObjectX *GetObjectX(void) { return this; }
	int GetModelIndx(void) { return m_nModelIdx; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファへの頂点情報
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	LPD3DXMESH m_pMesh;					//使用されているモデル数
	LPD3DXBUFFER m_pBuffMat;			//頂点カラー情報
	DWORD m_dwNumMat;					//カラーの数
	D3DXVECTOR3 m_vtxMin, m_vtxMax;		//オブジェクトの最大値・最小値
	int m_nTextureIdx;			//テクスチャ番号
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	int m_nModelIdx;			//モデル番号
};

#endif