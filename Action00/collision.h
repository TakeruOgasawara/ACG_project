//======================================================================================
//
// 当たり判定処理[collision.h]
// Author;小笠原　彪
//
//======================================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"
#include "object.h"

//=============================================
// プロトタイプ宣言
//=============================================
//汎用的に使える関数
bool CollisionCircleXZAllies(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2, int MaxCnt);	//X,Zを取った円の判定
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth);	//大人の壁の判定
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth, float fLimitWallx, float fLimitWallz);	//大人の壁の判定
bool CollisionCross(void);	//外積の当たり判定(できてない)
//bool CollisionInner(void);	//内積の当たり判定(できてない)

//判定を取りたいそれぞれの関数
bool CollisionObjectX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float size);	//オブジェクトXとの判定
bool CollisionObjectX1(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, bool bJunp, float size);	//オブジェクトXとの判定

bool CollisionObjectXType(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, bool bJunp, float size, CObject::TYPE type);


#endif
