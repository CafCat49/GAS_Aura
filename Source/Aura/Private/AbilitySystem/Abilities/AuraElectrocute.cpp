// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraElectrocute.h"

FString UAuraElectrocute::GetDescription(int32 Level)
{
	const int32 ScaledDmg = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n" //Level
			"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
			"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown
	
			// Description
			"<Default>Emits a beam of lightning, connecting with the target, repeatedly dealing "
			"</><Damage>%d </><Default>lightning damage with a chance to stun.</>"), //Damage

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDmg);
	}
	// Alt description for higher levels
	return FString::Printf(TEXT(
		// Title
		"<Title>ELECTROCUTE</>\n\n"

		// Details
		"<Small>Level: </><Level>%d</>\n" //Level
		"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
		"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown

		// Description
		"<Default>Emits a beam of lightning, spreading to %d additional targets, repeatedly dealing " //MaxShockTargets
		"</><Damage>%d </><Default>lightning damage with a chance to stun.</>"), //Damage

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxShockTargets) - 1,
		ScaledDmg);
}

FString UAuraElectrocute::GetNextLevelDescription(int32 Level)
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
		"<Default>Emits a beam of lightning, spreading to %d additional targets, repeatedly dealing " //MaxShockTargets
		"</><Damage>%d </><Default>lightning damage with a chance to stun.</>"), //Damage
	
		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxShockTargets) - 1,
		ScaledDmg);
}
