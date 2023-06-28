// Fill out your copyright notice in the Description page of Project Settings.


#include "GEC_RunStaminaExecution.h"

#include "CharacterAttributeSetBase.h"
#include "AbilitySystemComponent.h"

struct FStaminaStatics
{
	//DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);

	FStaminaStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Stamina, Source, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Damage, Source, false);

		//DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Health, Target, false);
	}
};

static const FStaminaStatics& StaminaStatics()
{
	static FStaminaStatics StaminaStatics;
	return StaminaStatics;
}

UGEC_RunStaminaExecution::UGEC_RunStaminaExecution()
{
	RelevantAttributesToCapture.Add(StaminaStatics().StaminaDef);
}

void UGEC_RunStaminaExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;

	UAbilitySystemComponent* SourceABSC = ExecutionParams.GetSourceAbilitySystemComponent();
	AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParamaters;
	EvaluationParamaters.SourceTags = SourceTags;
	EvaluationParamaters.TargetTags = TargetTags;


	float ConsumeStamina = 0.1f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(StaminaStatics().StaminaDef, EvaluationParamaters, ConsumeStamina);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(StaminaStatics().StaminaProperty, EGameplayModOp::Additive, -ConsumeStamina));

}

