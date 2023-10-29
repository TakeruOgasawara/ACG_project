//===============================================================================
//
// �X�e�[�W���[stage.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _STAGE0_H_	//���̃}�N����`������Ă��Ȃ�������
#define _STAGE0_H_	//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "manager.h"

//�O���錾
class CPlayer;
class CCamera;
class CNextStep;
class CLockDoor;

class CEdit;
class CEditor;

//�^�C�g���N���X
class CStage0
{
public:
	//�G���A�񋓌^
	enum EArea
	{
		AREA_0 = 0,
		AREA_1,
		AREA_2,
		AREA_MAX
	};

public:
	CStage0();
	~CStage0();

	static CStage0* Create(void);
	//static CStage0* GetInstance(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	EArea GetArea(void) { return m_area; }
	bool GetAreaEnd(void) { return m_bAreaEnd; }

private:
	void Area0(void);
	void Area1(void);
	void Area2(void);

private:	//�����o�ϐ�
	static CStage0* m_pStage0;
	D3DXVECTOR3 m_Savepos;
	EArea m_area;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CEdit* m_pEdit;
	CNextStep* m_pNextStep;

	bool m_bNext;	//���֐i�ނ�
	bool m_bLoad;	//�����ǂݍ��݃t���O
	bool m_bAreaEnd;
};

#endif