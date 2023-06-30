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
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSetBase, Stamina, Target, false);
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

	//Character.SprintStaminaConsume
	//float BaseDamage = FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	float ConsumeStamina = 0.f;
	if (ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(StaminaStatics().StaminaDef, EvaluationParamaters, ConsumeStamina) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("Failed in %s"), *FString{ __FUNCTION__ });
	}
	UE_LOG(LogTemp, Log, TEXT("%f"), ConsumeStamina);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(StaminaStatics().StaminaProperty, EGameplayModOp::Additive, -ConsumeStamina));

}

