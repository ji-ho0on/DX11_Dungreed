#pragma once

#include "Scene\SceneInfo.h"

class CNormalScene :
    public CSceneInfo
{
public:
    CNormalScene();
    CNormalScene(const CNormalScene& SceneInfo);
    ~CNormalScene();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void SceneChangeComplete();
};

