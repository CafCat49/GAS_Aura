// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemBPLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDmg = Damage.GetValueAtLevel(Level);
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
			"<Default>Launches a bolt of fire, exploding on impact and dealing </>"
			"<Damage>%d </><Default>fire damage with a chance to burn.</>"), //Damage

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDmg);
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
		"<Default>Launches %d bolts of fire, exploding on impact and dealing </>" //ProjectileCount
		"<Damage>%d </><Default>fire damage with a chance to burn.</>"), //Damage

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, ProjectileCount),
		ScaledDmg);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
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
		"<Default>Launches %d bolts of fire, exploding on impact and dealing </>" //ProjectileCount
		"<Damage>%d </><Default>fire damage with a chance to burn.</>"), //Damage

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, ProjectileCount),
		ScaledDmg);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketPos(
		GetAvatarActorFromActorInfo(),
		SocketTag);

	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();

	const int32 EffectiveProjectileCount = FMath::Min(ProjectileCount, GetAbilityLevel());
	TArray<FRotator> Rotations =
		UAuraAbilitySystemBPLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, EffectiveProjectileCount);

	for (const FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

		if (IsValid(HomingTarget))
		{
			if (HomingTarget->Implements<UCombatInterface>())
			{
				Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
			}
			else
			{
				Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
				Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
				Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
			}
			Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
			Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;
		}
		Projectile->FinishSpawning(SpawnTransform);
	}
}
