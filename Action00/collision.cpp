//======================================================================================
//
// �����蔻��̏���[Enemy.cpp]
// Author;���}���@�V
//
//======================================================================================
#include "collision.h"
#include "objectX.h"

const float LIMIT_POS_X = 700.0f;
const float  LIMIT_POS_Z = 700.0f;

//========================================================================
// �~�̓����蔻�� x�� z�� (���ނƂ̓�����)
//========================================================================
bool CollisionCircleXZAllies(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2, int MaxCnt)
{
	float fLength;				//���a�̌v�Z���ʂ̕ۑ��p
	bool bUse = false;			//false�ɏ�����(����p)

	//���ނƂ̑Ίp���̒������Z�o����
	for (int nCnt = 0; nCnt < MaxCnt; nCnt++, pPos2++)
	{//poa1�̃J�E���g��i�߂�
		fLength = sqrtf((pPos1->x - pPos2->x) * (pPos1->x - pPos2->x) +
						(pPos1->z - pPos2->z) * (pPos1->z - pPos2->z));
	}

	if (fLength <= (fLength1 / 2) + (fLength1 / 2))
	{
		bUse = true;			//�g�p����
	}

	return bUse;
}

//========================================================================
// ��l�̕Ǐ��� : CollisionAdultWall(���肷��I�u�W�F�N�g(�ʒu)�A���肷��I�u�W�F�N�g�̕�)
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
// ��l�̕Ǐ��� : CollisionAdultWall(���肷��I�u�W�F�N�g(�ʒu)�A���肷��I�u�W�F�N�g�̕��A��l�̕�x�A��l�̕�z)
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
// �O�ς̓����蔻��
//========================================================================
bool CollisionCross(void)
{
	//D3DXVec3Cross();

	return false;
}

//========================================================================
// ���ς̓����蔻��
//========================================================================
bool ollisionInner(void)
{
	return false;
}

//===========================================================================================
// �����蔻�� : CollisionObjectX(�ʒu�A�ߋ��ʒu�A�ړ��ʁA�傫��)
//===========================================================================================
bool CollisionObjectX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float size)
{
	bool bUse = false;

	//�I�u�W�F�N�g�Ƃ̓����蔻��
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
			{//�I�u�W�F�N�g�̕�(y)�ɓ������ꍇ
				if (pPos->x + size > pos.x + vtxMin.x &&
					pPos->x - size < pos.x + vtxMax.x)
				{//���E�̓����蕝�̎w��
					if (pPosOld->z + size <= pos.z + vtxMin.z &&
						pPos->z + size >= pos.z + vtxMin.z)
					{//�O�̓����蔻��
						pPos->z = pos.z + vtxMin.z - size;
						pMove->z = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
					if (pPosOld->z - size >= pos.z + vtxMax.z &&
						pPos->z - size <= pos.z + vtxMax.z)
					{//��̓����蔻��
						pPos->z = pos.z + vtxMax.z + size;
						pMove->z = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
				}
				if (pPos->z + size > pos.z + vtxMin.z &&
					pPos->z - size < pos.z + vtxMax.z)
				{//�I�u�W�F�N�g�̕�(z)�ɓ������ꍇ
					if (pPosOld->x + size <= pos.x + vtxMin.x &&
						pPos->x + size >= pos.x + vtxMin.x)
					{//���̓����蔻��
						pPos->x = pos.x + vtxMin.x - size;
						pMove->x = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
					if (pPosOld->x - size >= pos.x + vtxMax.x &&
						pPos->x - size <= pos.x + vtxMax.x)
					{//�E�̓����蔻��
						pPos->x = pos.x + vtxMax.x + size;
						pMove->x = 0.0f;			//�ړ��ʂ�0��
						bUse = true;
					}
				}
			}

			//y�̓����蔻��
			if (pPos->z + size > pos.z + vtxMin.z &&
				pPos->z - size < pos.z + vtxMax.z &&
				pPos->x + size > pos.x + vtxMin.x &&
				pPos->x - size < pos.x + vtxMax.x)
			{//�u���b�N�͈̔͂Ȃ��̏ꍇ
				if (pPosOld->y + size <= pos.y + vtxMin.y &&
					pPos->y + size >= pos.y + vtxMin.y)
				{//��̓����蔻��
					pPos->y = pos.y + vtxMin.y - size;
					pMove->y = 0.0f;			//�ړ��ʂ�0��
					bUse = true;
				}
				if (pPosOld->y - size >= pos.y + vtxMax.y &&
					pPos->y - size <= pos.y + vtxMax.y)
				{//���̓����蔻��
					pPos->y = pos.y + vtxMax.y + size;
					pMove->y = 0.0f;			//�ړ��ʂ�0��
					bUse = true;
				}
			}
		}
	}

	return bUse;
}