// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1003.h"

B1Skill1003::B1Skill1003(USkeletalMeshComponent* mesh)
{
	Mesh = mesh;
}

B1Skill1003::~B1Skill1003()
{
}
void B1Skill1003::Run()
{

}
bool B1Skill1003::IsRun()
{
	return (0 < SkillStartTimestamp) ? true : false;
}
ERES_ANIM_NUM B1Skill1003::GetAnimResNum()
{
	return ERES_ANIM_NUM::SingleTwoHandSword_3;
}