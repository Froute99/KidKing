// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"

// Sets default values
AMyWeapon::AMyWeapon(const class FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f));
	WeaponCollision->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform,"DamageSocket");
}

void AMyWeapon::SetOwningPawn(ACharacterBase* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AMyWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpesificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	}
}

void AMyWeapon::OnEquip(const AMyWeapon* LastWeapon)
{
	AttachMeshToPawn();
}
