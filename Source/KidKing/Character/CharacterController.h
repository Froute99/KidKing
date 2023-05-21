// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class KIDKING_API ACharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	ACharacterController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//virtual void BeginPlay() override;

	//virtual void SetupInputComponent() override;

	//UPROPERTY()
	//class UInputMappingContext* PawnMappingContext;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	//class UInputAction* MoveAction;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	//class UInputAction* LookAction;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	//class UInputAction* JumpAction;

	virtual void OnPossess(APawn* InPawn) override;
};
