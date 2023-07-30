// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEC_BotDamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UGEC_BotDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UGEC_BotDamageExecution();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
