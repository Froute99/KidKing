// Fill out your copyright notice in the Description page of Project Settings.


#include "KidKingPlayerState.h"

AKidKingPlayerState::AKidKingPlayerState()
{

}

UAbilitySystemComponent* AKidKingPlayerState::GetAbilitySystemComponent() const
{
	return nullptr;
}

CharacterAttributeSetBase* AKidKingPlayerState::GetAttributeSetBase() const
{
	return nullptr;
}

bool AKidKingPlayerState::IsAlive() const
{
	return false;
}

void AKidKingPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
}

float AKidKingPlayerState::GetHealth() const
{
	return 0.0f;
}

float AKidKingPlayerState::GetMaxHealth() const
{
	return 0.0f;
}

int32 AKidKingPlayerState::GetCharacterLevel() const
{
	return int32();
}

void AKidKingPlayerState::BeginPlay()
{
}

void AKidKingPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
}

void AKidKingPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}
