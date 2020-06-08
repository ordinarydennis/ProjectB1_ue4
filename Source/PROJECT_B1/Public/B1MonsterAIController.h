// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "AIController.h"
#include "B1MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API AB1MonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AB1MonsterAIController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
};
