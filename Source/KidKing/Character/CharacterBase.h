// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class KIDKING_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	USkeletalMeshComponent* GetSpesificPawnMesh()const;

	FName GetWeaponAttachPoint()const;

	void EquipWeapon(class AWeapon* Weapon);

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	// Must be overrided
	// https://docs.unrealengine.com/5.1/en-US/gameplay-ability-system-component-and-gameplay-attributes-in-unreal-engine/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;



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
	void OnRespawn();

	TArray<class AWeapon*>Inventory;

	// Includes Items to Use
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	//TArray<class Item*> Items;

	// Ultimate skill
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	//class Skill* Ultimate;

	
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

};
