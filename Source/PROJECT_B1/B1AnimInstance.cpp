// Fill out your copyright notice in the Description page of Project Settings.


#include "B1AnimInstance.h"
#include "B1Character.h"

UB1AnimInstance::UB1AnimInstance()
{

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

	//have to check object whether valid or not.
	if (::IsValid(B1Character)) {
		CurrentSkillAnimResNum = static_cast<int32>(B1Character->GetCurrentSkillAnimResNum());
	}
}
void UB1AnimInstance::AnimNotify_EndofAnim()
{
	print("AnimNotify_EndofAim");
	if (false == ::IsValid(B1Character)) {
		return;
	}
	CurrentSkillAnimResNum = static_cast<int32>(ERES_ANIM_NUM::NONE);
	B1Character->SetCurrentSkillAnimResNum(ERES_ANIM_NUM::NONE);
}