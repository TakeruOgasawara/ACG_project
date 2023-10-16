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

class CCollision
{
private:


	const float SIZE = 5.0f;

public:
	CCollision();
	~CCollision();

	static CCollision *Create(void);

	//�v���g�^�C�v�錾
	bool ClsCircleXZAllies(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2, int MaxCnt);
	bool ClsAdultWall(D3DXVECTOR3 *pPos, float fWidth);
	bool ClsAdultWall(D3DXVECTOR3 *pPos, float fWidth, float fLimitWallx, float fLimitWallz);
	bool ClsCross(void);
	bool ClsInner(void);

	bool CollisionObjectX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float size);
private:
};

#endif
