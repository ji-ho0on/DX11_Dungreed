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
	// NextScene 생성, Scene 전환은 되지 않도록 AutoChange를 false로 설정
	CSceneManager::GetInst()->CreateNextScene(false);

	const PathInfo* Info = CPathManager::GetInst()->FindPath(m_PathName);

	m_FullPath = Info->PathMultibyte + m_FileName;

	// Scene을 Load하면서 LoadingUI에 진행율을 전달해줄 함수 세팅
	CSceneManager::GetInst()->GetNextScene()->SetLoadingCallback<CLoadingThread>(this, &CLoadingThread::LoadingCallback);

	// 생성한 Scene을 FullPath를 통해 Load
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
