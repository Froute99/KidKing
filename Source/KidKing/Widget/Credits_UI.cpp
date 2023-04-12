// Fill out your copyright notice in the Description page of Project Settings.


#include "Credits_UI.h"
#include "Controller_StartMenu.h"


void UCredits_UI::NativeConstruct()
{
	if (Btn_Credits_Close)
	{
		Btn_Credits_Close->OnClicked.AddDynamic(this, &UCredits_UI::Btn_Credits_CloseWindow);
	}
}

void UCredits_UI::Btn_Credits_CloseWindow()
{
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->CloseCredits();
}