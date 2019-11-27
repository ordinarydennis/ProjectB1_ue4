// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "B1AIController.h"
#include "B1Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto ControllingPawn = Cast<AB1Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<AB1Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AB1AIController::TargetKey));
	if (nullptr == Target) {
		return false;
	}
	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.f);
	return bResult;

}

