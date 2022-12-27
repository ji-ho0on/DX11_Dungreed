#include "TestWindow.h"
#include "Editor/EditorButton.h"
#include "Editor/EditorColorButton.h"
#include "Editor/EditorRadioButton.h"
#include "Editor/EditorSmallButton.h"
#include "Editor/EditorSameLine.h"
#include "Editor/EditorNewLine.h"
#include "Editor/EditorLabel.h"
#include "Editor/EditorImage.h"
#include "Editor/EditorText.h"
#include "Editor/EditorBullet.h"
#include "Editor/EditorCheckBox.h"
#include "Editor/EditorInput.h"
#include "Editor/EditorListBox.h"
#include "Editor/EditorComboBox.h"
#include "Editor/EditorTree.h"

CTestWindow::CTestWindow()
{
}

CTestWindow::~CTestWindow()
{
}

bool CTestWindow::Init()
{
	// 텍스트 위젯
	CEditorBullet* TextBullet = CreateWidget<CEditorBullet>("텍스트");

	m_Text = CreateWidget<CEditorText>("Text");

	m_Text->SetText("테스트 윈도우");
	m_Text->SetColor(255, 0, 0, 255);

	strcpy_s(m_AddText, " Making");

	m_AddCount = (int)strlen(m_AddText);


	// 버튼 위젯
	CEditorBullet* ButtonBullet = CreateWidget<CEditorBullet>("버튼");

	CEditorButton* Button = CreateWidget<CEditorButton>("기본 버튼");
	Button->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);

	CEditorSameLine* SameLine = CreateWidget<CEditorSameLine>("Line");
	SameLine->SetSpacing(50.f);

	CEditorSmallButton* SmallButton = CreateWidget<CEditorSmallButton>("작은 버튼");
	SmallButton->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);

	SameLine = CreateWidget<CEditorSameLine>("Line");
	SameLine->SetSpacing(50.f);

	CEditorRadioButton* TestRadioButton = CreateWidget<CEditorRadioButton>("Radio 버튼", 100.f, 50.f);
	TestRadioButton->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);
	TestRadioButton->SetColor(255, 0, 0, 255);

	SameLine = CreateWidget<CEditorSameLine>("Line");
	SameLine->SetSpacing(50.f);

	CEditorColorButton* TestColorButton = CreateWidget<CEditorColorButton>("빨간 버튼", 80.f, 30.f);
	TestColorButton->SetColor(255, 0, 0, 255);
	TestColorButton->SetClickCallback<CTestWindow>(this, &CTestWindow::TestButtonCallback);



	// 이미지 위젯
	CEditorNewLine* NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorBullet* ImageBullet = CreateWidget<CEditorBullet>("이미지");

	CEditorImage* MushroomImage = CreateWidget<CEditorImage>("Mushroom");
	MushroomImage->SetTexture("Mushroom", TEXT("MainImage.png"));

	SameLine = CreateWidget<CEditorSameLine>("Line");
	SameLine->SetSpacing(50.f);

	CEditorImage* TeemoImage = CreateWidget<CEditorImage>("Teemo");
	TeemoImage->SetTexture("Teemo", TEXT("teemo.png"));



	// 라벨 위젯
	NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorBullet* LabelBullet = CreateWidget<CEditorBullet>("라벨");

	CEditorLabel* Label = CreateWidget<CEditorLabel>("라벨위젯", 100.f, 30.f);
	Label->SetColor(50, 50, 50, 255);
	Label->SetAlign(0.5f, 0.5f);

	SameLine = CreateWidget<CEditorSameLine>("Line");
	SameLine->SetSpacing(50.f);

	Label = CreateWidget<CEditorLabel>("왼쪽정렬", 100.f, 30.f);
	Label->SetColor(50, 100, 255, 255);
	Label->SetAlign(0.f, 0.5f);

	// 체크박스 위젯
	NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorBullet* CheckBoxBullet = CreateWidget<CEditorBullet>("체크박스");

	CEditorCheckBox* TestCheckBox = CreateWidget<CEditorCheckBox>("체크박스 위젯");

	// Input 위젯
	NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorBullet* InputBullet = CreateWidget<CEditorBullet>("Input");

	m_Input = CreateWidget<CEditorInput>("Input");
	m_Input->SetHideName(m_Input->GetName());
	m_Input->SetInputType(EImGuiInputType::Int);

	SameLine = CreateWidget<CEditorSameLine>("Line");
	SameLine->SetSpacing(50.f);

	CEditorInput* FloatInput = CreateWidget<CEditorInput>("FloatInput");
	FloatInput->SetHideName(FloatInput->GetName());
	FloatInput->SetInputType(EImGuiInputType::Float);


	// ListBox 위젯
	NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorBullet* ListBoxBullet = CreateWidget<CEditorBullet>("ListBox");

	m_List = CreateWidget<CEditorListBox>("ListBox");
	m_List->SetHideName(m_List->GetName());
	m_List->AddItem("List1");
	m_List->AddItem("List2");
	m_List->AddItem("List3");
	m_List->AddItem("List4");

	// ComboBox 위젯
	NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorBullet* ComboBoxBullet = CreateWidget<CEditorBullet>("ComboBox");

	m_Combo = CreateWidget<CEditorComboBox>("ComboBox");

	m_Combo->SetHideName(m_Combo->GetName());
	m_Combo->SetPrevViewName("콤보박스");
	m_Combo->AddItem("Combo1");
	m_Combo->AddItem("Combo2");
	m_Combo->AddItem("Combo3");
	m_Combo->AddItem("Combo4");

	// Tree 위젯
	NewLine = CreateWidget<CEditorNewLine>("NewLine");

	CEditorBullet* TreeBullet = CreateWidget<CEditorBullet>("Tree");

	//m_Tree = CreateWidget<CEditorTree>("Tree");
	//m_Tree->AddItem("Root");
	//m_Tree->AddItem("AnotherRoot");
	//m_Tree->AddItem("Child1", "AnotherTree");
	//m_Tree->AddItem("Child2", "AnotherTree");
	//m_Tree->AddItem("Child3", "AnotherTree");
	//m_Tree->AddItem("ChildChild1", "Child3");

	return true;
}

void CTestWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_AddIndex < m_AddCount)
	{
		m_AddTime += DeltaTime;

		if (m_AddTime >= 0.5f)
		{
			m_AddTime -= 0.5f;

			char	Text[2] = {};
			Text[0] = m_AddText[m_AddIndex];

			m_Text->AddText(Text);

			++m_AddIndex;
		}
	}
}

void CTestWindow::TestButtonCallback()
{
	MessageBox(0, TEXT("TestButton"), TEXT("TestButton"), MB_OK);
}
