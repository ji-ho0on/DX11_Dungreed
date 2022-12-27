#pragma once

#include "Creature.h"

class CCharacter :
    public CCreature
{
	friend class CScene;

protected:
	CCharacter();
	CCharacter(const CCharacter& Obj);
	virtual ~CCharacter();

// Component들
private:
	CSharedPtr<class CSpriteComponent>	m_Character;
	CSharedPtr<class CColliderBox2D>	m_Body;

	// 플레이어가 사용할 무기
	CSharedPtr<class CSpriteComponent>	m_Weapon;

	// 플레이어 시점으로 화면을 움직이게 할 카메라와 Offset설정을 위한 카메라 Arm
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>		m_Arm;

	// 중력을 적용시킬 ObjectComponent
	CSharedPtr<class CGravityAgent>		m_Gravity;

// Character의 능력치
private:
	EDirection				m_Direction;		// 캐릭터가 바라보는 방향
	ECharacterActionType	m_ActionType;		// 캐릭터 행동타입, Idle, Run, Jump, Die
	EWeaponType				m_CurrentWeapon;	// 캐릭터가 현재 장착중인 무기
	EWeaponType				m_EquippedWeapon1;	// 캐릭터가 가진 무기 1번
	EWeaponType				m_EquippedWeapon2;	// 캐릭터가 가진 무기 2번

	float					m_MouseAngleRight;	// 오른쪽 방향일 때 캐릭터와 마우스의 각도
	float					m_MouseAngleLeft;	// 왼쪽 방향일 때 캐릭터와 마우스의 각도

	// 무기가 ShortSword일 경우
	float					m_ShortSwordAngle[(int)EShortSwordState::End];	// ShortSword 기본 Angle(Up과 Down일 때 각각 있음)
	EShortSwordState		m_ShortSwordState;	// ShortSword의 상태(위, 아래)

// Character의 능력치
private:
	int						m_Level;		// 레벨
	int						m_HPMax;		// 최대체력
	int						m_Power;		// 공격력
	int						m_Armor;		// 방어력
	int						m_DashCount;	// Dash가 가능한 횟수
	int						m_Gold;			// 보유 골드
	int						m_Satiety;		// 포만감
	int						m_SatietyMax;	// 최대포만감

	// Run 상태 관련
	float					m_StepTime;
	int						m_StepCount;

	// Dash 관련
	bool					m_IsDash;		// Dash 상태인지
	Vector3					m_DashDir;		// Dash 방향
	float					m_DashTime;
	float					m_DashCountCooldown;	// DashCount가 충전되는 시간

// Character의 능력치를 나타내줄 UI
private:
	CSharedPtr<class CCharacterLTUI>	m_LTUI;		// Level, HP, DashCount를 나타냄
	CSharedPtr<class CCharacterLBUI>	m_LBUI;		// Gold, Satiety를 나타냄
	CSharedPtr<class CCharacterHitUI>	m_HitUI;	// 피격 당할 때, 화면 붉은색

private:
	bool					m_DownKey;

public:
	ECharacterActionType GetActionType()	const
	{
		return m_ActionType;
	}

	int GetLevel()	const
	{
		return m_Level;
	}

	int GetHP()	const
	{
		return m_HP;
	}

	int GetHPMax()	const
	{
		return m_HPMax;
	}

	int GetPower()	const
	{
		return m_Power;
	}

	int GetArmor()	const
	{
		return m_Armor;
	}

	int GetDashCount()	const
	{
		return m_DashCount;
	}

	int GetGold()	const
	{
		return m_Gold;
	}

	int GetSatiety()	const
	{
		return m_Satiety;
	}

	int GetSatietyMax()	const
	{
		return m_SatietyMax;
	}

public:
	void SetActionType(ECharacterActionType Type)
	{
		m_ActionType = Type;
	}

	void SetLevel(int Level)
	{
		m_Level = Level;
	}

	void SetHP(int HP)
	{
		int _HP = HP;

		if (_HP > m_HPMax)
			_HP = m_HPMax;

		m_HP = _HP;
	}

	void SetHPMax(int HPMax)
	{
		m_HPMax = HPMax;
	}

	void SetPower(int Power)
	{
		m_Power = Power;
	}

	void SetArmor(int Armor)
	{
		m_Armor = Armor;
	}

	void SetDashCount(int DashCount)
	{
		m_DashCount = DashCount;
	}

	void SetGold(int Gold)
	{
		m_Gold = Gold;
	}

	void SetSatiety(int Satiety)
	{
		m_Satiety = Satiety;
	}

	void SetSatietyMax(int SatietyMax)
	{
		m_SatietyMax = SatietyMax;
	}

	void SetCharacterPosition(const Vector2& Position);

public:
	virtual int InflictDamage(int Damage);
	void AddGold(int Gold);
	void AddSatiety(int Satiety);

public:
	void AddBindFunction();
	void DeleteBindFunction();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CCharacter* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);

private:
	void UpKey();
	void DownKey();
	void DownKeyCancel();
	void LeftKey();
	void RightKey();
	void Jump();
	void Dash();
	void Attack();
};

