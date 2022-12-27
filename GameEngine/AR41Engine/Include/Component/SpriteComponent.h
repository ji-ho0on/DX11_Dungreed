#pragma once

#include "PrimitiveComponent.h"
#include "../Animation/Animation2D.h"

class CSpriteComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;
    friend class CScene;

protected:
    CSpriteComponent();
    CSpriteComponent(const CSpriteComponent& component);
    virtual ~CSpriteComponent();

protected:
    CSharedPtr<CAnimation2D>    m_Animation;
    EDirection                  m_Dir;

public:
    void SetDir(EDirection Dir)
    {
        m_Dir = Dir;
    }

public:
    EDirection GetDir() const
    {
        return m_Dir;
    }

    CAnimation2D* GetAnimation()    const;

public:
    bool SetTexture(class CTexture* Texture);
    bool SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
    bool SetTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
    bool SetTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    bool SetTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName = TEXTURE_PATH);
    bool SetTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    void SetTextureFrameIndex(int Index);

    class CTexture* GetTexture(int Index = 0)    const;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CSpriteComponent* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);

public:
    template <typename T>
    T* SetAnimation(const std::string& Name)
    {
        T* Anim = new T;

        Anim->SetName(Name);
        Anim->m_Owner = this;

        if (!Anim->Init())
        {
            SAFE_DELETE(Anim);
            return nullptr;
        }

        m_Animation = Anim;

        return Anim;
    }

    void SetAnimationByCDO(CAnimation2D* Animation);
};

