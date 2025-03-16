// Copyright Caffeinated Cat


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura/AuraLogChannels.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();

	SpellPointsChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
	{
		if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;
			bool bEnableSpellPoints = false;
			bool bEnableAssign = false;
			ShouldEnableButtons(StatusTag, CurrentSpellPoints, bEnableSpellPoints, bEnableAssign);
			FString Description;
			FString NextLevelDescription;
			GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);
			SpellSelectedDelegate.Broadcast(bEnableSpellPoints, bEnableAssign, Description, NextLevelDescription);
		}
		
		if (AbilityInfo)
		{
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda([this](int32 Points)
	{
		SpellPointsChangedDelegate.Broadcast(Points);
		
		CurrentSpellPoints = Points;
		bool bEnableSpellPoints = false;
		bool bEnableAssign = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, bEnableSpellPoints, bEnableAssign);
		FString Description;
		FString NextLevelDescription;
		GetAuraASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);
		SpellSelectedDelegate.Broadcast(bEnableSpellPoints, bEnableAssign, Description, NextLevelDescription);
	}); 
}

void USpellMenuWidgetController::SpellSelected(const FGameplayTag& AbilityTag)
{
	if (bWaitingForAssignSelection)
	{
		const FGameplayTag SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType;
		StopWaitingForAssignDelegate.Broadcast(SelectedAbilityType);
		bWaitingForAssignSelection = false;
	}
	
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
	FGameplayTag Status;

	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	
	const FGameplayAbilitySpec* Spec = GetAuraASC()->GetAbilitySpecFromTag(AbilityTag);
	const bool bSpecValid = Spec != nullptr;
	
	if (!bTagValid || bTagNone || !bSpecValid)
	{
		Status = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		Status = GetAuraASC()->GetStatusFromSpec(*Spec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = Status;
	bool bEnableSpellPoints = false;
	bool bEnableAssign = false;
	ShouldEnableButtons(Status, SpellPoints, bEnableSpellPoints, bEnableAssign);
	FString Description;
	FString NextLevelDescription;
	GetAuraASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);
	SpellSelectedDelegate.Broadcast(bEnableSpellPoints, bEnableAssign, Description, NextLevelDescription);
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	if (GetAuraASC()) GetAuraASC()->ServerSpendSpellPoint(SelectedAbility.Ability);
}

void USpellMenuWidgetController::SpellDeselected()
{
	if (bWaitingForAssignSelection)
	{
		const FGameplayTag SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitingForAssignDelegate.Broadcast(SelectedAbilityType);
		bWaitingForAssignSelection = false;
	}
	
	SelectedAbility.Ability = FAuraGameplayTags::Get().Abilities_None;
	SelectedAbility.Status = FAuraGameplayTags::Get().Abilities_Status_Locked;

	SpellSelectedDelegate.Broadcast(false, false, FString(), FString());
}

void USpellMenuWidgetController::AssignButtonPressed()
{
	const FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;

	WaitForAssignDelegate.Broadcast(AbilityType);
	bWaitingForAssignSelection = true;
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& StatusTag, int32 SpellPoints,
                                                     bool& bEnableSpellPointsButton, bool& bEnableAssignButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	bEnableSpellPointsButton = false;
	bEnableAssignButton = false;
	
	if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked) ||
	StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Assigned))
	{
		if (SpellPoints > 0) bEnableSpellPointsButton = true;
		bEnableAssignButton = true;
	}
	else if (StatusTag.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0) bEnableSpellPointsButton = true;
	}
}
