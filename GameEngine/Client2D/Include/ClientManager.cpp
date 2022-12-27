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
    // Engine�� �ʱ�ȭ
    // ClientManager�� �Ҹ��ϸ� Engine�� Destroy�Ǳ� ������ ���н� DestroyInst�� ���� ���� �ʾ���
    if (!CEngine::GetInst()->Init(hInst, TEXT("Client2D"), TEXT("Client2D"), IDI_ICON1, IDI_ICON1, 1280, 720, 1280, 720, true))
        return false;

    CEngineShareSetting::Setting();

    // SceneInfo ����
    CSceneManager::GetInst()->CreateSceneInfo<CMainScene>();

    return true;
}

int CClientManager::Run()
{
    return CEngine::GetInst()->Run();
}
