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


UCLASS()
class KIDKING_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	FMyCharacterData* GetMyCharacterData(int32 Character);

	virtual void Init()override;

private:
	UPROPERTY()
		class UDataTable* MyCharacterTable;
};
