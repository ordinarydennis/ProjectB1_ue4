// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1002.h"
#include "B1Character.h"

B1Skill1002::B1Skill1002(AB1Character* character)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> ResTex2dSkill(*RES_TEX2D_SKILL1002);
	if (ResTex2dSkill.Succeeded()) {
		Tex2dSkill = ResTex2dSkill.Object;
	}

	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 5;
	SkillStartTimestamp = 0;
	ClassName = "B1Skill1002";

	Character = character;
	AnimInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
}
B1Skill1002::~B1Skill1002()
{
}
void B1Skill1002::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}


	//TODO: 일정 거리까지만 이동하도록 수정 현재 로직은 프레임마다 이동 거리가 다를수 있다.
	FRotator Rotation = Character->GetController()->GetControlRotation();
	if (Character->GetCharacterMovement()->IsMovingOnGround() || Character->GetCharacterMovement()->IsFalling()) {
		Rotation.Pitch = 0.0f;
	}
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	Character->AddMovementInput(Direction, 0.8);
}
void B1Skill1002::CheckAttack()
{

}
ERES_ANIM_NUM B1Skill1002::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1002;
}
void B1Skill1002::PlayAnimation()
{
	AnimInst->SetSkillAnimResNum(GetAnimResNum());
}