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

// Component��
private:
	CSharedPtr<class CSpriteComponent>	m_Character;
	CSharedPtr<class CColliderBox2D>	m_Body;

	// �÷��̾ ����� ����
	CSharedPtr<class CSpriteComponent>	m_Weapon;

	// �÷��̾� �������� ȭ���� �����̰� �� ī�޶�� Offset������ ���� ī�޶� Arm
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>		m_Arm;

	// �߷��� �����ų ObjectComponent
	CSharedPtr<class CGravityAgent>		m_Gravity;

// Character�� �ɷ�ġ
private:
	EDirection				m_Direction;		// ĳ���Ͱ� �ٶ󺸴� ����
	ECharacterActionType	m_ActionType;		// ĳ���� �ൿŸ��, Idle, Run, Jump, Die
	EWeaponType				m_CurrentWeapon;	// ĳ���Ͱ� ���� �������� ����
	EWeaponType				m_EquippedWeapon1;	// ĳ���Ͱ� ���� ���� 1��
	EWeaponType				m_EquippedWeapon2;	// ĳ���Ͱ� ���� ���� 2��

	float					m_MouseAngleRight;	// ������ ������ �� ĳ���Ϳ� ���콺�� ����
	float					m_MouseAngleLeft;	// ���� ������ �� ĳ���Ϳ� ���콺�� ����

	// ���Ⱑ ShortSword�� ���
	float					m_ShortSwordAngle[(int)EShortSwordState::End];	// ShortSword �⺻ Angle(Up�� Down�� �� ���� ����)
	EShortSwordState		m_ShortSwordState;	// ShortSword�� ����(��, �Ʒ�)

// Character�� �ɷ�ġ
private:
	int						m_Level;		// ����
	int						m_HPMax;		// �ִ�ü��
	int						m_Power;		// ���ݷ�
	int						m_Armor;		// ����
	int						m_DashCount;	// Dash�� ������ Ƚ��
	int						m_Gold;			// ���� ���
	int						m_Satiety;		// ������
	int						m_SatietyMax;	// �ִ�������

	// Run ���� ����
	float					m_StepTime;
	int						m_StepCount;

	// Dash ����
	bool					m_IsDash;		// Dash ��������
	Vector3					m_DashDir;		// Dash ����
	float					m_DashTime;
	float					m_DashCountCooldown;	// DashCount�� �����Ǵ� �ð�

// Character�� �ɷ�ġ�� ��Ÿ���� UI
private:
	CSharedPtr<class CCharacterLTUI>	m_LTUI;		// Level, HP, DashCount�� ��Ÿ��
	CSharedPtr<class CCharacterLBUI>	m_LBUI;		// Gold, Satiety�� ��Ÿ��
	CSharedPtr<class CCharacterHitUI>	m_HitUI;	// �ǰ� ���� ��, ȭ�� ������

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

