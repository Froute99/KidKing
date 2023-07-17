// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD_UI.h"
#include "GameFramework/PlayerController.h"
#include "Controller_StartMenu.h"
//#include "CharacterBase.h"

void UGameHUD_UI::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_PauseMenu)
	{
		Btn_PauseMenu->OnClicked.AddDynamic(this, &UGameHUD_UI::PauseMenu_Clicked);
	}
}

void UGameHUD_UI::PauseMenu_Clicked()
{
	AController_StartMenu* controller = Cast<AController_StartMenu>(GetOwningPlayer());
	controller->ShowPauseMenu();
}

