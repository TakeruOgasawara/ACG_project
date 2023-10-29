//===============================================================================
//
// [score.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _SCORE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _SCORE_H_				//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "number.h"

//�}�N����`
#define MAX_NUMSCORE			(8)

//�i���o�[�N���X
class CScore
{
public:
	CScore();
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void SetScore(void);
	void AddScore(int nValue);

private:
	static CNumber *m_apNumber[MAX_NUMSCORE];
	static D3DXVECTOR3 m_pos;
	static int m_nScore;
};

#endif