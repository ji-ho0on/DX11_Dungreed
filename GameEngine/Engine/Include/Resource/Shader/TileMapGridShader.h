#pragma once

#include "GraphicShader.h"

class CTileMapGridShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CTileMapGridShader();
    virtual ~CTileMapGridShader();

public:
    virtual bool Init();
};

