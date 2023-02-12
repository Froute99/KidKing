// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD_InGame.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


AMyHUD_InGame::AMyHUD_InGame()
{
	
	static ConstructorHelpers::FClassFinder<UUserWidget> obj(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/HUD.HUD_C'"));
	if (obj.Succeeded())
	{
		uiBPClass = obj.Class;
	}

	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);

		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}

	}

}

void AMyHUD_InGame::BeginPlay()
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
