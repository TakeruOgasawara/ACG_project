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
class CPlayer3D;
class CChain;
class CMeshWall;
class CObjectX;
class CBullet;
class CChainObject;

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
		TYPE_PLAYER3D,		//プレイヤー3D
		TYPE_ENEMY3D,		//敵3D
		TYPE_BULLET,		//弾
		TYPE_EXPLOSION,		//爆発
		TYPE_EFFECT,		//エフェクト
		TYPE_PARTICLE,		//パーティクル
		TYPE_SCORE,			//スコア
		TYPE_TIME,			//時間
		TYPE_BLOCK,			//ブロック
		TYPE_ITEM,			//アイテム
		TYPE_OBJECT3D,		//オブジェクト3D
		TYPE_BILLBOARD,		//ビルボード
		TYPE_OBJECTX,		//オブジェクトX(Xファイルから読み込んだモデル)
		TYPE_FRAME,			//枠
		TYPE_CHAIN,
		TYPE_DETONATION_POINT,
		TYPE_SCOREOBJECT,
		TYPE_MESHWALL,		//メッシュウォール
		TYPE_CHAINOBJECT,	//連鎖オブジェクト
		TYPE_MAX
	} TYPE;

public:			//メンバ関数用のpublic

	CObject(int nPriority = 3);			//コンストラクタ デフォルト引数
	virtual ~CObject();			//デストラクタ

	//******************************************
	// メンバ関数
	//******************************************
	virtual HRESULT Init(void) = 0;			//初期化
	virtual void Uninit(void) = 0;			//終了
	virtual void Update(void) = 0;			//更新
	virtual void Draw(void) = 0;			//描画

	static void ReleaseAll(void);			//全オブジェクトの破棄
	static void UpdateAll(void);			//全オブジェクトの更新
	static void DrawAll(void);				//全オブジェクトの描画

	static void ReleaseAll_specified(TYPE type);

	//******************************************
	// 設定用メンバ関数
	//******************************************
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;			//位置の設定
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;			//向きの設定
	void SetType(TYPE type) { m_type = type; }				//種類の設定

	//******************************************
	// 取得用メンバ関数
	//******************************************
	virtual D3DXVECTOR3 GetPosition(void) = 0;				//位置の取得
	virtual D3DXVECTOR3 GetRotation(void) = 0;				//向きの取得
	virtual D3DXVECTOR3 GetMovement(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//移動量の取得
	virtual CEnemy3D *GetEnemy3D(void) { return nullptr; }	//敵情報の取得
	virtual CPlayer3D *GetPlayer3D(void) { return nullptr; }//プレイやの取得
	virtual CChain *GetChain(void) { return nullptr; }		//連鎖情報の取得
	virtual CMeshWall *GetMeshWall(void) { return nullptr; }//メッシュウォールの取得
	virtual CObjectX *GetObjectX(void) { return nullptr; }	//オブジェXの取得
	virtual CBullet *GetBullet(void) { return nullptr; }
	virtual CChainObject *GetChainObject(void) { return nullptr; }
	static CObject *GetCObject(int nPriority, int nIdx);	//オブジェクトの取得
	static int GetNumAll(void) { return m_nNumAll; }		//オブジェクト総数の取得
	TYPE GetType(void) { return m_type; }					//種類の取得
	static bool TypeCheck(CObject *pObject, TYPE type);		//タイプ判定

protected:
	void Release(void);			//オブジェクト自身の破棄

private:
	static CObject *m_apObject[NUM_PRIORITY][MAX_OBJECT];
	static int m_nNumAll;
	int m_nID;				//それぞれのオブジェクトが持つ番号
	int m_nPriority;		//優先順位の位置
	TYPE m_type;			//それぞれのオブジェクトが持つ種類
};

#endif