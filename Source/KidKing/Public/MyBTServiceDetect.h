// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTServiceDetect.generated.h"

/**
 * 
 */
UCLASS()
class KIDKING_API UMyBTServiceDetect : public UBTService
{
	GENERATED_BODY()
public:
	UMyBTServiceDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
