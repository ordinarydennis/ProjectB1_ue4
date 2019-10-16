// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1001.h"

B1Skill1001::B1Skill1001(USkeletalMeshComponent* mesh)
{
	//��ȹ �����Ϳ��� ���������� ����
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Mesh = mesh;
}

B1Skill1001::~B1Skill1001()
{
}
void B1Skill1001::Run()
{
	if (IsCoolTime()) {
		return;
	}

	SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	PlayAnimation();
}
ERES_ANIM_NUM B1Skill1001::GetAnimResNum()
{
	return ERES_ANIM_NUM::SingleTwoHandSword_1;
}
void B1Skill1001::PlayAnimation()
{
	AnimationInst = static_cast<UB1AnimInstance*>(Mesh->GetAnimInstance());
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}
