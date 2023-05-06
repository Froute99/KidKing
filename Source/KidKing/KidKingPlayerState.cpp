// Fill out your copyright notice in the Description page of Project Settings.


#include "KidKingPlayerState.h"
#include "CharacterAttributeSetBase.h"
#include "CharacterAbilitySystemComponent.h"

AKidKingPlayerState::AKidKingPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* AKidKingPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* AKidKingPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool AKidKingPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void AKidKingPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	// TODO: implement HUD later
}

float AKidKingPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float AKidKingPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

int32 AKidKingPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

void AKidKingPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AKidKingPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AKidKingPlayerState::MaxHealthChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AKidKingPlayerState::CharacterLevelChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("state.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AKidKingPlayerState::StunTagChanged);
	}

}

void AKidKingPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed!"));
}

void AKidKingPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed!"));
}

void AKidKingPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Level Changed!"));
}

void AKidKingPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));
		
		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
