#include "Thread.h"
#include "Sync.h"

CThread::CThread() :
    m_Loop(false),
    m_Suspend(false)
{
}

CThread::~CThread()
{
    //Stop();

    DeleteCriticalSection(&m_CRT);
}

void CThread::Suspend()
{
    CSync   sync(&m_CRT);

    SuspendThread(m_Thread);

    m_Suspend = true;
}

void CThread::Resume()
{
    CSync   sync(&m_CRT);

    DWORD Count = ResumeThread(m_Thread);

    if (Count > 0)
        m_Suspend = false;
}

void CThread::ReStart()
{
    CSync   sync(&m_CRT);

    DWORD Count = 0;

    do
    {
        Count = ResumeThread(m_Thread);
    } while(Count > 0);

    m_Suspend = false;
}

void CThread::Stop()
{
    if (m_Thread)
    {
        m_Loop = false;
        Start();
        ReStart();

        // 스레드가 종료될 때까지 기다린다.
        WaitForSingleObject(m_Thread, INFINITE);
        CloseHandle(m_Thread);
        m_Thread = 0;
    }
}

void CThread::Start()
{
    // 이벤트 동기화를 위한 핸들에 신호를 준다.
    SetEvent(m_StartEvent);
}

bool CThread::Init()
{
    m_StartEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    InitializeCriticalSection(&m_CRT);

    m_Thread = (HANDLE)_beginthreadex(nullptr, 0, CThread::ThreadFunction, (void*)this, 0, nullptr);

    return true;
}

unsigned int __stdcall CThread::ThreadFunction(void* Arg)
{
    CThread* Thread = (CThread*)Arg;

    // 스레드를 시작하기 전에 이벤트 동기화
    // 신호가 있을 때까지 대기시키는 함수, 밀리세컨드를 무한으로 설정하면 내가 원할 때까지 무한으로 대기시킬 수 있음
    // 이후에 m_StartEvent를 내가 원하는 타이밍에 신호를 줄 수 있게끔 하여 Thread의 Loop를 동작한다.
    WaitForSingleObject(Thread->m_StartEvent, INFINITE);

    do
    {
        Thread->Run();
    } while (Thread->m_Loop);

    return 0;
}
