// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"


AMainCharacter::AMainCharacter()
{

}

void AMainCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}
