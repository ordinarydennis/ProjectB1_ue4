// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Animation/AnimInstance.h"
#include "B1MonsterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCheckSkillHitDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEndOfAttackDelegate);
/**
 * 
 */
UCLASS()
class PROJECT_B1_API UB1MonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UB1MonsterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void SetMonsterState(ERES_STATE_MONSTER monsterState);

public:
	FOnCheckSkillHitDelegate OnCheckSkillHit;
	FOnEndOfAttackDelegate OnEndOfAttack;

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();
	UFUNCTION()
	void AnimNotify_EndOfAttack();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	float CurrentPlayerSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	bool IsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	bool IsAttack = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player, Meta = (AllowPrivateAccess = true))
	int32 MonsterState = 0;
};
