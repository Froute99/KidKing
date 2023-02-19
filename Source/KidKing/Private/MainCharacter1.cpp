// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter1.h"


AMainCharacter1::AMainCharacter1()
{

}

void AMainCharacter1::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}