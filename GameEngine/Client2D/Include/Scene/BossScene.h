#pragma once

#include "Scene\SceneInfo.h"

class CBossScene :
    public CSceneInfo
{
public:
    CBossScene();
    CBossScene(const CBossScene& SceneInfo);
    ~CBossScene();

private:
    CSharedPtr<class CBossMap>  m_BossMap;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

