// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	FString CharacterDataPath = TEXT("/Script/Engine.DataTable'/Game/GameData/MyCharacterData.MyCharacterData'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_MYCHARACTER(*CharacterDataPath);

	if (DT_MYCHARACTER.Succeeded())
	{
		MyCharacterTable = DT_MYCHARACTER.Object;
		ensure(MyCharacterTable->GetRowMap().Num() > 0);
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init()"));
}

void UMyGameInstance::IncreaseScore()
{
	if (OccupyRate == 100)
	{
		TeamOneScore++;
	}
	else if (OccupyRate == -100)
	{
		TeamTwoScore++;
	}


	if (TeamOneScore == DesiredScore)
	{
		// call delegate to Team1 win pipe
	}
	else if (TeamTwoScore == DesiredScore)
	{
		// call delegate to Team2 win pipe
	}
}

FMyCharacterData* UMyGameInstance::GetMyCharacterData(int32 Character)
{
	return MyCharacterTable->FindRow<FMyCharacterData>(*FString::FromInt(Character), TEXT(""));
}