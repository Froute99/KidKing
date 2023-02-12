// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller_StartMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "CharacterBase.h"

AController_StartMenu::AController_StartMenu()
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> GameMenuUI(TEXT(""));
	if (GameMenuUI.Succeeded())
	{
		uiGameMenuBPClass = GameMenuUI.Class;
	}
}

void AController_StartMenu::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &AController_StartMenu::ShowGameMenu);
	

}

void AController_StartMenu::ShowGameMenu()
{
	if(uiGameMenuBPClass)
	{
		uiGameMenuWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameMenuBPClass);

		if (uiGameMenuWidget)
		{
			uiGameMenuWidget->AddToViewport();
		}

	}
}
