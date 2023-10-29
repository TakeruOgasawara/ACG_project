//======================================================================================
//
// �����L���O�̏���[ranking.h]
// Author : Takeru Ogasawara
//
//======================================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//�O���錾
class CTime;

class CRanking
{
private:
	static const int MAX_RANKING = 5;

public:
	enum RANK
	{
		RANK_NONE = 0,
		RANK_IN,
		RANK_OUT,
		RANK_MAX
	};

public:
	CRanking();
	~CRanking();

	//�v���g�^�C�v�錾
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Save(int* pTime);
	void Load(int* pTime);
	void Sort(int* pTime);

	static CTime* m_apTime[MAX_RANKING];
};

#endif