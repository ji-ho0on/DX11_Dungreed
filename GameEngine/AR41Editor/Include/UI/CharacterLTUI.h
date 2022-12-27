#pragma once

#include "UI\UIWindow.h"

class CCharacterLTUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CCharacterLTUI();
	CCharacterLTUI(const CCharacterLTUI& Window);
	virtual ~CCharacterLTUI();

private:
	class CUIImage*			m_HPBack;
	class CUIProgressBar*	m_HPBar;
	class CUIImage*			m_HPFront;
	class CUIText*			m_Level;
	class CUIText*			m_HP;
	class CUIText*			m_HPSlash;
	class CUIText*			m_HPMax;
	class CUIImage*			m_DashBack1;
	class CUIImage*			m_DashBack2;
	class CUIImage*			m_DashBack3;
	class CUIImage*			m_DashBack4;
	class CUIImage*			m_DashBack5;

	int						m_DashCount;

	class CUIImage*			m_DashCount1;
	class CUIImage*			m_DashCount2;
	class CUIImage*			m_DashCount3;
	class CUIImage*			m_DashCount4;

public:
	void SetLevel(int Level);
	void SetHP(int HP);
	void SetHPMax(int HPMax);
	void SetDashCount(int DashCount);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CCharacterLTUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

