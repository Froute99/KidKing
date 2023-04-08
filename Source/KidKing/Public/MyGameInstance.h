// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMyCharacterData() : Character(1), MaxHP(100.0f), MaxSP(100.0f), Attack(10.0f), Defence(5.0f), Speed(100.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float MaxSP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float Speed;
};


DECLARE_DELEGATE(FWinDelegate)

UCLASS()
class KIDKING_API UKidKingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UKidKingGameInstance();

	FMyCharacterData* GetMyCharacterData(int32 Character);

	virtual void Init()override;

	void IncreaseScore();

	// some binding functions here

private:
	UPROPERTY()
	class UDataTable* MyCharacterTable;

	int32 OccupyRate;		// 100 means team one occupy, -100 means the opposite team occupy

	int32 TeamOneScore;
	int32 TeamTwoScore;

	const int32 DesiredScore = 200;

	FWinDelegate WinDelegate;

};
