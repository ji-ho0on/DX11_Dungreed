#pragma once

#include "Scene\SceneInfo.h"

class CEndingScene :
    public CSceneInfo
{
public:
    CEndingScene();
    CEndingScene(const CEndingScene& SceneInfo);
    ~CEndingScene();

private:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

