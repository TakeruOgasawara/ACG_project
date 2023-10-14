//===============================================================================
//
// [renderer.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _RENDERER_H_				//���̃}�N����`������Ă��Ȃ�������
#define _RENDERER_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"
#include "sound.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);			//Directx3D�ւ̃f�o�C�X�ւ̃|�C���^

private:
	LPDIRECT3D9 m_pD3D;						//Directx3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;			//Directx3D�ւ̃f�o�C�X�ւ̃|�C���^
	bool m_bWireframe;
};

#endif