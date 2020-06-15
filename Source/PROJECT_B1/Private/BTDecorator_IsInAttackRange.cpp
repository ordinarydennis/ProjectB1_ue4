// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "B1MonsterAIController.h"
#include "B1MonsterAnimInstance.h"
#include "B1BaseCharacter.h"
#include "B1Monster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;


	auto Target = Cast<AB1BaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AB1MonsterAIController::TargetKey));
	if (nullptr == Target) {
		return false;
	}

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 100.f);

	//if (false == bResult) {
	//	auto Monster = Cast<AB1Monster>(ControllingPawn);
	//	Monster->SetMonsterState(ERES_STATE_MONSTER::IDLE);
	//}

	return bResult;
}
