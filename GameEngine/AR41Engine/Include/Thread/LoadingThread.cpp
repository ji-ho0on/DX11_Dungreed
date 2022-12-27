#include "LoadingThread.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../PathManager.h"
#include "DataStream.h"

CLoadingThread::CLoadingThread() :
	m_LoadComplete(false)
{
	m_PathName = SCENE_PATH;
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::Run()
{
	// NextScene ����, Scene ��ȯ�� ���� �ʵ��� AutoChange�� false�� ����
	CSceneManager::GetInst()->CreateNextScene(false);

	const PathInfo* Info = CPathManager::GetInst()->FindPath(m_PathName);

	m_FullPath = Info->PathMultibyte + m_FileName;

	// Scene�� Load�ϸ鼭 LoadingUI�� �������� �������� �Լ� ����
	CSceneManager::GetInst()->GetNextScene()->SetLoadingCallback<CLoadingThread>(this, &CLoadingThread::LoadingCallback);

	// ������ Scene�� FullPath�� ���� Load
	CSceneManager::GetInst()->GetNextScene()->Load(m_FullPath.c_str());

	m_LoadComplete = true;
}

void CLoadingThread::LoadingCallback(float Rate)
{
	unsigned char	Buffer[1024] = {};

	CDataStream	stream;
	stream.SetBuffer(Buffer);

	stream.AddData<float>(&Rate, sizeof(float));

	m_Queue.push((int)ELoadingHeader::LoadingRate, stream.GetSize(), Buffer);

	Sleep(200);
}
