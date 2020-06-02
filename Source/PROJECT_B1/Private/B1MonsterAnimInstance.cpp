// Fill out your copyright notice in the Description page of Project Settings.


#include "B1MonsterAnimInstance.h"

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
}
void UB1MonsterAnimInstance::SetDeadAnim()
{
	IsDead = true;
}
void UB1MonsterAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}