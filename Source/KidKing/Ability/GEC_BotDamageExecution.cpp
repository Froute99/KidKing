// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GEC_BotDamageExecution.h"

#include "CharacterAttributeSetBase.h"
#include "AbilitySystemComponent.h"

struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

	//DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Damage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Health, Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DmgStatics;
	return DmgStatics;
}

UGEC_BotDamageExecution::UGEC_BotDamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UGEC_BotDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* SourceABSC = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;


	//float BaseDamage = FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);
	float BaseDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, BaseDamage);

	float ArmorRate = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, ArmorRate);

	float DamageDone = BaseDamage;


	if (DamageDone < 0.0f)		DamageDone = 0.0f;



	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -DamageDone));
}
