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
class CPlayer3D;
class CMap;
class CUI_Manager;
class CPause;
class CSound;
class CEdit;

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

	static CPlayer3D *GetPlayer3D(void) { return m_pPlayer3D; }
	static CPause *GetPause(void) { return m_pPause; }

private:
	void Edit(void);

	static CPlayer3D *m_pPlayer3D;
	static CMap *m_pMap;
	static CUI_Manager *m_pUIManager;
	static CPause *m_pPause;
	static CEdit *m_pEdit;
	CSound *m_pSound;
};

#endif