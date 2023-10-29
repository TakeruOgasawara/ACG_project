//===============================================================================
//
// [scene.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _SCENE_H_				//このマクロ定義がされていなかったら
#define _SCENE_H_				//2重インクルード防止のマクロを定義

#include "main.h"

//シーンクラス(画面遷移)
class CScene
{
public:
	
	enum MODE	//シーン種類
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
