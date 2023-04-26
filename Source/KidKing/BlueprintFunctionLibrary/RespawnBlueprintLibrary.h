// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RespawnBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UKidKingBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// When Character Die, Register to respawn in 5sec.
	UFUNCTION(BlueprintCallable)
	static void RegisterRespawn(class ACharacterBase* Character);
	

	UFUNCTION(BlueprintCallable)
	static bool Purchase(class ACharacterBase* Character, int Cost);
};
