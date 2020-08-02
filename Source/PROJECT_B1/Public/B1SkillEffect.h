// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_B1_API B1SkillEffect
{
public:
	B1SkillEffect();
	~B1SkillEffect();
	
	void ApplyEffect(class AB1BaseCharacter* baseCharacter);
	bool IsEnd();
	int32 GetType();

private:
	int64 StartTimestamp = 0;
	int32 Duration = 0;
	int32 Type = 0;
	int32 Figure = 0;
};
