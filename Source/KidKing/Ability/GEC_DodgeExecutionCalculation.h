// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEC_DodgeExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UGEC_DodgeExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:

	UGEC_DodgeExecutionCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
