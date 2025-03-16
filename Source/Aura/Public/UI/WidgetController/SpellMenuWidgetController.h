// Copyright Caffeinated Cat

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellSelectedSignature, bool, bEnableSpendPointsButton, bool, bEnableAssignButton,
	FString, DescriptionString, FString, NextLevelDescriptionString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForAssignSelectionSignature, const FGameplayTag&, AbilityType);

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	void SpellSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();

	UFUNCTION(BlueprintCallable)
	void SpellDeselected();

	UFUNCTION(BlueprintCallable)
	void AssignButtonPressed();
	
	UFUNCTION(BlueprintCallable)
	void HotbarSpellPressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType);

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature SpellPointsChangedDelegate;

	UPROPERTY(BlueprintAssignable)
	FSpellSelectedSignature SpellSelectedDelegate;

	UPROPERTY(BlueprintAssignable)
	FWaitForAssignSelectionSignature WaitForAssignDelegate;

	UPROPERTY(BlueprintAssignable)
	FWaitForAssignSelectionSignature StopWaitingForAssignDelegate;

private:

	static void ShouldEnableButtons(const FGameplayTag& StatusTag, int32 SpellPoints, bool& bEnableSpellPointsButton, bool& bEnableAssignButton);

	void OnAbilityAssigned(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot);
	
	FSelectedAbility SelectedAbility = {FAuraGameplayTags::Get().Abilities_None, FAuraGameplayTags::Get().Abilities_Status_Locked};
	FGameplayTag SelectedSlot;
	int32 CurrentSpellPoints = 0;
	bool bWaitingForAssignSelection = false;
};
