//===============================================================================
//
// [object2D.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _OBJECT2D_H_				//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT2D_H_				//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "object.h"

class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 3);			//�R���X�g���N�^
	~CObject2D();			//�f�X�g���N�^

	static CObject2D *Create(void);
	static CObject2D *Create(D3DXVECTOR3 pos);
	static CObject2D *Create(const int nPriority = 3);
	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CObject2D *Create(D3DXVECTOR3 pos, const char *FileName);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//�ݒ�p
	void SetVertex(void);
	void SetVertex(D3DXVECTOR2 size);
	void SetVertex(float fWidth, float fHeight, float fSpeedx, float fSpeedy);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetColor(D3DXCOLOR col);
	void SetTexture(D3DXVECTOR2 tex);
	void SetSizeCenter(float fWidth, float fHeight);
	void SetSize_lefteEnd(float fWidth, float fHeight);
	void SetSizeLength(float fWidth, float fHeight);

	//�擾�p
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetRotation(void);
	D3DXCOLOR GetColor(void);
	D3DXVECTOR2 GetSize(void);
	float GetAngle(void);
	float GetLength(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);
	int GetNumObj3D(void) { return m_nNumObj2D; };

	//�e�N�X�`�����蓖��
	void BindTexture(int nIdx);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̒��_���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@�ւ̒��_���
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXCOLOR m_col;			//�F
	float m_fWidth;				//��
	float m_fHeight;			//�c
	float m_fLength;			//����
	float m_fAngle;				//�p�x
	static int m_nNumObj2D;
	int m_nTextureIdx;
};

#endif