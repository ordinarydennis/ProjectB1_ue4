// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Blueprint/UserWidget.h"
#include "B1HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API UB1HPWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void BindCharacterStat(class AB1BaseCharacter* pawn);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	UPROPERTY()
	class UProgressBar* HPProgressBar;

private:
	class AB1BaseCharacter* BaseCharacter = nullptr;
};
