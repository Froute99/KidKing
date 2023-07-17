// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillInterface.h"
#include "BaseCharacter.h"

// Sets default values
ASkillInterface::ASkillInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkillName = "";
	Cost = 0;
	Damage = -1;
}

// Called when the game starts or when spawned
void ASkillInterface::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillInterface::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//ACharacterBase* Target = Cast<ACharacterBase>(OtherActor);
	//ACharacterBase* Shooter = GetInstigator<ACharacterBase>();


	//if (Target && Target != Shooter && Target->GetLocalRole() == ROLE_Authority)
	//{
	//	float HealthDelta = -Damage;
	//	Target->UpdateHealth(HealthDelta);
	//}


	//Destroy();
}

