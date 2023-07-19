// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ConnectionState_HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AConnectionState_HUD::AConnectionState_HUD()
{
	//static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/ConnectionState.ConnectionState_C'"));

	//if (ui.Succeeded())
	//{
	//	uiBPClass = ui.Class;
	//}
}

void AConnectionState_HUD::BeginPlay()
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
