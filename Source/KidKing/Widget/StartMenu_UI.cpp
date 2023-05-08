// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_UI.h"
#include "Controller_StartMenu.h"
#include "Kismet/GameplayStatics.h"


void UStartMenu_UI::NativeConstruct()
{
	if (Bnt_StartGame)
	{
		Bnt_StartGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Bnt_StartGame_ButtonClicked);
	}

	if (Bnt_Credits)
	{
		Bnt_Credits->OnClicked.AddDynamic(this, &UStartMenu_UI::Bnt_Credits_ButtonClicked);
	}

	if (Bnt_ExitGame)
	{
		Bnt_ExitGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Bnt_ExitGame_ButtonClicked);
	}
}


void UStartMenu_UI::Bnt_StartGame_ButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Map/CharacterSelection");
	//UGameplayStatics::OpenLevel(GetWorld(), "127.0.0.1");
}

void UStartMenu_UI::Bnt_Credits_ButtonClicked()
{
	AController_StartMenu* controller = Cast<AController_StartMenu>(GetOwningPlayer());
	controller->ShowCredits();
}

void UStartMenu_UI::Bnt_ExitGame_ButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
