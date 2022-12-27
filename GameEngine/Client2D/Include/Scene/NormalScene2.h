#pragma once

#include "Scene/SceneInfo.h"

class CNormalScene2 :
    public CSceneInfo
{
public:
    CNormalScene2();
    CNormalScene2(const CNormalScene2& SceneInfo);
    ~CNormalScene2();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

