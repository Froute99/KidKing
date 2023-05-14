// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Actor.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API AMainCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplay")
	int32 TeamCode;


	AMainCharacter();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;



	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;


	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* MovementContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MovementAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpAction;



	// Killer is the "Pawn" which actually killed. DamageCauser can be a "Weapon or Some Object"
	virtual void Die(float Damage, const FDamageEvent& DamageEvent, AController* Killer, AActor* DamgeCauser);




/***********************************************************
 *	Widget
 ***********************************************************/

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class UPlayerWidget> PlayerWidgetClass;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = HUD)
	//class UPlayerWidget* PlayerWidget;


	//virtual void UpdateHealth(float Delta);

};
