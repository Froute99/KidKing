// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_UI.h"
#include "Kismet/GameplayStatics.h"


void UStartMenu_UI::NativeConstruct()
{
	if (Bnt_StartGame)
	{
		Bnt_StartGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Bnt_StartGame_ButtonClicked);
	}

	if (Bnt_ExitGame)
	{
		Bnt_ExitGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Bnt_ExitGame_ButtonClicked);
	}
}


void UStartMenu_UI::Bnt_StartGame_ButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Map/stage_01");
}

void UStartMenu_UI::Bnt_ExitGame_ButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
