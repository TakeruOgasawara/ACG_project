//===============================================================================
//
// �X�e�[�W���[stage.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _STAGE_MANAGER_H_	//���̃}�N����`������Ă��Ȃ�������
#define _STAGE_MANAGER_H_	//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "manager.h"

//�O���錾
class CStage0;

//�^�C�g���N���X
class CStageManager
{
private:
	//�X�e�[�W�񋓌^
	enum ESTAGE
	{
		STAGE_0 = 0,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		STAGE_5,
		STAGE_MAX
	};

	enum ESTATE
	{
		STATE_START = 0,
		STATE_END,
		STATE_MAX
	};

public:
	CStageManager();
	~CStageManager();

	//static CStageManager* GetInstance(void);
	static CStageManager* Create(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

private:	//�����o�ϐ�
	static CStageManager* m_pStageManager;

	ESTAGE m_stage;
	ESTATE m_state;
	CStage0* m_pStage0;

	int nProgress;	//�i�s�x
	bool m_bEnd;
};

#endif