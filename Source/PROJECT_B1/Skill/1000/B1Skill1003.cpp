// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1003.h"
#include "B1Character.h"

B1Skill1003::B1Skill1003(AB1Character* character)
{
	//��ȹ �����Ϳ��� ���������� ����
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Character = character;
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
	return ERES_ANIM_NUM::_1003;
}
void B1Skill1003::PlayAnimation()
{
	AnimationInst = static_cast<UB1AnimInstance*>(Character->GetMesh()->GetAnimInstance());
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}