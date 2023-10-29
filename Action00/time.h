//===============================================================================
//
// [time.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _TIME_H_				//���̃}�N����`������Ă��Ȃ�������
#define _TIME_H_				//2�d�C���N���[�h�X�q�̃}�N�����`

#include "main.h"

//**********************************
// �O���錾
//**********************************
class CNumber;
class CObject2D;

//�i���o�[�N���X
class CTime
{
private:	//�萔(�}�N���I�Ȗ���)

	static const int NUM_TIME = 5;

public:
	CTime();	//�R���X�g���N�^
	~CTime();	//�f�X�g���N�^

	static CTime* Create(D3DXVECTOR3 pos);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	void SetTime(void);
	void AddTime(int nValue);

	int GetTime(void);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

private:
	CNumber* m_apNumber[NUM_TIME];
	CObject2D* m_pPeriod;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nTimeCount;
	int m_nTime;	
	DWORD m_dwGameStartTime;	//�Q�[���J�n����
	DWORD m_dwGameTime;	//�Q�[���o�ߎ���
};

#endif