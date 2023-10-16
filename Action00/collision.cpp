//======================================================================================
//
// 当たり判定の処理[Enemy.cpp]
// Author;小笠原　彪
//
//======================================================================================
#include "collision.h"
#include "objectX.h"

const float LIMIT_POS_X = 700.0f;
const float  LIMIT_POS_Z = 700.0f;

//========================================================================
// 円の当たり判定 x軸 z軸 (同類との当たり)
//========================================================================
bool CollisionCircleXZAllies(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2, int MaxCnt)
{
	float fLength;				//半径の計算結果の保存用
	bool bUse = false;			//falseに初期化(判定用)

	//同類との対角線の長さを算出する
	for (int nCnt = 0; nCnt < MaxCnt; nCnt++, pPos2++)
	{//poa1のカウントを進める
		fLength = sqrtf((pPos1->x - pPos2->x) * (pPos1->x - pPos2->x) +
						(pPos1->z - pPos2->z) * (pPos1->z - pPos2->z));
	}

	if (fLength <= (fLength1 / 2) + (fLength1 / 2))
	{
		bUse = true;			//使用する
	}

	return bUse;
}

//========================================================================
// 大人の壁処理 : CollisionAdultWall(判定するオブジェクト(位置)、判定するオブジェクトの幅)
//========================================================================
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth)
{
	bool bAdultWall = false;

	if (pPos->x <= -LIMIT_POS_X + fWidth)
	{
		pPos->x = -LIMIT_POS_X + fWidth;
		bAdultWall = true;
	}
	if (pPos->x >= LIMIT_POS_X - fWidth)
	{
		pPos->x = LIMIT_POS_X - fWidth;
		bAdultWall = true;
	}
	if (pPos->z <= -LIMIT_POS_Z + fWidth)
	{
		pPos->z = -LIMIT_POS_Z + fWidth;
		bAdultWall = true;
	}
	if (pPos->z >= LIMIT_POS_Z - fWidth)
	{
		pPos->z = LIMIT_POS_Z - fWidth;
		bAdultWall = true;
	}

	return bAdultWall;
}

//========================================================================
// 大人の壁処理 : CollisionAdultWall(判定するオブジェクト(位置)、判定するオブジェクトの幅、大人の壁x、大人の壁z)
//========================================================================
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth, float fLimitWallx, float fLimitWallz)
{
	bool bAdultWall = false;

	if (pPos->x <= -fLimitWallx + fWidth)
	{
		pPos->x = -fLimitWallx + fWidth;
		bAdultWall = true;
	}
	if (pPos->x >= fLimitWallx - fWidth)
	{
		pPos->x = fLimitWallx - fWidth;
		bAdultWall = true;
	}
	if (pPos->z <= -fLimitWallz + fWidth)
	{
		pPos->z = -fLimitWallz + fWidth;
		bAdultWall = true;
	}
	if (pPos->z >= fLimitWallz - fWidth)
	{
		pPos->z = fLimitWallz - fWidth;
		bAdultWall = true;
	}

	return bAdultWall;
}

//========================================================================
// 外積の当たり判定
//========================================================================
bool CollisionCross(void)
{
	//D3DXVec3Cross();

	return false;
}

//========================================================================
// 内積の当たり判定
//========================================================================
bool ollisionInner(void)
{
	return false;
}

//===========================================================================================
// 当たり判定 : CollisionObjectX(位置、過去位置、移動量、大きさ)
//===========================================================================================
bool CollisionObjectX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float size)
{
	bool bUse = false;

	//オブジェクトとの当たり判定
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			if (pObject->GetType() != pObject->TYPE_OBJECTX)
			{
				continue;
			}

			CObjectX *pObjectX = pObject->GetObjectX();

			if (pObjectX == nullptr)
			{
				continue;
			}

			D3DXVECTOR3 pos = pObjectX->GetPosition();
			D3DXVECTOR3 vtxMax = pObjectX->GetVtxMax();
			D3DXVECTOR3 vtxMin = pObjectX->GetVtxMin();

			if (pPos->y + size > pos.y + vtxMin.y &&
				pPos->y + size < pos.y + vtxMax.y)
			{//オブジェクトの幅(y)に入った場合
				if (pPos->x + size > pos.x + vtxMin.x &&
					pPos->x - size < pos.x + vtxMax.x)
				{//左右の当たり幅の指定
					if (pPosOld->z + size <= pos.z + vtxMin.z &&
						pPos->z + size >= pos.z + vtxMin.z)
					{//前の当たり判定
						pPos->z = pos.z + vtxMin.z - size;
						pMove->z = 0.0f;			//移動量を0へ
						bUse = true;
					}
					if (pPosOld->z - size >= pos.z + vtxMax.z &&
						pPos->z - size <= pos.z + vtxMax.z)
					{//後の当たり判定
						pPos->z = pos.z + vtxMax.z + size;
						pMove->z = 0.0f;			//移動量を0へ
						bUse = true;
					}
				}
				if (pPos->z + size > pos.z + vtxMin.z &&
					pPos->z - size < pos.z + vtxMax.z)
				{//オブジェクトの幅(z)に入った場合
					if (pPosOld->x + size <= pos.x + vtxMin.x &&
						pPos->x + size >= pos.x + vtxMin.x)
					{//左の当たり判定
						pPos->x = pos.x + vtxMin.x - size;
						pMove->x = 0.0f;			//移動量を0へ
						bUse = true;
					}
					if (pPosOld->x - size >= pos.x + vtxMax.x &&
						pPos->x - size <= pos.x + vtxMax.x)
					{//右の当たり判定
						pPos->x = pos.x + vtxMax.x + size;
						pMove->x = 0.0f;			//移動量を0へ
						bUse = true;
					}
				}
			}

			//yの当たり判定
			if (pPos->z + size > pos.z + vtxMin.z &&
				pPos->z - size < pos.z + vtxMax.z &&
				pPos->x + size > pos.x + vtxMin.x &&
				pPos->x - size < pos.x + vtxMax.x)
			{//ブロックの範囲ないの場合
				if (pPosOld->y + size <= pos.y + vtxMin.y &&
					pPos->y + size >= pos.y + vtxMin.y)
				{//上の当たり判定
					pPos->y = pos.y + vtxMin.y - size;
					pMove->y = 0.0f;			//移動量を0へ
					bUse = true;
				}
				if (pPosOld->y - size >= pos.y + vtxMax.y &&
					pPos->y - size <= pos.y + vtxMax.y)
				{//下の当たり判定
					pPos->y = pos.y + vtxMax.y + size;
					pMove->y = 0.0f;			//移動量を0へ
					bUse = true;
				}
			}
		}
	}

	return bUse;
}