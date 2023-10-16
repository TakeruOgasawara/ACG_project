//===============================================================================
//
// �X�e�[�W���[stage.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _STAGE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _STAGE_H_				//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "manager.h"

//�O���錾
class CObject2D;

//�^�C�g���N���X
class CStage : public CScene
{
private:
	//�X�e�[�W�񋓌^
	enum STAGE
	{
		STAGE_0 = 0,
		STAGE_1,
		STAGE_2,
		STAGE_3,
		STAGE_4,
		STAGE_5,
		STAGE_MAX
	};

	//�G���A�񋓌^
	enum AREA
	{
		AREA_0 = 0,
		AREA_1,
		AREA_2,
		AREA_MAX
	};

	struct SData
	{
		STAGE stage;
		AREA area;
	};

public:
	CStage();
	~CStage();

	static CStage* Create(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static HRESULT Load(void);

private:
	SData m_data;
};

#endif