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
class CPlayer3D;
class CChain;
class CMeshWall;
class CObjectX;
class CBullet;
class CChainObject;

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
		TYPE_PLAYER3D,		//�v���C���[3D
		TYPE_ENEMY3D,		//�G3D
		TYPE_BULLET,		//�e
		TYPE_EXPLOSION,		//����
		TYPE_EFFECT,		//�G�t�F�N�g
		TYPE_PARTICLE,		//�p�[�e�B�N��
		TYPE_SCORE,			//�X�R�A
		TYPE_TIME,			//����
		TYPE_BLOCK,			//�u���b�N
		TYPE_ITEM,			//�A�C�e��
		TYPE_OBJECT3D,		//�I�u�W�F�N�g3D
		TYPE_BILLBOARD,		//�r���{�[�h
		TYPE_OBJECTX,		//�I�u�W�F�N�gX(X�t�@�C������ǂݍ��񂾃��f��)
		TYPE_FRAME,			//�g
		TYPE_CHAIN,
		TYPE_DETONATION_POINT,
		TYPE_SCOREOBJECT,
		TYPE_MESHWALL,		//���b�V���E�H�[��
		TYPE_CHAINOBJECT,	//�A���I�u�W�F�N�g
		TYPE_MAX
	} TYPE;

public:			//�����o�֐��p��public

	CObject(int nPriority = 3);			//�R���X�g���N�^ �f�t�H���g����
	virtual ~CObject();			//�f�X�g���N�^

	//******************************************
	// �����o�֐�
	//******************************************
	virtual HRESULT Init(void) = 0;			//������
	virtual void Uninit(void) = 0;			//�I��
	virtual void Update(void) = 0;			//�X�V
	virtual void Draw(void) = 0;			//�`��

	static void ReleaseAll(void);			//�S�I�u�W�F�N�g�̔j��
	static void UpdateAll(void);			//�S�I�u�W�F�N�g�̍X�V
	static void DrawAll(void);				//�S�I�u�W�F�N�g�̕`��

	static void ReleaseAll_specified(TYPE type);

	//******************************************
	// �ݒ�p�����o�֐�
	//******************************************
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;			//�ʒu�̐ݒ�
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;			//�����̐ݒ�
	void SetType(TYPE type) { m_type = type; }				//��ނ̐ݒ�

	//******************************************
	// �擾�p�����o�֐�
	//******************************************
	virtual D3DXVECTOR3 GetPosition(void) = 0;				//�ʒu�̎擾
	virtual D3DXVECTOR3 GetRotation(void) = 0;				//�����̎擾
	virtual D3DXVECTOR3 GetMovement(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }	//�ړ��ʂ̎擾
	virtual CEnemy3D *GetEnemy3D(void) { return nullptr; }	//�G���̎擾
	virtual CPlayer3D *GetPlayer3D(void) { return nullptr; }//�v���C��̎擾
	virtual CChain *GetChain(void) { return nullptr; }		//�A�����̎擾
	virtual CMeshWall *GetMeshWall(void) { return nullptr; }//���b�V���E�H�[���̎擾
	virtual CObjectX *GetObjectX(void) { return nullptr; }	//�I�u�W�FX�̎擾
	virtual CBullet *GetBullet(void) { return nullptr; }
	virtual CChainObject *GetChainObject(void) { return nullptr; }
	static CObject *GetCObject(int nPriority, int nIdx);	//�I�u�W�F�N�g�̎擾
	static int GetNumAll(void) { return m_nNumAll; }		//�I�u�W�F�N�g�����̎擾
	TYPE GetType(void) { return m_type; }					//��ނ̎擾
	static bool TypeCheck(CObject *pObject, TYPE type);		//�^�C�v����

protected:
	void Release(void);			//�I�u�W�F�N�g���g�̔j��

private:
	static CObject *m_apObject[NUM_PRIORITY][MAX_OBJECT];
	static int m_nNumAll;
	int m_nID;				//���ꂼ��̃I�u�W�F�N�g�����ԍ�
	int m_nPriority;		//�D�揇�ʂ̈ʒu
	TYPE m_type;			//���ꂼ��̃I�u�W�F�N�g�������
};

#endif