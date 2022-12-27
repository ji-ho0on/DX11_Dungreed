#include "SpriteComponentWidgetList.h"
#include "Component/SpriteComponent.h"
#include "../DetailWindow.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorNewLine.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorText.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorGUIManager.h"
#include "../Animation2DWindow.h"

// Animation
#include "Animation/Animation2D.h"

CSpriteComponentWidgetList::CSpriteComponentWidgetList()
{
}

CSpriteComponentWidgetList::~CSpriteComponentWidgetList()
{
}

bool CSpriteComponentWidgetList::Init()
{
	CEditorTree<void*>* SpriteComponentTree = CreateWidget<CEditorTree<void*>>("SpriteComponentTree");
	SpriteComponentTree->AddItem(nullptr, "SpriteComponent");
	SpriteComponentTree->FindItem("SpriteComponent")->AddFlag(ImGuiTreeNodeFlags_DefaultOpen);

	// Animation2D
	SpriteComponentTree->AddItem(nullptr, "Animation2D", "SpriteComponent");

	// AnimationClass
	CEditorGroup* AnimationClassGroup = CreateWidget<CEditorGroup>("AnimationClassGroup");

	CEditorText* AnimationClassText = AnimationClassGroup->CreateWidget<CEditorText>("AnimationClassText");
	AnimationClassText->SetText("AnimationClass");

	m_AnimationClass = AnimationClassGroup->CreateWidget<CEditorInput>("AnimationClass", 150.f, 30.f);
	m_AnimationClass->SetHideName(m_AnimationClass->GetName());
	m_AnimationClass->ReadOnly(true);

	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");

	CEditorGroup* AnimationclassSelectGroup = CreateWidget<CEditorGroup>("AnimationclassSelectGroup");

	CEditorText* SelectAnimationClassText = AnimationclassSelectGroup->CreateWidget<CEditorText>("SelectAnimationClassText");
	SelectAnimationClassText->SetText("SelectAnimationClass");

	m_SelectAnimationClass = AnimationclassSelectGroup->CreateWidget<CEditorInput>("SelectAnimationClass", 150.f, 30.f);
	m_SelectAnimationClass->SetHideName(m_SelectAnimationClass->GetName());
	m_SelectAnimationClass->ReadOnly(true);

	Line = AnimationclassSelectGroup->CreateWidget<CEditorSameLine>("Line");

	CEditorButton* AnimationClassSetButton = AnimationclassSelectGroup->CreateWidget<CEditorButton>("SetAnimation", 150.f, 30.f);
	AnimationClassSetButton->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::SetAnimation);


	// CurrentAnimationData
	CEditorGroup* CurrentAnimationGroup = CreateWidget<CEditorGroup>("CurrentAnimationGroup");

	CEditorText* CurrentAnimatoinText = CurrentAnimationGroup->CreateWidget<CEditorText>("CurrentAnimatoinText");
	CurrentAnimatoinText->SetText("CurrentAnimationData");

	m_CurrentAnimationData = CurrentAnimationGroup->CreateWidget<CEditorInput>("CurrentAnimationData", 150.f, 30.f);
	m_CurrentAnimationData->SetHideName(m_CurrentAnimationData->GetName());
	m_CurrentAnimationData->ReadOnly(true);


	CEditorNewLine* NewLine = CurrentAnimationGroup->CreateWidget<CEditorNewLine>("NewLine");


	// CurrentAnimationData Setting

	CEditorLabel* PlayTime = CurrentAnimationGroup->CreateWidget<CEditorLabel>("PlayTime", 100.f, 30.f);
	PlayTime->SetColor(29, 47, 73, 255);
	PlayTime->SetAlign(0.5f, 0.5f);

	Line = CurrentAnimationGroup->CreateWidget<CEditorSameLine>("Line");

	m_PlayTime = CurrentAnimationGroup->CreateWidget<CEditorInput>("PlayTimeInput", 60.f, 30.f);
	m_PlayTime->SetHideName(m_PlayTime->GetName());
	m_PlayTime->SetInputType(EImGuiInputType::Float);
	m_PlayTime->SetInputCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::SetPlayTime);


	CEditorLabel* PlayScale = CurrentAnimationGroup->CreateWidget<CEditorLabel>("PlayScale", 100.f, 30.f);
	PlayScale->SetColor(29, 47, 73, 255);
	PlayScale->SetAlign(0.5f, 0.5f);

	Line = CurrentAnimationGroup->CreateWidget<CEditorSameLine>("Line");

	m_PlayScale = CurrentAnimationGroup->CreateWidget<CEditorInput>("PlayScaleInput", 60.f, 30.f);
	m_PlayScale->SetHideName(m_PlayScale->GetName());
	m_PlayScale->SetInputType(EImGuiInputType::Float);
	m_PlayScale->SetInputCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::SetPlayScale);


	CEditorLabel* Loop = CurrentAnimationGroup->CreateWidget<CEditorLabel>("Loop", 100.f, 30.f);
	Loop->SetColor(29, 47, 73, 255);
	Loop->SetAlign(0.5f, 0.5f);

	Line = CurrentAnimationGroup->CreateWidget<CEditorSameLine>("Line");

	m_LoopCheck = CurrentAnimationGroup->CreateWidget<CEditorCheckBox>("LoopCheck");
	m_LoopCheck->SetHideName(m_LoopCheck->GetName());
	m_LoopCheck->SetCheckCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::SetLoop);


	CEditorLabel* Reverse = CurrentAnimationGroup->CreateWidget<CEditorLabel>("Reverse", 100.f, 30.f);
	Reverse->SetColor(29, 47, 73, 255);
	Reverse->SetAlign(0.5f, 0.5f);

	Line = CurrentAnimationGroup->CreateWidget<CEditorSameLine>("Line");

	m_ReverseCheck = CurrentAnimationGroup->CreateWidget<CEditorCheckBox>("ReverseCheck");
	m_ReverseCheck->SetHideName(m_ReverseCheck->GetName());
	m_ReverseCheck->SetCheckCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::SetReverse);


	Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetSpacing(20.f);


	CEditorGroup* ChangeAnimationGroup = CreateWidget<CEditorGroup>("ChangeAnimationGroup");


	CEditorText* ChangeAnimatoinText = ChangeAnimationGroup->CreateWidget<CEditorText>("ChangeAnimatoinText");
	ChangeAnimatoinText->SetText("AnimationDataList");

	m_AnimationDataListBox = ChangeAnimationGroup->CreateWidget<CEditorListBox>("AnimationDataListBox", 150.f);
	m_AnimationDataListBox->SetHideName(m_AnimationDataListBox->GetName());
	m_AnimationDataListBox->SetPageItemCount(6);
	m_AnimationDataListBox->SetSelectCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::AnimationDataListBoxClickCallback);


	Line = CreateWidget<CEditorSameLine>("Line");

	CEditorGroup* AnimationDataSelectGroup = CreateWidget<CEditorGroup>("AnimationDataSelectGroup");

	CEditorText* SelectAnimationText = AnimationDataSelectGroup->CreateWidget<CEditorText>("SelectAnimatoinText");
	SelectAnimationText->SetText("SelectAnimationData");

	m_SelectChangeAnimationData = AnimationDataSelectGroup->CreateWidget<CEditorInput>("SelectChangeAnimationData", 150.f, 30.f);
	m_SelectChangeAnimationData->SetHideName(m_SelectChangeAnimationData->GetName());
	m_SelectChangeAnimationData->ReadOnly(true);

	CEditorButton* AnimationChangeButton = AnimationDataSelectGroup->CreateWidget<CEditorButton>("ChangeAnimation", 150.f, 30.f);
	AnimationChangeButton->SetClickCallback<CSpriteComponentWidgetList>(this, &CSpriteComponentWidgetList::AnimationChangeButton);

    return true;
}

void CSpriteComponentWidgetList::SetComponentContents(CSceneComponent* Component)
{
	CSpriteComponent* SpriteComponent = (CSpriteComponent*)Component;

	CAnimation2D* Animation = SpriteComponent->GetAnimation();
	
	if (Animation)
	{
		m_Animation = Animation;

		m_AnimationClass->SetText(Animation->GetAnimationClassName().c_str());

		const CAnimation2DData* CurrentAnimation = Animation->GetCurrentAnimation();

		if (CurrentAnimation)
		{
			m_CurrentAnimationData->SetText(Animation->GetCurrentAnimationName().c_str());
			m_PlayTime->SetFloat(CurrentAnimation->GetPlayTime());
			m_PlayScale->SetFloat(CurrentAnimation->GetPlayScale());
			m_LoopCheck->SetCheck(CurrentAnimation->GetLoop());
			m_ReverseCheck->SetCheck(CurrentAnimation->GetReverse());


			CAnimation2DWindow* Animation2DWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CAnimation2DWindow>("Animation2DWindow");
			Animation2DWindow->SetSequence(CurrentAnimation->GetAnimationSequence());
		}

		else
		{
			m_CurrentAnimationData->SetText("");
			m_PlayTime->SetFloat(0.f);
			m_PlayScale->SetFloat(0.f);
			m_LoopCheck->SetCheck(false);
			m_ReverseCheck->SetCheck(false);
		}

		m_AnimationDataListBox->Clear();

		std::vector<std::string> vecName;

		Animation->GetAllAnimationName(vecName);

		size_t Size = vecName.size();

		for (size_t i = 0; i < Size; ++i)
		{
			m_AnimationDataListBox->AddItem(vecName[i]);
		}

		m_SelectChangeAnimationData->SetText("");
	}

	else
	{
		m_Animation = nullptr;

		m_AnimationClass->SetText("");
		m_CurrentAnimationData->SetText("");
		m_PlayTime->SetFloat(0.f);
		m_PlayScale->SetFloat(0.f);
		m_LoopCheck->SetCheck(false);
		m_ReverseCheck->SetCheck(false);
		m_AnimationDataListBox->Clear();
		m_SelectChangeAnimationData->SetText("");
	}
}

void CSpriteComponentWidgetList::SetSelectAnimationClass(const std::string& AnimationClassName)
{
	m_SelectAnimationClass->SetText(AnimationClassName.c_str());
}

void CSpriteComponentWidgetList::SetAnimation()
{
	std::string AnimationClassName = m_SelectAnimationClass->GetText();

	if (AnimationClassName == "" || AnimationClassName == m_AnimationClass->GetText())
		return;

	CSpriteComponent* SpriteComponent = (CSpriteComponent*)m_DetailWindow->GetSelectComponent();

	CAnimation2D* AnimationCDO = CAnimation2D::FindCDO(AnimationClassName);
	CAnimation2D* Animation = AnimationCDO->Clone();

	SpriteComponent->SetAnimationByCDO(Animation);

	SetComponentContents(SpriteComponent);

	m_SelectAnimationClass->SetText("");
}

void CSpriteComponentWidgetList::SetPlayTime()
{
	if (m_Animation)
		m_Animation->SetPlayTime(m_CurrentAnimationData->GetText(), m_PlayTime->GetFloat());
}

void CSpriteComponentWidgetList::SetPlayScale()
{
	if (m_Animation)
		m_Animation->SetPlayScale(m_CurrentAnimationData->GetText(), m_PlayScale->GetFloat());
}

void CSpriteComponentWidgetList::SetLoop()
{
	if (m_Animation)
		m_Animation->SetLoop(m_CurrentAnimationData->GetText(), m_LoopCheck->GetCheck());
}

void CSpriteComponentWidgetList::SetReverse()
{
	if (m_Animation)
		m_Animation->SetReverse(m_CurrentAnimationData->GetText(), m_ReverseCheck->GetCheck());
}

void CSpriteComponentWidgetList::AnimationDataListBoxClickCallback(int Index, const std::string& Item)
{
	m_SelectAnimationDataItem = Item;

	m_SelectChangeAnimationData->SetText(Item.c_str());
}

void CSpriteComponentWidgetList::AnimationChangeButton()
{
	if (m_SelectAnimationDataItem.empty())
		return;

	if (m_CurrentAnimationData->GetText() == m_SelectAnimationDataItem)
		return;

	m_Animation->ChangeAnimation(m_SelectAnimationDataItem);

	m_CurrentAnimationData->SetText(m_Animation->GetCurrentAnimationName().c_str());

	// Settingµé º¯°æ
	m_PlayTime->SetFloat(m_Animation->GetCurrentAnimation()->GetPlayTime());
	m_PlayScale->SetFloat(m_Animation->GetCurrentAnimation()->GetPlayScale());
	m_LoopCheck->SetCheck(m_Animation->GetCurrentAnimation()->GetLoop());
	m_ReverseCheck->SetCheck(m_Animation->GetCurrentAnimation()->GetReverse());

	m_SelectAnimationDataItem.clear();

	CAnimation2DWindow* Animation2DWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CAnimation2DWindow>("Animation2DWindow");
	Animation2DWindow->SetSequence(m_Animation->GetCurrentAnimation()->GetAnimationSequence());
}
