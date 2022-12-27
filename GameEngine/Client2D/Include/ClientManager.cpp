#include "ClientManager.h"
#include "Scene/SceneManager.h"
#include "Scene/MainScene.h"
#include "Input.h"
#include "Setting/EngineShareSetting.h"
#include "TransferInfo/TransferCharacterInfo.h"

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
    CEngine::DestroyInst();

    CTransferCharacterInfo::DestroyInst();
}

bool CClientManager::Init(HINSTANCE hInst)
{
    // Engine을 초기화
    // ClientManager가 소멸하면 Engine도 Destroy되기 때문에 실패시 DestroyInst를 굳이 넣지 않았음
    if (!CEngine::GetInst()->Init(hInst, TEXT("Client2D"), TEXT("Client2D"), IDI_ICON1, IDI_ICON1, 1280, 720, 1280, 720, true))
        return false;

    CEngineShareSetting::Setting();

    // SceneInfo 생성
    CSceneManager::GetInst()->CreateSceneInfo<CMainScene>();

    return true;
}

int CClientManager::Run()
{
    return CEngine::GetInst()->Run();
}
