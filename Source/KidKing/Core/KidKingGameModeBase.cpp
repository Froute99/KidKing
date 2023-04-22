// Copyright Epic Games, Inc. All Rights Reserved.


#include "KidKingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "StartMenu_HUD.h"
#include "MyHUD_InGame.h"
#include "Controller_StartMenu.h"
#include "UObject/ConstructorHelpers.h"


AKidKingGameModeBase::AKidKingGameModeBase()
{
	
	HUDClass = AMyHUD_InGame::StaticClass();
	PlayerControllerClass = AController_StartMenu::StaticClass();

}

void AKidKingGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AKidKingGameModeBase::ChangeUI()
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	CurrentWidget->AddToViewport();
}
