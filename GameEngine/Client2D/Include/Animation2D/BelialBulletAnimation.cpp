#include "BelialBulletAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CBelialBulletAnimation::CBelialBulletAnimation()
{
	m_ClassName = "BelialBulletAnimation";
}

CBelialBulletAnimation::CBelialBulletAnimation(const CBelialBulletAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBelialBulletAnimation::~CBelialBulletAnimation()
{
}

void CBelialBulletAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Destroy = FindAnimation("Destroy");

	if (Destroy)
		Destroy->SetEndFunction<CBelialBulletAnimation>(this, &CBelialBulletAnimation::DestroyEnd);
}

bool CBelialBulletAnimation::Init()
{
	AddAnimation("Idle", "BelialBullet_Idle", 1.f, 1.f, true);
	AddAnimation("Destroy", "BelialBullet_Destroy", 1.f, 2.f, false);

	return true;
}

void CBelialBulletAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBelialBulletAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBelialBulletAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBelialBulletAnimation* CBelialBulletAnimation::Clone()
{
	return new CBelialBulletAnimation(*this);
}

void CBelialBulletAnimation::DestroyEnd()
{
	m_Owner->GetOwner()->Destroy();
}
