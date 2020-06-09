// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "B1MonsterAIController.h"
#include "B1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}
void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) {
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 500.0f;

	if (nullptr == World) {
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.5f);

	if (bResult) {
		for (auto OverlapResult : OverlapResults) {
			AB1Character* B1Character = Cast<AB1Character>(OverlapResult.GetActor());
			if (B1Character && B1Character->GetController()->IsPlayerController()) {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AB1MonsterAIController::TargetKey, B1Character);
				
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, B1Character->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(),B1Character->GetActorLocation(), FColor::Blue, false, 0.2f);
				
				return;
			}
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AB1MonsterAIController::TargetKey, nullptr);
	}
}