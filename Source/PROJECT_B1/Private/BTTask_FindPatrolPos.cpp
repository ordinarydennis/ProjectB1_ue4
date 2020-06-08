// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "B1MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}
EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto ControllerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllerPawn) {
		return EBTNodeResult::Failed;
	}
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem) {
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AB1MonsterAIController::HomePosKey);
	FNavLocation NextLocation;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 300.0f, NextLocation)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AB1MonsterAIController::PatrolPosKey,
			NextLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
