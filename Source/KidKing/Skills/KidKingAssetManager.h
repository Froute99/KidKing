// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "KidKingAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UKidKingAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;


};
