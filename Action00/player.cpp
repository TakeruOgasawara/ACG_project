//===========================================================================================
//
// [player3D.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include <stdio.h>
#include "player.h"
#include "arrow_around.h"

#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "collision.h"

//マクロ定義
#define SIZE			(D3DXVECTOR2(5.0f, 10.0f))

#define MOVE			(3.5f)			//移動量
#define ATT				(0.3f)			//減衰
#define GRAVITY			(1.0f)			//重力

//矢印の位置
#define ARROW_POS		(70.0f)

//ジャンプ
#define FILSTJUMP_POWER		(20.4f)			//ジャンプ力
#define SECONDJUMP_POWER	(30.0f)			//

//===========================================================================================
// コンストラクタ
//===========================================================================================
CPlayer::CPlayer(int nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = STATE_NORMAL;
	m_pCamera = nullptr;
	m_pArrowAround = nullptr;
	m_bFirstJump = false;
	m_bSecondJump = false;
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

	// ビルボード(プレイヤー本体
	CBillboard::Init();
 	SetSize(D3DXVECTOR2(SIZE.x, SIZE.y));
	BindTexture("data\\TEXTURE\\player.png");

	// 矢印
	// 二回目のジャンプ方向を決める矢印
	m_pArrowAround = CArrowAround::Create();	//生成
	m_pArrowAround->BindTexture("data\\TEXTURE\\game\\arrow1.png");
	//m_pArrowAround->SetSize(D3DXVECTOR2(10.0f, 20.0f));
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
		m_pArrowAround = nullptr;
	}

	CBillboard::Uninit();

	//自分自身の破棄
	Release();
}

//===========================================================================================
// 更新処理
//===========================================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 posOld = pos;
	D3DXVECTOR3 rot = GetRotation();

	//重力
	m_move.y -= GRAVITY;

	//地面(0.0f)より下に行かないように
	if (pos.y <= SIZE.y)
	{
		pos.y = SIZE.y;
		m_move.y = 0.0f;
		m_bFirstJump = false;
		m_bSecondJump = false;
	}

	if (m_bSecondJump == false)
	{//二回目のジャンプをしてない場合

		//移動量を更新(減衰させる)
		m_move.x += (0.0f - m_move.x) * ATT;

		//操作
		InputMove();
	}

	//移動量の代入
	pos += m_move;

	
	if (CollisionObjectX(&pos, &posOld, &m_move, SIZE.y) == true)
	{
		m_bFirstJump = false;
		m_bSecondJump = false;
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

	CBillboard::Draw();

	//ライティングの有効/無効の設定
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
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

	//ジャンプをまとめた関数
	Jump();
}

//===========================================================================================
// ジャンプ
//===========================================================================================
void CPlayer::Jump(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//ジャンプできるか確認
	if (m_bFirstJump == false && m_bSecondJump == false)
	{//ジャンプしていない状態の場合
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{//キーが押された

			//移動量の初期化
			m_move.y = 0.0f;
			m_move.x = 0.0f;

			m_move.y += FILSTJUMP_POWER;			//数値分上へ

			m_bFirstJump = true;	//一回目のジャンプをしたことにする

		}
	}
	if (pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT))
	{//キーが押された

		//プレイヤーのスクリーン座標を取得
		D3DXVECTOR3 screemPos = GetScreenPosition();

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

		m_bSecondJump = true;	//二回目のジャンプをしたことにする
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
