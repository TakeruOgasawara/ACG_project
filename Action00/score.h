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

//�X�R�A�N���X
class CScore
{
public:
	static const int MAX_SCORE = 5;

public:
	CScore();
	~CScore();
	static CScore *Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void AddScore(int nValue);

private:
	void SetScore(void);

	CNumber *m_apNumber[MAX_SCORE];
	D3DXVECTOR3 m_pos;
	int m_nScore;
};

#endif