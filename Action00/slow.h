//==========================================================
//
// �X���[�̏����Ǘ� [slow.h]
// Author : Takeru Ogasawara
//
//==========================================================
#ifndef _SLOW_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SLOW_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

// �X���[�N���X
class CSlow
{
public:

	CSlow();	// �R���X�g���N�^
	~CSlow();	// �f�X�g���N�^

	// �����o�֐�
	void Init(void);
	void Uninit(void);
	void Update(void);
	float Get(void);
	void SetSlow(bool bUse);

private:
	float m_fValue;
	bool m_bUse;
};

#endif