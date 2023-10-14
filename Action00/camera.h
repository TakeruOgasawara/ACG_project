//===============================================================================
//
// [camera.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _CAMERA_H_				//このマクロ定義がされていなかったら
#define _CAMERA_H_				//2重インクルード防止のマクロを定義

#include "main.h"

//カメラクラス
class CCamera
{
private:
	struct Circle
	{
		float m_PosX;		// 描画座標X
		float m_PosY;		// 描画座標Y
		float m_Radius;		// 半径(描画用)
		float m_CenterX;	// 中心座標X
		float m_CenterY;	// 中心座標Y
		float m_Angle;		// 角度
		float m_Length;		// 半径の長さ
	};

public:
	CCamera();
	~CCamera();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//追従
	void Follow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHeightV, float fHeightR);			//追従
	void Back(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//背後

	void V_Move(void);
	void R_Move(void);
	void Zoom(void);			//ズーム

	void SetCamera(void);
	void SetLength(float fLength) { m_fLength = fLength; }
	void SetPosition_V(D3DXVECTOR3 pos) { m_posV = pos; }
	void SetPosition_R(D3DXVECTOR3 pos) { m_posR = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetValue(float fDistance, float fPosV, float fPosR);

	D3DXVECTOR3 GetPosition_V(void) { return m_posV; }
	D3DXVECTOR3 GetPosition_R(void) { return m_posR; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:
	void V_Move_Mouse(void);			//視点移動(マウス)
	void R_Move_Mouse(void);			//注視点移動(マウス)
	void FixOrientation(void);		//方向修正

	//変数
	D3DXMATRIX m_mtxView;			//ビューマトリックス
	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注視点
	D3DXVECTOR3 m_vecU;				//上方向ベクトル
	D3DXVECTOR3 m_rot;				//向き
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_posVDest;			//視点の差分
	D3DXVECTOR3 m_posRDest;			//注視点の差分
	float m_fLength;
	float m_fHeightV;
	float m_fHeightR;
	Circle m_circle;
};

#endif