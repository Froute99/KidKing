// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD_UI.h"
#include "GameFramework/PlayerController.h"
#include "Controller_StartMenu.h"
#include "CharacterBase.h"

void UGameHUD_UI::NativeConstruct()
{
	if (Btn_GameMenu)
	{
		Btn_GameMenu->OnClicked.AddDynamic(this, &UGameHUD_UI::GameMenu_Clicked);
	}
}

void UGameHUD_UI::set_bar_value_percent(float const value)
{
	HPbar_value->SetPercent(value);
}

void UGameHUD_UI::GameMenu_Clicked()
{
	AController_StartMenu* controller = Cast<AController_StartMenu>(GetOwningPlayer());
	controller->ShowGameMenu();
}
