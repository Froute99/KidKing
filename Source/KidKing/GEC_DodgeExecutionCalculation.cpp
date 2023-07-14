// Fill out your copyright notice in the Description page of Project Settings.


#include "GEC_DodgeExecutionCalculation.h"

#include "CharacterAttributeSetBase.h"
#include "AbilitySystemComponent.h"

struct FDodgeCostStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	FDodgeCostStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Damage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Stamina, Target, false);
	}
};

static const FDodgeCostStatics& CostStatics()
{
	static FDodgeCostStatics CostStatics;
	return CostStatics;
}


UGEC_DodgeExecutionCalculation::UGEC_DodgeExecutionCalculation()
{
	RelevantAttributesToCapture.Add(CostStatics().StaminaDef);
	RelevantAttributesToCapture.Add(CostStatics().DamageDef);
}

void UGEC_DodgeExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
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


	float BaseCost = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CostStatics().DamageDef, EvaluationParameters, BaseCost);

	float TotalCost = BaseCost;

	if (TotalCost < 0.0f)
	{
		TotalCost = 0.0f;
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(CostStatics().StaminaProperty, EGameplayModOp::Additive, -TotalCost));

}
