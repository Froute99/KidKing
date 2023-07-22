// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KidKingGameModeBase.generated.h"

/**
 * 
 */


UCLASS()
class KIDKING_API AKidKingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	
	AKidKingGameModeBase();
	
	virtual void BeginPlay()override;

public:

};
