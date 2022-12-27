#include "Horse.h"
#include "Component/SpriteComponent.h"
#include "../Animation2D/HorseAnimation.h"
#include "../Animation2D/CharacterAnimation.h"

CHorse::CHorse()
{
	SetTypeID<CHorse>();

	m_ObjectTypeName = "Horse";
}

CHorse::CHorse(const CHorse& Obj) :
	CGameObject(Obj)
{
	m_Horse = (CSpriteComponent*)FindComponent("Horse");
	m_Character = (CSpriteComponent*)FindComponent("Character");
}

CHorse::~CHorse()
{
}

void CHorse::Start()
{
	CGameObject::Start();
}

bool CHorse::Init()
{
	CGameObject::Init();

	m_Horse = CreateComponent<CSpriteComponent>("Horse");
	m_Horse->SetWorldPosition(50.f, 192.f);
	m_Horse->SetWorldScale(480.f, 152.f);
	m_Horse->SetAnimation<CHorseAnimation>("HorseAnimation");

	m_Character = CreateComponent<CSpriteComponent>("Character");
	m_Character->SetWorldScale(60.f, 80.f);
	m_Character->SetRelativePosition(370.f, 80.f);
	m_Character->SetAnimation<CCharacterAnimation>("CharacterAnimation");
	m_Character->SetDir(EDirection::Left);

	m_Horse->AddChild(m_Character);


	return true;
}

void CHorse::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CHorse::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CHorse* CHorse::Clone() const
{
	return new CHorse(*this);
}