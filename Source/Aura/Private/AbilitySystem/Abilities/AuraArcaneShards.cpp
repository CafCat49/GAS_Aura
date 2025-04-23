// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraArcaneShards.h"

FString UAuraArcaneShards::GetDescription(int32 Level)
{
	const int32 ScaledDmg = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ARCANE SHARDS</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n" //Level
			"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
			"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown
	
			// Description
			"<Default>Summon a shard of arcane energy, dealing </>"
			"<Damage>%d </><Default>radial arcane damage at the shard origin.</>"), //Damage

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDmg);
	}
	// Alt description for higher levels
	return FString::Printf(TEXT(
		// Title
		"<Title>ARCANE SHARDS</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n" //Level
		"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
		"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown

		// Description
		"<Default>Summon %d shards of arcane energy, dealing </>" //Level
		"<Damage>%d </><Default>radial arcane damage at the shards' origins.</>"), //Damage

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxShards),
		ScaledDmg);
}

FString UAuraArcaneShards::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDmg = Damage.GetValueAtLevel(Level);
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
		"<Default>Summon %d shards of arcane energy, dealing </>" //Level
		"<Damage>%d </><Default>radial arcane damage at the shards' origins.</>"), //Damage

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxShards),
		ScaledDmg);
}
