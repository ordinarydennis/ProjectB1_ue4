// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1002.h"
#include "B1Character.h"

B1Skill1002::B1Skill1002()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> SkillIcon(TEXT("/Game/Resources/Market/CraftResourcesIcons/Textures/Tex_gemstone_08_b"));
	if (SkillIcon.Succeeded()) {
		SkillIconTexture = SkillIcon.Object;
	}
}
B1Skill1002::~B1Skill1002()
{
}
void B1Skill1002::init(AB1Character* character)
{
	//TODO: ��ȹ �����Ϳ��� ���������� ����
	CoolTime = 3;
	SkillStartTimestamp = 0;
	Character = character;
	AnimationInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
	ClassName = "B1Skill1002";
}
void B1Skill1002::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}


	//TODO: ���� �Ÿ������� �̵��ϵ��� ���� ���� ������ �����Ӹ��� �̵� �Ÿ��� �ٸ��� �ִ�.
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
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}