//===============================================================================
//
// [billboard.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _BILLBOARD_H_				//���̃}�N����`������Ă��Ȃ�������
#define _BILLBOARD_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "object.h"

//�r���{�[�h�N���X
class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = 3);			//�R���X�g���N�^
	~CBillboard();			//�f�X�g���N�^

	static CBillboard *Create(void);
	static CBillboard *Create(D3DXVECTOR3 pos);
	static CBillboard *Create(D3DXVECTOR3 pos, const char *pTexName);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�p
	void SetverTex(void);	//���_�ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }	//�����ݒ�
	void SetSize(D3DXVECTOR2 size) { m_size = size; }
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetLighting(bool bUse) { m_bUseLighting = bUse; }
	void SetRadius(D3DXVECTOR2 radius);

	//�擾�p
	D3DXVECTOR3 GetPosition(void) { return m_pos; }	//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	//�����擾
	D3DXVECTOR2 GetSize(void) { return m_size; }	//�傫���擾
	D3DXCOLOR GetColor(void) { return m_col; }	//�F�擾

	//�e�N�X�`�����蓖��
	void BindTexture(int nIdx);
	void BindTexture(const char *texName);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̒��_���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@�ւ̒��_���
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_move;			//�ړ�
	D3DXCOLOR m_col;			//�F
	D3DXVECTOR2 m_size;

	bool m_bUseLighting;				//�g���Ă��邩
	int m_nTextureIdx;			//�e�N�X�`���ԍ�

	struct Size
	{
		float fLength;
		float fangle;
	};
	//Size m_size;
};
#endif