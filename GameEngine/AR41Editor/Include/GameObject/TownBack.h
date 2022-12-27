#pragma once

#include "GameObject\GameObject.h"

class CTownBack :
    public CGameObject
{
	friend class CScene;

protected:
	CTownBack();
	CTownBack(const CTownBack& Obj);
	virtual ~CTownBack();

private:
	//CSharedPtr<class CSpriteComponent>	m_TownCloud;
	//CSharedPtr<class CSpriteComponent>	m_TownForest1;
	//CSharedPtr<class CSpriteComponent>	m_TownForest2;
	CSharedPtr<class CTileMapComponent>	m_TownTileMap;
	CSharedPtr<class CSpriteComponent>	m_TownFloor;
	CSharedPtr<class CSpriteComponent>	m_TrainingSchool;
	CSharedPtr<class CSpriteComponent>	m_StreetLight0_1;
	CSharedPtr<class CSpriteComponent>	m_Target;
	CSharedPtr<class CSpriteComponent>	m_Tree1_1;
	CSharedPtr<class CSpriteComponent>	m_Wagon;
	CSharedPtr<class CSpriteComponent>	m_Boutique;
	CSharedPtr<class CSpriteComponent>	m_Grass2_1;
	CSharedPtr<class CSpriteComponent>	m_StreetLight0_2;
	CSharedPtr<class CSpriteComponent>	m_Grass1_1;
	CSharedPtr<class CSpriteComponent>	m_Tree1_2;
	//CSharedPtr<class CSpriteComponent>	m_Grass0;
	//CSharedPtr<class CSpriteComponent>	m_Grass1_1;
	//CSharedPtr<class CSpriteComponent>	m_Grass1_2;
	//CSharedPtr<class CSpriteComponent>	m_Grass2_1;
	//CSharedPtr<class CSpriteComponent>	m_Grass2_2;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CTownBack* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

