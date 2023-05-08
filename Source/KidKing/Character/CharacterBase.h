// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"

#include "GameplayTagContainer.h"

#include "ItemInterface.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.h"
#include "KidKingPlayerState.h"

#include "KidKing.h"

#include "CharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate,
	ACharacterBase*, Character);


UCLASS()
class KIDKING_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	ACharacterBase(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "KidKing|Character")
	FCharacterDiedDelegate OnCharacterDied;


	UFUNCTION(BlueprintCallable, Category = "KidKing|Character")
	virtual bool IsAlive() const;

	// Later, want some additive features something like "Skill Tier", edit this
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character")
	virtual int32 GetAbilityLevel(KidKingAbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void GSADie();

	UFUNCTION(BlueprintCallable, Category = "KidKing|Character")
	virtual void FinishDying();


	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Character|Attributes")
	float GetMaxHealth() const;


	virtual void OnRep_PlayerState() override;

	bool ASCInputBound = false;

	void BindASCInput();

	void InitializeStartingValues(AKidKingPlayerState* PS);

//**********************************************************


	USkeletalMeshComponent* GetSpesificPawnMesh()const;

	FName GetWeaponAttachPoint()const;

	void EquipWeapon(class AWeapon* Weapon);

	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KidKing|Animation")
	UAnimMontage* DeathMontage;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Abilities")
	TArray<TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();


	virtual void SetHealth(float Health);

	virtual void PossessedBy(AController* NewController) override;

//**********************************************************



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void BotDie(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	void DeathAnimationEnd();

	void EnhancedMove(const FInputActionValue& Value);
	void EnhancedLook(const FInputActionValue& Value);
	void Attack();
	void AttackHitCheck();

	FOnAttackEndDelegate OnAttackEnd; // bot notify

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	FName MyCharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	float HpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Gold;


	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditDefaultsOnly, Category = Anim)
	UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Anim)
	UAnimMontage* BeDeath_AnimMontage;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	bool IsBlocking;

	bool IsAttacking;

	float get_Health()const;
	float get_maxHealth()const;
	void set_health(float const new_health);

	UFUNCTION(BlueprintCallable)
	void DebugDecreaseHp();

	const FVector& GetSpawnLocation() const { return SpawnLocation; }
	const FRotator& GetSpawnRotator() const { return SpawnRotator; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCharacterAnimInstance* MyAnim;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	const float DeathAnimDuration = 5.0f;
	FTimerHandle DeathAnimationTimer;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* MovementContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttachPoint;

	UFUNCTION(BlueprintCallable)
	void Respawn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterDie();
	UFUNCTION(BlueprintImplementableEvent)
	void OnRespawn();
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttackStart();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<class AWeapon*> Inventory;



	// Includes Items to Use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<class AItemInterface*> Items;

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(class AItemInterface* Item);


	// Ultimate skill
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	//class USkillInterface* Ultimate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class AWeapon* CurrentWeapon;

	void AddWeapon(class AWeapon* Weapon);

	void SetCurrentWeapon(class AWeapon* NewWeapon, class AWeapon* LastWeapon);

	void SpawnDefaultInventory();

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AWeapon>> DefaultInventoryClasses;


	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* Widget_Component;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FRotator SpawnRotator;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSkillPurchased = false;

};
