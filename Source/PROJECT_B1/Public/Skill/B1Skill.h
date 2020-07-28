// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "B1AnimInstance.h"
#include "UObject/Interface.h"
#include "B1Skill.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UB1Skill : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class PROJECT_B1_API IB1Skill
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Run() = 0;
	virtual void CheckAttack() = 0;

protected:
	virtual ERES_ANIM_NUM GetAnimResNum() = 0;

public:
	bool IsCoolTime();
	void SetBtnImage(class UButton* btn);
	UTexture2D* GetBtnImage();
	FString GetName();

protected:
	int64 SkillStartTimestamp = 0;
	int32 CoolTime = 10;
	int64 Damage = 0;
	class AB1Character* Character = nullptr;
	UB1AnimInstance* AnimInst = nullptr;
	UTexture2D* Tex2dSkill = nullptr;
	FString ClassName = "NULL";
};
