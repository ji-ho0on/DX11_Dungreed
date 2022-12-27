#pragma once

#include "Scene\SceneInfo.h"

class CNormalScene6 :
    public CSceneInfo
{
public:
    CNormalScene6();
    CNormalScene6(const CNormalScene6& SceneInfo);
    ~CNormalScene6();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

