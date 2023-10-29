//===============================================================================
//
// [scene.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _SCENE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _SCENE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//�V�[���N���X(��ʑJ��)
class CScene
{
public:
	
	enum MODE	//�V�[�����
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_RANKING,
		MODE_MAX
	} ;

public:
	CScene();
	~CScene();

	static CScene* Create(MODE mode);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetMode(MODE mode) { m_mode = mode; }
	MODE GetMode(void) { return m_mode; }

private:
	MODE m_mode;
};

#endif
