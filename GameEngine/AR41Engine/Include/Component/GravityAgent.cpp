#include "GravityAgent.h"
#include "SceneComponent.h"
#include "../GameObject/GameObject.h"
#include "../Scene/Scene.h"
#include "ColliderBox2D.h"
#include "ColliderOBB2D.h"
#include "ColliderSphere2D.h"
#include "ColliderPixel.h"

CGravityAgent::CGravityAgent() :
	m_PhysicsSimulate(false),
	m_GroundCheck(false),
	m_Ground(false),
	m_OneWayThrough(false),
	m_GravityAccel(10.f),
	m_FallTime(0.f),
	m_FallStartY(0.f),
	m_Jump(false),
	m_JumpVelocity(0.f)
{
	m_ComponentType = EComponentType::Object;

	SetTypeID<CGravityAgent>();

	m_ComponentTypeName = "GravityAgent";
}

CGravityAgent::CGravityAgent(const CGravityAgent& Component) :
	CObjectComponent(Component)
{
	m_PhysicsSimulate = Component.m_PhysicsSimulate;
	m_GroundCheck = Component.m_GroundCheck;
	m_Ground = Component.m_Ground;
	m_OneWayThrough = Component.m_OneWayThrough;
	m_OneWayTime = Component.m_OneWayTime;
	m_GravityAccel = Component.m_GravityAccel;
	m_FallTime = Component.m_FallTime;
	m_FallStartY = Component.m_FallStartY;
	m_Jump = Component.m_Jump;
	m_JumpVelocity = Component.m_JumpVelocity;
}

CGravityAgent::~CGravityAgent()
{
}

void CGravityAgent::SetUpdateComponent(CSceneComponent* Component)
{
	m_UpdateComponent = Component;
}

void CGravityAgent::Jump()
{
	if (!m_Jump)
	{
		m_Jump = true;
		m_GroundCheck = false;
		m_Ground = false;

		m_FallTime = 0.f;
		m_FallStartY = m_UpdateComponent->GetWorldPos().y;
	}
}

void CGravityAgent::CheckMoveRight()
{
	Vector2 LB = m_Pos - m_BodyPivot * m_BodySize;
	Vector2 RT = m_Pos + (Vector2(1.f, 1.f) - m_BodyPivot) * m_BodySize;

	Vector2 PrevLB = m_PrevPos - m_BodyPivot * m_BodySize;
	Vector2 PrevRT = m_PrevPos + (Vector2(1.f, 1.f) - m_BodyPivot) * m_BodySize;

	Vector2 ResultLB, ResultRT;

	ResultRT = RT;
	ResultLB.x = PrevRT.x;
	ResultLB.y = LB.y < PrevLB.y ? LB.y : PrevLB.y;
	ResultRT.y = RT.y > PrevRT.y ? RT.y : PrevRT.y;

	int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLB.x, m_Pos.y));
	int TopIndex = m_TileMap->GetTileIndexY(Vector2(m_Pos.x, ResultRT.y));
	int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRT.x, m_Pos.y));
	int BottomIndex = m_TileMap->GetTileIndexY(Vector2(m_Pos.x, ResultLB.y));

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

	if (RightIndex == 9 && RightIndex == LeftIndex)
		int a = 1;

	if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 && RightIndex >= 0 && BottomIndex >= 0)
	{
	   bool SideCollisionCheck = false;

	   for (int i = BottomIndex; i <= TopIndex; ++i)
	   {
	      for (int j = LeftIndex; j <= RightIndex; ++j)
	      {
	         CTile* Tile = m_TileMap->GetTile(j, i);

	         if (Tile->GetTileOption() != ETileOption::SideWall)
	            continue;

	         Vector2 TilePos = Tile->GetPos();
	         Vector2 TileSize = m_TileMap->GetTileSize();

	         if (TilePos.y - 0.001f <= LB.y && RT.y <= TilePos.y + 0.001f)
	            continue;

	         if (LB.x <= TilePos.x + (TileSize.x * 2.f) && RT.y <= TilePos.y + (TileSize.y * 2.f) && RT.x >= TilePos.x && RT.y >= TilePos.y - (TileSize.y * 2.f) )
	         {
	            SideCollisionCheck = true;

	            float MoveX = TilePos.x - RT.x - 0.001f;
	         
	            m_UpdateComponent->SetWorldPositionX(m_UpdateComponent->GetWorldPos().x + MoveX);
	            m_Move.x += MoveX;                              

	            break;
	         }
	      }

	      if (SideCollisionCheck)
	         break;
	   }
	}
}

void CGravityAgent::CheckMoveLeft()
{
	Vector2 LB = m_Pos - m_BodyPivot * m_BodySize;
	Vector2 RT = m_Pos + (Vector2(1.f, 1.f) - m_BodyPivot) * m_BodySize;

	Vector2 PrevLB = m_PrevPos - m_BodyPivot * m_BodySize;
	Vector2 PrevRT = m_PrevPos + (Vector2(1.f, 1.f) - m_BodyPivot) * m_BodySize;

	Vector2 ResultLB, ResultRT;

	ResultLB = LB;
	ResultRT.x = PrevLB.x;
	ResultLB.y = LB.y < PrevLB.y ? LB.y : PrevLB.y;
	ResultRT.y = RT.y > PrevRT.y ? RT.y : PrevRT.y;

	int LeftIndex = m_TileMap->GetTileIndexX(Vector2(ResultLB.x, m_Pos.y));
	int TopIndex = m_TileMap->GetTileIndexY(Vector2(m_Pos.x, ResultRT.y));
	int RightIndex = m_TileMap->GetTileIndexX(Vector2(ResultRT.x, m_Pos.y));
	int BottomIndex = m_TileMap->GetTileIndexY(Vector2(m_Pos.x, ResultLB.y));

	LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
	TopIndex = TopIndex < 0 ? 0 : TopIndex;
	RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
	BottomIndex = BottomIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : BottomIndex;

	if (LeftIndex <= m_TileMap->GetCountX() - 1 && TopIndex <= m_TileMap->GetCountY() - 1 && RightIndex >= 0 && BottomIndex >= 0)
	{
		bool SideCollisionCheck = false;

		for (int i = BottomIndex; i <= TopIndex; ++i)
		{
			for (int j = LeftIndex; j <= RightIndex; ++j)
			{
				CTile* Tile = m_TileMap->GetTile(j, i);

				if (Tile->GetTileOption() != ETileOption::SideWall)
					continue;

				Vector2 TilePos = Tile->GetPos();
				Vector2 TileSize = m_TileMap->GetTileSize();

				if (TilePos.y - 0.001f <= LB.y && RT.y <= TilePos.y + 0.001f)
					continue;

				if (LB.x <= TilePos.x + (TileSize.x * 2.f) && RT.y <= TilePos.y + (TileSize.y * 2.f) && RT.x >= TilePos.x && LB.y >= TilePos.y - (TileSize.y * 2.f))
				{
					SideCollisionCheck = true;

					float MoveX = TilePos.x + TileSize.x - LB.x + 0.001f;

					m_UpdateComponent->SetWorldPositionX(m_UpdateComponent->GetWorldPos().x + MoveX);
					m_Move.x += MoveX;

					break;
				}
			}

			if (SideCollisionCheck)
				break;
		}
	}
}

void CGravityAgent::Destroy()
{
	CObjectComponent::Destroy();
}

void CGravityAgent::Start()
{
	CObjectComponent::Start();

	// GravityAgent가 적용될 Object의 RootComponent는 Collider가 들어가 있을것임
	if (!m_UpdateComponent)
		m_UpdateComponent = m_Owner->GetRootComponent();

	// Start시 Scene에 소속되어 있는 TileMap을 하나 받아둔다.
	if (m_Scene)
		m_TileMap = m_Owner->GetScene()->GetTileMap();

	if (m_UpdateComponent)
	{
		m_Pos = m_UpdateComponent->GetWorldPos();
		m_PrevPos = m_Pos;
		m_BodyPivot = m_UpdateComponent->GetPivot();

		if (((CCollider2D*)m_UpdateComponent.Get())->GetCollider2DType() == ECollider2D_Type::Sphere2D)
			m_BodySize = ((CColliderSphere2D*)m_UpdateComponent.Get())->GetRadius() * 2;

		else if (((CCollider2D*)m_UpdateComponent.Get())->GetCollider2DType() == ECollider2D_Type::Box2D)
			m_BodySize = ((CColliderBox2D*)m_UpdateComponent.Get())->GetBoxSize();

		else if (((CCollider2D*)m_UpdateComponent.Get())->GetCollider2DType() == ECollider2D_Type::OBB2D)
			m_BodySize = ((CColliderOBB2D*)m_UpdateComponent.Get())->GetBoxHalfSize() * 2;

		// 아마 Pixel 충돌체는 안쓸듯
		else if (((CCollider2D*)m_UpdateComponent.Get())->GetCollider2DType() == ECollider2D_Type::Pixel)
			m_BodySize = Vector2((float)((CColliderPixel*)m_UpdateComponent.Get())->GetInfo().Width, (float)((CColliderPixel*)m_UpdateComponent.Get())->GetInfo().Height);
	}
}

bool CGravityAgent::Init()
{
	if (!CObjectComponent::Init())
		return false;

	return true;
}

void CGravityAgent::Update(float DeltaTime)
{
	CObjectComponent::Update(DeltaTime);

	// 중력 적용
	if (m_UpdateComponent && m_PhysicsSimulate)
	{
		if (!m_GroundCheck)
		{
			// 떨어지는 시간을 누적시켜준다.
			m_FallTime += DeltaTime * m_GravityAccel;

			float Velocity = 0.f;

			if (m_Jump)
				Velocity = m_JumpVelocity * m_FallTime;

			// 중력을 적용시킬 Component의 Y값을 갱신한다.
			m_UpdateComponent->SetWorldPositionY((m_FallStartY + (Velocity - 0.5f * GRAVITY * m_FallTime * m_FallTime)));
		}
	}
}

void CGravityAgent::PostUpdate(float DeltaTime)
{
	CObjectComponent::PostUpdate(DeltaTime);

	m_Pos = m_UpdateComponent->GetWorldPos();
	m_Move = m_Pos - m_PrevPos;

	if (m_UpdateComponent && m_TileMap)
	{
		if (m_Move.x != 0.f)
		{
			// 오른쪽으로 이동할때
			if (m_Move.x > 0.f)
			{
				CheckMoveRight();
			}

			// 왼쪽으로 이동할때
			else
			{
				CheckMoveLeft();
			}
		}

		if (m_OneWayThrough)
		{
			m_OneWayTime += DeltaTime;

			if (m_OneWayTime >= 0.4f)
			{
				m_OneWayThrough = false;
				m_OneWayTime = 0.f;
			}
		}

		// 바닥에 착지시킨다.
		if (m_Move.y <= 0.f)
		{
			float	PrevBottom = m_PrevPos.y - m_BodyPivot.y * m_BodySize.y;
			float	CurBottom = m_Pos.y - m_BodyPivot.y * m_BodySize.y;

			float	PrevLeft = m_PrevPos.x - m_BodyPivot.x * m_BodySize.x;
			float	CurLeft = m_Pos.x - m_BodyPivot.x * m_BodySize.x;

			float	PrevRight = m_PrevPos.x + (1.f - m_BodyPivot.x) * m_BodySize.x;
			float	CurRight = m_Pos.x + (1.f - m_BodyPivot.x) * m_BodySize.x;

			float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
			float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
			float ResultTop = PrevBottom > CurBottom ? PrevBottom : CurBottom;
			float ResultBottom = PrevBottom < CurBottom ? PrevBottom : CurBottom;

			Vector2 LB = Vector2(ResultLeft, ResultBottom);
			Vector2 RT = Vector2(ResultRight, ResultTop);

			int LeftIndex = m_TileMap->GetTileIndexX(LB);
			int RightIndex = m_TileMap->GetTileIndexX(RT);
			int TopIndex = m_TileMap->GetTileIndexY(RT);
			int BottomIndex = m_TileMap->GetTileIndexY(LB);

			LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
			BottomIndex = BottomIndex < 0 ? 0 : BottomIndex;
			RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
			TopIndex = TopIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : TopIndex;
			
			if ((LeftIndex <= m_TileMap->GetCountX() - 1) && (TopIndex <= m_TileMap->GetCountY() - 1) && (RightIndex >= 0) && (BottomIndex >= 0))
			{
				bool Check = false;

				// 위에서 아래로 차례로 검사를 해나간다.
				// 아래에서부터 하게 되면 위에 벽이 있을 경우 무시하고 처리되버릴 수도 있기 때문이다.
				for (int i = TopIndex; i <= BottomIndex; ++i)
				{
					for (int j = LeftIndex; j <= RightIndex; ++j)
					{
						CTile* Tile = m_TileMap->GetTile(j, i);

						if (!Tile)
							continue;

						float TileTop = Tile->GetPos().y + Tile->GetSize().y;

						if (TileTop < PrevBottom)
							continue;

						// 현재 타일이 OneWay일 경우 중력을 받으면서 아래로 떨어지는 경우만 걸러준다.
						if (Tile->GetTileOption() == ETileOption::OneWay && !m_GroundCheck)
						{
							// 만약 타일을 파고들었는데 ResultTop < Tile의 Top 일 경우는 패스한다.
							//if (ResultTop + 2.5f < TileTop)
							//	continue;

							// OneWay상태일 때 OneWayThrough 가 되면 통과한다.
							if (m_OneWayThrough)
								break;

							Check = true;
							m_FallTime = 0.f;

							// 현재 타일의 Top을 이 오브젝트의 Bottom값으로 지정한다.
							m_UpdateComponent->SetWorldPositionY(TileTop + m_UpdateComponent->GetPivot().y * m_BodySize.y + 0.05f);
							m_GroundCheck = true;
							m_Jump = false;
							m_OneWayThrough = false;
							break;
						}

						// 현재 타일이 Wall일 경우 바닥을 밟았다는 것이다.
						if (Tile->GetTileOption() == ETileOption::Wall)
						{
							Check = true;
							m_FallTime = 0.f;

							// 0.05만큼 미세 보정값
							m_UpdateComponent->SetWorldPositionY(TileTop + m_UpdateComponent->GetPivot().y * m_BodySize.y + 0.05f);
							m_GroundCheck = true;
							m_Jump = false;
							m_OneWayThrough = false;
							break;
						}
					}

					if (Check)
						break;
				}

				// 바닥이 없을 경우
				if (!Check)
				{
					// 땅을 밟고 있던 상태라면 이제 떨어지는 상태가 될것이다.
					if (m_GroundCheck)
					{
						m_FallTime = 0.f;
						m_FallStartY = m_UpdateComponent->GetWorldPos().y;
					}

					m_GroundCheck = false;
				}

				// GroundCheck 상태에서 Y방향 움직임이 미미하다면 땅을 밟고있는것으로 간주
				if (m_GroundCheck && ::abs(m_Move.y) < 0.5f)
					m_Ground = true;


				if (m_Ground)
				{
					if (m_Jump)
						m_Ground = false;

					else if (::abs(m_Move.y) >= 0.5f)
						m_Ground = false;
				}

			}
		}

		else
		{
			// 위로 올라갈 때 천장 Tile에 부딪혀야함.
			float	PrevTop = m_PrevPos.y + (1.f - m_BodyPivot.y) * m_BodySize.y;
			float	CurTop = m_Pos.y + (1.f - m_BodyPivot.y) * m_BodySize.y;

			float	PrevLeft = m_PrevPos.x - m_BodyPivot.x * m_BodySize.x;
			float	CurLeft = m_Pos.x - m_BodyPivot.x * m_BodySize.x;

			float	PrevRight = m_PrevPos.x + (1.f - m_BodyPivot.x) * m_BodySize.x;
			float	CurRight = m_Pos.x + (1.f - m_BodyPivot.x) * m_BodySize.x;

			float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
			float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
			float ResultTop = PrevTop > CurTop ? PrevTop : CurTop;
			float ResultBottom = PrevTop < CurTop ? PrevTop : CurTop;

			Vector2 LB = Vector2(ResultLeft, ResultBottom);
			Vector2 RT = Vector2(ResultRight, ResultTop);

			int LeftIndex = m_TileMap->GetTileIndexX(LB);
			int RightIndex = m_TileMap->GetTileIndexX(RT);
			int TopIndex = m_TileMap->GetTileIndexY(RT);
			int BottomIndex = m_TileMap->GetTileIndexY(LB);

			LeftIndex = LeftIndex < 0 ? 0 : LeftIndex;
			BottomIndex = BottomIndex < 0 ? 0 : BottomIndex;
			RightIndex = RightIndex > m_TileMap->GetCountX() - 1 ? m_TileMap->GetCountX() - 1 : RightIndex;
			TopIndex = TopIndex > m_TileMap->GetCountY() - 1 ? m_TileMap->GetCountY() - 1 : TopIndex;

			if ((LeftIndex <= m_TileMap->GetCountX() - 1) && (TopIndex <= m_TileMap->GetCountY() - 1) && (RightIndex >= 0) && (BottomIndex >= 0))
			{
				bool Check = false;

				// 아래에서 위로 차례로 검사를 해나간다.
				for (int i = BottomIndex; i <= TopIndex; ++i)
				{
					for (int j = LeftIndex; j <= RightIndex; ++j)
					{
						CTile* Tile = m_TileMap->GetTile(j, i);

						if (!Tile)
							continue;

						float TileBottom = Tile->GetPos().y;

						if (TileBottom > PrevTop)
							continue;

						// 현재 타일이 Wall일 경우 천장에 닿았다는 것이다.
						if (Tile->GetTileOption() == ETileOption::Wall)
						{
							Check = true;

							m_UpdateComponent->SetWorldPositionY(TileBottom - (1.f - m_UpdateComponent->GetPivot().y) * m_BodySize.y);
							break;
						}
					}

					if (Check)
						break;
				}
			}
		}
	}

	m_PrevPos = m_Pos;
}

void CGravityAgent::Render()
{
	CObjectComponent::Render();
}

CGravityAgent* CGravityAgent::Clone() const
{
	return new CGravityAgent(*this);
}

void CGravityAgent::Save(FILE* File)
{
	CObjectComponent::Save(File);

	/*
    bool                                m_PhysicsSimulate;
    bool		                        m_GroundCheck;      // 땅을 밟았는지 체크
    bool                                m_Ground;           // 땅을 밟고있는 상태인지
    bool                                m_OneWayThrough;     // OneWay를 통과할 것인지
    float                               m_OneWayTime;
    float		                        m_GravityAccel;
    float		                        m_FallTime;
    float		                        m_FallStartY;
    bool		                        m_Jump;
    float		                        m_JumpVelocity;
	*/

	fwrite(&m_PhysicsSimulate, sizeof(bool), 1, File);
	fwrite(&m_GroundCheck, sizeof(bool), 1, File);
	fwrite(&m_Ground, sizeof(bool), 1, File);
	fwrite(&m_OneWayThrough, sizeof(bool), 1, File);
	fwrite(&m_OneWayTime, sizeof(float), 1, File);
	fwrite(&m_GravityAccel, sizeof(float), 1, File);
	fwrite(&m_FallTime, sizeof(float), 1, File);
	fwrite(&m_FallStartY, sizeof(float), 1, File);
	fwrite(&m_Jump, sizeof(bool), 1, File);
	fwrite(&m_JumpVelocity, sizeof(float), 1, File);
}

void CGravityAgent::Load(FILE* File)
{
	CObjectComponent::Load(File);

	fread(&m_PhysicsSimulate, sizeof(bool), 1, File);
	fread(&m_GroundCheck, sizeof(bool), 1, File);
	fread(&m_Ground, sizeof(bool), 1, File);
	fread(&m_OneWayThrough, sizeof(bool), 1, File);
	fread(&m_OneWayTime, sizeof(float), 1, File);
	fread(&m_GravityAccel, sizeof(float), 1, File);
	fread(&m_FallTime, sizeof(float), 1, File);
	fread(&m_FallStartY, sizeof(float), 1, File);
	fread(&m_Jump, sizeof(bool), 1, File);
	fread(&m_JumpVelocity, sizeof(float), 1, File);
}