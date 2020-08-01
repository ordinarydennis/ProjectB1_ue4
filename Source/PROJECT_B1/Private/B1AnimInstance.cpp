// Fill out your copyright notice in the Description page of Project Settings.


#include "B1AnimInstance.h"
#include "B1Character.h"
#include "B1DebugPrint.h"

UB1AnimInstance::UB1AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(
		TEXT("/Game/Animation/UE4_Mannequin_Skeleton_Montage.UE4_Mannequin_Skeleton_Montage")
	);
	if (ATTACK_MONTAGE.Succeeded()) {
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}
void UB1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn)){
		CurrentPlayerSpeed = Pawn->GetVelocity().Size();
	}

	if (nullptr == B1Character) {
		B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
}
void UB1AnimInstance::SetSkillAnimResNum(ERES_ANIM_NUM skillAnimResNum)
{
	SkillAnimResNum = static_cast<int32>(skillAnimResNum);
}
void UB1AnimInstance::AnimNotify_EndOfAttack()
{
	if (false == ::IsValid(B1Character)) {
		return;
	}
	SetIsAttack(false);
}
void UB1AnimInstance::AnimNotify_EndOfSkill()
{
	if (false == ::IsValid(B1Character)) {
		return;
	}
	SkillAnimResNum = static_cast<int32>(ERES_ANIM_NUM::NONE);
	OnEndOfSkill.Broadcast();
}
void UB1AnimInstance::AnimNotify_CheckAttackHit()
{
	OnCheckAttackHit.Broadcast();
}
void UB1AnimInstance::AnimNotify_CheckNextAttack()
{
	//printf("AnimNotify_CheckNextAttack");
	OnCheckNextAttack.Broadcast();
}
//void UB1AnimInstance::AnimNotify_CheckSkillHit()
//{
//	OnCheckSkillHit.Broadcast();
//}
void UB1AnimInstance::SetIsDeath(bool isDeath)
{
	IsDeath = isDeath;
}
void UB1AnimInstance::SetIsAttack(bool isAttack)
{
	IsAttack = isAttack;
}
void UB1AnimInstance::PlayAttack()
{
	Montage_Play(AttackMontage, 1.0f);
}
FName UB1AnimInstance::GetAttackMontageSectionName(int32 Section)
{
	//ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	//ABLOG(Warning, TEXT("Section Name: %s"), *FString::Printf(TEXT("Attack%d"), Section));
	printf("Section Name: %s", *FString::Printf(TEXT("Attack%d"), Section));
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
void UB1AnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	//ABCHECK(!IsDead);
	//ABCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}