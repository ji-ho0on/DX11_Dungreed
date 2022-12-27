#include "DefaultSetting.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "CollisionManager.h"
#include "PathManager.h"

// Animation2D
#include "Animation/Animation2D.h"
#include "../Animation2D/TestAnimation2D.h"
#include "../Animation2D/BirdAnimation.h"
#include "../Animation2D/PlayerAnimation.h"
#include "../Animation2D/CharacterAnimation.h"
#include "../Animation2D/AliceAnimation.h"
#include "../Animation2D/MetalPlateAnimation.h"
#include "../Animation2D/PickaxAnimation.h"
#include "../Animation2D/RedLotusAnimation.h"
#include "../Animation2D/SkelAnimation.h"
#include "../Animation2D/SkelSwordAnimation.h"
#include "../Animation2D/SkelBowAnimation.h"
#include "../Animation2D/ShortSwordSwing.h"
#include "../Animation2D/ArrowHitAnimation.h"
#include "../Animation2D/MonsterDestroyAnimation.h"
#include "../Animation2D/BelialHeadAnimation.h"
#include "../Animation2D/BelialHandAnimation.h"
#include "../Animation2D/BelialBulletAnimation.h"
#include "../Animation2D/BelialBackAnimation.h"
#include "../Animation2D/BelialSwordAnimation.h"
#include "../Animation2D/DoorAnimation.h"
#include "../Animation2D/BansheeAnimation.h"
#include "../Animation2D/BansheeBulletAnimation.h"
#include "../Animation2D/BatBulletAnimation.h"
#include "../Animation2D/NormalBatAnimation.h"
#include "../Animation2D/RedBatAnimation.h"
#include "../Animation2D/GiantNormalBatAnimation.h"
#include "../Animation2D/GiantRedBatAnimation.h"
#include "../Animation2D/GhostAnimation.h"
#include "../Animation2D/DustEffectAnimation.h"
#include "../Animation2D/JumpEffectAnimation.h"
#include "../Animation2D/PortalAnimation.h"
#include "../Animation2D/HorseAnimation.h"
#include "../Animation2D/GoldAnimation.h"


// GameObject
#include "../GameObject/Player2D.h"
#include "../GameObject/Creature.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Bird.h"
#include "../GameObject/FrontCloud.h"
#include "../GameObject/BackCloud.h"
#include "../GameObject/TownBack.h"
#include "../GameObject/Character.h"
#include "../GameObject/SkelSword.h"
#include "../GameObject/SkelSwordAttack.h"
#include "../GameObject/SkelBow.h"
#include "../GameObject/SkelBowAttack.h"
#include "../GameObject/ShortSwordEffect.h"
#include "../GameObject/ArrowHitEffect.h"
#include "../GameObject/MonsterDestroyEffect.h"
#include "../GameObject/Belial.h"
#include "../GameObject/BelialLaser.h"
#include "../GameObject/BelialBullet.h"
#include "../GameObject/BelialSword.h"
#include "../GameObject/Banshee.h"
#include "../GameObject/BansheeBullet.h"
#include "../GameObject/BatBullet.h"
#include "../GameObject/NormalBat.h"
#include "../GameObject/RedBat.h"
#include "../GameObject/GiantNormalBat.h"
#include "../GameObject/GiantRedBat.h"
#include "../GameObject/Ghost.h"
#include "../GameObject/DustEffect.h"
#include "../GameObject/JumpEffect.h"
#include "../GameObject/BossDoor.h"
#include "../GameObject/EndingPortal.h"
#include "../GameObject/Horse.h"
#include "../GameObject/EndingBack.h"
#include "../GameObject/EndingTree.h"
#include "../GameObject/EndingTile.h"
#include "../GameObject/Gold.h"



#include "../GameObject/BossMap.h"
#include "../GameObject/BossEntranceMap.h"
#include "../GameObject/NormalMap1.h"
#include "../GameObject/NormalMap2.h"
#include "../GameObject/NormalMap3.h"
#include "../GameObject/NormalMap4.h"
#include "../GameObject/NormalMap5.h"
#include "../GameObject/NormalMap6.h"

// SceneInfo
#include "../Scene/MainScene.h"
#include "../Scene/LoadingScene.h"
#include "../Scene/TownScene.h"
#include "../Scene/BossScene.h"
#include "../Scene/BossEntranceScene.h"
#include "../Scene/NormalScene.h"
#include "../Scene/NormalScene1.h"
#include "../Scene/NormalScene2.h"
#include "../Scene/NormalScene3.h"
#include "../Scene/NormalScene4.h"
#include "../Scene/NormalScene5.h"
#include "../Scene/NormalScene6.h"
#include "../Scene/EndingScene.h"

// UIWindow
#include "../UI/StartSceneUI.h"
#include "../UI/MainUI.h"
#include "../UI/LoadingUI.h"
#include "../UI/PlaySlotUI.h"
#include "../UI/SettingUI.h"
#include "../UI/CharacterLBUI.h"
#include "../UI/CharacterLTUI.h"
#include "../UI/CharacterHitUI.h"
#include "../UI/BossUI.h"

CDefaultSetting::CDefaultSetting()
{
}

CDefaultSetting::~CDefaultSetting()
{
}

void CDefaultSetting::Init()
{
    LoadResource();

    SetCollision();

    CreateCDO();

    SetInput();
}

void CDefaultSetting::CreateCDO()
{
    // ========== Animation2D ==========
    CScene::CreateAnimationCDO<CTestAnimation2D>("TestAnimation2D");
    CScene::CreateAnimationCDO<CBirdAnimation>("BirdAnimation");
    CScene::CreateAnimationCDO<CPlayerAnimation>("PlayerAnimation");
    CScene::CreateAnimationCDO<CCharacterAnimation>("CharacterAnimation");
    CScene::CreateAnimationCDO<CAliceAnimation>("AliceAnimation");
    CScene::CreateAnimationCDO<CMetalPlateAnimation>("MetalPlateAnimation");
    CScene::CreateAnimationCDO<CPickaxAnimation>("PickaxAnimation");
    CScene::CreateAnimationCDO<CRedLotusAnimation>("RedLotusAnimation");
    CScene::CreateAnimationCDO<CSkelAnimation>("SkelAnimation");
    CScene::CreateAnimationCDO<CSkelSwordAnimation>("SkelSwordAnimation");
    CScene::CreateAnimationCDO<CSkelBowAnimation>("SkelBowAnimation");
    CScene::CreateAnimationCDO<CShortSwordSwing>("ShortSwordSwing");
    CScene::CreateAnimationCDO<CArrowHitAnimation>("ArrowHitAnimation");
    CScene::CreateAnimationCDO<CBelialHeadAnimation>("BelialHeadAnimation");
    CScene::CreateAnimationCDO<CBelialHandAnimation>("BelialHandAnimation");
    CScene::CreateAnimationCDO<CBelialBulletAnimation>("BelialBulletAnimation");
    CScene::CreateAnimationCDO<CBelialBackAnimation>("BelialBackAnimation");
    CScene::CreateAnimationCDO<CBelialSwordAnimation>("BelialSwordAnimation");
    CScene::CreateAnimationCDO<CDoorAnimation>("DoorAnimation");
    CScene::CreateAnimationCDO<CBansheeAnimation>("BansheeAnimation");
    CScene::CreateAnimationCDO<CBansheeBulletAnimation>("BansheeBulletAnimation");
    CScene::CreateAnimationCDO<CBatBulletAnimation>("BatBulletAnimation");
    CScene::CreateAnimationCDO<CNormalBatAnimation>("NormalBatAnimation");
    CScene::CreateAnimationCDO<CRedBatAnimation>("RedBatAnimation");
    CScene::CreateAnimationCDO<CGiantNormalBatAnimation>("GiantNormalBatAnimation");
    CScene::CreateAnimationCDO<CGiantRedBatAnimation>("GiantRedBatAnimation");
    CScene::CreateAnimationCDO<CGhostAnimation>("GhostAnimation");
    CScene::CreateAnimationCDO<CDustEffectAnimation>("DustEffectAnimation");
    CScene::CreateAnimationCDO<CJumpEffectAnimation>("JumpEffectAnimation");
    CScene::CreateAnimationCDO<CPortalAnimation>("PortalAnimation");
    CScene::CreateAnimationCDO<CHorseAnimation>("HorseAnimation");
    CScene::CreateAnimationCDO<CGoldAnimation>("GoldAnimation");

    // ========== GameObject ==========
    CScene::CreateObjectCDO<CCharacter>("Character");
    CScene::CreateObjectCDO<CPlayer2D>("Player2D");
    CScene::CreateObjectCDO<CCreature>("Creature");
    CScene::CreateObjectCDO<CMonster>("Monster");
    CScene::CreateObjectCDO<CBullet>("Bullet");
    CScene::CreateObjectCDO<CBird>("Bird");
    CScene::CreateObjectCDO<CFrontCloud>("FrontCloud");
    CScene::CreateObjectCDO<CBackCloud>("BackCloud");
    CScene::CreateObjectCDO<CTownBack>("TownBack");
    CScene::CreateObjectCDO<CSkelSword>("SkelSword");
    CScene::CreateObjectCDO<CSkelSwordAttack>("SkelSwordAttack");
    CScene::CreateObjectCDO<CSkelBow>("SkelBow");
    CScene::CreateObjectCDO<CSkelBowAttack>("SkelBowAttack");
    CScene::CreateObjectCDO<CShortSwordEffect>("ShortSwordEffect");
    CScene::CreateObjectCDO<CArrowHitEffect>("ArrowHitEffect");
    CScene::CreateObjectCDO<CBelial>("Belial");
    CScene::CreateObjectCDO<CBelialLaser>("BelialLaser");
    CScene::CreateObjectCDO<CBelialBullet>("BelialBullet");
    CScene::CreateObjectCDO<CBelialSword>("BelialSword");
    CScene::CreateObjectCDO<CBanshee>("Banshee");
    CScene::CreateObjectCDO<CBansheeBullet>("BansheeBullet");
    CScene::CreateObjectCDO<CBatBullet>("BatBullet");
    CScene::CreateObjectCDO<CNormalBat>("NormalBat");
    CScene::CreateObjectCDO<CRedBat>("RedBat");
    CScene::CreateObjectCDO<CGiantNormalBat>("GiantNormalBat");
    CScene::CreateObjectCDO<CGiantRedBat>("GiantRedBat");
    CScene::CreateObjectCDO<CGhost>("Ghost");
    CScene::CreateObjectCDO<CDustEffect>("DustEffect");
    CScene::CreateObjectCDO<CJumpEffect>("JumpEffect");
    CScene::CreateObjectCDO<CBossDoor>("BossDoor");
    CScene::CreateObjectCDO<CEndingPortal>("EndingPortal");
    CScene::CreateObjectCDO<CHorse>("Horse");
    CScene::CreateObjectCDO<CEndingBack>("EndingBack");
    CScene::CreateObjectCDO<CEndingTree>("EndingTree");
    CScene::CreateObjectCDO<CEndingTile>("EndingTile");
    CScene::CreateObjectCDO<CGold>("Gold");



    CScene::CreateObjectCDO<CBossMap>("BossMap");
    CScene::CreateObjectCDO<CBossEntranceMap>("BossEntranceMap");
    CScene::CreateObjectCDO<CNormalMap1>("NormalMap1");
    CScene::CreateObjectCDO<CNormalMap2>("NormalMap2");
    CScene::CreateObjectCDO<CNormalMap3>("NormalMap3");
    CScene::CreateObjectCDO<CNormalMap4>("NormalMap4");
    CScene::CreateObjectCDO<CNormalMap5>("NormalMap5");
    CScene::CreateObjectCDO<CNormalMap6>("NormalMap6");

    // ========== SceneInfo ==========
    CScene::CreateSceneInfoCDO<CMainScene>("MainScene");
    CScene::CreateSceneInfoCDO<CLoadingScene>("LoadingScene");
    CScene::CreateSceneInfoCDO<CTownScene>("TownScene");
    CScene::CreateSceneInfoCDO<CBossScene>("BossScene");
    CScene::CreateSceneInfoCDO<CBossEntranceScene>("BossEntranceScene");
    CScene::CreateSceneInfoCDO<CNormalScene>("NormalScene");
    CScene::CreateSceneInfoCDO<CNormalScene1>("NormalScene1");
    CScene::CreateSceneInfoCDO<CNormalScene2>("NormalScene2");
    CScene::CreateSceneInfoCDO<CNormalScene3>("NormalScene3");
    CScene::CreateSceneInfoCDO<CNormalScene4>("NormalScene4");
    CScene::CreateSceneInfoCDO<CNormalScene5>("NormalScene5");
    CScene::CreateSceneInfoCDO<CNormalScene6>("NormalScene6");
    CScene::CreateSceneInfoCDO<CEndingScene>("EndingScene");

    // ========== UIWindow ==========
    CScene::CreateUIWindowCDO<CStartSceneUI>("StartSceneUI");
    CScene::CreateUIWindowCDO<CMainUI>("MainUI");
    CScene::CreateUIWindowCDO<CLoadingUI>("LoadingUI");
    CScene::CreateUIWindowCDO<CPlaySlotUI>("PlaySlotUI");
    CScene::CreateUIWindowCDO<CSettingUI>("SettingUI");
    CScene::CreateUIWindowCDO<CCharacterLBUI>("CharacterLBUI");
    CScene::CreateUIWindowCDO<CCharacterLTUI>("CharacterLTUI");
    CScene::CreateUIWindowCDO<CCharacterHitUI>("CharacterHitUI");
    CScene::CreateUIWindowCDO<CBossUI>("BossUI");
}

void CDefaultSetting::LoadResource()
{
    // 여기서 Animation2D 폴더에 저장된 Sequence들을 CreateAnimationSequence2D 로 다 로딩 해줘야함.
    const PathInfo* Info = CPathManager::GetInst()->FindPath(ROOT_PATH);

    char	Path[MAX_PATH] = {};

    strcpy_s(Path, Info->PathMultibyte);
    strcat_s(Path, "AnimationSequence2D/");

    for (const auto& file : std::filesystem::directory_iterator(Path))
    {
        char	Name[64] = {};
        char	FullPath[MAX_PATH] = {};
        char	Ext[_MAX_EXT] = {};

        strcpy_s(FullPath, file.path().generic_string().c_str());

        _splitpath_s(FullPath, nullptr, 0, nullptr, 0, Name, 64, Ext, _MAX_EXT);

        CResourceManager::GetInst()->LoadSequence2D(Name, FullPath);
    }
}

void CDefaultSetting::SetInput()
{
    // 키 등록
    CInput::GetInst()->AddBindKey("D", 'D');
    CInput::GetInst()->AddBindKey("A", 'A');

    CInput::GetInst()->AddBindKey("W", 'W');
    CInput::GetInst()->AddBindKey("S", 'S');

    CInput::GetInst()->AddBindKey("Space", VK_SPACE);

    CInput::GetInst()->AddBindKey("LClick", VK_LBUTTON);
    CInput::GetInst()->AddBindKey("RClick", VK_RBUTTON);

    CInput::GetInst()->AddBindKey("F", 'F');
}

void CDefaultSetting::SetCollision()
{
    // Channel, Profile 생성 및 Interaction 설정
    CCollisionManager::GetInst()->CreateChannel("Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Monster", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Trigger", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("NPC", ECollision_Interaction::Collision);

    CCollisionManager::GetInst()->CreateProfile("Player", "Player", true);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", "PlayerAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Monster", "Monster", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterAttack", "MonsterAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Trigger", "Trigger", true);
    CCollisionManager::GetInst()->CreateProfile("NPC", "NPC", true);

    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "PlayerAttack", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Trigger", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "NPC", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Trigger", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "NPC", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Trigger", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "NPC", ECollision_Interaction::Ignore);


    CCollisionManager::GetInst()->SetCollisionInteraction("Trigger", "Trigger", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Trigger", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Trigger", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Trigger", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Trigger", "NPC", ECollision_Interaction::Ignore);


    CCollisionManager::GetInst()->SetCollisionInteraction("NPC", "NPC", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("NPC", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("NPC", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("NPC", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("NPC", "Trigger", ECollision_Interaction::Ignore);
}
