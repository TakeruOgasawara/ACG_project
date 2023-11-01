//===========================================================================================
//
// [particle3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "particle3D.h"
#include "effect3D.h"

//===========================================================================================
// コンストラクタ
//===========================================================================================
CParticle3D::CParticle3D()
{

}

//===========================================================================================
// デストラクタ
//===========================================================================================
CParticle3D::~CParticle3D()
{

}

//===========================================================================================
// 生成
//===========================================================================================
CParticle3D *CParticle3D::Create(D3DXVECTOR3 pos, TYPE type)
{
	CParticle3D *pParticle = nullptr;

	if (pParticle == nullptr)
	{
		pParticle = new CParticle3D;

		if (pParticle != nullptr)
		{
			pParticle->Set(pos, type);

			return pParticle;
		}
		else
		{
			return nullptr;
		}
	}

	return pParticle;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CParticle3D::Uninit(void)
{
	Release();
}

//===========================================================================================
// タイプ
//===========================================================================================
void CParticle3D::Set(D3DXVECTOR3 pos, TYPE type)
{
	//変数宣言
	float fRot;
	float fMove;
	float fRadius;
	int nLife;
	D3DXVECTOR3 move;
	D3DXCOLOR col;

	switch (type)
	{
	case TYPE_EXPLOSION:
		for (int nCnt = 0; nCnt < 100; nCnt++)
		{
			//x
			fRot = (float)(rand() % 629 - 314) / 100.0f;			//角度の設定
			fMove = (float)(rand() % 60) / 10;			//移動量の設定
			move.x = sinf(fRot) * fMove;			//移動量の設定

			//y
			fRot = (float)(rand() % 629 - 314) / 100.0f;			//角度の設定
			fMove = (float)(rand() % 45) / 10;			//移動量の設定
			move.y = cosf(fRot) * fMove;			//移動量の設定

			//z
			fRot = (float)(rand() % 629 - 314) / 100.0f;			//角度の設定
			fMove = (float)(rand() % 45) / 10;			//移動量の設定
			move.z = cosf(fRot) * fMove;			//移動量の設定

			//色の設定
			col = D3DXCOLOR(0.3f, 0.6f, 0.4f, 1.0f);

			//半径の設定
			fRadius = 10.0f;

			//体力の設定
			nLife = 100;

			//エフェクト設定
			CEffect3D::Create(pos, move, col, fRadius, nLife);
		}

		break;
	}
}
