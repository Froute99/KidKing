// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"

#include "BaseCharacter.h"

#include "BotCharacterBase.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBotDiedDelegate, ABaseCharacter*, Character);

UCLASS()
class KIDKING_API ABotCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABotCharacterBase();


	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	UPROPERTY(BlueprintAssignable, Category = "KidKing|Bot")
	FBotDiedDelegate OnBotDied;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category = "KidKing|Bot|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Bot|Attributes")
	float GetMaxHealth() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);





	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KidKing|BotAbilities")
	TWeakObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "KidKing|BotAbilities")
	TWeakObjectPtr<class UBotAttributeSetBase> AttributeSetBase;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Bot|Abilities")
	TArray<TSubclassOf<class UCharacterGameplayAbility>> BotAbilities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KidKing|Bot|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
