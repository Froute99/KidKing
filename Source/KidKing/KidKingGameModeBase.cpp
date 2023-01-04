// Copyright Epic Games, Inc. All Rights Reserved.


#include "KidKingGameModeBase.h"
#include "MainCharacter1.h" 
#include "Blueprint/UserWidget.h"

void AKidKingGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();

}
