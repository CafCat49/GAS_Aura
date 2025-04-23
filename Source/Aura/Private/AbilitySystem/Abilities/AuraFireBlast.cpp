// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraFireBlast.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 ScaledDmg = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BLAST</>\n\n"

			// Details
			"<Small>Level: </><Level>%d</>\n" //Level
			"<Small>Mana cost: </><ManaCost>%.1f</>\n" //ManaCost
			"<Small>Cooldown: </><Cooldown>%.1f</><Small>s</>\n\n" //Cooldown
	
			// Description
			"<Default>Launches %d fire balls in all directions, each coming back and exploding on return, </>" //FireBallAmount
			"dealing <Damage>%d </><Default> radial fire damage with a chance to burn.</>"), //Damage

			// Values
			Level,
			ManaCost,
			Cooldown,
			FireBallAmount,
			ScaledDmg);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
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
			"<Default>Launches %d fire balls in all directions, each coming back and exploding on return, </>" //FireBallAmount
			"dealing <Damage>%d </><Default> radial fire damage with a chance to burn.</>"), //Damage

			// Values
			Level,
			ManaCost,
			Cooldown,
			FireBallAmount,
			ScaledDmg);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	return TArray<AAuraFireBall*>();
}
