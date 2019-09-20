// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "GameFramework/PlayerController.h"
#include "B1PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API AB1PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AB1PlayerController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = WIDGET)
	TSubclassOf<class UB1InGameWidget> InGameWidgetClass;

private:

	UPROPERTY()
	class UB1InGameWidget* InGameWidget;
};
