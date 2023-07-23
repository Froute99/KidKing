 //Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSetBase.h"

#include "GameplayEffectTypes.h"

#include "KidKingPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API AKidKingPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AKidKingPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UCharacterAttributeSetBase* GetAttributeSetBase() const;


	UFUNCTION(BlueprintCallable, Category = "KidKing|KidKingPlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "KidKing|KidKingPlayerState|Attributes")
	void ShowAbilityConfirmCancelText(bool ShowText);


	UFUNCTION(BlueprintCallable, Category = "KidKing|KidKingPlayerState|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|KidKingPlayerState|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|KidKingPlayerState|Attributes")
	float GetStamina() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|KidKingPlayerState|Attributes")
	float GetMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|KidKingPlayerState|Attributes")
	int32 GetCharacterLevel() const;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KidKing|KidKingPlayerState")
	//class UPlayerWidget* PlayerWidget;

protected:
	UPROPERTY()
	class UCharacterAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	class UCharacterAttributeSetBase* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;
	FDelegateHandle CharacterLevelChangedDelegateHandle;

	
	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

};
