// Copyright Epic Games, Inc. All Rights Reserved.


#include "KidKingGameModeBase.h"
#include "MainCharacter_Boy1.h"

AKidKingGameModeBase::AKidKingGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BluePrint/MainCharacter/BP_Boy01.BP_Boy01_C"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
