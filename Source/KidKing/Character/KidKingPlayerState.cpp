// Fill out your copyright notice in the Description page of Project Settings.


#include "KidKingPlayerState.h"
#include "CharacterAttributeSetBase.h"
#include "CharacterAbilitySystemComponent.h"

#include "BaseCharacter.h"
#include "Components/ProgressBar.h"

#include "PlayerWidget.h"
#include "PlayerHUD.h"

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

float AKidKingPlayerState::GetStamina() const
{
	return AttributeSetBase->GetStamina();
}

float AKidKingPlayerState::GetMaxStamina() const
{
	return AttributeSetBase->GetMaxStamina();
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
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AKidKingPlayerState::MaxHealthChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetStaminaAttribute()).AddUObject(this, &AKidKingPlayerState::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxStaminaAttribute()).AddUObject(this, &AKidKingPlayerState::MaxStaminaChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &AKidKingPlayerState::CharacterLevelChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("state.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AKidKingPlayerState::StunTagChanged);
	}

	//APlayerController* PC = GetPlayerController();
	//if (PC->IsValidLowLevel())
	//{
	//	AHUD* HUD = PC->GetHUD();
	//	if (HUD->IsValidLowLevel())
	//	{
	//		PlayerWidget = Cast<APlayerHUD>(GetPlayerController()->GetHUD())->PlayerWidget;
	//	}
	//}
}

void AKidKingPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UPlayerWidget* PlayerWidget = nullptr;
	APlayerController* PC = GetPlayerController();
	APlayerHUD* HUD;

	if (IsValid(PC))
	{
		HUD = Cast<APlayerHUD>(PC->GetHUD());
		if (IsValid(HUD))
		{
			PlayerWidget = HUD->PlayerWidget;
		}
	}
	

	if (IsValid(PlayerWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Data.NewValue);
		PlayerWidget->SetHealth(Data.NewValue);
		if (FMath::IsNearlyZero(Data.NewValue))
		{

			if (IsValid(PC->GetCharacter()))
			{
				if (IsValid(PC->GetCharacter()))
				{
					Cast<ABaseCharacter>(PC->GetCharacter())->Die();
				}
			}
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Health Changed!"));
}

void AKidKingPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed!"));
}

void AKidKingPlayerState::StaminaChanged(const FOnAttributeChangeData& Data)
{
	UPlayerWidget* PlayerWidget = nullptr;
	APlayerController* PC = GetPlayerController();
	APlayerHUD* HUD;

	if (IsValid(PC))
	{
		HUD = Cast<APlayerHUD>(PC->GetHUD());
		if (IsValid(HUD))
		{
			PlayerWidget = HUD->PlayerWidget;
		}
	}


	if (IsValid(PlayerWidget))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Stamina: %f"), Data.NewValue);
		PlayerWidget->SetStamina(Data.NewValue);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Stamina Changed!"));
}

void AKidKingPlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Stamina Changed!"));
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
