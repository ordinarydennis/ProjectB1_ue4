// Fill out your copyright notice in the Description page of Project Settings.


#include "B1MonsterAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AB1MonsterAIController::AB1MonsterAIController()
{
	RepeatInterval = 3.0f;

}
void AB1MonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, 
		&AB1MonsterAIController::OnRepeatTimer,RepeatInterval, true);
}
void AB1MonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}
void AB1MonsterAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation)) {
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
	}
}