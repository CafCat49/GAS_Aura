// Copyright Caffeinated Cat

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTAsk_Attack.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UBTTAsk_Attack : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
