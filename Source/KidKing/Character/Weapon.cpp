// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

// Sets default values
AWeapon::AWeapon(const class FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f));
	WeaponCollision->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

//void AWeapon::SetOwningPawn(ACharacter* NewOwner)
//{
//	if (OwningCharacter != NewOwner)
//	{
//		OwningCharacter = NewOwner;
//	}
//}

//void AWeapon::AttachMeshToPawn()
//{
//	if (OwningCharacter)
//	{
//		USkeletalMeshComponent* PawnMesh = OwningCharacter->GetMesh();
//		FName AttachPoint = OwningCharacter->GetWeaponAttachPoint();
//		WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
//	}
//}

//void AWeapon::OnEquip(const AWeapon* LastWeapon)
//{
//	AttachMeshToPawn();
//}

//void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	if (MyPawn)
//	{
//		if (OtherActor->IsA(AActor::StaticClass()) && MyPawn->IsAttacking && OtherActor != MyPawn)
//		{
//			UGameplayStatics::ApplyDamage(OtherActor, 10.f, NULL, this, UDamageType::StaticClass());
//			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ApplyDamage");
//		}
//	}
//}
