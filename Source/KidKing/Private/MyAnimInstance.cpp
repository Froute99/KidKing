// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

UMyAnimInstance::UMyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_HERO(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/MainCharacter/Attack_Hero.Attack_Hero'"));
	if (ATTACK_MONTAGE_HERO.Succeeded())
	{
		AttackMontage_Hero = ATTACK_MONTAGE_HERO.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE_BOT(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Bot/Attack_Bot.Attack_Bot'"));
	if (ATTACK_MONTAGE_BOT.Succeeded())
	{
		AttackMontage_Bot = ATTACK_MONTAGE_BOT.Object;
	}

}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}

void UMyAnimInstance::PlayAttackMontage_Hero()
{
	Montage_Play(AttackMontage_Hero, 1.0f);
}

void UMyAnimInstance::PlayAttackMontage_Bot()
{
	Montage_Play(AttackMontage_Bot, 1.0f);
}

void UMyAnimInstance::AnimNotify_AttackHitCheck()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AnimNofify_HitCheck"));
	
	OnAttackHitCheck.Broadcast();
}

void UMyAnimInstance::SetDeadAnim()
{
	bDeadAnim = true;
}

void UMyAnimInstance::SetHitAnim()
{
	bHitAnim = true;
}
