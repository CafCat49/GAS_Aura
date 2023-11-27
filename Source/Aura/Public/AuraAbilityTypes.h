#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsCriticalHit() const { return bIsCrit; }
	bool IsBlockedHit() const { return bIsBlocked; }

	void SetIsCriticalHit(bool bInIsCrit) { bIsCrit = bInIsCrit; }
	void SetIsBlockedHit(bool bInIsBlocked) { bIsBlocked = bInIsBlocked; }
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext::StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	
protected:

	UPROPERTY()
	bool bIsBlocked = false;
	
	UPROPERTY()
	bool bIsCrit = false;
	
};