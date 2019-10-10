// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "B1InGameWidget.h"
#include "Skill/B1Skill.h"
#include "GameFramework/Character.h"
#include "B1Character.generated.h"

UCLASS()
class PROJECT_B1_API AB1Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AB1Character();
	void RunSkill(BTN_SKILL_INDEX BtnSkillIdx);
	ERES_ANIM_NUM GetCurrentSkillAnimResNum();
	void SetCurrentSkillAnimResNum(ERES_ANIM_NUM SkillAnimResNum);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	FVector DirectionToMove = FVector::ZeroVector;

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
		
private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

private:
	float MovingSpeed = 0.8f;
	//�̸ֹ��̼� Ÿ�� �����
	ERES_ANIM_NUM CurrentSkillAnimResNum;

	TMap<BTN_SKILL_INDEX, TSharedPtr<IB1Skill>> InGameSkills;
};
