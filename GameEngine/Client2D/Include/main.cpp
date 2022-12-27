#include "ClientManager.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // Client 2D�� Manager ����
    CClientManager  mgr;

    if (!mgr.Init(hInstance))
        return 0;

    int Ret = mgr.Run();

    return Ret;
}