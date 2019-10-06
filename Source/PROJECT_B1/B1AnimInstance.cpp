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
		//CurrentSkillAnimNum = B1Character->GetCurrentSkillAnimNum();
	}
}
void UB1AnimInstance::AnimNotify_EndofAim()
{
	if (false == ::IsValid(B1Character)) {
		return;
	}

	//CurrentSkillAnimNum = RES_ANIM_NUM::NONE;
	//B1Character->SetCurrentSkillAnimNum((int32)CurrentSkillAnimNum);
}