//===============================================================================
//
// �^�C�g�����[title.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TITLE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_				//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"
#include "manager.h"

//�O���錾
class CObject2D;

//�^�C�g���N���X
class CTitle : public CScene
{
private:	//�\���́E�񋓌^�p

	enum MENU
	{
		MENU_START = 0,
		MENU_END,
		MENU_MAX
	};

	struct SObject2D
	{
		CObject2D* pMenu2D;
		D3DXCOLOR col;
	};

public:
	CTitle();
	~CTitle();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw(); 

private:
	void SelectMenu(void);

	int m_nTextureIdx;
	CObject2D* pName2D;
	SObject2D m_apMenu[MENU_MAX];
	MENU m_menu;
	int m_nSelect;
};

#endif