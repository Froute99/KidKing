// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "StartMenu_UI.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UStartMenu_UI : public UUserWidget
{
	GENERATED_BODY()
public:

	void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* Bnt_StartGame = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* Bnt_Credits = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* Bnt_ExitGame = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* Bnt_Option = nullptr;
	

protected:


private:

	UFUNCTION(BlueprintCallable)
		void Bnt_StartGame_ButtonClicked();
	
	UFUNCTION(BlueprintCallable)
		void Bnt_Credits_ButtonClicked();

	UFUNCTION(BlueprintCallable)
		void Bnt_ExitGame_ButtonClicked();

};
