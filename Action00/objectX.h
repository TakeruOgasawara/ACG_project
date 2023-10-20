//===============================================================================
//
// [objectX.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _OBJECTX_H_				//���̃}�N����`������Ă��Ȃ�������
#define _OBJECTX_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "object.h"

//�O���錾
class CXfile;

class CObjectX : public CObject
{
private:
	const float SIZE = 20.0f;

public:
	CObjectX(int nPriority = 0);			//�R���X�g���N�^
	~CObjectX();			//�f�X�g���N�^

	//����
	static CObjectX *Create(void);
	static CObjectX *Create(const char *c_pFileName, D3DXVECTOR3 pos);

	HRESULT Init(void);
	HRESULT Init(const char *c_pFileName, D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 pVtxMax, D3DXVECTOR3 pVtxMin);

	//�ݒ�p
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetModelIdx(int nIdx) { m_nModelIdx = nIdx; }

	//�擾�p
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }
	CObjectX *GetObjectX(void) { return this; }
	int GetModelIndx(void) { return m_nModelIdx; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//�o�b�t�@�ւ̒��_���
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;					//�g�p����Ă��郂�f����
	LPD3DXBUFFER m_pBuffMat;			//���_�J���[���
	DWORD m_dwNumMat;					//�J���[�̐�
	D3DXVECTOR3 m_vtxMin, m_vtxMax;		//�I�u�W�F�N�g�̍ő�l�E�ŏ��l
	int m_nTextureIdx;			//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	int m_nModelIdx;			//���f���ԍ�
};

#endif