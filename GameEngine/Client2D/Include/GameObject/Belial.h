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
	CSharedPtr<class CBossUI>			m_BellialHPUI; // 보스 다만들고 만들거임

protected:
	CSharedPtr<CGameObject>	m_PlayerObject;

	bool				m_Attack;		// 공격중인지
	float				m_AttackDelay;	// 다음 공격까지 대기시간
	EBelialActionType	m_ActionType;	// 현재 공격중인 패턴

	// Laser 패턴
	bool				m_SelectLaserAttackCount;
	int					m_LaserAttackCount;
	float				m_LaserAttackDelay;	// Laser 공격 대기시간

	// Bullet 패턴
	float				m_BulletAttackTime;		// Bullet 공격 시간
	int					m_BulletAttackCount;	// Bullet 공격 횟수
	Vector2				m_BulletSummonPosition;	// Bullet 소환 위치
	float				m_BulletAngle;			// Bullet을 발사할 각도
	bool				m_BulletClockwise;		// Bullet을 시계방향으로 발사할지

	// Sword 패턴
	float				m_SwordAttackTime;		// Sword 공격 시간
	int					m_SwordAttackCount;		// Sword 공격 횟수
	Vector2				m_SwordSummonPosition;	// Sword 소환 위치

	// Die 패턴
	bool				m_DieMotion;			// 죽을때 모션들
	float				m_DieMotionTime;		// 5초동안

	float				m_DestroyEffectTime;
	int					m_DestroyEffectCount;
	float				m_DestroyEffectDistance;

	bool				m_DieEnd;

protected:
	bool				m_BossStart;			// 보스 패턴을 시작시킬지
	bool				m_CameraStart;
	float				m_CameraTime;			// 보스 패턴이 시작되고 시점 변환시간

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

