// Copyright Caffeinated Cat

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MaxManaMMC.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMaxManaMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMaxManaMMC();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition IntDef;
};
