//===============================================================================
//
// [number.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _NUMBER_H_				//このマクロ定義がされていなかったら
#define _NUMBER_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "object.h"

//前方宣言
class CObject2D;

//ナンバークラス
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static CNumber *Create(D3DXVECTOR3 pos);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(float fWidth, float fHeight);
	CObject2D *GetObject2D(void);

private:
	static int m_nTextureIdx;			//テクスチャ番号
	CObject2D *m_pObject2D;
};

#endif