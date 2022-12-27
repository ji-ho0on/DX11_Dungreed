#include "BelialLaserAnimation.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CBelialLaserAnimation::CBelialLaserAnimation()
{
	m_ClassName = "BelialLaserAnimation";
}

CBelialLaserAnimation::CBelialLaserAnimation(const CBelialLaserAnimation& Anim) :
	CAnimation2D(Anim)
{
}

CBelialLaserAnimation::~CBelialLaserAnimation()
{
}

void CBelialLaserAnimation::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* Laser = FindAnimation("Head");

	if (Laser)
	{
		Laser->AddNotify<CBelialLaserAnimation>("ColliderDestroy", 5, this, &CBelialLaserAnimation::ColliderDestroy);
		Laser->SetEndFunction<CBelialLaserAnimation>(this, &CBelialLaserAnimation::LaserEnd);
	}
}

bool CBelialLaserAnimation::Init()
{
	AddAnimation("Head", "BelialLaser_Head", 0.5f, 1.f, false);
	AddAnimation("Body", "BelialLaser_Body", 0.5f, 1.f, false);

	return true;
}

void CBelialLaserAnimation::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CBelialLaserAnimation::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CBelialLaserAnimation::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CBelialLaserAnimation* CBelialLaserAnimation::Clone()
{
	return new CBelialLaserAnimation(*this);
}

void CBelialLaserAnimation::ColliderDestroy()
{
	m_Owner->GetOwner()->FindComponent("Body")->SetEnable(false);
}

void CBelialLaserAnimation::LaserEnd()
{
	m_Owner->GetOwner()->Destroy();
}
