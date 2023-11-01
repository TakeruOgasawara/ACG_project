//===============================================================================
//
// [billboard.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _BILLBOARD_H_				//このマクロ定義がされていなかったら
#define _BILLBOARD_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "object.h"

//ビルボードクラス
class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = 3);			//コンストラクタ
	~CBillboard();			//デストラクタ

	static CBillboard *Create(void);
	static CBillboard *Create(D3DXVECTOR3 pos);
	static CBillboard *Create(D3DXVECTOR3 pos, const char *pTexName);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定用
	void SetverTex(void);	//頂点設定
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//位置設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//向き設定
	void SetSize(D3DXVECTOR2 size) { m_size = size; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetLighting(bool bUse) { m_bUseLighting = bUse; }
	void SetRadius(D3DXVECTOR2 radius);

	//取得用
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//位置取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//向き取得
	D3DXVECTOR2 GetSize(void) { return m_size; }	//大きさ取得
	D3DXCOLOR GetColor(void) { return m_col; }	//色取得

	//テクスチャ割り当て
	void BindTexture(int nIdx);
	void BindTexture(const char *texName);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへの頂点情報
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//バッファへの頂点情報
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_move;			//移動
	D3DXCOLOR m_col;			//色
	D3DXVECTOR2 m_size;

	bool m_bUseLighting;				//使っているか
	int m_nTextureIdx;			//テクスチャ番号

	struct Size
	{
		float fLength;
		float fangle;
	};
	//Size m_size;
};
#endif