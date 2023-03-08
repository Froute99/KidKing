// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_FinalStage.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API AHUD_FinalStage : public AHUD
{
	GENERATED_BODY()
public:
	AHUD_FinalStage();
	void BeginPlay()override;

private:
	TSubclassOf<class UUserWidget>uiBPClass;
	UUserWidget* uiWidget;
};
