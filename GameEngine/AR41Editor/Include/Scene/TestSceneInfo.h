#pragma once

#include "Scene\SceneInfo.h"

class CTestSceneInfo :
    public CSceneInfo
{
public:
    CTestSceneInfo();
    ~CTestSceneInfo();

public:
    virtual bool Init();
};

