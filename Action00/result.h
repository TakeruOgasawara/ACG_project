//===============================================================================
//
// ���U���g���[result.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _RESULT_H_				//���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "manager.h"

//�O���錾
class CObject2D;
class CScore;
class CTime;

//�^�C�g���N���X
class CResult : public CScene
{
private:

	enum EUI	//UI�̎��
	{
		YOUR_NAME = 0,
		RANK_FONT,
		RANK,
		TIME,
		UI_MAX
	};

public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Save(int* pTime);
	void Load(int* pTime);
	void Sort(int* pTime);
	void RankingIn(int* pTime, int nResult);
	int m_nRank;

	int m_nTextureIdx;	//�e�N�X�`���ւ̒��_���
	int m_nResultCnt;
	CObject2D* m_pBg2D;
	CObject2D* m_pUi2D[UI_MAX];
	CTime* m_pScore;
	CTime* m_pRanking[5];
};

#endif