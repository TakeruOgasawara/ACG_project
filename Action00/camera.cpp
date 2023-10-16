//===========================================================================================
//
// [camera.cpp]
// Author : Takeru Ogasawara
//
//===========================================================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"

//マクロ定義
#define VIEWING_ANGLE		(45.0f)			//視野角

#define LENGTH				(500.0f)			//カメラとの距離
#define V_POSITION			(D3DXVECTOR3(0.0f, 1020.0f, 0.0f))			//視点の高さ
#define R_POSITION			(D3DXVECTOR3(0.0f, 540.0f, 0.0f))			//注視点の高さ
#define ROTATION			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//向き

//追従関係マクロ
#define V_FOLLOW_HEIGHT		(200.0f)			//視点の高さ(追従)
#define R_FOLLOW_HEIGHT		(100.0f)			//注視点の高さ(追従)
#define R_FOLLOW_MAE		(D3DXVECTOR3(20.0f, 100.0f, 20.0f))			//追従時に注視点をどのくらい前に出すか

#define OFFSET_V			(0.3f)				//視点の補正
#define OFFSET_R			(0.3f)				//注視点の補正

#define MOUSE_SENSITIVITY	(0.004f)			//マウス感度
#define PAD_SENSITIVITY		(0.045f)			//パッド感度

#define CAMERA_ROT_LIMIT_UP		(0.35f)			//カメラの上限
#define CAMERA_ROT_LIMIT_DOWN	(0.01f)			//カメラの上限

//===========================================================================================
// コンストラクタ
//===========================================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fHeightV = 0.0f;
	m_fHeightR = 0.0f;
}

//===========================================================================================
// デストラクタ
//===========================================================================================
CCamera::~CCamera()
{

}

//===========================================================================================
// 初期化処理
//===========================================================================================
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(V_POSITION.x, V_POSITION.y, V_POSITION.z);
	m_posR = D3DXVECTOR3(R_POSITION.x, R_POSITION.y, R_POSITION.z);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(ROTATION.x, ROTATION.y, ROTATION.z);
	m_fLength = LENGTH;
	m_fHeightV = V_FOLLOW_HEIGHT;
	m_fHeightR = R_FOLLOW_HEIGHT;

	return S_OK;
}

//===========================================================================================
// 終了処理
//===========================================================================================
void CCamera::Uninit(void)
{

}

//===========================================================================================
// 更新処理
//===========================================================================================
void CCamera::Update(void)
{
	//V_Move_Mouse();
	R_Move_Mouse();

	V_Move();
	R_Move();

	//カメラの向きを修正する
	FixOrientation();

	CManager::GetInstance()->GetDebugProc()->Print("\n\n【カメラ情報】");
	CManager::GetInstance()->GetDebugProc()->Print("\n視点： x:%f y:%f z:%f", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n注視点： x:%f y:%f z:%f", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetInstance()->GetDebugProc()->Print("\n向き： x:%f, y:%f z:%f\n", m_rot.z, m_rot.y, m_rot.z);
}

//===========================================================================================
// カメラ設定
//===========================================================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	//D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
	//	D3DXToRadian(VIEWING_ANGLE),					//視野角
	//	(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		//画面のアスペクト比
	//	10.0f,				//z値の最小値
	//	10000.0f);			//z値の最大値

	//プロジェクションマトリックスを作成[平行投影]
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH,				//視野角
		(float)SCREEN_HEIGHT,				//画面のアスペクト比
		1.0f,				//z値の最小値
		1000.0f);			//z値の最大値

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,			//視点
		&m_posR,			//注視点
		&m_vecU);			//情報ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//===========================================================================================
// カメラの向きを直す
//===========================================================================================
void CCamera::FixOrientation(void)
{
	//向きが3.14以上-3.14以下に行かないようにする
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x = -D3DX_PI;
	}
	if (m_rot.x < -D3DX_PI)
	{
		m_rot.x = D3DX_PI;
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z = -D3DX_PI;
	}
	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z = D3DX_PI;
	}
}

//===========================================================================================
// 視点(マウス)
//===========================================================================================
void CCamera::V_Move_Mouse(void)
{
	//インプット情報の取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();
	CInputJoyPad *pInpuJoyPad = CManager::GetInstance()->GetInputJoyPad();

	//視点の移動
	if (pInputMouse->GetPress(pInputMouse->MOUSE_LEFT))
	{
		m_rot.z += -pInputMouse->GetMovement().y * MOUSE_SENSITIVITY;
		m_rot.y += pInputMouse->GetMovement().x * MOUSE_SENSITIVITY;

		//マウスの移動量から視点を動かす
		V_Move();
	}

	//パッド
	/*m_rot.z += pInpuJoyPad->GetJoyStickRY(0) * PAD_SENSITIVITY;
	m_rot.y += pInpuJoyPad->GetJoyStickRX(0) * PAD_SENSITIVITY;*/
}

//===========================================================================================
// 注視点(マウス)
//===========================================================================================
void CCamera::R_Move_Mouse(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//視点の移動
	if (pInputMouse->GetPress(pInputMouse->MOUSE_RIGHT))
	{
		//マウスの移動量から注視点を動かす
		m_rot.z += -pInputMouse->GetMovement().y * MOUSE_SENSITIVITY;
		m_rot.y += pInputMouse->GetMovement().x * MOUSE_SENSITIVITY;

		//注視点の移動
		R_Move();
	}
}

//===========================================================================================
// 視点
//===========================================================================================
void CCamera::V_Move(void)
{
	m_posV.x = m_posR.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength;
	m_posV.y = m_posR.y + sinf(m_rot.z) * -m_fLength;
	m_posV.z = m_posR.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength;
}

//===========================================================================================
// 注視点
//===========================================================================================
void CCamera::R_Move(void)
{
	m_posR.x = m_posV.x + (cosf(m_rot.z) * sinf(m_rot.y)) * m_fLength;
	m_posR.y = m_posV.y + sinf(m_rot.z) * m_fLength;
	m_posR.z = m_posV.z + (cosf(m_rot.z) * cosf(m_rot.y)) * m_fLength;
}

//===========================================================================================
// ズーム
//===========================================================================================
void CCamera::Zoom(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//if (pInputMouse->GetPress(pInputMouse->MOUSE_HWEEL) == true)
	//{
	//	//注視点の移動
	//	m_posR.x += (-pInputMouse->GetMovement.x * sinf(m_rot.x)) * 0.1f;
	//	m_posR.y += (pInputMouse->GetMovement.y * sinf(m_rot.y)) * 0.1f;
	//	m_posR.z += (pInputMouse->GetMovement.z * sinf(m_rot.z)) * 0.1f;

	//	//注視点の更新処理
	//	V_Move();

	//	//視点の移動
	//	m_posV.x += (-pInputMouse->GetMovement.x * cosf(m_rot.x)) * 0.1f;
	//	m_posV.y += (pInputMouse->GetMovement.y * cosf(m_rot.y)) * 0.1f;
	//	m_posV.z += (pInputMouse->GetMovement.z * cosf(m_rot.z)) * 0.1f;

	//	//視点の更新処理
	//	R_Move();
	//}
}

//-------------------------------------------------------------------------------------------
// カメラの追従処理 : Follow(位置、向き)
//-------------------------------------------------------------------------------------------
void CCamera::Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//目的の視点/注視点を設定(初期値)
	//注視点
	m_posRDest =
	{
		pos.x + sinf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.x,
		pos.y + m_fHeightR,
		pos.z + cosf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.z
	};

	//視点
	m_posVDest =
	{
		m_posRDest.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength,
		pos.y + m_fHeightV,
		m_posRDest.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength
	};

	m_posR += (m_posRDest - m_posR) * OFFSET_R;			//注視点を補正
	m_posV += (m_posVDest - m_posV) * OFFSET_R;			//視点を補正
}

//-------------------------------------------------------------------------------------------
// カメラの追従処理 : Follow(位置、向き、視点高さ、注視点高さ)
//-------------------------------------------------------------------------------------------
void CCamera::Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeightV, float fHeightR)
{
	m_fHeightV = fHeightV;
	m_fHeightR = fHeightR;

	//目的の視点/注視点を設定(初期値)
	//注視点
	m_posRDest =
	{
		pos.x + sinf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.x,
		m_fHeightR,
		pos.z + cosf(m_rot.y - D3DX_PI) * -R_FOLLOW_MAE.z
	};

	//視点
	m_posVDest =
	{
		m_posRDest.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength,
		m_fHeightV,
		m_posRDest.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength
	};

	m_posR += (m_posRDest - m_posR) * OFFSET_R;			//注視点を補正
	m_posV += (m_posVDest - m_posV) * OFFSET_R;			//視点を補正
}

//====================================================================
// 横スク(x軸)専用追従処理
//====================================================================
void CCamera::Follow2D_x_axisDedicated(D3DXVECTOR3 pos)
{
	//目的の視点/注視点を設定(初期値)
//注視点
	m_posRDest =
	{
		pos.x + sinf(m_rot.y - D3DX_PI),
		/*pos.y + */m_fHeightR,
		pos.z + cosf(m_rot.y - D3DX_PI)
	};

	//視点
	m_posVDest =
	{
		m_posRDest.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength,
		/*pos.y + */m_fHeightV,
		m_posRDest.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength
	};

	m_posR += (m_posRDest - m_posR) * OFFSET_R;			//注視点を補正
	m_posV += (m_posVDest - m_posV) * OFFSET_R;			//視点を補正
}

//====================================================================
// カメラの位置を自動的に後ろ側へ
//====================================================================
void  CCamera::Back(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//変数宣言
	float fRotDiff = 0.0f;			//差分保存用

	fRotDiff = (rot.y + D3DX_PI) - m_rot.y;			//差分を計算

	//目標の角度の補正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= (D3DX_PI * 2);
	}
	if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	m_rot.y += fRotDiff * 0.045f;			//補正する

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= 6.28f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += 6.28f;
	}

	//カメラを更新する
	m_posVDest.x = pos.x + (cosf(m_rot.z) * sinf(m_rot.y)) * -m_fLength;
	m_posVDest.y = pos.y + sinf(m_rot.z) * -m_fLength;			//視点Y
	m_posVDest.z = pos.z + (cosf(m_rot.z) * cosf(m_rot.y)) * -m_fLength;
}

//===========================================================================================
// カメラの設定(数値) : SetValue(視点と注視点の距離、視点の高さ、注視点の高さ)
//===========================================================================================
void CCamera::SetValue(float fDistance, D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	m_fLength = fDistance;
	m_posV = posV;
	m_fHeightV = posV.y;
	m_posR = posR;
}