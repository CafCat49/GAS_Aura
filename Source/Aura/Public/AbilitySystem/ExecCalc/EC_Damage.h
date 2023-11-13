// Copyright Caffeinated Cat

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EC_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UEC_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UEC_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
