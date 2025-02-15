// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttackNotify.h"
#include "BaseCharacter.h"


void UCharacterAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, __FUNCTION__);
	
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
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
		ABaseCharacter* Player = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->IsAttacking = false;
		}
	}
}
