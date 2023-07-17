// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "CustomAIController.h"
#include "BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	//
	//auto MyCharacter = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	//if (nullptr == MyCharacter)
	//	return EBTNodeResult::Failed;

	//auto Target = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACustomAIController::TargetKey));
	//if (nullptr == Target)
	//	return EBTNodeResult::Failed;

	//FVector LookVector = Target->GetActorLocation() - MyCharacter->GetActorLocation();
	//LookVector.Z = 0.0f;
	//FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	//MyCharacter->SetActorRotation(TargetRot);

	//MyCharacter->Attack();
	//

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}