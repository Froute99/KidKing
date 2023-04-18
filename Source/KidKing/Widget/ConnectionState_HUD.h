// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ConnectionState_HUD.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API AConnectionState_HUD : public AHUD
{
	GENERATED_BODY()
public:
	AConnectionState_HUD();
	void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget>uiBPClass;
	UUserWidget* uiWidget;
};
