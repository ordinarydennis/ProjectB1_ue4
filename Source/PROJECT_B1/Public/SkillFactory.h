// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "UObject/NoExportTypes.h"
#include "Skill/B1Skill.h"
#include "SkillFactory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API USkillFactory : public UObject
{
	GENERATED_BODY()

public:
	static USkillFactory* GetInstance();
	static TSharedPtr<IB1Skill> CreateSkill(ERES_ANIM_NUM SkillNum, AB1Character* character);

private:
	USkillFactory();
	static USkillFactory* Instance;
};
