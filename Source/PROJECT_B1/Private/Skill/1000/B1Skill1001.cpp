// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1001.h"
#include "B1Character.h"
#include "B1DebugPrint.h"

B1Skill1001::B1Skill1001(AB1Character* character)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ResTex2dSkill(*RES_TEX2D_SKILL1001);
	if (ResTex2dSkill.Succeeded()) {
		Tex2dSkill = ResTex2dSkill.Object;
	}

	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 3;
	SkillStartTimestamp = 0;
	//ClassName = __CLASS__;

	Character = character;
	AnimInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
}
B1Skill1001::~B1Skill1001()
{
}
void B1Skill1001::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}
}
void B1Skill1001::CheckAttack()
{

}
ERES_ANIM_NUM B1Skill1001::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1001;
}
void B1Skill1001::PlayAnimation()
{
	AnimInst->SetSkillAnimResNum(GetAnimResNum());
}