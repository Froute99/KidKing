// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"
#include "TimerManager.h"


void UKidKingBlueprintLibrary::RegisterRespawn(ACharacterBase* Character)
{
	UWorld* World = GEngine->GameViewport->GetWorld();

	FTimerHandle RespawnHandle;
	
	FTimerDelegate Delegate;
	Delegate.BindUFunction(Character, "Respawn");


	World->GetTimerManager().SetTimer(RespawnHandle, Delegate, 5.0f, false);
	
}

bool UKidKingBlueprintLibrary::Purchase(ACharacterBase* Character, int Cost)
{
	if (Character->Gold >= Cost)
	{
		Character->Gold -= Cost;
		return true;
	}
	else
	{
		return false;
	}
}

