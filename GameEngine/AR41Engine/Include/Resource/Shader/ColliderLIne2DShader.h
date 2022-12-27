#pragma once

#include "GraphicShader.h"

class CColliderLIne2DShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CColliderLIne2DShader();
    virtual ~CColliderLIne2DShader();

public:
    virtual bool Init();
};

