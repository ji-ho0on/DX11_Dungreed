#pragma once

#include "UI\UIWindow.h"

class CBossUI :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CBossUI();
	CBossUI(const CBossUI& Window);
	virtual ~CBossUI();

private:
	class CUIImage*			m_HPBack;
	class CUIProgressBar*	m_HPBar;
	class CUIImage*			m_HPBase;
	class CUIImage*			m_BossImage;

public:
	void SetHP(int HP);
	void SetHPMax(int HPMax);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CBossUI* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

