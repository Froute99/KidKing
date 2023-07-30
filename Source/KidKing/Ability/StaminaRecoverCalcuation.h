// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "StaminaRecoverCalcuation.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UStaminaRecoverCalcuation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:

	UStaminaRecoverCalcuation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
