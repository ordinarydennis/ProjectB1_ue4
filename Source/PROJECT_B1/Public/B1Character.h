// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "B1InGameWidget.h"
#include "Skill/B1Skill.h"
//#include "GameFramework/Character.h"
#include "B1BaseCharacter.h"
#include "B1Character.generated.h"

UCLASS()
class PROJECT_B1_API AB1Character : public AB1BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AB1Character();
	void RunAttack();
	void RunSkill(IB1Skill* skill);
	void StopSkill();
	void CheckAttackHit();
	void CheckSkillHit();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstiator, AActor* DamageCauser) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

	
private:
	enum class EControlMode
	{
		QUARTER_VIEW,
		NPC,
	};
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void SetControlMode(EControlMode ControlMode);
	void AttackStartComboState();
	void AttackEndComboState();
	void SetWeapon();
	
private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	UPROPERTY()
	class AB1PlayerController* B1PlayerController;
	UPROPERTY()
	class UB1AnimInstance* AnimInst;

	float MovingSpeed = 0.8f;
	IB1Skill* Skill = nullptr;
	BTN_SKILL_INDEX Btn = BTN_SKILL_INDEX::INDEX_NONE;
	EControlMode CurrentControlMode = EControlMode::QUARTER_VIEW;
	FVector DirectionToMove = FVector::ZeroVector;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo = 0;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo = 5;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> AmmoBlueprint;
	AActor* effect = nullptr;
};
