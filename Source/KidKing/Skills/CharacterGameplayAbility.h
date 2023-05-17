// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "KidKing.h"
#include "CharacterGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCharacterGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	KidKingAbilityID AbilityInputID = KidKingAbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	KidKingAbilityID AbilityID = KidKingAbilityID::None;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;


};
