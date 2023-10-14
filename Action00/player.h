//===============================================================================
//
// [player3D.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _PLAYER_H_				//このマクロ定義がされていなかったら
#define _PLAYER_H_				//2重インクルード防止のマクロを定義

#include "main.h"
#include "billboard.h"

//前方宣言
class CCollision;
class CCamera;
class CArrowAround;

//プレイヤークラス
class CPlayer : public CBillboard
{
public:
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_RUN,
		STATE_DEATH,
		STATE_RETRY,
		STATE_MAX
	};

public:
	CPlayer(int nPriority = 1);
	~CPlayer();

	static CPlayer *Create(D3DXVECTOR3 pos);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//static bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pVtxMax, D3DXVECTOR3 *pVtxMin);

	//設定用
	void SetState(STATE state) { m_state = state; }

	//取得用
	D3DXVECTOR3 GetMove(void) { return m_move; }
	STATE GetState(void) { return m_state; }

private:
	//関数
	void InputMove(void);		//行動入力
	void Jump(void);			//ジャンプをまとめた
	void CameraRelationship(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//カメラ関係
	void Arrow(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetScreenPosition(void);

	//変数
	D3DXVECTOR3 m_move;			//移動量
	bool m_bFirstJump;			//一回目のジャンプをしたか
	bool m_bSecondJump;			//二回目のジャンプをしたか
	STATE m_state;				//状態

	//他プロジェクトから
	CCollision *m_pCollision;	//当たり判定
	CCamera *m_pCamera;			//カメラ
	CArrowAround *m_pArrowAround;
};

#endif