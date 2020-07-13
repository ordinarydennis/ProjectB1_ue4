// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Animation/AnimInstance.h"
#include "B1AnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCheckAttackHitDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCheckSkillHitDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEndofAnimDelegate);

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
	void SetIsDeath(bool isDeath);
	void SetIsAttack(bool isAttack);

public:
	FOnCheckAttackHitDelegate OnCheckAttackHit;
	FOnCheckSkillHitDelegate OnCheckSkillHit;
	FOnEndofAnimDelegate OnEndofAnim;
	
private:
	UFUNCTION()
	void AnimNotify_CheckAttackHit();
	UFUNCTION()
	void AnimNotify_EndOfAttack();
	UFUNCTION()
	void AnimNotify_EndofAnim();
	UFUNCTION()
	void AnimNotify_CheckSkillHit();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	float CurrentPlayerSpeed = 0.0f;

	//���߿� ������Ʈ Ÿ������ �����ϱ� using ����ϱ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	int32 SkillAnimResNum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	bool IsDeath = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	bool IsAttack = false;

	class AB1Character* B1Character = nullptr;
};
