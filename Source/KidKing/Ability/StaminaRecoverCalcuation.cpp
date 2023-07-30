// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/StaminaRecoverCalcuation.h"

#include "CharacterAttributeSetBase.h"
#include "AbilitySystemComponent.h"


struct FStaminaStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);

	FStaminaStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Stamina, Source, false);
	}
};

static const FStaminaStatics& StaminaStatics()
{
	static FStaminaStatics Statics;
	return Statics;
}

UStaminaRecoverCalcuation::UStaminaRecoverCalcuation()
{
	RelevantAttributesToCapture.Add(StaminaStatics().StaminaDef);
}

void UStaminaRecoverCalcuation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
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


	float CurrentStamina = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(StaminaStatics().StaminaDef, EvaluationParameters, CurrentStamina);

	float ResultStamina = CurrentStamina + 1.f;
	if (ResultStamina >= 100.f)
	{
		ResultStamina = 100.f;
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(StaminaStatics().StaminaProperty, EGameplayModOp::Override, ResultStamina));
}

