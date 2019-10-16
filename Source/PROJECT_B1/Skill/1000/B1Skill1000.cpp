// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1000.h"

B1Skill1000::B1Skill1000(USkeletalMeshComponent* mesh)
{
	//��ȹ �����Ϳ��� ���������� ����
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Mesh = mesh;
}

B1Skill1000::~B1Skill1000()
{
	//ȣ��Ǵ��� Ȯ���ϱ�
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
	return ERES_ANIM_NUM::SingleTwoHandSword_0;
}
void B1Skill1000::PlayAnimation()
{
	AnimationInst = static_cast<UB1AnimInstance*>(Mesh->GetAnimInstance());
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}
