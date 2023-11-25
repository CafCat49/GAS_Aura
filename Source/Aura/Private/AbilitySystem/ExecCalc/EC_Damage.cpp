// Copyright Caffeinated Cat


#include "AbilitySystem/ExecCalc/EC_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemBPLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorClass);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalAvoidance);
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorClass, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalAvoidance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DmgStatics;
	return DmgStatics;
}

UEC_Damage::UEC_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorClassDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalAvoidanceDef);
}

void UEC_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Get Damage Set by Called Magnitude
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	//Capture Block Chance on Target, and determine if there was a successful block
	float TargetBlockChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().BlockChanceDef,
		EvaluationParameters,
		TargetBlockChance);

	TargetBlockChance = FMath::Max<float>(0, TargetBlockChance);
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	//If successful block, take half damage
	if (bBlocked) Damage *= 0.5;
	
	float TargetArmorClass = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().ArmorClassDef,
		EvaluationParameters,
		TargetArmorClass);

	TargetArmorClass = FMath::Max<float>(0, TargetArmorClass);

	float SourceArmorPenetration = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().ArmorPenetrationDef,
		EvaluationParameters,
		SourceArmorPenetration);

	SourceArmorPenetration = FMath::Max<float>(0, SourceArmorPenetration);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemBPLibrary::GetCharacterClassInfo(SourceAvatar);
	const FRealCurve* ArmorPenCurve =
		CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenCoeff = ArmorPenCurve->Eval(SourceCombatInterface->GetCharacterLevel());
	
	//Armor Penetration ignores a percent of Target's Armor
	const float EffectiveArmor =
		TargetArmorClass * (100 - SourceArmorPenetration * ArmorPenCoeff) / 100;

	const FRealCurve* EffectiveArmorCurve =
		CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoeff = EffectiveArmorCurve->Eval(TargetCombatInterface->GetCharacterLevel());
	
	//Armor Class ignores a percent of incoming damage
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoeff) / 100;

	float SourceCritChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CriticalChanceDef,
		EvaluationParameters,
		SourceCritChance);

	SourceCritChance = FMath::Max<float>(0, SourceCritChance);

	float TargetCritAvoid = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CriticalAvoidanceDef,
		EvaluationParameters,
		TargetCritAvoid);

	TargetCritAvoid = FMath::Max<float>(0, TargetCritAvoid);

	float SourceCritDamage = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CriticalDamageDef,
		EvaluationParameters,
		SourceCritDamage);

	SourceCritDamage = FMath::Max<float>(0, SourceCritDamage);
	
	const FRealCurve* CritAvoidCurve =
		CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalAvoidance"), FString());
	const float CritAvoidCoeff = CritAvoidCurve->Eval(TargetCombatInterface->GetCharacterLevel());

	//Critical Avoidance reduces Critical Chance by a certain percent
	const float EffectiveCritChance = SourceCritChance - TargetCritAvoid * CritAvoidCoeff;
	const bool bCrit = FMath::RandRange(1, 100) < EffectiveCritChance;

	//Double damage plus Critical Damage bonus if critical hit
	if (bCrit)
		Damage += Damage + SourceCritDamage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(
		UAuraAttributeSet::GetIncomingDamageAttribute(),
		EGameplayModOp::Additive,
		Damage);
	
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
