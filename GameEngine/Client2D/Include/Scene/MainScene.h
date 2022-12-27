#pragma once

#include "Scene\SceneInfo.h"

class CMainScene :
    public CSceneInfo
{
public:
    CMainScene();
    CMainScene(const CMainScene& SceneInfo);
    ~CMainScene();

private:
    CSharedPtr<class CMainUI>       m_MainUI;
    CSharedPtr<class CPlaySlotUI>   m_PlaySlotUI;
    CSharedPtr<class CSettingUI>    m_SettingUI;

    CSharedPtr<class CFrontCloud>   m_FrontCloud1;
    CSharedPtr<class CFrontCloud>   m_FrontCloud2;
    CSharedPtr<class CBackCloud>    m_BackCloud1;
    CSharedPtr<class CBackCloud>    m_BackCloud2;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();

private:
    void CreateBird(const Vector2& Pos);
    void CreateBirds(const Vector2& Pos);
};

