#include "EditorManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/EditorDefaultScene.h"
#include "Editor/EditorGUIManager.h"
#include "CollisionManager.h"
#include "Input.h"
#include "Resource/Animation/AnimationSequence2D.h"
#include "PathManager.h"
#include "Setting/EngineShareSetting.h"
#include "Scene/EditorDefaultScene.h"
#include "Scene/TownScene.h"
#include "TransferInfo/TransferCharacterInfo.h"

// Window
#include "Window/ObjectWindow.h"
#include "Window/ClassWindow.h"
#include "Window/ComponentWindow.h"
#include "Window/TransformWindow.h"
#include "Window/SceneWindow.h"
#include "Window/DetailWindow.h"
#include "Window/Animation2DWindow.h"
#include "Window/EditorUIWindow.h"      // 昏力且 淀
#include "Window/UIWindowEditor.h"
#include "Window/UIWidgetEditor.h"
#include "Window/TileMapWindow.h"

// GameObject
#include "GameObject/Player2D.h"
#include "GameObject/Bullet.h"
#include "GameObject/Monster.h"

CEditorManager::CEditorManager()
{
}

CEditorManager::~CEditorManager()
{
    CEngine::DestroyInst();

    CTransferCharacterInfo::DestroyInst();
}

bool CEditorManager::Init(HINSTANCE hInst)
{
    // EditorMode肺 汲沥
    CEngine::GetInst()->EnableEditor();

    if (!CEngine::GetInst()->Init(hInst, TEXT("Editor"), TEXT("Editor"), IDI_ICON1, IDI_ICON1, 1280, 720, 1280, 720, true, IDR_MENU1))
        return false;

    CScene::CreateSceneInfoCDO<CEditorDefaultScene>("EditorDefaultScene");

    CEngineShareSetting::Setting();

    CEngine::SetWndProcCallback<CEditorManager>(this, &CEditorManager::WndProc);

    // EditorWindow甸 积己
    CreateEditorWindow();

    // Editor侩 Default SceneInfo 积己
    CSceneManager::GetInst()->CreateSceneInfo<CEditorDefaultScene>();

    return true;
}

int CEditorManager::Run()
{
    return CEngine::GetInst()->Run();
}

bool CEditorManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case ID_FILE_SCENE_SAVE:
            SaveScene();
            return true;
        case ID_FILE_SCENE_OPEN:
            OpenScene();
            return true;
        case ID_FILE_EXIT:
            DestroyWindow(hWnd);
            return true;
        case ID_OBJECT_EMPTY:
            CreateEmptyObject();
            return true;
        case ID_OBJECT:
            CreateObject();
            return true;
        case ID_WINDOW_OBJECT:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ObjectWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_CLASS:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ClassWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_COMPONENT:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("ComponentWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_TRANSFORM:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("TransformWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_SCENE:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CEditorWindow>("SceneWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_DETAIL:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("DetailWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_ANIMATION:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("Animation2DWindow");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_UIWINDOWEDITOR:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("UIWindowEditor");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_UIWIDGETEDITOR:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CDetailWindow>("UIWidgetEditor");

            if (Window)
                Window->Open();
        }
        return true;
        case ID_WINDOW_TILEMAP:
        {
            CEditorWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CTileMapWindow>("TileMapWindow");

            if (Window)
                Window->Open();
        }
        return true;
        }
        break;
    }

    return false;
}

void CEditorManager::SaveScene()
{
}

void CEditorManager::OpenScene()
{
}

void CEditorManager::CreateEmptyObject()
{
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    CGameObject* EmptyObj = Scene->CreateObject<CGameObject>("GameObjectEmpty");

    CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

    if (Window)
    {
        Window->AddItem(EmptyObj, "GameObjectEmpty");
    }
}

void CEditorManager::CreateObject()
{
    CScene* Scene = CSceneManager::GetInst()->GetScene();

    CGameObject* Obj = nullptr;

    CClassWindow* ClassWindow = CEditorGUIManager::GetInst()->FindEditorWindow<CClassWindow>("ClassWindow");

    std::string SelectObjectItem = ClassWindow->GetSelectObjectItem();

    if (SelectObjectItem == "")
        return;

    CObjectWindow* Window = CEditorGUIManager::GetInst()->FindEditorWindow<CObjectWindow>("ObjectWindow");

    if (SelectObjectItem == "GameObject")
        Obj = Scene->CreateObject<CGameObject>(SelectObjectItem);

    else if (SelectObjectItem == "Player2D")
        Obj = Scene->CreateObject<CPlayer2D>(SelectObjectItem);

    else if (SelectObjectItem == "Bullet")
        Obj = Scene->CreateObject<CBullet>(SelectObjectItem);

    else if (SelectObjectItem == "Monster")
        Obj = Scene->CreateObject<CMonster>(SelectObjectItem);

    if (Window)
    {
        Window->AddItem(Obj, SelectObjectItem);
    }
}

void CEditorManager::CreateEditorWindow()
{
    // ObjectWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CObjectWindow>("ObjectWindow");

    // ClassWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CClassWindow>("ClassWindow");

    // ComponentWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CComponentWindow>("ComponentWindow");

    // TransformWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CTransformWindow>("TransformWindow");

    // SceneWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CSceneWindow>("SceneWindow"); // ->Close();

    // DetailWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CDetailWindow>("DetailWindow");

    // Animation2DWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CAnimation2DWindow>("Animation2DWindow")->Close();

    // EditorUIWindow 积己 (弊成 UIWidnow绰 捞固 荤侩吝牢 努贰胶 捞抚捞扼辑 Editor狼 UI Window肺 匙捞怪窃)
    //CEditorGUIManager::GetInst()->CreateEditorWindow<CEditorUIWindow>("EditorUIWindow");

    // UIWindowEditor 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CUIWindowEditor>("UIWindowEditor")->Close();

    // UIWidgetEditor 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CUIWidgetEditor>("UIWidgetEditor")->Close();

    // TileMapWindow 积己
    CEditorGUIManager::GetInst()->CreateEditorWindow<CTileMapWindow>("TileMapWindow")->Close();
}
