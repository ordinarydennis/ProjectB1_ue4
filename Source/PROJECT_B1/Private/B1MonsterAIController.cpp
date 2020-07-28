// Fill out your copyright notice in the Description page of Project Settings.


#include "B1MonsterAIController.h"
#include "B1Resources.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AB1MonsterAIController::HomePosKey(TEXT("HomePos"));
const FName AB1MonsterAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AB1MonsterAIController::TargetKey(TEXT("Target"));


AB1MonsterAIController::AB1MonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(*RES_BB_MONSTER);

	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(*RES_BT_MONSTER);

	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
	}
}
void AB1MonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (UseBlackboard(BBAsset, Blackboard)) {
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset)) {
			printf("AIController couln't run behavior tree!");
		}
	}
}
