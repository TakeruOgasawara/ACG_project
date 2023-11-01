//===========================================================================================
//
// [player3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "arrow_around.h"
#include "object2D.h"
#include "objectX.h"

#include "break_block.h"
#include "damage_block .h"
#include "object_next_step.h"
#include "trap_scissors.h"

#include "sound.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "collision.h"
#include "fade_death.h"

//マクロ定義
#define SIZE			(D3DXVECTOR2(5.0f, 10.0f))

#define MOVE			(2.5f)			//移動量
#define ATT				(0.3f)			//減衰
#define GRAVITY			(1.0f)			//重力
#define LIFE			(1)				//体力
#define JUMPEND			(10)


//矢印の位置
#define ARROW_POS		(70.0f)

//ジャンプ
#define FILSTJUMP_POWER		(20.0f)			//ジャンプ力
#define SECONDJUMP_POWER	(15.0f)			//

//===========================================================================================
// コンストラクタ
//===========================================================================================
CPlayer::CPlayer(int nPriority)
{
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = STATE_NORMAL;
	m_nLife = 0;
	m_nNormalJumpCount = 0;
	m_nSecondJumpCount = 0;
	m_pCamera = nullptr;
	m_pCollision = nullptr;
	m_pArrowAround = nullptr;
	m_pObject2D = nullptr;
	m_bNormalJump = false;
	m_bSecondJump = false;
	m_bJumpFlag = false;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CPlayer::~CPlayer()
{

}

//===========================================================================================
// オブジェクト3Dの生成
//===========================================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			pPlayer->Init();

			pPlayer->SetPosition(pos);

			pPlayer->SetType(CObject::TYPE_PLAYER);

			return pPlayer;
		}
		else
		{
			return nullptr;
		}
	}

	return pPlayer;
}

//===========================================================================================
// オブジェクト3Dの生成
//===========================================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer;

		if (pPlayer != nullptr)
		{
			//初期化処理
			pPlayer->Init();

			//位置設定
			pPlayer->SetPosition(pos);

			//向き設定
			pPlayer->SetRotation(rot);

			pPlayer->SetType(CObject::TYPE_PLAYER);

			return pPlayer;
		}
		else
		{
			return nullptr;
		}
	}

	return pPlayer;
}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CPlayer::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	CObject::SetType(CObject::TYPE_PLAYER);

	m_nLife = LIFE;

	// ビルボード(プレイヤー本体
	CBillboard::Init();
 	SetSize(D3DXVECTOR2(SIZE.x, SIZE.y));
	BindTexture("data\\TEXTURE\\player.png");

	// 矢印
	// 二回目のジャンプ方向を決める矢印
	m_pArrowAround = CArrowAround::Create();	//生成
	m_pArrowAround->BindTexture("data\\TEXTURE\\game\\arrow1.png");
	m_pArrowAround->SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y + 50.0f, 0.0f));

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CPlayer::Uninit(void)
{
	if (m_pArrowAround != nullptr)
	{
		m_pArrowAround->Uninit();
		m_pArrowAround = nullptr;
	}

	CBillboard::Uninit();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotation();

	//過去位置の保存
	m_posOld = pos;

	if (m_state == STATE_DEATH)
	{//死亡状態の場合
		return;
	}

	if (m_bSecondJump == false)
	{
		//重力を加える
		m_move.y -= GRAVITY;

		//移動量を更新(減衰させる)
		m_move.x += (0.0f - m_move.x) * ATT;

		//操作
		InputMove();

		//ジャンプをまとめた関数
		NormalJump();
	}

	if (m_bSecondJump == true)
	{
		m_nSecondJumpCount++;

		if (m_nSecondJumpCount > JUMPEND)
		{
			m_bSecondJump = false;
			m_nSecondJumpCount = 0;
		}
	}

	//画面外に出た時の判定
	if (GetScreenPosition().y > SCREEN_HEIGHT)
	{
		Hit(10);
		return;
	}

	//if (GetScreenPosition().y < 0)
	//{
	//	m_move.y = 0.0f;
	//	pos.y = SIZE.y + 15.0f;
	//}

	//移動量の代入
	pos += m_move;

	//オブジェクトとの当たり判定関数
	if (CollisionObjectX1(&pos, &m_posOld, &m_move, m_bNormalJump, SIZE.y + 15.0f) == true)
	{
		m_bNormalJump = false;
		m_bSecondJump = false;
		m_bJumpFlag = false;
	}
	if (CollisionObjectX1(&pos, &m_posOld, &m_move, m_bSecondJump, SIZE.y + 15.0f) == true)
	{
		m_bNormalJump = false;
		m_bSecondJump = false;
		m_bJumpFlag = false;
	}	
	//崩れるブロックとの当たり判定
	if (CollisionBreakBlock(&pos, &m_posOld, &m_move, SIZE.y + 15.0f) == true)
	{
		m_bNormalJump = false;
		m_bSecondJump = false;
		m_bJumpFlag = false;
	}
	//ダメージブロックとの当たり判定
	if (CollisionDamageBlock(pos, SIZE.y + 15.0f) == true)
	{
		Hit(10);
		return;
	}
	//次との当たり判定
	if (CollisionNextStep(pos, SIZE.y + 15.0f) == true)
	{
		return;
	}

	//矢印
	Arrow(pos);

	//位置の設定
	SetPosition(pos);

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("\n\n【プレイヤー情報】");
	CManager::GetInstance()->GetDebugProc()->Print("\n位置： x:%f y:%f z:%f", pos.x, pos.y, pos.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n向き： x:%f y:%f z:%f", rot.x, rot.y, rot.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n移動量： x:%f y:%f z:%f\n", m_move.x, m_move.y, m_move.z);
}

//===========================================================================================
// 描画処理
//===========================================================================================
void CPlayer::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングの有効/無効の設定
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (m_state != STATE_DEATH)
	{
		CBillboard::Draw();
	}

	//ライティングの有効/無効の設定
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===========================================================================================
// ヒット処理
//===========================================================================================
void CPlayer::Hit(int nDamage)
{
	//体力を減らす
	m_nLife -= nDamage;

	if (m_nLife < 0 && m_state != STATE_DEATH)
	{
		CFadeDeath::Create();
		m_state = STATE_DEATH;
		m_nLife = 0;

		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DEATH);
	}
}

//===========================================================================================
// 動作入力
//===========================================================================================
void CPlayer::InputMove(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	//キー入力で移動する処理
	if (pInputKeyboard->GetPress(DIK_A) == true || pInpuJoyPad->GetJoyStickLX(0) < 0)
	{//Aキーが押された

		m_move.x -= MOVE;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true || pInpuJoyPad->GetJoyStickLX(0) > 0)
	{//Dキーが押された

		m_move.x += MOVE;	
	}
}

//===========================================================================================
// ノーマルジャンプ
//===========================================================================================
void CPlayer::NormalJump(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	if (m_bNormalJump == false && m_bSecondJump == false)
	{//ジャンプしていない状態の場合

		if (pInputKeyboard->GetPress(DIK_SPACE) == true || pInpuJoyPad->GetPress(pInpuJoyPad->BUTTON_RB, 0) == true)
		{//キーが押された

			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_JUMP);

			m_move.y += FILSTJUMP_POWER;

			m_bNormalJump = true;
		}
	}

	//ブーストジャンプ
	SecondJump();

	if (pInpuJoyPad->GetJoyStickLX(0) < 0)
	{//左
		//移動量の初期化
		m_move.y = 0.0f;
		m_move.x = 0.0f;
	}
	if (pInpuJoyPad->GetJoyStickLX(0) > 0)
	{//右
		//移動量の初期化
		m_move.y = 0.0f;
		m_move.x = 0.0f;
	}
}

//===========================================================================================
// ジャンプ
//===========================================================================================
void CPlayer::SecondJump(void)
{
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad* pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();
	CInputMouse* pInputMouse = CManager::GetInstance()->GetInputMouse();

	//プレイヤーのスクリーン座標を取得
	D3DXVECTOR3 screemPos = GetScreenPosition();

	if (m_bJumpFlag == false)
	{//ジャンプしていない状態の場合

		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT))
		{//キーが押された

			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BOOST);

			//プレイヤーからマウスカーソルの角度を算出
			float fAngle = atan2f((screemPos.x - pInputMouse->GetPoint().x) + D3DX_PI, (screemPos.y - pInputMouse->GetPoint().y) + D3DX_PI);

			//移動量の初期化
			m_move.y = 0.0f;
			m_move.x = 0.0f;

			//移動量に加える
			m_move +=
			{
				sinf(fAngle + D3DX_PI) * SECONDJUMP_POWER,
				cosf(fAngle) * SECONDJUMP_POWER,
				0.0f
			};

			m_bNormalJump = true;
			m_bSecondJump = true;	//二回目のジャンプをしたことにする
			m_bJumpFlag = true;
		}
	}
}

//===========================================================================================
// 矢印
//===========================================================================================
void CPlayer::Arrow(D3DXVECTOR3 pos)
{
	CInputMouse* pInputMouse = CManager::GetInstance()->GetInputMouse();

	//プレイヤーのスクリーン座標を取得
	D3DXVECTOR3 screemPos = GetScreenPosition();

	//プレイヤーからマウスカーソルの角度を算出
	float fAngle = atan2f((screemPos.x - pInputMouse->GetPoint().x) + D3DX_PI, (screemPos.y - pInputMouse->GetPoint().y) + D3DX_PI);

	//nullチェック
	if (m_pArrowAround != nullptr)
	{
		//位置設定
		m_pArrowAround->SetPosition(D3DXVECTOR3(pos.x + sinf(-fAngle) * ARROW_POS, pos.y + cosf(-fAngle) * ARROW_POS, 0.0f));

		//向き
		m_pArrowAround->SetRotation(D3DXVECTOR3(0.0f, 0.0f, fAngle));
	}

	CManager::GetInstance()->GetDebugProc()->Print("\n\n【矢印】\n");
	CManager::GetInstance()->GetDebugProc()->Print("位置 x:%f y:%f z%f\n", m_pArrowAround->GetPosition().x, m_pArrowAround->GetPosition().y, m_pArrowAround->GetPosition().z);
	CManager::GetInstance()->GetDebugProc()->Print("向き x:%f y:%f z%f\n", m_pArrowAround->GetRotation().x, m_pArrowAround->GetRotation().y, m_pArrowAround->GetRotation().z);
}

//===========================================================================================
// スクリーン上のプレイヤーの位置
//===========================================================================================
D3DXVECTOR3 CPlayer::GetScreenPosition(void)
{
	//変数宣言
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 playerPos = GetPosition();
	D3DXVECTOR3 screenPos;
	D3DVIEWPORT9 viewport;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetViewport(&viewport);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//スクリーン座標に変換
	D3DXVec3Project(&screenPos, &playerPos, &viewport, &mtxProjection, &mtxView, &mtxWorld);

	return screenPos;
}

//===========================================================================================
// 崩れるブロックとの当たり判定
//===========================================================================================
bool CPlayer::CollisionBreakBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float size)
{
	bool bLand = false;	//着地したか

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject* pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			if (pObject->GetType() != pObject->TYPE_BREAKBLOCK)
			{
				continue;
			}

			CBreakBlock* pBreakBlock = pObject->GetBreakBlock();	//子クラス、壊れるブロックの情報取得

			if (pBreakBlock == nullptr)
			{
				continue;
			}

			if (pBreakBlock->Collision(pPos, pPosOld, pMove, size) == true)
			{
				bLand = true;
			}
		}
	}
	return bLand;	//bLandの結果を関数に返す
}

//===========================================================================================
// ダメージブロックとの当たり判定
//===========================================================================================
bool CPlayer::CollisionDamageBlock(D3DXVECTOR3 pos, float size)
{
	bool bTouch = false;	//接触したか

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject* pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			if (pObject->GetType() != pObject->TYPE_DAMAGEBLOCK)
			{
				continue;
			}

			CDamageBlock* pDamageBlock = pObject->GetDamageBlock();	//子クラス、壊れるブロックの情報取得

			if (pDamageBlock == nullptr)
			{
				continue;
			}

			if (pDamageBlock->Collision(pos, size) == true)
			{
				bTouch = true;
			}
		}
	}

	return bTouch;			//bLandの結果を関数に返す
}

//===========================================================================================
// ステージ切り替えの当たり判定
//===========================================================================================
bool CPlayer::CollisionNextStep(D3DXVECTOR3 pos, float size)
{
	bool bTouch = false;	//接触したか

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject* pObject = CObject::GetCObject(nCntPriority, nCntObj);

			if (pObject == nullptr)
			{
				continue;
			}

			if (pObject->GetType() != pObject->TYPE_NEXTSTEP)
			{
				continue;
			}

			CNextStep* pNextStep = pObject->GetNextStep();	//子クラス、壊れるブロックの情報取得

			if (pNextStep == nullptr)
			{
				continue;
			}

			if (pNextStep->Collision(pos, size) == true)
			{
				bTouch = true;
			}
		}
	}

	return bTouch;			//bLandの結果を関数に返す
}
