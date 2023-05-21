// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttackNotify.h"
#include "NiceCleanCharacter.h"


void UCharacterAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, __FUNCTION__);
	
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ANiceCleanCharacter* Player = Cast<ANiceCleanCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->IsAttacking = true;
		}
	}

}

void UCharacterAttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, __FUNCTION__);

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ANiceCleanCharacter* Player = Cast<ANiceCleanCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->IsAttacking = false;
		}
	}
}
