#pragma once

#include "Thread.h"
#include "ThreadQueue.h"

class CNavigationThread :
    public CThread
{
	friend class CThreadManager;

protected:
	CNavigationThread();
	virtual ~CNavigationThread();

private:
	class CTileMapComponent*	m_TileMapComponent;
	class CNavigation*			m_Navigation;
	CThreadQueue				m_InputQueue;	// 길찾기를 요청받은 Queue

public:
	int GetWorkCount()
	{
		return m_InputQueue.size();
	}

public:
	void SetTileMapComponent(class CTileMapComponent* TileMapComponent);

	void AddInputData(class CNavigationAgent* Agent, const Vector2& End);

public:
	virtual void Run();
};

