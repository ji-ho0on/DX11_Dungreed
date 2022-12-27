#include "TransferCharacterInfo.h"
#include "../GameObject/Character.h"

DEFINITION_SINGLE(CTransferCharacterInfo);

CTransferCharacterInfo::CTransferCharacterInfo()
{

}

CTransferCharacterInfo::~CTransferCharacterInfo()
{

}

void CTransferCharacterInfo::ReadInfo(CCharacter* Character)
{
	if (!Character)
		return;

	m_Level = Character->GetLevel();
	m_HP = Character->GetHP();
	m_HPMax = Character->GetHPMax();
	m_Power = Character->GetPower();
	m_Armor = Character->GetArmor();
	m_DashCount = Character->GetDashCount();
	m_Gold = Character->GetGold();
	m_Satiety = Character->GetSatiety();
	m_SatietyMax = Character->GetSatietyMax();
}

void CTransferCharacterInfo::SetInfo(CCharacter* Character)
{
	if (!Character)
		return;

	Character->SetLevel(m_Level);
	Character->SetHP(m_HP);
	Character->SetHPMax(m_HPMax);
	Character->SetPower(m_Power);
	Character->SetArmor(m_Armor);
	Character->SetDashCount(m_DashCount);
	Character->SetGold(m_Gold);
	Character->SetSatiety(m_Satiety);
	Character->SetSatietyMax(m_SatietyMax);
}
