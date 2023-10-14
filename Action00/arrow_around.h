//===============================================================================
//
// [arrow_around.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _ARROW_AROUND_H_			//このマクロ定義がされていなかったら
#define _ARROW_AROUND_H_			//2重インクルード防止のマクロを定義

#include "main.h"
#include "billboard.h"

//周りの矢クラス
class CArrowAround : public CBillboard
{
public:
	CArrowAround();			//コンストラクタ
	~CArrowAround();		//デストラクタ

	//生成処理
	static CArrowAround *Create(void);

	//メインの関数
	HRESULT Init(void);
	void Uninit(void);
	void Upadate(void);
	void Draw(void);

	//その他

private:
};

#endif
