#include "SceneInfo.h"
#include "../GameObject/GameObject.h"
#include "Scene.h"

CSceneInfo::CSceneInfo()	:
	m_MonsterClear(false)
{
	m_ClassTypeName = "SceneInfo";
}

CSceneInfo::CSceneInfo(const CSceneInfo& Info)
{
	m_ClassTypeName = Info.m_ClassTypeName;
}

CSceneInfo::~CSceneInfo()
{
}

void CSceneInfo::PushMonsterList(CGameObject* Monster)
{
	m_MonsterList.push_back(Monster);
}

void CSceneInfo::DeleteMonsterList(CGameObject* Monster)
{
	auto iter = m_MonsterList.begin();
	auto iterEnd = m_MonsterList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == Monster)
		{
			m_MonsterList.erase(iter);
			break;
		}
	}
}

void CSceneInfo::SetPlayerObject(CGameObject* Player)
{
	m_PlayerObject = Player;

	if (Player)
		m_PlayerObjectName = Player->GetName();
}

void CSceneInfo::LoadComplete()
{
	// 플레이어 이름을 이용해서 플레이어를 얻어온다.
	if (!m_PlayerObjectName.empty())
		m_PlayerObject = m_Owner->FindObject(m_PlayerObjectName);
}

void CSceneInfo::Start()
{
	if (m_MonsterClear)
	{
		auto iter = m_MonsterList.begin();
		auto iterEnd = m_MonsterList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Destroy();
		}
	}
}

bool CSceneInfo::Init()
{
	return true;
}

void CSceneInfo::Update(float DeltaTime)
{
}

void CSceneInfo::PostUpdate(float DeltaTime)
{
}

CSceneInfo* CSceneInfo::Clone()
{
	return new CSceneInfo(*this);
}

void CSceneInfo::Save(FILE* File)
{
	// 클래스 타입 저장
	int	Length = (int)m_ClassTypeName.length();

	fwrite(&Length, 4, 1, File);
	fwrite(m_ClassTypeName.c_str(), 1, Length, File);

	fwrite(&m_MonsterClear, sizeof(bool), 1, File);

	bool	PlayerEnable = false;

	if (m_PlayerObject)
		PlayerEnable = true;

	fwrite(&PlayerEnable, 1, 1, File);

	if (PlayerEnable)
	{
		Length = (int)m_PlayerObject->GetName().length();

		fwrite(&Length, 4, 1, File);
		fwrite(m_PlayerObject->GetName().c_str(), 1, Length, File);
	}
}

void CSceneInfo::Load(FILE* File)
{
	fread(&m_MonsterClear, sizeof(bool), 1, File);

	bool	PlayerEnable = false;

	fread(&PlayerEnable, 1, 1, File);

	if (PlayerEnable)
	{
		int Length = 0;

		char	Name[256] = {};

		fread(&Length, 4, 1, File);
		fread(Name, 1, Length, File);

		m_PlayerObjectName = Name;
	}
}

void CSceneInfo::SceneChangeComplete()
{
}
