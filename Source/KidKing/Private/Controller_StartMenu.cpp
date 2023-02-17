// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller_StartMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "CharacterBase.h"

AController_StartMenu::AController_StartMenu()
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> GamePauseUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Pause_BP.Pause_BP_C'"));
	if (GamePauseUI.Succeeded())
	{
		uiGameMenuBPClass = GamePauseUI.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> GameCreditsUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Credits_BP.Credits_BP_C'"));
	if (GameCreditsUI.Succeeded())
	{
		uiCreditsBPClass = GameCreditsUI.Class;
	}
}

void AController_StartMenu::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction(TEXT("ShowGameMenu"), EInputEvent::IE_Pressed, this, &AController_StartMenu::ShowGameMenu);
	

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

void AController_StartMenu::ShowCredits()
{
	if (uiCreditsBPClass)
	{
		uiCreditsWidget = CreateWidget<UUserWidget>(GetWorld(), uiCreditsBPClass);

		if (uiCreditsWidget)
		{
			uiCreditsWidget->AddToViewport();
		}

	}
}
