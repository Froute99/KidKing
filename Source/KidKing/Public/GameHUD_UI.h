// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "GameHUD_UI.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UGameHUD_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_PauseMenu = nullptr;

private:
	UFUNCTION()
		void PauseMenu_Clicked();


};
