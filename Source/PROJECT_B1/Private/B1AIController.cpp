// Fill out your copyright notice in the Description page of Project Settings.


#include "B1AIController.h"
#include "B1Resources.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AB1AIController::HomePosKey(TEXT("HomePos"));
const FName AB1AIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AB1AIController::TargetKey(TEXT("Target"));

AB1AIController::AB1AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> ResBBCharacter(*RES_BB_CHARACTER);
	if (ResBBCharacter.Succeeded()) {
		BBCharacter = ResBBCharacter.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> ResBTCharacter(*RES_BT_CHARACTER);
	if (ResBTCharacter.Succeeded()) {
		BTCharacter = ResBTCharacter.Object;
	}

	//RepeatInterval = 3.0f;
}
void AB1AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BBCharacter, Blackboard)) {
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTCharacter)) {
			printf("AIController couln't run behavior tree!");
		}
	}
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AB1AIController::OnRepeatTimer, RepeatInterval, true);
	

}
//void AB1AIController::RunAI()
//{
//	//if (UseBlackboard(BBAsset, Blackboard)) {
//	//	Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
//	//	if (!RunBehaviorTree(BTAsset)) {
//	//		//ABLOG(Error, TEXT("AIController couln't run behavior tree!"));
//	//	}
//	//}
//}

//void AB1AIController::StopAI()
//{
//	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
//	if (nullptr != BehaviorTreeComponent) {
//		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
//	}
//}
//void AB1AIController::OnUnPossess()
//{
//	Super::OnUnPossess();
//	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
//}
//void AB1AIController::OnRepeatTimer()
//{
//	printf("OnRepeatTimer()");
//	auto CurrentPawn = GetPawn();
//
//	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//
//	if (nullptr == NavSystem) return;
//
//	FNavLocation NextLocation;
//	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation)) {
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
//		printf("Next Location: %s", *NextLocation.Location.ToString());
//	}
//}