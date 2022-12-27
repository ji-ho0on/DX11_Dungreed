#include "ComponentWidgetList.h"

CComponentWidgetList::CComponentWidgetList()
{
}

CComponentWidgetList::~CComponentWidgetList()
{
}

bool CComponentWidgetList::Init()
{
    return true;
}

void CComponentWidgetList::Render()
{
    CEditorGroup::Render();
}

void CComponentWidgetList::SetComponentContents(CSceneComponent* Component)
{
}
