// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Animation/AnimInstance.h"
#include "B1AnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

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

public:
	void SetSkillAnimResNum(ERES_ANIM_NUM skillAnimResNum);

public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;

private:
	UFUNCTION()
	void AnimNotify_EndofAnim();
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	float CurrentPlayerSpeed = 0.0f;

	//���߿� ������Ʈ Ÿ������ �����ϱ� using ����ϱ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	int32 SkillAnimResNum;

	class AB1Character* B1Character = nullptr;
};
