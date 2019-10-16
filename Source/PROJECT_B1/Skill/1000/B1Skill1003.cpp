// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1003.h"

B1Skill1003::B1Skill1003(USkeletalMeshComponent* mesh)
{
	//기획 데이터에서 가져오도록 수정
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Mesh = mesh;
}

B1Skill1003::~B1Skill1003()
{
}
void B1Skill1003::Run()
{
	if (IsCoolTime()) {
		return;
	}

	SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	PlayAnimation();
}
ERES_ANIM_NUM B1Skill1003::GetAnimResNum()
{
	return ERES_ANIM_NUM::SingleTwoHandSword_3;
}
void B1Skill1003::PlayAnimation()
{
	AnimationInst = static_cast<UB1AnimInstance*>(Mesh->GetAnimInstance());
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}