// Copyright Caffeinated Cat


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
//#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();
	//UAbilitySystemGlobals::Get().InitGlobalData(); - required to use target data, seems to be deprecated in 5.3
}
