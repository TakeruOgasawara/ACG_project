//=============================================================================
//
// �T�E���h����[sound.h]
// Author : Takeru Ogasawara
//
//=============================================================================
#ifndef _SOUND_H_			//���̃}�N����`������Ă��Ȃ�������
#define _SOUND_H_			//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//*****************************************************************************
// �T�E���h�N���X
//*****************************************************************************
class CSound
{
public:

	// �T�E���h�ꗗ
	typedef enum
	{
		LABEL_BGM_TITLE = 0,	// BGM�^�C�g��
		LABEL_SE_ENTER,	// ����
		LABEL_SE_JUMP,	// �W�����v
		LABEL_SE_BOOST,	// �W�����v
		LABEL_SE_DEATH,
		LABEL_MAX,
	} SOUND_LABEL;

private:

	// �T�E���h���̍\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

public:

	CSound();
	~CSound();

	//*****************************************************************************
	// �����o�֐�
	//*****************************************************************************
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	static CSound m_pSound;

private:
	
	// �����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �����o�ϐ�
	static const SOUNDINFO m_aSoundInfo[LABEL_MAX];	// �T�E���h�t�@�C����
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
