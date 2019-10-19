// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1000.h"
#include "B1Character.h"

B1Skill1000::B1Skill1000(AB1Character* character)
{
	//��ȹ �����Ϳ��� ���������� ����
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Character = character;
}
B1Skill1000::~B1Skill1000()
{
}
void B1Skill1000::Run()
{
	if (IsCoolTime()) {
		return ;
	}

	SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	PlayAnimation();
}
ERES_ANIM_NUM B1Skill1000::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1000;
}
void B1Skill1000::PlayAnimation()
{
	AnimationInst = static_cast<UB1AnimInstance*>(Character->GetMesh()->GetAnimInstance());
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}
