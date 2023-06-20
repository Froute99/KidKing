// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_FinalStage.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AHUD_FinalStage::AHUD_FinalStage()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> obj(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/HUD_FinalStage.HUD_FinalStage_C'"));
	if (obj.Succeeded())
	{
		uiBPClass = obj.Class;
	}
}


void AHUD_FinalStage::BeginPlay()
{
	Super::BeginPlay();

	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);

		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}

	}
}
