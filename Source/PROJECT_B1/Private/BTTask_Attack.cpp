// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "B1Monster.h"
#include "AIController.h"
//#include "B1MonsterAnimInstance.h"

UBTTask_Attack::UBTTask_Attack()
{
	IsAttacking = false;
}
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AB1Monster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		return EBTNodeResult::Failed;
	}
	
	Monster->Attack();

	//IsAttacking = true;

	//auto AnimInst = Cast<UB1MonsterAnimInstance>(Monster->GetMesh()->GetAnimInstance());
	//AnimInst->OnEndofAnim.AddLambda([this]() ->  void {
	//	IsAttacking = false;
	//	});
	
	return EBTNodeResult::InProgress;
}
void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	/*if (!IsAttacking) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}*/
}
