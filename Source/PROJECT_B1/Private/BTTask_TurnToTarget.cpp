// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "B1AIController.h"
#include "B1Character.h"
#include "B1Monster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto B1Monster = Cast<AB1Monster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == B1Monster) {
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<AB1Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AB1AIController::TargetKey));
	if (nullptr == Target) {
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - B1Monster->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	B1Monster->SetActorRotation(
		FMath::RInterpTo(B1Monster->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f)
	);

	return EBTNodeResult::Succeeded;
}