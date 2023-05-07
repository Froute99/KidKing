// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/UniformGridSlot.h"
#include "Controller_StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API AController_StartMenu : public APlayerController
{
	GENERATED_BODY()
	
		AController_StartMenu();
protected:
	void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;


public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ClosePauseMenu();

	void ShowCredits();
	void CloseCredits();

	void ShowDieUI();
	void ShowFinalStageDieUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isShowPauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isShowCredits;

private:
	
	TSubclassOf<class UUserWidget>uiGamePauseBPClass;
		UUserWidget* uiPauseMenuWidget;

	TSubclassOf<class UUserWidget>uiCreditsBPClass;
		UUserWidget* uiCreditsWidget;

	TSubclassOf<class UUserWidget>uiDieBPClass;
		UUserWidget* uiDieWidget;
	
	TSubclassOf<class UUserWidget>uiFinalStageDieBPClass;
		UUserWidget* uiFinalStageDieWidget;


};
