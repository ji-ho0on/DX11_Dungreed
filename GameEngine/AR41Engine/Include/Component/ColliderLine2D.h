#pragma once

#include "Collider2D.h"

class CColliderLine2D :
    public CCollider2D
{
    friend class CGameObject;
    friend class CScene;

protected:
    CColliderLine2D();
    CColliderLine2D(const CColliderLine2D& component);
    virtual ~CColliderLine2D();

protected:
    Vector2     m_RelativeDestPoint;
    Line2DInfo  m_Info;

public:
    const Line2DInfo& GetInfo()  const
    {
        return m_Info;
    }

    const Vector2& GetRelativeDestPoint() const
    {
        return m_RelativeDestPoint;
    }

public:
    void SetRelativeDestPoint(const Vector2& Point);
    void SetRelativeDestPoint(float x, float y);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CColliderLine2D* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
    virtual bool Collision(CCollider* Dest);
    virtual bool CollisionMouse(const Vector2& MouseWorldPos);
};

