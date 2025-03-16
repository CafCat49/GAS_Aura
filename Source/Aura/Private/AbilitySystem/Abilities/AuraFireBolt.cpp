// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "Aura/Public/AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 Damage = GetDamageByType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n" //Level
			"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
			"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown
	
			// Description
			"<Default>Launches a bolt of fire, exploding on impact and dealing "
			"</><Damage>%d </><Default>fire damage with a chance to burn.</>"), //Damage

			// Values
			Level,
			ManaCost,
			Cooldown,
			Damage);
	}
	// Alt description for higher levels
	return FString::Printf(TEXT(
		// Title
		"<Title>FIRE BOLT</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n" //Level
		"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
		"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown

		// Description
		"<Default>Launches %d bolts of fire, exploding on impact and dealing " //ProjectileCount
		"</><Damage>%d </><Default>fire damage with a chance to burn.</>"), //Damage

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, ProjectileCount),
		Damage);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = GetDamageByType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n" //Level
		"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
		"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown

		// Description
		"<Default>Launches %d bolts of fire, exploding on impact and dealing " //ProjectileCount
		"</><Damage>%d </><Default>fire damage with a chance to burn.</>"), //Damage

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, ProjectileCount),
		Damage);
}