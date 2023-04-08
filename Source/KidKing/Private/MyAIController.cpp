// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"


const FName ACustomAIController::HomePosKey(TEXT("HomePos"));
const FName ACustomAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ACustomAIController::TargetKey(TEXT("Target"));


ACustomAIController::ACustomAIController()
{
	
}

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
}

void ACustomAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
}

void ACustomAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	ensure(nullptr != CurrentPawn);
	//ABCHECK(nullptr != CurrentPawn);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem) {
		UE_LOG(LogTemp, Warning, TEXT("NavSystem is nullptr!"));
		return;
	}

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		//UNavigationSystemV1::SimpleMoveToLocation(this, NextLocation.Location);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		UE_LOG(LogTemp, Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
	}

}