// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RespawnBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class URespawnBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// call when player died
	UFUNCTION(BlueprintCallable)
	static void RegisterRespawn(class ACharacterBase* Character);
	
};
