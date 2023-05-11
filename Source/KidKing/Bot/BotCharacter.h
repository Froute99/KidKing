// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "BotCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API ABotCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:



	virtual void Die(float Damage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);


};
