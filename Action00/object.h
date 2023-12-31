//===============================================================================
//
// [object.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _OBJECT_H_				//このマクロ定義がされていなかったら
#define _OBJECT_H_				//2重インクルード防止のマクロを定義

#include "main.h"

//前方宣言
class CObject2D;
class CEnemy3D;
class CPlayer;
class CMeshWall;
class CObjectX;
class CBreakBlock;
class CDamageBlock;
class CTrapScissors;
class CNextStep;

//マクロ定義
#define MAX_OBJECT		(5000)
#define NUM_PRIORITY	(8)

//オブジェクトクラス
class CObject
{
public:			//構造体・列挙型用のpublic
	//オブジェクトの種類
	typedef enum
	{
		TYPE_NONE,			//無し
		TYPE_PLAYER,		//プレイヤー3D
		TYPE_EFFECT,		//エフェクト
		TYPE_PARTICLE,		//パーティクル
		TYPE_OBJECTX,		//オブジェクトX
		TYPE_NEXTSTEP,		//
		TYPE_LOCKDOOR,		//
		TYPE_BREAKBLOCK,	//壊れるブロック
		TYPE_DAMAGEBLOCK,	//ダメージブロック
		TYPE_TRAPSCISSORS, //トラばさみ
		TYPE_MAX
	} TYPE;

public:			//メンバ関数用のpublic

	CObject(int nPriority = 3);	//コンストラクタ デフォルト引数
	virtual ~CObject();	//デストラクタ

	//******************************************
	// メンバ関数
	//******************************************
	virtual HRESULT Init(void) = 0;	//初期化
	virtual void Uninit(void) = 0;	//終了
	virtual void Update(void) = 0;	//更新
	virtual void Draw(void) = 0;	//描画

	static void ReleaseAll(void);	//全オブジェクトの破棄
	static void UpdateAll(void);	//全オブジェクトの更新
	static void DrawAll(void);	//全オブジェクトの描画

	static void ReleaseAllSpecified(TYPE type);

	//******************************************
	// 設定用メンバ関数
	//******************************************
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;	//位置の設定
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;	//向きの設定
	void SetType(TYPE type) { m_type = type; }	//種類の設定

	//******************************************
	// 取得用メンバ関数
	//******************************************
	virtual D3DXVECTOR3 GetPosition(void) = 0;	//位置の取得
	virtual D3DXVECTOR3 GetRotation(void) = 0;	//向きの取得
	virtual D3DXVECTOR3 GetMovement(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//移動量の取得
	virtual CEnemy3D *GetEnemy3D(void) { return nullptr; }	//敵情報の取得
	virtual CPlayer *GetPlayer(void) { return nullptr; }//プレイやの取得
	virtual CMeshWall *GetMeshWall(void) { return nullptr; }//メッシュウォールの取得
	virtual CObjectX *GetObjectX(void) { return nullptr; }	//オブジェXの取得
	virtual CBreakBlock* GetBreakBlock(void) { return nullptr; }	//壊れるブロックの取得
	virtual CDamageBlock* GetDamageBlock(void) { return nullptr; }	//ダメージブロック
	virtual CNextStep* GetNextStep(void) { return nullptr; }
	virtual CTrapScissors* GetTrapScissors(void) { return nullptr; }
	static CObject *GetCObject(int nPriority, int nIdx);	//オブジェクトの取得
	static int GetNumAll(void) { return m_nNumAll; }	//オブジェクト総数の取得
	TYPE GetType(void) { return m_type; }	//種類の取得
	static bool TypeCheck(CObject *pObject, TYPE type);	//タイプ判定

protected:
	void Release(void);	//オブジェクト自身の破棄

private:
	static CObject *m_apObject[NUM_PRIORITY][MAX_OBJECT];	//オブジェクト格納用
	static int m_nNumAll;	//オブジェクト総数
	int m_nID;	//それぞれのオブジェクトが持つ番号
	int m_nPriority;	//優先順位の位置
	TYPE m_type;	//それぞれのオブジェクトが持つ種類
};

#endif