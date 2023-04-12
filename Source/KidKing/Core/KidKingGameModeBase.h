// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KidKingGameModeBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EKidKingGameState :uint8
{
	GameStart,
	GamePlay,
	GamePause,
	GameOver,
};


UCLASS()
class KIDKING_API AKidKingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	
	AKidKingGameModeBase();
	
	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, Category = "UMG Game")
	EKidKingGameState GameStateEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget>HUDWidgetClass;


	UUserWidget* CurrentWidget;

	float OccupationPoint;

public:
	void ChangeUI();
};
