// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "B1AIController.h"
#include "B1Character.h"
#include "Skill/1000/B1Skill1000.h"

UBTTask_Attack::UBTTask_Attack()
{
	IsAttacking = false;
}
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto AICharacter = Cast<AB1Character>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == AICharacter) {
		return EBTNodeResult::Failed;
	}

	if (nullptr == B1Character) {
		B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	//TSharedPtr<IB1Skill> skill(new B1Skill1000(B1Character));
	AICharacter->RunSkill(new B1Skill1000(AICharacter));
	
	IsAttacking = true;

	auto AnimInst = Cast<UB1AnimInstance>(B1Character->GetMesh()->GetAnimInstance());
	AnimInst->OnEndofAnim.AddLambda([this]() ->  void {
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
