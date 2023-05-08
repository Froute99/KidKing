// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTServiceDetect.h"
#include "CustomAIController.h"
#include "CharacterBase.h"
#include "MainCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UMyBTServiceDetect::UMyBTServiceDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UMyBTServiceDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			TOptional<FOverlapResult> ToCheck(OverlapResult);

			if (ToCheck.IsSet())
			{
				AMainCharacter* MyCharacter = Cast<AMainCharacter>(OverlapResult.GetActor());
				if (MyCharacter && MyCharacter->GetController()->IsPlayerController() && MyCharacter->Hp != 0)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACustomAIController::TargetKey, MyCharacter);
					DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

					DrawDebugPoint(World, MyCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
					DrawDebugLine(World, ControllingPawn->GetActorLocation(), MyCharacter->GetActorLocation(), FColor::Blue, false, 0.27f);
					return;
				}
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ACustomAIController::TargetKey, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}

