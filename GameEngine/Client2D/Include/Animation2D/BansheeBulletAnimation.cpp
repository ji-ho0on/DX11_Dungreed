#include "BansheeBulletAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CBansheeBulletAnimation::CBansheeBulletAnimation()
{
	m_ClassName = "BansheeAnimation";
}

CBansheeBulletAnimation::CBansheeBulletAnimation(const CBansheeBulletAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBansheeBulletAnimation::~CBansheeBulletAnimation()
{
}

void CBansheeBulletAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Destroy = FindAnimation("Destroy");

	if (Destroy)
	{
		Destroy->SetEndFunction<CBansheeBulletAnimation>(this, &CBansheeBulletAnimation::DestroyEnd);
	}
}

bool CBansheeBulletAnimation::Init()
{
	AddAnimation("Idle", "BansheeBullet_Idle", 1.f, 1.f, true);
	AddAnimation("Destroy", "BansheeBullet_Destroy", 1.f, 2.f, false);

	return true;
}

void CBansheeBulletAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBansheeBulletAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBansheeBulletAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBansheeBulletAnimation* CBansheeBulletAnimation::Clone()
{
	return new CBansheeBulletAnimation(*this);
}

void CBansheeBulletAnimation::DestroyEnd()
{
	m_Owner->GetOwner()->Destroy();
}