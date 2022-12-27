#include "BelialSwordAnimation.h"
#include "Component/SpriteComponent.h"
//#include "GameObject/GameObject.h"

CBelialSwordAnimation::CBelialSwordAnimation()
{
	m_ClassName = "BelialSwordAnimation";
}

CBelialSwordAnimation::CBelialSwordAnimation(const CBelialSwordAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBelialSwordAnimation::~CBelialSwordAnimation()
{
}

void CBelialSwordAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Sword = FindAnimation("Hit");

	if (Sword)
		Sword->SetEndFunction<CBelialSwordAnimation>(this, &CBelialSwordAnimation::HitEnd);
}

bool CBelialSwordAnimation::Init()
{
	AddAnimation("Charge", "BelialSword_Charge", 0.5f, 1.f, true);
	AddAnimation("Hit", "BelialSword_Hit", 1.f, 1.f, false);

	return true;
}

void CBelialSwordAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBelialSwordAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBelialSwordAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBelialSwordAnimation* CBelialSwordAnimation::Clone()
{
	return new CBelialSwordAnimation(*this);
}

void CBelialSwordAnimation::HitEnd()
{
	m_Owner->SetEnable(false);
}
