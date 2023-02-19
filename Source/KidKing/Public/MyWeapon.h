// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MyWeapon.generated.h"


UCLASS()
class KIDKING_API AMyWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyWeapon(const class FObjectInitializer& ObjectInitializer);
	void SetOwningPawn(ACharacterBase* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const AMyWeapon* LastWeapon);
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		class UBoxComponent* WeaponCollision;

protected:
	class ACharacterBase* MyPawn;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

};
