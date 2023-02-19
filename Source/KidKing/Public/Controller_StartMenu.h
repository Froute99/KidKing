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
	void SetupInputComponent()override;


public:
	void ShowGameMenu();
	void ShowCredits();

private:
	//TSubclassOf<class UUserWidget> uiBPClass;
	//	UUserWidget* uiWidget;

	TSubclassOf<class UUserWidget>uiGameMenuBPClass;
		UUserWidget* uiGameMenuWidget;

	TSubclassOf<class UUserWidget>uiCreditsBPClass;
		UUserWidget* uiCreditsWidget;

//public:
//	void ShowGameMenu();
//	void CloseGameMenu();
//
//	void ShowInventory();
//	void ShowShopUI();
//	UFUNCTION(BlueprintCallable, Category = "MyUI")
//		void CloseShopUI();
//
//
//	UFUNCTION(BlueprintCallable, Category = "MyUI")
//		void CreateItemSlots();
//
//	UFUNCTION(BlueprintCallable, Category = "MyUI")
//		void CloseInventory();
//
//	void WeaponAttack();
//	void ChangeWeapon();
//	void ShowDieUI();
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		bool isShowGameMenu;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		bool isShowShopMenu;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		bool isShowInventory;
//
//
//	TSubclassOf<class UUserWidget>uiItemSlotBPClass;
//	UUserWidget* uiItemSlotWidget;
//
//private:
//	TSubclassOf<class UUserWidget>uiGameBPClass;
//	UUserWidget* uiGameWidget;
//
//	TSubclassOf<class UUserWidget>uiGameMenuBPClass;
//	UUserWidget* uiGameMenuWidget;
//
//	TSubclassOf<class UUserWidget>uiInventoryBPClass;
//	UUserWidget* uiInventoryWidget;
//
//	TSubclassOf<class UUserWidget>uiGameShopBPClass;
//	UUserWidget* uiGameShopWidget;
//
//	TSubclassOf<class UUserWidget>uiGameDieBPClass;
//	UUserWidget* uiGameDieWidget;
};
