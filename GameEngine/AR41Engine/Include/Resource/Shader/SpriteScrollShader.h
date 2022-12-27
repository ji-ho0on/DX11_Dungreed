#pragma once

#include "GraphicShader.h"

class CSpriteScrollShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CSpriteScrollShader();
    virtual ~CSpriteScrollShader();

public:
    virtual bool Init();
};

