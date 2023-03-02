// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu_UI.h"
#include "Controller_StartMenu.h"


void UPauseMenu_UI::NativeConstruct()
{
	if (Btn_PauseMenu_Close)
	{
		Btn_PauseMenu_Close->OnClicked.AddDynamic(this, &UPauseMenu_UI::Btn_PauseMenu_CloseWindow);
	}
}

void UPauseMenu_UI::Btn_PauseMenu_CloseWindow()
{
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->ClosePauseMenu();
}
