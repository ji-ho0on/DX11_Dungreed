#pragma once

#include "../EngineInfo.h"

class CSceneInfo
{
	friend class CScene;
	friend class CSceneManager;

protected:
	CSceneInfo();
	CSceneInfo(const CSceneInfo& Info);
	virtual ~CSceneInfo();

protected:
	class CScene*					m_Owner;
	CSharedPtr<class CGameObject>	m_PlayerObject;
	std::string						m_ClassTypeName;
	std::string						m_PlayerObjectName;

protected:
	std::list<CSharedPtr<class CGameObject>>	m_MonsterList;
	bool										m_MonsterClear;

public:
	virtual void PushMonsterList(class CGameObject* Monster);
	virtual void DeleteMonsterList(class CGameObject* Monster);

public:
	void SetMonsterClear(bool Clear)
	{
		m_MonsterClear = Clear;
	}

	bool GetMonsterClear()	const
	{
		return m_MonsterClear;
	}

protected:
	void SetClassTypeName(const std::string& Name)
	{
		m_ClassTypeName = Name;
	}

public:
	const std::string& GetClassTypeName()	const
	{
		return m_ClassTypeName;
	}

public:
	class CGameObject* GetPlayerObject()	const
	{
		return m_PlayerObject;
	}

public:
	void SetPlayerObject(class CGameObject* Player);
	void LoadComplete();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSceneInfo* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void SceneChangeComplete();
};

