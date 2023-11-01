//===============================================================================
//
// [object2D.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _OBJECT2D_H_				//このマクロ定義がされていなかったら
#define _OBJECT2D_H_				//2重インクルード帽子のマクロを定義

#include "main.h"
#include "object.h"

class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 3);			//コンストラクタ
	~CObject2D();			//デストラクタ

	static CObject2D *Create(void);
	static CObject2D *Create(D3DXVECTOR3 pos);
	static CObject2D *Create(const int nPriority = 3);
	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CObject2D *Create(D3DXVECTOR3 pos, const char *FileName);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//設定用
	void SetVertex(void);
	void SetVertex(D3DXVECTOR2 size);
	void SetVertex(float fWidth, float fHeight, float fSpeedx, float fSpeedy);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetColor(D3DXCOLOR col);
	void SetTexture(D3DXVECTOR2 tex);
	void SetSizeCenter(float fWidth, float fHeight);
	void SetSize_lefteEnd(float fWidth, float fHeight);
	void SetSizeLength(float fWidth, float fHeight);

	//取得用
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetRotation(void);
	D3DXCOLOR GetColor(void);
	D3DXVECTOR2 GetSize(void);
	float GetAngle(void);
	float GetLength(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);
	int GetNumObj3D(void) { return m_nNumObj2D; };

	//テクスチャ割り当て
	void BindTexture(int nIdx);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへの頂点情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//バッファへの頂点情報
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	D3DXCOLOR m_col;			//色
	float m_fWidth;				//横
	float m_fHeight;			//縦
	float m_fLength;			//長さ
	float m_fAngle;				//角度
	static int m_nNumObj2D;
	int m_nTextureIdx;
};

#endif