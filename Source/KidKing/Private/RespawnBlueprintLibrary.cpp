// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnBlueprintLibrary.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

void URespawnBlueprintLibrary::RegisterRespawn(float RespawnTime, ACharacter* Character, FTimerHandle* TimerHandle)
{
	Character->GetWorldTimerManager().SetTimer(TimerHandle, 0.0f, false, RespawnTime);

}

