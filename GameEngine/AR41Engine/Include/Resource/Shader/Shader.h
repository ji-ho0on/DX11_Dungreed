#pragma once

#include "../../Ref.h"

class CShader :
    public CRef
{
    friend class CShaderManager;

protected:
    CShader();
    virtual ~CShader() = 0;

protected:
    EShaderType m_ShaderType;

public:
    EShaderType GetShaderType()  const
    {
        return m_ShaderType;
    }

public:
    virtual bool Init() = 0;
    virtual void SetShader() = 0;
};