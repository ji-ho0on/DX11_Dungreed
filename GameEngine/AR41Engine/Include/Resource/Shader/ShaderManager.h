#pragma once

#include "../../EngineInfo.h"

class CShaderManager
{
	friend class CResourceManager;

private:
	CShaderManager();
	~CShaderManager();

private:
	std::unordered_map<std::string, CSharedPtr<class CShader>>			m_mapShader;				// 셰이더 맵
	std::unordered_map<std::string, CSharedPtr<class CShader>>			m_mapGlobalShader;			// 글로벌로 사용할 셰이더 맵
	std::unordered_map<std::string, CSharedPtr<class CConstantBuffer>>	m_mapCBuffer;				// 상수 버퍼 맵
	class CColliderConstantBuffer*										m_ColliderCBuffer;			// 충돌체용 상수 버퍼
	class CColliderLine2DConstantBuffer*								m_ColliderLine2DCBuffer;	// 선충돌체용 상수 버퍼

public:
	class CColliderConstantBuffer* GetColliderCBuffer()	const
	{
		return m_ColliderCBuffer;
	}

	class CColliderLine2DConstantBuffer* GetColliderLine2DCBuffer()	const
	{
		return m_ColliderLine2DCBuffer;
	}

public:
	bool Init();
	class CShader* FindShader(const std::string& Name);
	void ReleaseShader(const std::string& Name);

	bool CreateConstantBuffer(const std::string& Name, int Size, int Register,
		int ShaderBufferType = (int)EShaderBufferType::All);
	class CConstantBuffer* FindConstantBuffer(const std::string& Name);

public:
	template <typename T>
	bool CreateShader(const std::string& Name, bool GlobalShader = false)
	{
		T* Shader = (T*)FindShader(Name);

		if (Shader)
			return true;

		Shader = new T;

		Shader->SetName(Name);

		if (!Shader->Init())
		{
			SAFE_DELETE(Shader);
			return false;
		}

		m_mapShader.insert(std::make_pair(Name, Shader));

		if (GlobalShader)
			m_mapGlobalShader.insert(std::make_pair(Name, Shader));

		return true;
	}
};

