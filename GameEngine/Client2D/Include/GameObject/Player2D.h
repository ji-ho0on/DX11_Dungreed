#pragma once

#include "GameObject/GameObject.h"

class CPlayer2D :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& Obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;
	//CSharedPtr<class CColliderOBB2D>	m_Body;
	//CSharedPtr<class CColliderSphere2D>	m_Body;
	CSharedPtr<class CColliderLine2D>	m_Line;
	CSharedPtr<class CSceneComponent>	m_SpriteChild;
	CSharedPtr<class CSpriteComponent>	m_SpriteChildChild;
	CSharedPtr<class CGravityAgent>	m_Gravity;

	// �÷��̾� �������� ȭ���� �����̰� �� ī�޶�� Offset������ ���� ī�޶� Arm
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>		m_Arm;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer2D* Clone()    const;

private:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Rotation();
	void RotationInv();
	void Fire();
	void Shotgun();
	void Jump();
};

