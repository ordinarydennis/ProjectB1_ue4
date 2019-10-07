// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Animation/AnimInstance.h"
#include "B1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API UB1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UB1AnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
	UFUNCTION()
	void AnimNotify_EndofAnim();


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	float CurrentPlayerSpeed = 0.0f;

	//나중에 프로젝트 타입으로 수정하기 using 사용하기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	int32 CurrentSkillAnimResNum;

	class AB1Character* B1Character = nullptr;
};
