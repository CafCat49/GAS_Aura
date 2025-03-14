// Copyright Caffeinated Cat


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"

FString UAuraProjectileSpell::GetDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT("<Title>FIRE BOLT</>\n\n<Default>Launches a bolt of fire, exploding on impact and dealing </><Damage>%d </><Default>fire damage with a chance to burn.</>\n\n<Small>Level: </><Level>%d</>"),
			Damage, Level);
	}
	return FString::Printf(TEXT("<Title>FIRE BOLT</>\n\n<Default>Launches %d bolts of fire, exploding on impact and dealing </><Damage>%d </><Default>fire damage with a chance to burn.</>\n\n<Small>Level: </><Level>%d</>"),
		FMath::Min(Level, ProjectileCount), Damage, Level);
}

FString UAuraProjectileSpell::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = DamageTypes[FAuraGameplayTags::Get().Damage_Fire].GetValueAtLevel(Level);
	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n\n<Default>Launches %d bolts of fire, exploding on impact and dealing </><Damage>%d </><Default>fire damage with a chance to burn.</>\n\n<Small>Level: </><Level>%d</>"),
			FMath::Min(Level, ProjectileCount), Damage, Level);
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetPos, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	const FVector SocketPos = ICombatInterface::Execute_GetCombatSocketPos(
		GetAvatarActorFromActorInfo(),
		SocketTag
		);
	FRotator Rotation = (ProjectileTargetPos - SocketPos).Rotation();

	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
		
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketPos);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	const UAbilitySystemComponent* SrcASC =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

	FGameplayEffectContextHandle EffectContextHandle = SrcASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	TArray<TWeakObjectPtr<AActor>> Actors;
	Actors.Add(Projectile);
	EffectContextHandle.AddActors(Actors);
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetPos;
	EffectContextHandle.AddHitResult(HitResult);

	const FGameplayEffectSpecHandle SpecHandle =
		SrcASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	for (auto& Pair : DamageTypes)
		{
			const float ScaledDmg = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDmg);
		}
		
	Projectile->DamageEffectSpecHandle = SpecHandle;
		
	Projectile->FinishSpawning(SpawnTransform);
}
