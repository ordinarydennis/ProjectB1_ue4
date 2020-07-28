// Fill out your copyright notice in the Description page of Project Settings.


#include "B1MonsterAnimInstance.h"
#include "B1Resources.h"

UB1MonsterAnimInstance::UB1MonsterAnimInstance()
{

}
void UB1MonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn)) {
		CurrentPlayerSpeed = Pawn->GetVelocity().Size();
	}

	if (0 < CurrentPlayerSpeed) {
		SetMonsterState(ERES_STATE_MONSTER::RUN);
	}
}
void UB1MonsterAnimInstance::SetMonsterState(ERES_STATE_MONSTER monsterState)
{
	MonsterState = static_cast<int32>(monsterState);
}

void UB1MonsterAnimInstance::AnimNotify_AttackHitCheck()
{
	//AnimNotify_AttackHitCheck -> AnimNotify_CheckAttackHit 으로 바꾸자
	OnCheckAttackHit.Broadcast();
}
void UB1MonsterAnimInstance::AnimNotify_EndOfAttack()
{
	OnEndOfAttack.Broadcast();
}
void UB1MonsterAnimInstance::SetIsDeath(bool isDeath)
{
	IsDeath = isDeath;
}
