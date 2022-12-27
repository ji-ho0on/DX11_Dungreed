#pragma once

#include "Scene\SceneInfo.h"

class CBossEntranceScene :
    public CSceneInfo
{
public:
    CBossEntranceScene();
    CBossEntranceScene(const CBossEntranceScene& SceneInfo);
    ~CBossEntranceScene();

private:
    CSharedPtr<class CBossEntranceMap>  m_BossEntranceMap;

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

