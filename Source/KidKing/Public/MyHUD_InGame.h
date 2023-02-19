// Fill out your copyright notice in the Description page of Project Settings.
// Unable
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD_InGame.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API AMyHUD_InGame : public AHUD
{
	GENERATED_BODY()
	
public:
	AMyHUD_InGame();
	void BeginPlay()override;

private:
	TSubclassOf<class UUserWidget>uiBPClass;
	UUserWidget* uiWidget;
};
