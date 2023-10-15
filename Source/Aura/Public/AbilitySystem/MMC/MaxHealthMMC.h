// Copyright Caffeinated Cat

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxHealthMMC.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMaxHealthMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMaxHealthMMC();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition ConDef;
};
