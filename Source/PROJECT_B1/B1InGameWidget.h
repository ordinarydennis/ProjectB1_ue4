// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Blueprint/UserWidget.h"
#include "B1InGameWidget.generated.h"

UENUM()
enum class BTN_SKILL_INDEX : uint8 {
	INDEX_NONE,
	INDEX_1,
	INDEX_2,
	INDEX_3,
	INDEX_4
};

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

private:
	class AB1Character* B1Character = nullptr;
};

