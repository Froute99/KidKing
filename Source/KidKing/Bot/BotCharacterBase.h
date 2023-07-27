// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "CharacterAttributeSetBase.h"

#include "BotCharacterBase.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBotDiedDelegate, ABaseCharacter*, Character);

UCLASS()
class KIDKING_API ABotCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABotCharacterBase();


	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	UPROPERTY(BlueprintAssignable, Category = "KidKing|Bot")
	FBotDiedDelegate OnBotDied;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category = "KidKing|Bot|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "KidKing|Bot|Attributes")
	float GetMaxHealth() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KidKing|Bot")
	FName MonsterName;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);





	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KidKing|Bot|Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , Category = "KidKing|Bot|Abilities")
	UCharacterAttributeSetBase* AttributeSetBase;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "KidKing|Bot|Abilities")
	TArray<TSubclassOf<class UCharacterGameplayAbility>> BotAbilities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "KidKing|Bot|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

private:	
	void InitializeAttributes();


};
