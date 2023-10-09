// Copyright Caffeinated Cat


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

	const FActiveGameplayEffectHandle ActiveEffectHandle =
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite =
		EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{

	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (!InstantGEClasses.IsEmpty())
		{
			ApplyMultipleEffectsToTarget(TargetActor, InstantGEClasses);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}
	
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (!DurationGEClasses.IsEmpty())
		{
			ApplyMultipleEffectsToTarget(TargetActor, DurationGEClasses);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}


	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (!InfiniteGEClasses.IsEmpty())
		{
			ApplyMultipleEffectsToTarget(TargetActor, InfiniteGEClasses);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if (!InstantGEClasses.IsEmpty())
		{
			ApplyMultipleEffectsToTarget(TargetActor, InstantGEClasses);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}
	
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if (!DurationGEClasses.IsEmpty())
		{
			ApplyMultipleEffectsToTarget(TargetActor, DurationGEClasses);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}
	
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		if (!InfiniteGEClasses.IsEmpty())
		{
			ApplyMultipleEffectsToTarget(TargetActor, InfiniteGEClasses);
		}
		else
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
	}
	
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

void AAuraEffectActor::ApplyMultipleEffectsToTarget(AActor* TargetActor, TArray<TSubclassOf<UGameplayEffect>> GEArray)
{
	for (const auto GEClass : GEArray)
	{
		ApplyEffectToTarget(TargetActor, GEClass);
	}
}
