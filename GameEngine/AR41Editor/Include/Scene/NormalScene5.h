#pragma once

#include "Scene\SceneInfo.h"

class CNormalScene5 :
    public CSceneInfo
{
public:
    CNormalScene5();
    CNormalScene5(const CNormalScene5& SceneInfo);
    ~CNormalScene5();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

