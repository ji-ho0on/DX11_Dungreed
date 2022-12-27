#pragma once

#include "EngineInfo.h"

class CTransferCharacterInfo
{
public:
	void ReadInfo(class CCharacter* Character);
	void SetInfo(class CCharacter* Character);

private:
	int	m_Level;
	int	m_HP;
	int m_HPMax;
	int m_Power;
	int m_Armor;
	int m_DashCount;
	int m_Gold;
	int m_Satiety;
	int m_SatietyMax;

public:
	DECLARE_SINGLE(CTransferCharacterInfo)
};

