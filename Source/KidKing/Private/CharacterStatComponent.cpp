// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatComponent.h"
#include "MyGameInstance.h"

// Sets default values for this component's properties
UCharacterStatComponent::UCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	Character = 1;
	
}

void UCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewCharacter(Character);

}

void UCharacterStatComponent::SetNewCharacter(int32 NewCharacter)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ensure(nullptr != MyGameInstance);

	CurrentStatData = MyGameInstance->GetMyCharacterData(NewCharacter);
	if (nullptr != CurrentStatData)
	{
		Character = NewCharacter;
		SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Character (%d) data doesn't exist"), NewCharacter);
	}
}


void UCharacterStatComponent::SetDamage(float NewDamage)
{
	ensure(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
}

float UCharacterStatComponent::GetAttack()
{
	ensure(nullptr != CurrentStatData);
	return CurrentStatData->Attack;
}

void UCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0f;
		OnHPIsZero.Broadcast();
	}
}

float UCharacterStatComponent::GetHPRatio()
{
	return CurrentHP / CurrentStatData->MaxHP;
}
