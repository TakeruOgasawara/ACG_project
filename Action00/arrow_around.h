//===============================================================================
//
// [arrow_around.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _ARROW_AROUND_H_			//���̃}�N����`������Ă��Ȃ�������
#define _ARROW_AROUND_H_			//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "billboard.h"

//����̖�N���X
class CArrowAround : public CBillboard
{
public:
	CArrowAround();			//�R���X�g���N�^
	~CArrowAround();		//�f�X�g���N�^

	//��������
	static CArrowAround *Create(void);

	//���C���̊֐�
	HRESULT Init(void);
	void Uninit(void);
	void Upadate(void);
	void Draw(void);

	//���̑�

private:
};

#endif
