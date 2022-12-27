#pragma once

#include "ObjectComponent.h"

class CGravityAgent :
    public CObjectComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CGravityAgent();
    CGravityAgent(const CGravityAgent& Component);
    virtual ~CGravityAgent();

private:
    CSharedPtr<class CSceneComponent>   m_UpdateComponent;  // 중력을 적용시킬 Component를 받아둠
    CSharedPtr<class CTileMapComponent> m_TileMap;          // 현재 Scene에서 충돌시킬 TileMap을 받아둠
    Vector2                             m_Pos;
    Vector2                             m_PrevPos;
    Vector2                             m_Move;
    Vector2                             m_BodySize;         // 충돌체의 Size;
    Vector2                             m_BodyPivot;        // 충돌체의 Pivot;
    bool                                m_PhysicsSimulate;
    bool		                        m_GroundCheck;      // 땅을 밟았는지 체크
    bool                                m_Ground;           // 땅을 밟고있는 상태인지
    bool                                m_OneWayThrough;     // OneWay를 통과할 것인지
    float                               m_OneWayTime;
    float		                        m_GravityAccel;
    float		                        m_FallTime;
    float		                        m_FallStartY;
    bool		                        m_Jump;
    float		                        m_JumpVelocity;

    // 공중에 떠있다는 변수를 하나 줘서 Move.y 값이 미세한 값 말고 일정이상이면 바꿔준다.

public:
    class CSceneComponent* GetUpdateComponent() const
    {
        return m_UpdateComponent;
    }

    const Vector2& GetMove()    const
    {
        return m_Move;
    }

    bool IsPhysicsSimulate()    const
    {
        return m_PhysicsSimulate;
    }

    bool IsJump()   const
    {
        return m_Jump;
    }

    bool IsGround() const
    {
        return m_Ground;
    }

    float GetFallTime() const
    {
        return m_FallTime;
    }

public:
    void SetUpdateComponent(class CSceneComponent* Component);

    void SetFallStartY(float y)
    {
        m_FallStartY = y;
    }

    void SetFallTime(float FallTime)
    {
        m_FallTime = FallTime;
    }

    void SetPhysicsSimulate(bool Physics)
    {
        m_PhysicsSimulate = Physics;
    }

    void SetGroundCheck(bool Ground)
    {
        m_GroundCheck = Ground;
    }

    void SetOneWayThrough(bool Through)
    {
        m_OneWayThrough = Through;
    }

    void SetGravityAccel(float Accel)
    {
        m_GravityAccel = Accel;
    }

    void SetJumpVelocity(float JumpVelocity)
    {
        m_JumpVelocity = JumpVelocity;
    }

    void SetJump(bool Jump)
    {
        m_Jump = Jump;
    }

public:
    void Jump();

private:
    void CheckMoveRight();
    void CheckMoveLeft();

public:
    virtual void Destroy();
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CGravityAgent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

