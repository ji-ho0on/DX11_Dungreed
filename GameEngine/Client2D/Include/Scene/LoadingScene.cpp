#include "LoadingScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneViewport.h"
#include "../UI/LoadingUI.h"
#include "Thread/ThreadManager.h"
#include "Thread/LoadingThread.h"
#include "Thread/ThreadQueue.h"
#include "Thread/DataStream.h"

CLoadingScene::CLoadingScene()
{
}

CLoadingScene::CLoadingScene(const CLoadingScene& SceneInfo)
{
}

CLoadingScene::~CLoadingScene()
{
}

bool CLoadingScene::Init()
{
	m_LoadingUI = m_Owner->GetViewport()->CreateUIWindow<CLoadingUI>("LoadingUI");

	return true;
}

void CLoadingScene::Update(float DeltaTime)
{
	CSceneInfo::Update(DeltaTime);

	// Queue�� �����Ͱ� ���� ��� �޾ƿͼ� ó���Ѵ�.
	if (!m_LoadingQueue->empty())
	{
		int	Header, Size;
		unsigned char	Data[1024] = {};

		m_LoadingQueue->pop(&Header, &Size, Data);

		CDataStream	stream;
		stream.SetBuffer(Data);

		float	Rate = 0.f;

		stream.GetData<float>(&Rate, 4);

		m_LoadingUI->SetLoadingPercent(Rate);
	}

	if (m_LoadingThread->IsLoadComplete())
	{
		CSceneManager::GetInst()->ChangeNextScene();

		CThreadManager::GetInst()->Delete("Loading");
	}
}

void CLoadingScene::SceneChangeComplete()
{
	// �ε� ������ ����
	m_LoadingThread = CThreadManager::GetInst()->Create<CLoadingThread>("LoadingThread");

	m_LoadingThread->SetLoadingSceneFileName("TestScene.scn");

	m_LoadingQueue = m_LoadingThread->GetQueue();

	m_LoadingThread->Start();
}
