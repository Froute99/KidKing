// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemInterface.h"

// Sets default values
AItemInterface::AItemInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemName = "";
	Cost = 0;

}

// Called when the game starts or when spawned
void AItemInterface::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemInterface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

