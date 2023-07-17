// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Weapon.generated.h"


UCLASS()
class KIDKING_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon(const class FObjectInitializer& ObjectInitializer);
	//void SetOwningPawn(ACharacter* NewOwner);
	//void AttachMeshToPawn();
	//void OnEquip(const AWeapon* LastWeapon);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* WeaponCollision;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacter* OwningCharacter;

public:
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
