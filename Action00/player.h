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
class CObject2D;

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
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer *Create(D3DXVECTOR3 pos);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定用
	void SetState(STATE state) { m_state = state; }
	void SetMovement(D3DXVECTOR3 move) { m_move = move; }
	void SetMoveX(float x) { m_move.x = x; }
	void SetMoveY(float y) { m_move.y = y; }
	void SetMoveZ(float z) { m_move.z = z; }
	void SetFirstJamp(bool bJamp) { m_bNormalJump = bJamp; }
	void SetSecondJamp(bool bJamp) { m_bSecondJump = bJamp; }

	//取得用
	D3DXVECTOR3 GetPosisionOld(void) { return m_posOld; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetScreenPosition(void);	//スクリーン上の位置
	STATE GetState(void) { return m_state; }
	bool GetFirstJamp(void) { return m_bNormalJump; }
	bool GetSecondJamp(void) { return m_bSecondJump; }

	//その他
	void Hit(int nDamage);	//ダメージ

private:
	//関数
	void InputMove(void);	//行動入力
	void NormalJump(void);	//ジャンプ
	void SecondJump(void);	//ジャンプ
	void Arrow(D3DXVECTOR3 pos);	//矢印

	bool CollisionBreakBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float size);
	bool CollisionDamageBlock(D3DXVECTOR3 pos, float size);
	bool CollisionNextStep(D3DXVECTOR3 pos, float size);
	bool CollisionTrapScissors(D3DXVECTOR3 pos, float size);

	//変数
	D3DXVECTOR3 m_posOld;	//過去位置
	D3DXVECTOR3 m_move;	//移動量
	int m_nLife;
	int m_nNormalJumpCount;
	int m_nSecondJumpCount;
	bool m_bNormalJump;	//一回目のジャンプをしたか
	bool m_bSecondJump;	//二回目のジャンプをしたか

	STATE m_state;	//状態

	//他プロジェクトから
	CCollision *m_pCollision;	//当たり判定
	CCamera *m_pCamera;	//カメラ
	CArrowAround *m_pArrowAround;	//矢印
	CObject2D* m_pObject2D;	//2Dポリゴン
};

#endif