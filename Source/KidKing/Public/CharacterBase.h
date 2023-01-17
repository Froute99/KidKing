// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterBase.generated.h"



UCLASS()
class KIDKING_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);
	void Attack();
	void AttackHitCheck();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY()
	class UMyAnimInstance* MyAnim;

	bool IsAttacking = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* MovementContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* JumpAction;

};
