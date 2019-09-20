// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Blueprint/UserWidget.h"
#include "B1InGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API UB1InGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void onSkill1Clicked();

	UFUNCTION()
	void onSkill2Clicked();

	UFUNCTION()
	void onSkill3Clicked();

	UFUNCTION()
	void onSkill4Clicked();
};
