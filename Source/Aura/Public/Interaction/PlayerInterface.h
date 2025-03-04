// Copyright Caffeinated Cat

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	int32 FindLevelForXP(int32 XP) const;
	
	UFUNCTION(BlueprintNativeEvent)
	int32 GetXP() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePointReward(int32 Level) const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPointReward(int32 Level) const;

	UFUNCTION(BlueprintNativeEvent)
	void AddLevel(int32 InLevel);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddXP(int32 InXP);

	UFUNCTION(BlueprintNativeEvent)
	void AddAttributePoints(int32 InAttributePts);

	UFUNCTION(BlueprintNativeEvent)
	void AddSpellPoints(int32 InSpellPts);
	
	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();
};
