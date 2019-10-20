// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill1000.h"
#include "B1Character.h"

B1Skill1000::B1Skill1000()
{
}
B1Skill1000::~B1Skill1000()
{
}
void B1Skill1000::init(AB1Character* character)
{
	//TODO: 기획 데이터에서 가져오도록 수정
	CoolTime = 2;
	SkillStartTimestamp = 0;
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
	printf("B1Skill1000::AttackCheck");
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
	float DebugLifeTime = 5.0f;

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
			printf("Attack");
			//ABLOG(Warning, TEXT("Hit Actor Name: %s"), *HitResult.Actor->GetName());
			//FDamageEvent DamageEvent;
			//HitResult.Actor->TakeDamage(GetFinalAttackDamage(), DamageEvent, GetController(), this);
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