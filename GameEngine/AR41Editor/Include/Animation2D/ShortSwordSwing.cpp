#include "ShortSwordSwing.h"
#include "Component/SpriteComponent.h"
#include "GameObject/GameObject.h"

CShortSwordSwing::CShortSwordSwing()
{
	m_ClassName = "ShortSwordSwing";
}

CShortSwordSwing::CShortSwordSwing(const CShortSwordSwing& Anim) :
	CAnimation2D(Anim)
{
}

CShortSwordSwing::~CShortSwordSwing()
{
}

void CShortSwordSwing::Start()
{
	CAnimation2D::Start();

	CAnimation2DData* WeaponEffect = FindAnimation("WeaponEffect");

	if (WeaponEffect)
		WeaponEffect->SetEndFunction<CShortSwordSwing>(this, &CShortSwordSwing::ShortSwordSwingEnd);
}

bool CShortSwordSwing::Init()
{
	AddAnimation("WeaponEffect", "ShortSwordSwing", 0.25f, 1.f, false);

	return true;
}

void CShortSwordSwing::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

void CShortSwordSwing::Save(FILE* File)
{
	CAnimation2D::Save(File);
}

void CShortSwordSwing::Load(FILE* File)
{
	CAnimation2D::Load(File);
}

CShortSwordSwing* CShortSwordSwing::Clone()
{
	return new CShortSwordSwing(*this);
}

void CShortSwordSwing::ShortSwordSwingEnd()
{
	m_Owner->GetOwner()->Destroy();
}
