#pragma once

#include "Editor\EditorWindow.h"

class CAnimation2DWindow :
    public CEditorWindow
{
	friend class CEditorGUIManager;

protected:
	CAnimation2DWindow();
	virtual ~CAnimation2DWindow();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

protected:
	CSharedPtr<class CSpriteComponent>			m_SelectComponent;

	// Sequence
	CSharedPtr<class CAnimationSequence2D>		m_Sequence;

	std::string									m_CurrentSequenceName;

	class CEditorListBox*						m_SequenceListBox;
	std::string									m_SelectSequenceItem;

	class CEditorInput*							m_SelectSequenceNameInput;

	class CEditorListBox*						m_FrameDataListBox;

	int											m_CurrentFrameIndex;
	class CEditorImage*							m_CurrentFrameImage;

	bool										m_CurrentSequencePlay;
	float										m_PlayTime;
	float										m_SettingPlayTime;

	class CEditorSlider*						m_SequencePreviewSlider;

	// Animation
	class CEditorInput*							m_AddAnimatoinNameInput;	// Sprite쪽으로 옮겨야함.(근데 이미 세팅된 애니메이션을 쓸텐데 굳이 쓸까...?)

	class CEditorListBox*						m_AnimationClassListBox;
	std::string									m_SelectAnimationClassItem;

public:
	void SetSelectComponent(class CSpriteComponent* Component);
	void SetSequence(class CAnimationSequence2D* Sequence);

private:
	void UpdateSequenceData(class CAnimationSequence2D* Sequence);

private:
	void ImageLoadButton();
	void SequenceCreateButton();
	void SequenceSaveButton();
	void SequenceListBoxClickCallback(int Index, const std::string& Item);
	void LoadSequenceDirectory();
	void SequenceChangeButton();
	void AddFrameButton();
	void EditFrameButton();
	void DeleteFrameButton();
	void FrameDataListBoxClickCallback(int Index, const std::string& Item);
	void PlayTimeSetButton();
	void CurrentSequencePlayButton();
	void AnimationAddButton();
	void AnimationClassListBoxClickCallback(int Index, const std::string& Item);
	void LoadAnimation2DDirectory();
};

