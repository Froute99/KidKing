// Copyright Epic Games, Inc. All Rights Reserved.


#include "KidKingGameModeBase.h"
#include "MainCharacter_Boy1.h"

AKidKingGameModeBase::AKidKingGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/MainCharacter/BP_Boy1.BP_Boy1_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
