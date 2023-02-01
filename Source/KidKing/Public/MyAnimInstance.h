// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

UCLASS()
class KIDKING_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void PlayAttackMontage_Hero();
	void PlayAttackMontage_Bot();
	void SetDeadAnim();
	void SetHitAnim();

	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	FOnAttackHitCheckDelegate OnAttackHitCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_Hero;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_Bot;

	UPROPERTY(BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bDeadAnim;

	UPROPERTY(BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bHitAnim;
};
