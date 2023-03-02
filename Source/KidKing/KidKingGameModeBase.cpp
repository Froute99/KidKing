// Copyright Epic Games, Inc. All Rights Reserved.


#include "KidKingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "StartMenu_HUD.h"
#include "MyHUD_InGame.h"
#include "Controller_StartMenu.h"
#include "UObject/ConstructorHelpers.h"



AKidKingGameModeBase::AKidKingGameModeBase()
{

	/*static ConstructorHelpers::FClassFinder<APawn> Player(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/MainCharacter/MyMainCharacter1.MyMainCharacter1_C'"));
	if (Player.Succeeded())
	{
		DefaultPawnClass = Player.Class;		
	}*/
	
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
