//===============================================================================
//
// �Q�[�����[game.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _GAME_H_				//���̃}�N����`������Ă��Ȃ�������
#define _GAME_H_				//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "manager.h"

//�O���錾
class CUI_Manager;
class CPause;
class CSound;
class CEdit;
class CXfile;

class CStage;

//�^�C�g���N���X
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	static CGame* GetInstance(void);
	static void Release(void);

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	CPause* GetPause(void) { return m_pPause; }
	CXfile* GetXfile(void) { return m_pXfile; }

private:
	void Edit(void);

	static CGame* m_pGame;

	CUI_Manager* m_pUIManager;
	CPause* m_pPause;
	CXfile* m_pXfile;
	CSound* m_pSound;

	CStage* m_pStage;

	bool m_bEdit;
};

#endif