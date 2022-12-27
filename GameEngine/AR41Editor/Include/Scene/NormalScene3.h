#pragma once

#include "Scene\SceneInfo.h"

class CNormalScene3 :
    public CSceneInfo
{
public:
    CNormalScene3();
    CNormalScene3(const CNormalScene3& SceneInfo);
    ~CNormalScene3();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

