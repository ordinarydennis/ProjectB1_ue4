// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1000.h"

B1Skill1000::B1Skill1000(USkeletalMeshComponent* mesh)
{
	//기획 데이터에서 가져오도록 수정
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Mesh = mesh;
}

B1Skill1000::~B1Skill1000()
{
}
void B1Skill1000::Run()
{
	//스킬 사용중이 아닐때 스킬 시작 시간 기록
	//
	//현재 시간 - 스킬 시작시간 
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
bool B1Skill1000::IsRun()
{
	return (0 < SkillStartTimestamp) ? true : false;
}
ERES_ANIM_NUM B1Skill1000::GetAnimResNum()
{
	return ERES_ANIM_NUM::SingleTwoHandSword_0;
}

