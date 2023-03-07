// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnBlueprintLibrary.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

void URespawnBlueprintLibrary::RegisterRespawn(ACharacterBase* Character)
{
	UWorld* World = GEngine->GameViewport->GetWorld();

	FTimerHandle RespawnHandle;
	
	FTimerDelegate Delegate;
	Delegate.BindUFunction(Character, "Respawn");

	World->GetTimerManager().SetTimer(RespawnHandle, Delegate, 5.0f, false);
	
}

