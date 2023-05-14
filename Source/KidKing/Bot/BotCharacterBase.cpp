// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot/BotCharacterBase.h"

// Sets default values
ABotCharacterBase::ABotCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetMesh()->OnComponentHit.AddDynamic(this, &ABotCharacterBase::OnActorHit);
}

// Called when the game starts or when spawned
void ABotCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABotCharacterBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

// Called every frame
void ABotCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABotCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

