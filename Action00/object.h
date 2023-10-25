//===============================================================================
//
// [object.h]
// Author : Takeru Ogasawara
//
//===============================================================================
#ifndef _OBJECT_H_				//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_				//2�d�C���N���[�h�h�~�̃}�N�����`

#include "main.h"

//�O���錾
class CObject2D;
class CEnemy3D;
class CPlayer;
class CMeshWall;
class CObjectX;
class CBreakBlock;

//�}�N����`
#define MAX_OBJECT		(5000)
#define NUM_PRIORITY	(8)

//�I�u�W�F�N�g�N���X
class CObject
{
public:			//�\���́E�񋓌^�p��public
	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		TYPE_NONE,			//����
		TYPE_PLAYER,		//�v���C���[3D
		TYPE_EFFECT,		//�G�t�F�N�g
		TYPE_PARTICLE,		//�p�[�e�B�N��
		TYPE_OBJECTX,		//�I�u�W�F�N�gX
		TYPE_NEXTSTEP,		//
		TYPE_LOCKDOOR,		//
		TYPE_BREAKBLOCK,
		TYPE_MAX
	} TYPE;

public:			//�����o�֐��p��public

	CObject(int nPriority = 3);	//�R���X�g���N�^ �f�t�H���g����
	virtual ~CObject();	//�f�X�g���N�^

	//******************************************
	// �����o�֐�
	//******************************************
	virtual HRESULT Init(void) = 0;	//������
	virtual void Uninit(void) = 0;	//�I��
	virtual void Update(void) = 0;	//�X�V
	virtual void Draw(void) = 0;	//�`��

	static void ReleaseAll(void);	//�S�I�u�W�F�N�g�̔j��
	static void ParticularRelease(TYPE type);	//����̃I�u�W�F�N�g�̔j��
	static void UpdateAll(void);	//�S�I�u�W�F�N�g�̍X�V
	static void DrawAll(void);	//�S�I�u�W�F�N�g�̕`��

	static void ReleaseAll_specified(TYPE type);

	//******************************************
	// �ݒ�p�����o�֐�
	//******************************************
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;	//�ʒu�̐ݒ�
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;	//�����̐ݒ�
	void SetType(TYPE type) { m_type = type; }	//��ނ̐ݒ�

	//******************************************
	// �擾�p�����o�֐�
	//******************************************
	virtual D3DXVECTOR3 GetPosition(void) = 0;	//�ʒu�̎擾
	virtual D3DXVECTOR3 GetRotation(void) = 0;	//�����̎擾
	virtual D3DXVECTOR3 GetMovement(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//�ړ��ʂ̎擾
	virtual CEnemy3D *GetEnemy3D(void) { return nullptr; }	//�G���̎擾
	virtual CPlayer *GetPlayer(void) { return nullptr; }//�v���C��̎擾
	virtual CMeshWall *GetMeshWall(void) { return nullptr; }//���b�V���E�H�[���̎擾
	virtual CObjectX *GetObjectX(void) { return nullptr; }	//�I�u�W�FX�̎擾
	virtual CBreakBlock* GetBreakBlock(void) { return nullptr; }	//����u���b�N�̎擾
	static CObject *GetCObject(int nPriority, int nIdx);	//�I�u�W�F�N�g�̎擾
	static int GetNumAll(void) { return m_nNumAll; }	//�I�u�W�F�N�g�����̎擾
	TYPE GetType(void) { return m_type; }	//��ނ̎擾
	static bool TypeCheck(CObject *pObject, TYPE type);	//�^�C�v����

protected:
	void Release(void);	//�I�u�W�F�N�g���g�̔j��

private:
	static CObject *m_apObject[NUM_PRIORITY][MAX_OBJECT];	//�I�u�W�F�N�g�i�[�p
	static int m_nNumAll;	//�I�u�W�F�N�g����
	int m_nID;	//���ꂼ��̃I�u�W�F�N�g�����ԍ�
	int m_nPriority;	//�D�揇�ʂ̈ʒu
	TYPE m_type;	//���ꂼ��̃I�u�W�F�N�g�������
};

#endif