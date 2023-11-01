//======================================================================================
//
// パーティクル3D処理[particle3D.h]
// Author : Takeru Ogasawara
//
//======================================================================================
#ifndef _PARTICLE3D_H_			//このマクロ定義がされていなかったら
#define _PARTICLE3D_H_			//2重インクルード防止のマクロを定義

#include "main.h"
#include "effect3D.h"

//*****************************
//マクロ定義
//*****************************
#define MAX_PARTICLE			(100)			//エフェクトの最大数

//エフェクトクラス
class CParticle3D : public CEffect3D
{
public:
	//種類
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_EXPLOSION,
		TYPE_MAX
	} TYPE;

public:

	CParticle3D();
	~CParticle3D();

	static CParticle3D *Create(D3DXVECTOR3 pos, TYPE type);
	void Uninit(void);

	void Set(D3DXVECTOR3 pos, TYPE type);

private:
	
};

#endif