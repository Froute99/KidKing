// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_HERO(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/MainCharacter/Joyce/JoyceOrigin/JoyceAttack.JoyceAttack'"));
	if (ATTACK_MONTAGE_HERO.Succeeded())
	{
		AttackMontage_Hero = ATTACK_MONTAGE_HERO.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_BOT(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Bot/Poprika_Attack_Montage.Poprika_Attack_Montage'"));
	if (ATTACK_MONTAGE_BOT.Succeeded())
	{
		AttackMontage_Bot = ATTACK_MONTAGE_BOT.Object;
	}

}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}

void UCharacterAnimInstance::PlayAttackMontage_Hero()
{
	Montage_Play(AttackMontage_Hero, 1.0f);
}

void UCharacterAnimInstance::PlayAttackMontage_Bot()
{
	Montage_Play(AttackMontage_Bot, 1.0f);
}

void UCharacterAnimInstance::PlayAttackMontage_Poprika()
{
	Montage_Play(AttackMontage_Paprika, 1.0f);
}

void UCharacterAnimInstance::AnimNotify_AttackHitCheck()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AnimNofify_HitCheck"));

	OnAttackHitCheck.Broadcast();

}

void UCharacterAnimInstance::SetDeadAnim(bool Value)
{
	bDeadAnim = Value;
}

