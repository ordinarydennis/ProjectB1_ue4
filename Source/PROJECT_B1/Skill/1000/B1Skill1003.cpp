// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1003.h"
#include "B1Character.h"

B1Skill1003::B1Skill1003()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> SkillIcon(TEXT("/Game/Resources/Market/CraftResourcesIcons/Textures/Tex_gemstone_09_b"));
	if (SkillIcon.Succeeded()) {
		SkillIconTexture = SkillIcon.Object;
	}
}
B1Skill1003::~B1Skill1003()
{
}
void B1Skill1003::init(AB1Character* character)
{
	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 2;
	SkillStartTimestamp = 0;
	Character = character;
	AnimationInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
}
void B1Skill1003::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}
}
void B1Skill1003::CheckAttack()
{

}
ERES_ANIM_NUM B1Skill1003::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1003;
}
void B1Skill1003::PlayAnimation()
{
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}