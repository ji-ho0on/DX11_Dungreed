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

	// GravityAgent�� ����� Object�� RootComponent�� Collider�� �� ��������
	if (!m_UpdateComponent)
		m_UpdateComponent = m_Owner->GetRootComponent();

	// Start�� Scene�� �ҼӵǾ� �ִ� TileMap�� �ϳ� �޾Ƶд�.
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

		// �Ƹ� Pixel �浹ü�� �Ⱦ���
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

	// �߷� ����
	if (m_UpdateComponent && m_PhysicsSimulate)
	{
		if (!m_GroundCheck)
		{
			// �������� �ð��� ���������ش�.
			m_FallTime += DeltaTime * m_GravityAccel;

			float Velocity = 0.f;

			if (m_Jump)
				Velocity = m_JumpVelocity * m_FallTime;

			// �߷��� �����ų Component�� Y���� �����Ѵ�.
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
			// ���������� �̵��Ҷ�
			if (m_Move.x > 0.f)
			{
				CheckMoveRight();
			}

			// �������� �̵��Ҷ�
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

		// �ٴڿ� ������Ų��.
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

				// ������ �Ʒ��� ���ʷ� �˻縦 �س�����.
				// �Ʒ��������� �ϰ� �Ǹ� ���� ���� ���� ��� �����ϰ� ó���ǹ��� ���� �ֱ� �����̴�.
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

						// ���� Ÿ���� OneWay�� ��� �߷��� �����鼭 �Ʒ��� �������� ��츸 �ɷ��ش�.
						if (Tile->GetTileOption() == ETileOption::OneWay && !m_GroundCheck)
						{
							// ���� Ÿ���� �İ����µ� ResultTop < Tile�� Top �� ���� �н��Ѵ�.
							//if (ResultTop + 2.5f < TileTop)
							//	continue;

							// OneWay������ �� OneWayThrough �� �Ǹ� ����Ѵ�.
							if (m_OneWayThrough)
								break;

							Check = true;
							m_FallTime = 0.f;

							// ���� Ÿ���� Top�� �� ������Ʈ�� Bottom������ �����Ѵ�.
							m_UpdateComponent->SetWorldPositionY(TileTop + m_UpdateComponent->GetPivot().y * m_BodySize.y + 0.05f);
							m_GroundCheck = true;
							m_Jump = false;
							m_OneWayThrough = false;
							break;
						}

						// ���� Ÿ���� Wall�� ��� �ٴ��� ��Ҵٴ� ���̴�.
						if (Tile->GetTileOption() == ETileOption::Wall)
						{
							Check = true;
							m_FallTime = 0.f;

							// 0.05��ŭ �̼� ������
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

				// �ٴ��� ���� ���
				if (!Check)
				{
					// ���� ��� �ִ� ���¶�� ���� �������� ���°� �ɰ��̴�.
					if (m_GroundCheck)
					{
						m_FallTime = 0.f;
						m_FallStartY = m_UpdateComponent->GetWorldPos().y;
					}

					m_GroundCheck = false;
				}

				// GroundCheck ���¿��� Y���� �������� �̹��ϴٸ� ���� ����ִ°����� ����
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
			// ���� �ö� �� õ�� Tile�� �ε�������.
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

				// �Ʒ����� ���� ���ʷ� �˻縦 �س�����.
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

						// ���� Ÿ���� Wall�� ��� õ�忡 ��Ҵٴ� ���̴�.
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
    bool		                        m_GroundCheck;      // ���� ��Ҵ��� üũ
    bool                                m_Ground;           // ���� ����ִ� ��������
    bool                                m_OneWayThrough;     // OneWay�� ����� ������
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