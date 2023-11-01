//=============================================================================
//
// サウンド処理[sound.h]
// Author : Takeru Ogasawara
//
//=============================================================================
#ifndef _SOUND_H_			//このマクロ定義がされていなかったら
#define _SOUND_H_			//2重インクルード防止のマクロを定義

#include "main.h"

//*****************************************************************************
// サウンドクラス
//*****************************************************************************
class CSound
{
public:

	// サウンド一覧
	typedef enum
	{
		LABEL_BGM_TITLE = 0,	// BGMタイトル
		LABEL_SE_ENTER,	// 決定
		LABEL_SE_JUMP,	// ジャンプ
		LABEL_SE_BOOST,	// ジャンプ
		LABEL_SE_DEATH,
		LABEL_MAX,
	} SOUND_LABEL;

private:

	// サウンド情報の構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

public:

	CSound();
	~CSound();

	//*****************************************************************************
	// メンバ関数
	//*****************************************************************************
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	static CSound m_pSound;

private:
	
	// メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// メンバ変数
	static const SOUNDINFO m_aSoundInfo[LABEL_MAX];	// サウンドファイル名
	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX];					// オーディオデータサイズ
};

#endif
