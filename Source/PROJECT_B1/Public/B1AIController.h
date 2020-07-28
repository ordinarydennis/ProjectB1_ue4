// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "B1AIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API AB1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AB1AIController();
	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	//void RunAI();
	//void StopAI();

private:
	UPROPERTY()
	class UBlackboardData* BBCharacter;
	UPROPERTY()
	class UBehaviorTree* BTCharacter;

	//void OnRepeatTimer();
	//FTimerHandle RepeatTimerHandle;
	//float RepeatInterval;
};
