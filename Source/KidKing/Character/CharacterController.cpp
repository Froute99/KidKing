// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterController.h"
#include "KidKingPlayerState.h"
#include "AbilitySystemComponent.h"

#include "InputAction.h"
#include "InputMappingContext.h"


ACharacterController::ACharacterController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ACharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}
