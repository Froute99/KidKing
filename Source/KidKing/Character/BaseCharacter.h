// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputAction.h"

#include "KidKing.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "KidKingPlayerState.h"

#include "BaseCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ABaseCharacter*, Character);

UCLASS()
class KIDKING_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	void OnActorHit(class AActor* SelfActor, class AActor* OtherActor,
		FVector NormalImpulse, struct FHitResult Hit);

	UFUNCTION(BlueprintCallable)
	void Respawn();
	UFUNCTION(BlueprintImplementableEvent)
	void OnRespawn();

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void Win();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWin();

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void Lose();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLose();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TeamIndex;


/***********************************************************
 * View
 ***********************************************************/

	UPROPERTY(VisibleAnywhere, Category = View)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = View)
	class UCameraComponent* Camera;


/***********************************************************
 * Ability
 ***********************************************************/

	UPROPERTY(BlueprintAssignable, Category = "KidKing|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "KidKing|Character")
	virtual bool IsAlive() const;

	// Later, want some additive features something like "Skill Tier", edit this
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character")
	virtual int32 GetAbilityLevel(KidKingAbilityID AbilityID) const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void RemoveCharacterAbilities();

	virtual void Die();
	UFUNCTION(BlueprintImplementableEvent)
	void OnDyingBP();

	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetStamina() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetMaxStamina() const;


	virtual void OnRep_PlayerState() override;


	void BindASCInput();
	bool ASCInputBound = false;

	void InitializeStartingValues(AKidKingPlayerState* PS);


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities")
	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> CharacterAbilities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KidKing|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;


	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;


	virtual void AddCharacterAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();

	UFUNCTION(BlueprintCallable, Category = "KidKing|Character")
	void SetHealth(float Value);

/***********************************************************
 * Input
 ***********************************************************/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);
	//void DebugAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* MappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* AttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* RunAction;



/***********************************************************
 * Weapon
 ***********************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TWeakObjectPtr<class AWeapon> Weapon;



/***********************************************************
 * Widget
 ***********************************************************/

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerWidget> PlayerWidgetClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	//class UPlayerWidget* PlayerWidget;



	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

};
