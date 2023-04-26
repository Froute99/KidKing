// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/SkillInterface.h"

// Sets default values
ASkillInterface::ASkillInterface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkillName = "";
	Cost = 0;

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

