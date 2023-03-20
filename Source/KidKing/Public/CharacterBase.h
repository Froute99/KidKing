// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "CharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class KIDKING_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	USkeletalMeshComponent* GetSpesificPawnMesh()const;

	FName GetWeaponAttachPoint()const;

	void EquipWeapon(class AMyWeapon* Weapon);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);


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

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	UAnimMontage* BeHit_AnimMontage;

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
	class UMyAnimInstance* MyAnim;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	const float DeathAnimDuration = 5;
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

	TArray<class AMyWeapon*>Inventory;

	class AMyWeapon* CurrentWeapon;

	void AddWeapon(class AMyWeapon* Weapon);

	void SetCurrentWeapon(class AMyWeapon* NewWeapon, class AMyWeapon* LastWeapon);

	void SpawnDefaultInventory();

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AMyWeapon>>DefaultInventoryClasses;


	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* Widget_Component;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FRotator SpawnRotator;

};
