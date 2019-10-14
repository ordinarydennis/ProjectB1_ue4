// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1002.h"

B1Skill1002::B1Skill1002(USkeletalMeshComponent* mesh)
{
	Mesh = mesh;
}

B1Skill1002::~B1Skill1002()
{
}
void B1Skill1002::Run()
{
}
bool B1Skill1002::IsRun()
{
	return (0 < SkillStartTimestamp) ? true : false;
}
ERES_ANIM_NUM B1Skill1002::GetAnimResNum()
{
	return ERES_ANIM_NUM::SingleTwoHandSword_2;
}