//======================================================================================
//
// エフェクト3D処理[effect.h]
// Author : Takeru Ogasawara
//
//======================================================================================
#ifndef _EFFECT3D_H_			//このマクロ定義がされていなかったら
#define _EFFECT3D_H_			//2重インクルード防止のマクロを定義

#include "main.h"
#include "billboard.h"

//*****************************
//マクロ定義
//*****************************
#define MAX_EFFECT			(100)			//エフェクトの最大数

//エフェクトクラス
class CEffect3D : public CBillboard
{
public:
	CEffect3D(int nPriority = 5);
	~CEffect3D();

	static HRESULT Load(void);
	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, int nLife);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int life);

private:
	D3DXVECTOR3 m_move;
	D3DXCOLOR m_col;			//色
	int m_nLife;				//寿命
	int m_nMaxLife;				//最大寿命
	static int m_nTextureIdx;
};

#endif