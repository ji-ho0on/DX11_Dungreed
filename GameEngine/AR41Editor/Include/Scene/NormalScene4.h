#pragma once

#include "Scene\SceneInfo.h"

class CNormalScene4 :
    public CSceneInfo
{
public:
    CNormalScene4();
    CNormalScene4(const CNormalScene4& SceneInfo);
    ~CNormalScene4();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void SceneChangeComplete();
};

