// Fill out your copyright notice in the Description page of Project Settings.


#include "BotCharacter.h"
#include "Engine/DamageEvents.h"

void ABotCharacter::Die(float Damage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Super::Die(Damage, DamageEvent, Killer, DamageCauser);



	//Hp = FMath::Max(0.f, Hp);		// ?

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);


	GetWorldTimerManager().ClearTimer(DeathAnimationTimer);

	PlayAnimMontage(BeDeath_AnimMontage);
	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}


	if (Controller != NULL)
	{
		Controller->UnPossess();
	}



	//GetMesh()->SetCollisionProfileName("Ragdoll");
	//GetMesh()->SetSimulatePhysics(true);

	GetWorldTimerManager().SetTimer(DeathAnimationTimer, this, &ACharacterBase::DeathAnimationEnd, DeathAnimDuration, false);
}

