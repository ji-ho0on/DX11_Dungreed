#pragma once

#include "Scene/SceneInfo.h"

class CNormalScene1 :
    public CSceneInfo
{
public:
    CNormalScene1();
    CNormalScene1(const CNormalScene1& SceneInfo);
    ~CNormalScene1();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

