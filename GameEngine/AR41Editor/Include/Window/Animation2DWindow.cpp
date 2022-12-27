#include "Animation2DWindow.h"
#include "Animation/Animation2D.h"
#include "Resource/Animation/AnimationManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Resource/ResourceManager.h"
#include "Component/SpriteComponent.h"
#include "PathManager.h"
#include "Engine.h"
#include "Editor/EditorGUIManager.h"

// Widget
#include "Editor/EditorButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorTree.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorNewLine.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorTap.h"
#include "Editor/EditorGroup.h"
#include "Editor/EditorSlider.h"
#include "Editor/EditorSeparator.h"

// Window
#include "DetailWindow.h"
#include "DetailWindow/SpriteComponentWidgetList.h"

CAnimation2DWindow::CAnimation2DWindow() :
	m_CurrentFrameIndex(0),
	m_CurrentSequencePlay(false),
	m_PlayTime(0.f),
	m_SettingPlayTime(0.1f)
{
}

CAnimation2DWindow::~CAnimation2DWindow()
{
}

bool CAnimation2DWindow::Init()
{
	CEditorGroup* ImageLoadGroup = CreateWidget<CEditorGroup>("ImageLoadGroup");


	CEditorImage* Image = ImageLoadGroup->CreateWidget<CEditorImage>("Image", 150.f, 150.f);

	CEditorButton* ImageLoadButton = ImageLoadGroup->CreateWidget<CEditorButton>("ImageLoad", 150.f, 30.f);
	ImageLoadButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::ImageLoadButton);



	CEditorSameLine* Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(200.f);



	CEditorGroup* SequenceCreateGroup = CreateWidget<CEditorGroup>("SequenceCreateGroup");

	CEditorText* CreateSequenceName = SequenceCreateGroup->CreateWidget<CEditorText>("SequenceName");
	CreateSequenceName->SetText("SequenceName");

	CEditorInput* CreateSequenceNameInput = SequenceCreateGroup->CreateWidget<CEditorInput>("CreateSequenceNameInput", 150.f, 30.f);
	CreateSequenceNameInput->SetHideName(CreateSequenceNameInput->GetName());

	CEditorButton* SequenceCreateButton = SequenceCreateGroup->CreateWidget<CEditorButton>("SequenceCreate", 150.f, 60.f);
	SequenceCreateButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::SequenceCreateButton);



	Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(400.f);



	CEditorGroup* CurrentSequenceGroup = CreateWidget<CEditorGroup>("CurrentSequenceGroup");

	CEditorText* CurrentSequenceName = CurrentSequenceGroup->CreateWidget<CEditorText>("CurrentSequenceName");
	CurrentSequenceName->SetText("CurrentSequence");

	CEditorInput* CurrentSequenceNameInput = CurrentSequenceGroup->CreateWidget<CEditorInput>("CurrentSequenceNameInput", 150.f, 30.f);
	CurrentSequenceNameInput->SetHideName(CurrentSequenceNameInput->GetName());
	CurrentSequenceNameInput->ReadOnly(true);

	CEditorButton* SequenceSaveButton = CurrentSequenceGroup->CreateWidget<CEditorButton>("SequenceSave", 150.f, 60.f);
	SequenceSaveButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::SequenceSaveButton);



	Line = CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(600.f);



	CEditorGroup* SequenceListGroup = CreateWidget<CEditorGroup>("SequenceListGroup");

	CEditorText* SequenceListName = SequenceListGroup->CreateWidget<CEditorText>("SequenceListName");
	SequenceListName->SetText("SequenceList");

	m_SequenceListBox = SequenceListGroup->CreateWidget<CEditorListBox>("SequenceListBox", 150.f);
	m_SequenceListBox->SetHideName(SequenceListGroup->GetName());
	m_SequenceListBox->SetPageItemCount(6);
	m_SequenceListBox->SetSelectCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::SequenceListBoxClickCallback);

	LoadSequenceDirectory();

	Line = CreateWidget<CEditorSameLine>("Line");


	CEditorGroup* SequenceListGroup2 = CreateWidget<CEditorGroup>("SequenceListGroup2");

	CEditorText* SelectSequenceName = SequenceListGroup2->CreateWidget<CEditorText>("SelectSequenceName");
	SelectSequenceName->SetText("SelectSequence");

	m_SelectSequenceNameInput = SequenceListGroup2->CreateWidget<CEditorInput>("SelectSequenceNameInput", 150.f, 30.f);
	m_SelectSequenceNameInput->SetHideName(m_SelectSequenceNameInput->GetName());
	m_SelectSequenceNameInput->ReadOnly(true);

	CEditorButton* SequenceChangeButton = SequenceListGroup2->CreateWidget<CEditorButton>("Change", 150.f, 30.f);
	SequenceChangeButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::SequenceChangeButton);



	CEditorNewLine* NewLine = CreateWidget<CEditorNewLine>("NewLine");



	CEditorGroup* FrameDataGroup = CreateWidget<CEditorGroup>("FrameDataGroup");

	CEditorText* FrameStartXText = FrameDataGroup->CreateWidget<CEditorText>("FrameStartX");
	FrameStartXText->SetText("FrameStartX");

	Line = FrameDataGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(100.f);

	CEditorInput* FrameStartXInput = FrameDataGroup->CreateWidget<CEditorInput>("FrameStartXInput", 60.f, 30.f);
	FrameStartXInput->SetHideName(FrameStartXInput->GetName());
	FrameStartXInput->SetInputType(EImGuiInputType::Float);

	CEditorText* FrameStartYText = FrameDataGroup->CreateWidget<CEditorText>("FrameStartY");
	FrameStartYText->SetText("FrameStartY");

	Line = FrameDataGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(100.f);

	CEditorInput* FrameStartYInput = FrameDataGroup->CreateWidget<CEditorInput>("FrameStartYInput", 60.f, 30.f);
	FrameStartYInput->SetHideName(FrameStartYInput->GetName());
	FrameStartYInput->SetInputType(EImGuiInputType::Float);

	CEditorText* FrameEndXText = FrameDataGroup->CreateWidget<CEditorText>("FrameEndX");
	FrameEndXText->SetText("FrameEndX");

	Line = FrameDataGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(100.f);

	CEditorInput* FrameEndXInput = FrameDataGroup->CreateWidget<CEditorInput>("FrameEndXInput", 60.f, 30.f);
	FrameEndXInput->SetHideName(FrameEndXInput->GetName());
	FrameEndXInput->SetInputType(EImGuiInputType::Float);

	CEditorText* FrameEndYText = FrameDataGroup->CreateWidget<CEditorText>("FrameEndY");
	FrameEndYText->SetText("FrameEndY");

	Line = FrameDataGroup->CreateWidget<CEditorSameLine>("Line");
	Line->SetOffsetX(100.f);

	CEditorInput* FrameEndYInput = FrameDataGroup->CreateWidget<CEditorInput>("FrameEndYInput", 60.f, 30.f);
	FrameEndYInput->SetHideName(FrameEndYInput->GetName());
	FrameEndYInput->SetInputType(EImGuiInputType::Float);

	CEditorButton* AddFrameButton = FrameDataGroup->CreateWidget<CEditorButton>("AddFrame", 160.f, 30.f);
	AddFrameButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::AddFrameButton);

	CEditorButton* EditFrameButton = FrameDataGroup->CreateWidget<CEditorButton>("EditFrame", 160.f, 30.f);
	EditFrameButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::EditFrameButton);

	CEditorButton* DeleteFrameButton = FrameDataGroup->CreateWidget<CEditorButton>("DeleteFrame", 160.f, 30.f);
	DeleteFrameButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::DeleteFrameButton);



	Line = CreateWidget<CEditorSameLine>("Line");



	m_FrameDataListBox = CreateWidget<CEditorListBox>("FrameDataListBox", 100.f, 150.f);
	m_FrameDataListBox->SetHideName(m_FrameDataListBox->GetName());
	m_FrameDataListBox->SetPageItemCount(9);
	m_FrameDataListBox->SetSelectCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::FrameDataListBoxClickCallback);


	Line = CreateWidget<CEditorSameLine>("Line");



	m_CurrentFrameImage = CreateWidget<CEditorImage>("CurruntFrameImage", 215.f, 215.f);


	Line = CreateWidget<CEditorSameLine>("Line");


	CEditorGroup* SequencePlayGroup = CreateWidget<CEditorGroup>("SequencePlayGroup");

	CEditorText* PlayTimeText = SequencePlayGroup->CreateWidget<CEditorText>("PlayTimeText");
	PlayTimeText->SetText("PlayTime Set");

	CEditorInput* SequencePlayTimeInput = SequencePlayGroup->CreateWidget<CEditorInput>("SequencePlayTimeInput", 115.f, 30.f);
	SequencePlayTimeInput->SetHideName(SequencePlayTimeInput->GetName());
	SequencePlayTimeInput->SetInputType(EImGuiInputType::Float);

	CEditorButton* PlayTimeSettingButton = SequencePlayGroup->CreateWidget<CEditorButton>("PlayTime Set", 115.f, 30.f);
	PlayTimeSettingButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::PlayTimeSetButton);

	CEditorButton* CurrentSequencePlayButton = SequencePlayGroup->CreateWidget<CEditorButton>("Play", 115.f, 125.f);
	CurrentSequencePlayButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::CurrentSequencePlayButton);


	m_SequencePreviewSlider = CreateWidget<CEditorSlider>("SequencePreviewSlider");
	m_SequencePreviewSlider->SetHideName(m_SequencePreviewSlider->GetName());


	NewLine = CreateWidget<CEditorNewLine>("NewLine");


	CEditorSeparator* Separator = CreateWidget<CEditorSeparator>("Separator");


	NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorGroup* AnimationClassGroup = CreateWidget<CEditorGroup>("AnimationClassGroup");


	CEditorText* AnimationClassText = AnimationClassGroup->CreateWidget<CEditorText>("AnimationClassText");
	AnimationClassText->SetText("AnimationClassList");

	m_AnimationClassListBox = AnimationClassGroup->CreateWidget<CEditorListBox>("AnimationClassListBox", 150.f);
	m_AnimationClassListBox->SetHideName(m_AnimationClassListBox->GetName());
	m_AnimationClassListBox->SetPageItemCount(6);
	m_AnimationClassListBox->SetSelectCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::AnimationClassListBoxClickCallback);

	LoadAnimation2DDirectory();


	Line = CreateWidget<CEditorSameLine>("Line");


	CEditorGroup* AnimationAddGroup = CreateWidget<CEditorGroup>("AnimationAddGroup");

	CEditorText* AddAnimationName = AnimationAddGroup->CreateWidget<CEditorText>("AddAnimationName");
	AddAnimationName->SetText("AnimationName");

	CEditorInput* AddAnimationNameInput = AnimationAddGroup->CreateWidget<CEditorInput>("AddAnimationNameInput", 150.f, 30.f);
	AddAnimationNameInput->SetHideName(AddAnimationNameInput->GetName());

	CEditorButton* AnimationAddButton = AnimationAddGroup->CreateWidget<CEditorButton>("AddAnimation", 150.f, 60.f);
	AnimationAddButton->SetClickCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::AnimationAddButton);

	return true;
}

void CAnimation2DWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_FrameDataListBox->GetItemCount() == 0)
	{
		m_SequencePreviewSlider->SetIntMax(0);
	}

	else if (m_FrameDataListBox->GetItemCount() != m_SequencePreviewSlider->GetIntMax())
	{
		m_SequencePreviewSlider->SetIntMax(m_FrameDataListBox->GetItemCount() - 1);
	}

	if (m_Sequence)
	{
		// 재생
		if (m_CurrentSequencePlay)
		{
			m_PlayTime += DeltaTime;

			if (m_PlayTime >= m_SettingPlayTime)
			{
				m_PlayTime -= m_SettingPlayTime;

				int Index = m_SequencePreviewSlider->GetInt();

				if (Index >= m_Sequence->GetFrameCount() - 1)
				{
					Index = 0;
				}

				else
				{
					++Index;
				}

				m_SequencePreviewSlider->SetInt(Index);
			}
		}

		if (m_CurrentFrameIndex != m_SequencePreviewSlider->GetInt())
		{
			int Index = m_SequencePreviewSlider->GetInt();

			Animation2DFrameData FrameData = m_Sequence->GetFrameData(Index);

			// m_CurrentFrameImage에 해당 Index번째 Sequence의 Texture를 가져와야함.
			m_CurrentFrameImage->SetImageIndex(Index);
			m_CurrentFrameImage->SetImageStart(FrameData.Start.x, FrameData.Start.y);
			m_CurrentFrameImage->SetImageEnd(FrameData.End.x, FrameData.End.y);

			CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

			CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
			CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
			CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
			CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

			FrameStartXInput->SetFloat(FrameData.Start.x);
			FrameStartYInput->SetFloat(FrameData.Start.y);
			FrameEndXInput->SetFloat(FrameData.End.x);
			FrameEndYInput->SetFloat(FrameData.End.y);
		}
	}

	m_CurrentFrameIndex = m_SequencePreviewSlider->GetInt();
}

void CAnimation2DWindow::SetSelectComponent(CSpriteComponent* Component)
{
	if (Component)
	{
		if (Component->GetComponentTypeName() == "SpriteComponent")
		{
			CAnimation2D* Animation = Component->GetAnimation();

			if (Animation)
			{
				m_Sequence = Animation->GetCurrentAnimationSequence();

				UpdateSequenceData(m_Sequence);

				m_CurrentSequenceName = m_Sequence->GetName();

				CEditorInput* CurrentSequenceNameInput = ((CEditorGroup*)FindWidget("CurrentSequenceGroup"))->FindWidget<CEditorInput>("##CurrentSequenceNameInput");
				CurrentSequenceNameInput->SetText(m_CurrentSequenceName.c_str());
			}

			m_SelectComponent = Component;
		}

		else
		{
			m_SelectComponent = nullptr;
		}
	}
}

void CAnimation2DWindow::SetSequence(CAnimationSequence2D* Sequence)
{
	m_Sequence = Sequence;

	CEditorInput* CurrentSequenceNameInput = ((CEditorGroup*)FindWidget("CurrentSequenceGroup"))->FindWidget<CEditorInput>("##CurrentSequenceNameInput");
	CurrentSequenceNameInput->SetText(m_CurrentSequenceName.c_str());

	UpdateSequenceData(m_Sequence);
}

void CAnimation2DWindow::UpdateSequenceData(CAnimationSequence2D* Sequence)
{
	if (!Sequence)
		return;

	// FrameDataListBox에 있는 Item 전부 날리고 현재 들어온 Sequence의 FrameData 개수만큼 List채우기
	m_FrameDataListBox->Clear();

	int Count = Sequence->GetFrameCount();

	for (int i = 0; i < Count; ++i)
	{
		char AddItemName[4] = {};

		_itoa_s(i, AddItemName, 10);

		m_FrameDataListBox->AddItem(AddItemName);
	}

	// List 채워진만큼 Slider Max값 조정, Slider 값 0번으로 변경
	m_SequencePreviewSlider->SetIntMax(m_FrameDataListBox->GetItemCount() - 1);
	m_SequencePreviewSlider->SetInt(0);
	m_CurrentFrameIndex = 0;

	// 0번 Index로 CurrentFrameImage 변경
	Animation2DFrameData FrameData = m_Sequence->GetFrameData(m_CurrentFrameIndex);

	CTexture* Texture = m_Sequence->GetTexture();

	m_CurrentFrameImage->SetTexture(Texture);
	m_CurrentFrameImage->SetImageStart(FrameData.Start.x, FrameData.Start.y);
	m_CurrentFrameImage->SetImageEnd(FrameData.End.x, FrameData.End.y);
	m_CurrentFrameImage->SetImageIndex(0);

	CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

	CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
	CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
	CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
	CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

	FrameStartXInput->SetFloat(FrameData.Start.x);
	FrameStartYInput->SetFloat(FrameData.Start.y);
	FrameEndXInput->SetFloat(FrameData.End.x);
	FrameEndYInput->SetFloat(FrameData.End.y);
}

void CAnimation2DWindow::ImageLoadButton()
{
	OPENFILENAME	ofn = {};

	TCHAR	FullPath[2048] = {};

	TCHAR	Filter[] = TEXT("모든 파일\0*.*\0PNG\0*.png\0JPG\0*.jpg\0BMP\0*.bmp");

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetWindowHandle();
	ofn.lpstrFilter = Filter;
	ofn.lpstrFile = FullPath;
	ofn.nMaxFile = 2048;
	ofn.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->Path;
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT;

	if (GetOpenFileName(&ofn) != 0)
	{
		CEditorGroup* Group = (CEditorGroup*)FindWidget("ImageLoadGroup");

		CEditorImage* Image = Group->FindWidget<CEditorImage>("Image");

		if (Image)
		{
			// Image를 한장 선택했는지 or 여러장 선택했는지 나눈다.
			TCHAR Path[2048] = {};

			lstrcpy(Path, FullPath);

			size_t Size = lstrlen(FullPath);

			// 한 장 선택했을 때 (Atlas)
			if (FullPath[Size + 1] == 0)
			{
				TCHAR	wTexName[256] = {};

				_wsplitpath_s(FullPath, 0, 0, 0, 0, wTexName, 256, 0, 0);

				char	TexName[256] = {};

				int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

				WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

				Image->SetTextureFullPath(TexName, FullPath);
			}

			// 여러 장 선택했을 때 (Frame)
			else
			{
				lstrcat(Path, L"/");

				std::vector<const TCHAR*> vecFileName;

				for (size_t i = lstrlen(FullPath) + 1; FullPath[i] != 0; i += (lstrlen(FullPath + i) + 1))
				{
					TCHAR* FileName = new TCHAR[256];

					lstrcpy(FileName, Path);

					lstrcat(FileName, FullPath + i);

					vecFileName.push_back(FileName);
				}

				// TexName을 구해야함.
				//보통 TexName_00.png or TexName-00.png 형태로 들어오니까 vecFileName에서 첫번째꺼를
				TCHAR	wTexName[256] = {};

				_wsplitpath_s(vecFileName[0], 0, 0, 0, 0, wTexName, 256, 0, 0);

				char	TexName[256] = {};

				int Length = (int)WideCharToMultiByte(CP_ACP, 0, wTexName, -1, nullptr, 0, nullptr, nullptr);

				WideCharToMultiByte(CP_ACP, 0, wTexName, -1, TexName, Length, nullptr, nullptr);

				// 여기서 뒤에 _ 이나 - 까지를 떼줘야함.
				for (int i = Length - 2; i > 0; --i)
				{
					if ((TexName[i] == '-') || (TexName[i] == '_'))
					{
						TexName[i] = 0;
						break;
					}

					TexName[i] = 0;
				}


				Image->SetTextureFullPath(TexName, vecFileName);

				size_t vecSize = vecFileName.size();

				for (size_t i = 0; i < vecSize; ++i)
				{
					SAFE_DELETE_ARRAY(vecFileName[i]);
				}
			}
		}
	}
}

void CAnimation2DWindow::SequenceCreateButton()
{
	CTexture* Texture = ((CEditorGroup*)FindWidget("ImageLoadGroup"))->FindWidget<CEditorImage>("Image")->GetTexture();

	if (!Texture)
		return;

	CEditorInput* CreateSequenceNameInput = ((CEditorGroup*)FindWidget("SequenceCreateGroup"))->FindWidget<CEditorInput>("##CreateSequenceNameInput");
	std::string CreateSequenceName = CreateSequenceNameInput->GetText();

	if (CreateSequenceName.empty())
		return;

	if (m_SelectComponent)
	{
		CScene* Scene = m_SelectComponent->GetScene();

		if (Scene)
		{
			Scene->GetResource()->CreateAnimationSequence2D(CreateSequenceName, Texture);
			m_Sequence = Scene->GetResource()->FindAnimationSequence2D(CreateSequenceName);
		}

		else
		{
			CResourceManager::GetInst()->CreateAnimationSequence2D(CreateSequenceName, Texture);
			m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(CreateSequenceName);
		}
	}

	else
	{
		CResourceManager::GetInst()->CreateAnimationSequence2D(CreateSequenceName, Texture);
		m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(CreateSequenceName);
	}

	m_CurrentSequenceName = CreateSequenceName;

	CEditorInput* CurrentSequenceNameInput = ((CEditorGroup*)FindWidget("CurrentSequenceGroup"))->FindWidget<CEditorInput>("##CurrentSequenceNameInput");
	CurrentSequenceNameInput->SetText(m_CurrentSequenceName.c_str());

	m_FrameDataListBox->Clear();

	if (Texture->GetImageType() == EImageType::Frame)
	{
		// m_FrameDataList와 m_Sequence에 현재 Texture의 ImageCount만큼 Frame을 자동으로 넣어준다.
		int Size = Texture->GetImageCount();

		for (int i = 0; i < Size; ++i)
		{
			Animation2DFrameData FrameData = {};

			FrameData.End = Vector2((float)Texture->GetWidth(i), (float)Texture->GetHeight(i));

			m_Sequence->AddFrame(FrameData.Start, FrameData.End);

			int IndexCount = m_FrameDataListBox->GetItemCount();

			// ItemCount 숫자를 int -> char로 변경하여 ListBox에 추가
			char AddItemName[4] = {};

			_itoa_s(IndexCount, AddItemName, 10);

			m_FrameDataListBox->AddItem(AddItemName);
		}

		Animation2DFrameData FrameData = m_Sequence->GetFrameData(0);

		m_CurrentFrameImage->SetTexture(Texture);
		m_CurrentFrameImage->SetImageStart(FrameData.Start.x, FrameData.Start.y);
		m_CurrentFrameImage->SetImageEnd(FrameData.End.x, FrameData.End.y);
		m_CurrentFrameImage->SetImageIndex(0);

		m_SequencePreviewSlider->SetInt(0);
		m_SequencePreviewSlider->SetIntMax(Texture->GetImageCount() - 1);
		m_CurrentFrameIndex = 0;

		CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

		CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
		CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
		CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
		CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

		FrameStartXInput->SetFloat(FrameData.Start.x);
		FrameStartYInput->SetFloat(FrameData.Start.y);
		FrameEndXInput->SetFloat(FrameData.End.x);
		FrameEndYInput->SetFloat(FrameData.End.y);
	}

	else if (Texture->GetImageType() == EImageType::Atlas)
	{
		m_CurrentFrameImage->SetTexture("DefaultUI");

		m_SequencePreviewSlider->SetInt(0);
		m_SequencePreviewSlider->SetIntMax(0);
		m_CurrentFrameIndex = 0;

		CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

		CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
		CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
		CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
		CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

		FrameStartXInput->SetFloat(0.f);
		FrameStartYInput->SetFloat(0.f);
		FrameEndXInput->SetFloat(0.f);
		FrameEndYInput->SetFloat(0.f);
	}
}

void CAnimation2DWindow::SequenceSaveButton()
{
	if (!m_Sequence)
		return;

	std::string Name = m_Sequence->GetName();

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "AnimationSequence2D/");
	strcat_s(FullPath, Name.c_str());
	strcat_s(FullPath, ".sqc");

	// 현재 설정된 AnimationSequence2D 저장
	m_Sequence->Save(FullPath);

	// 기존 리스트에 없으면 리스트에 추가
	if (!m_SequenceListBox->CheckItem(Name))
		m_SequenceListBox->AddItem(Name);
}

void CAnimation2DWindow::SequenceListBoxClickCallback(int Index, const std::string& Item)
{
	m_SelectSequenceItem = Item;

	m_SelectSequenceNameInput->SetText(Item.c_str());
}

void CAnimation2DWindow::LoadSequenceDirectory()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);
	strcat_s(Path, "AnimationSequence2D/");

	for (const auto& file : std::filesystem::directory_iterator(Path))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		m_SequenceListBox->AddItem(Name);
	}
}

void CAnimation2DWindow::SequenceChangeButton()
{
	if (m_SelectSequenceItem == m_CurrentSequenceName)
		return;

	m_CurrentSequenceName = m_SelectSequenceItem;

	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	FullPath[MAX_PATH] = {};

	if (Info)
		strcpy_s(FullPath, Info->PathMultibyte);

	strcat_s(FullPath, "AnimationSequence2D/");
	strcat_s(FullPath, m_SelectSequenceItem.c_str());
	strcat_s(FullPath, ".sqc");

	if (m_SelectComponent)
	{
		CScene* Scene = m_SelectComponent->GetScene();

		if (Scene)
		{
			Scene->GetResource()->LoadSequence2D(m_SelectSequenceItem, FullPath);
			m_Sequence = Scene->GetResource()->FindAnimationSequence2D(m_SelectSequenceItem);
		}

		else
		{
			CResourceManager::GetInst()->LoadSequence2D(m_SelectSequenceItem, FullPath);
			m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_SelectSequenceItem);
		}
	}

	else
	{
		CResourceManager::GetInst()->LoadSequence2D(m_SelectSequenceItem, FullPath);
		m_Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_SelectSequenceItem);
	}


	CEditorInput* CurrentSequenceNameInput = ((CEditorGroup*)FindWidget("CurrentSequenceGroup"))->FindWidget<CEditorInput>("##CurrentSequenceNameInput");
	CurrentSequenceNameInput->SetText(m_CurrentSequenceName.c_str());

	UpdateSequenceData(m_Sequence);
}

void CAnimation2DWindow::AddFrameButton()
{
	if (!m_Sequence)
		return;

	CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

	CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
	CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
	CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
	CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

	Vector2 FrameStart = Vector2(FrameStartXInput->GetFloat(), FrameStartYInput->GetFloat());
	Vector2 FrameEnd = Vector2(FrameEndXInput->GetFloat(), FrameEndYInput->GetFloat());

	m_Sequence->AddFrame(FrameStart, FrameEnd);

	int IndexCount = m_FrameDataListBox->GetItemCount();

	// ItemCount 숫자를 int -> char로 변경하여 ListBox에 추가
	char AddItemName[4] = {};

	_itoa_s(IndexCount, AddItemName, 10);

	m_FrameDataListBox->AddItem(AddItemName);

	int Index = m_FrameDataListBox->GetItemCount() - 1;

	Animation2DFrameData FrameData = m_Sequence->GetFrameData(Index);

	CTexture* Texture = m_Sequence->GetTexture();

	if (m_CurrentFrameImage->GetTexture() != Texture)
	{
		m_CurrentFrameImage->SetTexture(Texture);
	}

	m_CurrentFrameImage->SetImageStart(FrameData.Start.x, FrameData.Start.y);
	m_CurrentFrameImage->SetImageEnd(FrameData.End.x, FrameData.End.y);

	m_SequencePreviewSlider->SetInt(Index);
	m_CurrentFrameIndex = Index;
}

void CAnimation2DWindow::EditFrameButton()
{
	if (!m_Sequence)
		return;

	int Index = m_SequencePreviewSlider->GetInt();

	if (Index < 0)
		return;

	CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

	CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
	CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
	CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
	CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

	Vector2 FrameStart = Vector2(FrameStartXInput->GetFloat(), FrameStartYInput->GetFloat());
	Vector2 FrameEnd = Vector2(FrameEndXInput->GetFloat(), FrameEndYInput->GetFloat());

	m_Sequence->EditFrame(Index, FrameStart, FrameEnd);

	m_CurrentFrameImage->SetImageStart(FrameStart.x, FrameStart.y);
	m_CurrentFrameImage->SetImageEnd(FrameEnd.x, FrameEnd.y);
}

void CAnimation2DWindow::DeleteFrameButton()
{
	if (!m_Sequence)
		return;

	int Index = m_SequencePreviewSlider->GetInt();

	if (Index < 0)
		return;

	m_Sequence->DeleteFrame(Index);

	m_FrameDataListBox->DeleteItem(Index);

	// 지웠는데 FrmaeData가 하나도 없다면
	if (m_FrameDataListBox->GetItemCount() == 0)
	{
		m_SequencePreviewSlider->SetIntMax(0);
		m_SequencePreviewSlider->SetInt(0);
		m_CurrentFrameIndex = 0;
	}

	// 지우고 나서도 FrameData가 남아있다면
	else
	{
		int Count = m_FrameDataListBox->GetItemCount();

		if (Index == 0)
		{
			m_SequencePreviewSlider->SetIntMax(Count - 1);
			m_SequencePreviewSlider->SetInt(Index + 1);
			m_CurrentFrameIndex = Index + 1;

			Animation2DFrameData FrameData = m_Sequence->GetFrameData(Index + 1);

			// m_CurrentFrameImage에 해당 Index번째 Sequence의 Texture를 가져와야함.
			m_CurrentFrameImage->SetImageIndex(Index + 1);
			m_CurrentFrameImage->SetImageStart(FrameData.Start.x, FrameData.Start.y);
			m_CurrentFrameImage->SetImageEnd(FrameData.End.x, FrameData.End.y);

			CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

			CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
			CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
			CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
			CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

			FrameStartXInput->SetFloat(FrameData.Start.x);
			FrameStartYInput->SetFloat(FrameData.Start.y);
			FrameEndXInput->SetFloat(FrameData.End.x);
			FrameEndYInput->SetFloat(FrameData.End.y);
		}

		else
		{
			m_SequencePreviewSlider->SetIntMax(Count - 1);
			m_SequencePreviewSlider->SetInt(Index - 1);
			m_CurrentFrameIndex = Index - 1;

			Animation2DFrameData FrameData = m_Sequence->GetFrameData(Index - 1);

			// m_CurrentFrameImage에 해당 Index번째 Sequence의 Texture를 가져와야함.
			m_CurrentFrameImage->SetImageIndex(Index - 1);
			m_CurrentFrameImage->SetImageStart(FrameData.Start.x, FrameData.Start.y);
			m_CurrentFrameImage->SetImageEnd(FrameData.End.x, FrameData.End.y);

			CEditorGroup* FrameDataGroup = (CEditorGroup*)FindWidget("FrameDataGroup");

			CEditorInput* FrameStartXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartXInput");
			CEditorInput* FrameStartYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameStartYInput");
			CEditorInput* FrameEndXInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndXInput");
			CEditorInput* FrameEndYInput = FrameDataGroup->FindWidget<CEditorInput>("##FrameEndYInput");

			FrameStartXInput->SetFloat(FrameData.Start.x);
			FrameStartYInput->SetFloat(FrameData.Start.y);
			FrameEndXInput->SetFloat(FrameData.End.x);
			FrameEndYInput->SetFloat(FrameData.End.y);
		}

		m_FrameDataListBox->Clear();

		for (int i = 0; i < Count; ++i)
		{
			char AddItemName[4] = {};

			_itoa_s(i, AddItemName, 10);

			m_FrameDataListBox->AddItem(AddItemName);
		}
	}
}

void CAnimation2DWindow::FrameDataListBoxClickCallback(int Index, const std::string& Item)
{
	if (!m_Sequence)
		return;

	CTexture* Texture = m_Sequence->GetTexture();
	Animation2DFrameData FrameData = m_Sequence->GetFrameData(Index);

	m_CurrentFrameImage->SetTexture(Texture);
	m_CurrentFrameImage->SetImageStart(FrameData.Start.x, FrameData.Start.y);
	m_CurrentFrameImage->SetImageEnd(FrameData.End.x, FrameData.End.y);

	m_SequencePreviewSlider->SetInt(Index);
}

void CAnimation2DWindow::PlayTimeSetButton()
{
	CEditorGroup* SequencePlayGroup = (CEditorGroup*)FindWidget("SequencePlayGroup");

	CEditorInput* PlayTimeInput = SequencePlayGroup->FindWidget<CEditorInput>("##SequencePlayTimeInput");

	float PlayTime = PlayTimeInput->GetFloat();

	if (PlayTime <= 0.f)
		return;

	if (!m_Sequence)
		m_SettingPlayTime = PlayTime;

	else
	{
		int FrameCount = m_Sequence->GetFrameCount();

		m_SettingPlayTime = PlayTime / FrameCount;
	}
}

void CAnimation2DWindow::CurrentSequencePlayButton()
{
	if (m_CurrentSequencePlay)
	{
		m_CurrentSequencePlay = false;
	}

	else
	{
		m_CurrentSequencePlay = true;

		m_PlayTime = 0.f;
	}
}

void CAnimation2DWindow::AnimationAddButton()
{
	//if (!m_SelectComponent)
	//	return;

	//if (m_SelectSequenceItem.empty())
	//	return;

	//const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	//char	FullPath[MAX_PATH] = {};

	//if (Info)
	//	strcpy_s(FullPath, Info->PathMultibyte);

	//strcat_s(FullPath, "AnimationSequence2D/");
	//strcat_s(FullPath, m_SelectSequenceItem.c_str());
	//strcat_s(FullPath, ".sqc");

	//CScene* Scene = m_SelectComponent->GetScene();

	//CAnimationSequence2D* Sequence = nullptr;

	//if (Scene)
	//{
	//	Scene->GetResource()->LoadSequence2D(m_SelectSequenceItem, FullPath);
	//	Sequence = Scene->GetResource()->FindAnimationSequence2D(m_SelectSequenceItem);
	//}

	//else
	//{
	//	CResourceManager::GetInst()->LoadSequence2D(m_SelectSequenceItem, FullPath);
	//	Sequence = CResourceManager::GetInst()->FindAnimationSequence2D(m_SelectSequenceItem);
	//}

	//CEditorGroup* AnimationAddGroup = (CEditorGroup*)FindWidget("AnimationAddGroup");
	//std::string AddAnimationName = AnimationAddGroup->FindWidget<CEditorInput>("##AddAnimationNameInput")->GetText();

	//CAnimation2D* Animation = m_SelectComponent->GetAnimation();

	//if (!Animation)
	//{
	//	const char* AnimationName = m_SelectComponent->GetName().c_str();

	//	char NewAnimationName[256] = {};

	//	strcpy_s(NewAnimationName, AnimationName);
	//	strcat_s(NewAnimationName, "Animation");

	//	m_SelectComponent->SetAnimation<CAnimation2D>(NewAnimationName);

	//	m_CurrentAnimationName = AddAnimationName;

	//	((CEditorGroup*)FindWidget("CurrentAnimationGroup"))->FindWidget<CEditorInput>("##CurrentAnimationInput")->SetText(m_CurrentAnimationName.c_str());
	//}

	//m_SelectComponent->GetAnimation()->AddAnimation(AddAnimationName, Sequence);

	//if (!m_ChangeAnimationListBox->CheckItem(AddAnimationName))
	//	m_ChangeAnimationListBox->AddItem(AddAnimationName);
}

void CAnimation2DWindow::AnimationClassListBoxClickCallback(int Index, const std::string& Item)
{
	m_SelectAnimationClassItem = Item;

	CDetailWindow* DetailWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("DetailWindow");

	CSceneComponent* SelectComponent = DetailWindow->GetSelectComponent();

	if (!SelectComponent)
		return;

	if (SelectComponent->GetComponentTypeName() != "SpriteComponent")
		return;

	CSpriteComponentWidgetList* SpriteComponentWidgetList = (CSpriteComponentWidgetList*)DetailWindow->GetComponentWidgetList(ESceneComponentType::Sprite);

	SpriteComponentWidgetList->SetSelectAnimationClass(Item);
}

void CAnimation2DWindow::LoadAnimation2DDirectory()
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

	char	Path[MAX_PATH] = {};

	strcpy_s(Path, Info->PathMultibyte);

	int	Length = (int)strlen(Path);

	// Root Path에서 Bin\을 지워준다.
	for (int i = Length - 2; i >= 0; --i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}
	}

	char	Directory[MAX_PATH] = {};

	strcpy_s(Directory, Path);

	// Editor의 Animation2D폴더에 있는 파일을 읽어온다.
	strcat_s(Directory, "Include/Animation2D/");

	for (const auto& file : std::filesystem::directory_iterator(Directory))
	{
		char	Name[64] = {};
		char	FullPath[MAX_PATH] = {};
		char	Ext[_MAX_EXT] = {};

		strcpy_s(FullPath, file.path().generic_string().c_str());

		_splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

		if (strcmp(Ext, ".cpp") == 0)
			continue;

		m_AnimationClassListBox->AddItem(Name);
	}

	// Engine에는 기본 클래스 하나밖에 없으므로 하나 추가해준다.
	m_AnimationClassListBox->AddItem("Animation2D");
}
