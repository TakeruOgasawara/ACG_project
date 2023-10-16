//======================================================================================
//
// �����蔻�菈��[collision.h]
// Author;���}���@�V
//
//======================================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"
#include "object.h"


//�v���g�^�C�v�錾
bool CollisionCircleXZAllies(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2, int MaxCnt);
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth);
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth, float fLimitWallx, float fLimitWallz);
bool CollisionCross(void);
bool CollisionInner(void);
bool CollisionObjectX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float size);

#endif
