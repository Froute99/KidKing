// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEC_RunStaminaExecution.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UGEC_RunStaminaExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	
	UGEC_RunStaminaExecution();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


};
