#pragma once

#include "Scene\SceneInfo.h"

class CTownScene :
    public CSceneInfo
{
public:
    CTownScene();
    CTownScene(const CTownScene& SceneInfo);
    ~CTownScene();

private:
    

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

