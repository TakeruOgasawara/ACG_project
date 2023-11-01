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
class CTime;

class CStageManager;
class CPlayer;

//�^�C�g���N���X
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static void SetPlayerNULL(void) { m_pPlayer = nullptr; }
	CPause* GetPause(void) { return m_pPause; }
	CXfile* GetXfile(void) { return m_pXfile; }
	static CTime* GetTime(void) { return m_pTime; }

private:
	CUI_Manager* m_pUIManager;
	CPause* m_pPause;
	CXfile* m_pXfile;
	CSound* m_pSound;
	static CPlayer* m_pPlayer;
	CStageManager* m_pStageManager;
	static CTime* m_pTime;

	bool m_bEdit;
};

#endif