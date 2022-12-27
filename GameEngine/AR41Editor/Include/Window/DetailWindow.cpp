#include "DetailWindow.h"
#include "Component/SceneComponent.h"

// WidgetList
#include "DetailWindow/SceneComponentWidgetList.h"
#include "DetailWindow/PrimitiveComponentWidgetList.h"
#include "DetailWindow/SpriteComponentWidgetList.h"
#include "DetailWindow/TileMapComponentWidgetList.h"
#include "DetailWindow/CameraComponentWidgetList.h"
#include "DetailWindow/TargetArmWidgetList.h"
#include "DetailWindow/ColliderWidgetList.h"
#include "DetailWindow/Collider2DWidgetList.h"
#include "DetailWindow/ColliderBox2DWidgetList.h"
#include "DetailWindow/ColliderOBB2DWidgetList.h"
#include "DetailWindow/ColliderSphere2DWidgetList.h"
#include "DetailWindow/ColliderPixelWidgetList.h"
#include "DetailWindow/ColliderLine2DWidgetList.h"
#include "DetailWindow/Collider3DWidgetList.h"

CDetailWindow::CDetailWindow()
{
}

CDetailWindow::~CDetailWindow()
{
	ClearWidget();

	size_t	Size = m_vecComponentWidgetList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		AddWidget(m_vecComponentWidgetList[i]);
	}
}

CComponentWidgetList* CDetailWindow::GetComponentWidgetList(ESceneComponentType Type)
{
	if ((int)Type <= (int)ESceneComponentType::Max)
		return m_vecComponentWidgetList[(int)Type];

	return nullptr;
}

void CDetailWindow::SetSelectComponent(CSceneComponent* Component)
{
	// 처음 선택시 m_SelectComponent가 없으면 바로 위젯을 바꿔줌
	if (!m_SelectComponent)
	{
		ClearWidget();
		ChangeWidget(Component);
	}

	// m_SelectComponent가 있고 Component가 들어왔을 경우 서로 다른 Component라면 위젯을 바꿔줌
	if (m_SelectComponent && Component)
	{
		if (m_SelectComponent != Component)
		{
			ClearWidget();

			// 타입에 맞는 GUI 추가
			ChangeWidget(Component);
		}
	}

	// m_SelectComponent를 들어온 Component로 교체
	m_SelectComponent = Component;
}

bool CDetailWindow::Init()
{
	m_vecComponentWidgetList.resize(size_t(ESceneComponentType::Max));

	for (int i = 0; i < (int)ESceneComponentType::Max; ++i)
	{
		CreateEditorWidgetList((ESceneComponentType)i);
	}

	// 위젯 한번 지워주기
	ClearWidget();

	return true;
}

void CDetailWindow::Update(float DeltaTime)
{
	CEditorWindow::Update(DeltaTime);

	if (m_SelectComponent)
	{
		if (!m_SelectComponent->GetActive())
		{
			m_SelectComponent = nullptr;
			ClearWidget();
		}
	}
}

void CDetailWindow::CreateEditorWidgetList(ESceneComponentType Type)
{
	CComponentWidgetList* WidgetList = nullptr;

	switch (Type)
	{
	case ESceneComponentType::Scene:
		WidgetList = CreateWidgetEmpty<CSceneComponentWidgetList>("SceneComponent");
		break;
	case ESceneComponentType::Primitive:
		WidgetList = CreateWidgetEmpty<CPrimitiveComponentWidgetList>("PrimitiveComponent");
		break;
	case ESceneComponentType::Sprite:
		WidgetList = CreateWidgetEmpty<CSpriteComponentWidgetList>("SpriteComponent");
		break;
	case ESceneComponentType::TileMap:
		WidgetList = CreateWidgetEmpty<CTileMapComponentWidgetList>("TileMapComponent");
		break;
	case ESceneComponentType::Camera:
		WidgetList = CreateWidgetEmpty<CCameraComponentWidgetList>("CameraComponent");
		break;
	case ESceneComponentType::TargetArm:
		WidgetList = CreateWidgetEmpty<CTargetArmWidgetList>("TargetArm");
		break;
	case ESceneComponentType::Collider:
		WidgetList = CreateWidgetEmpty<CColliderWidgetList>("Collider");
		break;
	case ESceneComponentType::Collider2D:
		WidgetList = CreateWidgetEmpty<CCollider2DWidgetList>("Collider2D");
		break;
	case ESceneComponentType::ColliderBox2D:
		WidgetList = CreateWidgetEmpty<CColliderBox2DWidgetList>("ColliderBox2D");
		break;
	case ESceneComponentType::ColliderOBB2D:
		WidgetList = CreateWidgetEmpty<CColliderOBB2DWidgetList>("ColliderOBB2D");
		break;
	case ESceneComponentType::ColliderSphere2D:
		WidgetList = CreateWidgetEmpty<CColliderSphere2DWidgetList>("ColliderSphere2D");
		break;
	case ESceneComponentType::ColliderPixel:
		WidgetList = CreateWidgetEmpty<CColliderPixelWidgetList>("ColliderPixel");
		break;
	case ESceneComponentType::ColliderLine2D:
		WidgetList = CreateWidgetEmpty<CColliderLine2DWidgetList>("ColliderLine2D");
		break;
	case ESceneComponentType::Collider3D:
		WidgetList = CreateWidgetEmpty<CCollider3DWidgetList>("Collider3D");
		break;
	}

	if (!WidgetList)
		return;

	WidgetList->m_DetailWindow = this;

	m_vecComponentWidgetList[(int)Type] = WidgetList;
}

void CDetailWindow::ChangeWidget(CSceneComponent* Component)
{
	if (!Component)
		return;

	if (Component->GetComponentTypeName() == "SceneComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Scene]);
	}

	else if (Component->GetComponentTypeName() == "PrimitiveComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Primitive]);
		((CPrimitiveComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Primitive])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "SpriteComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Primitive]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Sprite]);

		((CPrimitiveComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Primitive])->SetComponentContents(Component);
		((CSpriteComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Sprite])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "TileMapComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Primitive]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::TileMap]);

		((CPrimitiveComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Primitive])->SetComponentContents(Component);
		((CTileMapComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::TileMap])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "CameraComponent")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Camera]);
		((CCameraComponentWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Camera])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "TargetArm")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::TargetArm]);
		((CTargetArmWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::TargetArm])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "Collider")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "Collider2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D]);

		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
		((CCollider2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "ColliderBox2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::ColliderBox2D]);

		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
		((CCollider2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D])->SetComponentContents(Component);
		((CColliderBox2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::ColliderBox2D])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "ColliderOBB2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::ColliderOBB2D]);

		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
		((CCollider2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D])->SetComponentContents(Component);
		((CColliderOBB2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::ColliderOBB2D])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "ColliderSphere2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::ColliderSphere2D]);

		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
		((CCollider2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D])->SetComponentContents(Component);
		((CColliderSphere2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::ColliderSphere2D])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "ColliderPixel")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::ColliderPixel]);

		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
		((CCollider2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D])->SetComponentContents(Component);
		((CColliderPixelWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::ColliderPixel])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "ColliderLine2D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::ColliderLine2D]);

		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
		((CCollider2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider2D])->SetComponentContents(Component);
		((CColliderLine2DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::ColliderLine2D])->SetComponentContents(Component);
	}

	else if (Component->GetComponentTypeName() == "Collider3D")
	{
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider]);
		AddWidget(m_vecComponentWidgetList[(int)ESceneComponentType::Collider3D]);

		((CColliderWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider])->SetComponentContents(Component);
		((CCollider3DWidgetList*)m_vecComponentWidgetList[(int)ESceneComponentType::Collider3D])->SetComponentContents(Component);
	}
}
