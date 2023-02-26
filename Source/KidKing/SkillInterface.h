// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "SkillInterface.generated.h"

/**
 * 
 */

UCLASS()
class KIDKING_API ASkillInterface
{
	GENERATED_BODY()
protected:
	
	AKidKingGameModeBase();
	
	virtual void BeginPlay()override;


public:
	void ChangeUI();
};
