// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill.h"

// Add default functionality here for any IB1Skill functions that are not pure virtual.

bool IB1Skill::IsCoolTime()
{
	bool ret = false;
	if (FDateTime::Now().ToUnixTimestamp() - SkillStartTimestamp <= CoolTime) {
		ret = true;
	}
	else {
		SkillStartTimestamp = 0;
	}
	return ret;
}