// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "B1GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API UB1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UB1GameInstance();
	virtual void Init() override;

	FStreamableManager StreamableManager;
};
