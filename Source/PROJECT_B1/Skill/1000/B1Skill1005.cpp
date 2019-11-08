// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1005.h"
#include "B1Character.h"

B1Skill1005::B1Skill1005()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> SkillIcon(TEXT("/Game/Resources/Market/CraftResourcesIcons/Textures/Tex_gemstone_11_b"));
	if (SkillIcon.Succeeded()) {
		SkillIconTexture = SkillIcon.Object;
	}
}
B1Skill1005::~B1Skill1005()
{
}
void B1Skill1005::init(AB1Character* character)
{
	//TODO: ��ȹ �����Ϳ��� ���������� ����
	CoolTime = 6;
	SkillStartTimestamp = 0;
	Character = character;
	AnimationInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
	ClassName = "B1Skill1005";
}
void B1Skill1005::Run()
{
	if(0 == SkillStartTimestamp){
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}

	Move();
}
void B1Skill1005::CheckAttack()
{

}
void B1Skill1005::Move()
{
	//TODO: ���� �Ÿ������� �̵��ϵ��� ���� ���� ������ �����Ӹ��� �̵� �Ÿ��� �ٸ��� �ִ�.
	FRotator Rotation = Character->GetController()->GetControlRotation();
	if (Character->GetCharacterMovement()->IsMovingOnGround() || Character->GetCharacterMovement()->IsFalling()){
		Rotation.Pitch = 0.0f;
	}
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	Character->AddMovementInput(Direction, 0.8);
}
ERES_ANIM_NUM B1Skill1005::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1005;
}
void B1Skill1005::PlayAnimation()
{
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}
