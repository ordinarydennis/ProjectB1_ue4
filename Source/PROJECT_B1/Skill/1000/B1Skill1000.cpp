// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1000.h"
#include "B1Character.h"

B1Skill1000::B1Skill1000()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> SkillIcon(TEXT("/Game/Resources/Market/CraftResourcesIcons/Textures/Tex_gemstone_06_b"));
	if (SkillIcon.Succeeded()) {
		SkillIconTexture = SkillIcon.Object;
	}

	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 1;
	SkillStartTimestamp = 0;
	ClassName = "B1Skill1000";
}
B1Skill1000::~B1Skill1000()
{
}
void B1Skill1000::init(AB1Character* character)
{
	Character = character;
	AnimationInst = Cast<UB1AnimInstance>(Character->GetMesh()->GetAnimInstance());
}
void B1Skill1000::Run()
{
	if (0 == SkillStartTimestamp) {
		PlayAnimation();
		SkillStartTimestamp = FDateTime::Now().ToUnixTimestamp();
	}
}
void B1Skill1000::CheckAttack()
{
	float FinalAttackRange = 150.f;
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, Character);
	bool bResult = Character->GetWorld()->SweepSingleByChannel(
		HitResult,
		Character->GetActorLocation(),
		Character->GetActorLocation() + Character->GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = Character->GetActorForwardVector() * FinalAttackRange;
	FVector Center = Character->GetActorLocation() + TraceVec * 0.5f;
	float AttackRadius = 50.f;
	float HalfHeight = FinalAttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 2.0f;

	DrawDebugCapsule(Character->GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult) {
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(100, DamageEvent, Character->GetController(), Character);
		}
	}
}
ERES_ANIM_NUM B1Skill1000::GetAnimResNum()
{
	return ERES_ANIM_NUM::_1000;
}
void B1Skill1000::PlayAnimation()
{
	AnimationInst->SetSkillAnimResNum(GetAnimResNum());
}