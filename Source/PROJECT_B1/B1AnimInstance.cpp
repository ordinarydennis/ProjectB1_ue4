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
	if (::IsValid(Pawn))
	{
		CurrentPlayerSpeed = Pawn->GetVelocity().Size();
	}

	auto B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//have to check object whether valid or not.
	if (::IsValid(B1Character)){
		CurrentSkillAnimID = B1Character->GetCurrentSkillAnimID();
	}
}