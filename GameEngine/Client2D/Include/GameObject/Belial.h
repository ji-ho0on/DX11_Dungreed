#pragma once

#include "Creature.h"

enum class EBelialActionType
{
	Idle,
	Laser,
	Bullet,
	Sword,
	Die
};

class CBelial :
    public CCreature
{
	friend class CScene;

protected:
	CBelial();
	CBelial(const CBelial& Obj);
	virtual ~CBelial();

protected:
	CSharedPtr<class CColliderBox2D>	m_Body;
	CSharedPtr<class CSpriteComponent>	m_BelialHead;
	CSharedPtr<class CSpriteComponent>	m_BelialBack;
	CSharedPtr<class CSpriteComponent>	m_BelialLeftHand;
	CSharedPtr<class CSpriteComponent>	m_BelialRightHand;

	CSharedPtr<class CSpriteComponent>	m_BelialDeadHead;
	CSharedPtr<class CSpriteComponent>	m_BelialDeadMouth;

	CSharedPtr<class CCameraComponent>	m_BelialCamera;
	CSharedPtr<class CTargetArm>		m_BelialTargetArm;


protected:
	CSharedPtr<class CBossUI>			m_BellialHPUI; // ���� �ٸ���� �������

protected:
	CSharedPtr<CGameObject>	m_PlayerObject;

	bool				m_Attack;		// ����������
	float				m_AttackDelay;	// ���� ���ݱ��� ���ð�
	EBelialActionType	m_ActionType;	// ���� �������� ����

	// Laser ����
	bool				m_SelectLaserAttackCount;
	int					m_LaserAttackCount;
	float				m_LaserAttackDelay;	// Laser ���� ���ð�

	// Bullet ����
	float				m_BulletAttackTime;		// Bullet ���� �ð�
	int					m_BulletAttackCount;	// Bullet ���� Ƚ��
	Vector2				m_BulletSummonPosition;	// Bullet ��ȯ ��ġ
	float				m_BulletAngle;			// Bullet�� �߻��� ����
	bool				m_BulletClockwise;		// Bullet�� �ð�������� �߻�����

	// Sword ����
	float				m_SwordAttackTime;		// Sword ���� �ð�
	int					m_SwordAttackCount;		// Sword ���� Ƚ��
	Vector2				m_SwordSummonPosition;	// Sword ��ȯ ��ġ

	// Die ����
	bool				m_DieMotion;			// ������ ��ǵ�
	float				m_DieMotionTime;		// 5�ʵ���

	float				m_DestroyEffectTime;
	int					m_DestroyEffectCount;
	float				m_DestroyEffectDistance;

	bool				m_DieEnd;

protected:
	bool				m_BossStart;			// ���� ������ ���۽�ų��
	bool				m_CameraStart;
	float				m_CameraTime;			// ���� ������ ���۵ǰ� ���� ��ȯ�ð�

public:
	void SetBossStart();

public:
	virtual int InflictDamage(int Damage);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBelial* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void SummonBulletClockwise();
	void SummonBulletCounterClockwise();
	void SummonSword();
	void RandomDestroyEffect();
	void LastDestroyEffect();
};

