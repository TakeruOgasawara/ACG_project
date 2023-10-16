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


//プロトタイプ宣言
bool CollisionCircleXZAllies(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2, int MaxCnt);
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth);
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth, float fLimitWallx, float fLimitWallz);
bool CollisionCross(void);
bool CollisionInner(void);
bool CollisionObjectX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float size);

#endif
