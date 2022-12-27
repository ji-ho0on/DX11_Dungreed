#include "BelialBackAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CBelialBackAnimation::CBelialBackAnimation()
{
	m_ClassName = "BelialBackAnimation";
}

CBelialBackAnimation::CBelialBackAnimation(const CBelialBackAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBelialBackAnimation::~CBelialBackAnimation()
{
}

void CBelialBackAnimation::Start()
{
	CAnimation2D::Start();

	//CAnimation2DData* WeaponEffect = FindAnimation("WeaponEffect");

	//if (WeaponEffect)
	//	WeaponEffect->SetEndFunction<CBelialBackAnimation>(this, &CBelialBackAnimation::ShortSwordSwingEnd);
}

bool CBelialBackAnimation::Init()
{
	AddAnimation("Idle", "BelialBack_Circle", 1.f, 1.f, true);

	return true;
}

void CBelialBackAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBelialBackAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBelialBackAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBelialBackAnimation* CBelialBackAnimation::Clone()
{
	return new CBelialBackAnimation(*this);
}