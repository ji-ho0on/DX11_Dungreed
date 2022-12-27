#pragma once

#include "UI\UIWindow.h"

class CCharacterLBUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CCharacterLBUI();
	CCharacterLBUI(const CCharacterLBUI& Window);
	virtual ~CCharacterLBUI();

private:
	class CUIImage*			m_GoldImage;
	class CUIText*			m_Gold;

	class CUIImage*			m_FoodImage;
	class CUIText*			m_Satiety;
	class CUIText*			m_SatietySlash;
	class CUIText*			m_SatietyMax;

public:
	void SetGold(int Gold);
	void SetSatiety(int Satiety);
	void SetSatietyMax(int SatietyMax);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CCharacterLBUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

