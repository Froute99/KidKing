// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Actor.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API AMainCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AMainCharacter();

	virtual void PostInitializeComponents()override;
};
