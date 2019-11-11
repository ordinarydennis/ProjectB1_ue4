// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1004.h"
#include "B1Character.h"

B1Skill1004::B1Skill1004(AB1Character* character)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> SkillIcon(TEXT("/Game/Resources/Market/CraftResourcesIcons/Textures/Tex_gemstone_10_b"));
	if (SkillIcon.Succeeded()) {
		SkillIconTexture = SkillIcon.Object;
	}

	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 3;
	SkillStartTimestamp = 0;
	ClassName = "B1Skill1004";

	Character = character;
	AnimationInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
}
B1Skill1004::~B1Skill1004()
{
}
void B1Skill1004::init(AB1Character* character)
{

}
void B1Skill1004::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}
}
void B1Skill1004::CheckAttack()
{

}
ERES_ANIM_NUM B1Skill1004::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1004;
}
void B1Skill1004::PlayAnimation()
{
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}

