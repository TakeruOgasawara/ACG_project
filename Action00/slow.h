//==========================================================
//
// スローの処理管理 [slow.h]
// Author : Takeru Ogasawara
//
//==========================================================
#ifndef _SLOW_H_		// このマクロが定義されていない場合
#define _SLOW_H_		// 二重インクルード防止用マクロを定義

// スロークラス
class CSlow
{
public:

	CSlow();	// コンストラクタ
	~CSlow();	// デストラクタ

	// メンバ関数
	void Init(void);
	void Uninit(void);
	void Update(void);
	float Get(void);
	void SetSlow(bool bUse);

private:
	float m_fValue;
	bool m_bUse;
};

#endif