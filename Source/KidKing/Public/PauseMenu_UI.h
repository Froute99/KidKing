// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "PauseMenu_UI.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UPauseMenu_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_PauseMenu_Close = nullptr;

	UFUNCTION()
		void Btn_PauseMenu_CloseWindow();
};
