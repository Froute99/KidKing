// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/KidKingAssetManager.h"
#include "AbilitySystemGlobals.h"

void UKidKingAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Asset Manager Initialized"));



}
