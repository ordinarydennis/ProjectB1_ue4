// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1001.h"

B1Skill1001::B1Skill1001(USkeletalMeshComponent* mesh)
{
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Mesh = mesh;
}

B1Skill1001::~B1Skill1001()
{
}
void B1Skill1001::Run()
{
	if (0 == SkillStartTimestamp) {
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}

	if (0 < SkillStartTimestamp) {
		//멤버 변수로 수정하기
		static UB1AnimInstance* Animation = nullptr;
		if (FDateTime::Now().ToUnixTimestamp() - SkillStartTimestamp > CoolTime) {
			SkillStartTimestamp = 0;
			Animation = nullptr;
			print("skill end");
		}

		if (nullptr == Animation) {
			Animation = Cast<UB1AnimInstance>(Mesh->GetAnimInstance());
			if (Animation) {
				print("skill start");
				Animation->SetSkillAnimResNum(GetAnimResNum());
			}
		}
	}
}
bool B1Skill1001::IsRun()
{
	return (0 < SkillStartTimestamp) ? true : false;
}
ERES_ANIM_NUM B1Skill1001::GetAnimResNum()
{
	return ERES_ANIM_NUM::SingleTwoHandSword_1;
}