// Fill out your copyright notice in the Description page of Project Settings.
//Unable

#include "StartMenu_HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


AStartMenu_HUD::AStartMenu_HUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/StartMenu_BP.StartMenu_BP_C'"));
	
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class;
	}

}


void AStartMenu_HUD::BeginPlay()
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
