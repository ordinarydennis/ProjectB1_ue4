// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "B1Monster.h"
#include "AIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	IsAttacking = false;
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AB1Monster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		return EBTNodeResult::Failed;
	}
	
	Monster->SetMonsterState(ERES_STATE_MONSTER::ATTACK);

	IsAttacking = true;

	Monster->OnAttackEnd.AddLambda([this]() ->  void {
		IsAttacking = false;
		});
	
	return EBTNodeResult::InProgress;
}
void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
