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

//void ACharacterController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//
//
//	PawnMappingContext = NewObject<UInputMappingContext>(this);
//
//	MoveAction = NewObject<UInputAction>(this);
//	MoveAction->ValueType = EInputActionValueType::Axis3D;
//	PawnMappingContext->MapKey(MoveAction, EKeys::W);
//
//}

void ACharacterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//AKidKingPlayerState* PS = GetPlayerState<AKidKingPlayerState>();
	//if (PS)
	//{
	//	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	//}

	//EnableInput(this);
}
