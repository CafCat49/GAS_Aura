// Copyright Caffeinated Cat


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 xp)
{
	int32 level = 1;

	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= level) return level;

		if (xp >=  LevelUpInformation[level].LevelUpRequirement)
		{
			++level;
		}
		else
		{
			bSearching = false;
		}
	}
	
	return level;
}
