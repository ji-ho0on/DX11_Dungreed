#pragma once

#include "ComponentWidgetList.h"

class CSpriteComponentWidgetList :
    public CComponentWidgetList
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;
	friend class CDetailWindow;

protected:
	CSpriteComponentWidgetList();
	virtual ~CSpriteComponentWidgetList();

private:
	CSharedPtr<class CAnimation2D>	m_Animation;

	class CEditorInput*				m_AnimationClass;
	class CEditorInput*				m_SelectAnimationClass;

	class CEditorInput*				m_CurrentAnimationData;

	class CEditorInput*				m_PlayTime;
	class CEditorInput*				m_PlayScale;
	class CEditorCheckBox*			m_LoopCheck;
	class CEditorCheckBox*			m_ReverseCheck;

	class CEditorListBox*			m_AnimationDataListBox;
	std::string						m_SelectAnimationDataItem;

	class CEditorInput*				m_SelectChangeAnimationData;

public:
	virtual bool Init();
	virtual void SetComponentContents(class CSceneComponent* Component);

public:
	void SetSelectAnimationClass(const std::string& AnimationClassName);

private:
	void SetAnimation();
	void SetPlayTime();
	void SetPlayScale();
	void SetLoop();
	void SetReverse();
	void AnimationDataListBoxClickCallback(int Index, const std::string& Item);
	void AnimationChangeButton();
};

