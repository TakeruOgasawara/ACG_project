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

//=============================================
// �v���g�^�C�v�錾
//=============================================
//�ėp�I�Ɏg����֐�
bool CollisionCircleXZAllies(D3DXVECTOR3 *pPos1, D3DXVECTOR3 *pPos2, float fLength1, float fLength2, int MaxCnt);	//X,Z��������~�̔���
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth);	//��l�̕ǂ̔���
bool CollisionAdultWall(D3DXVECTOR3 *pPos, float fWidth, float fLimitWallx, float fLimitWallz);	//��l�̕ǂ̔���
bool CollisionCross(void);	//�O�ς̓����蔻��(�ł��ĂȂ�)
//bool CollisionInner(void);	//���ς̓����蔻��(�ł��ĂȂ�)

//�������肽�����ꂼ��̊֐�
bool CollisionObjectX(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float size);	//�I�u�W�F�N�gX�Ƃ̔���
bool CollisionObjectX1(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, bool bJunp, float size);	//�I�u�W�F�N�gX�Ƃ̔���

bool CollisionObjectXType(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, bool bJunp, float size, CObject::TYPE type);


#endif
