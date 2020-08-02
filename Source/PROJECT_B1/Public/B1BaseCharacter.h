// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "B1BaseCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS()
class PROJECT_B1_API AB1BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AB1BaseCharacter();
	float GetHP();
	float GetMaxHP();
	float GetDamage();
	bool GetIsDeath();

	void SetDamage(float damage);

public:
	FOnHPChangedDelegate OnHPChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Inform, Meta = (AllowPrivateAccess = true))
	float Damage = 0.f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Inform, Meta = (AllowPrivateAccess = true))
	float HP = 0.f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Inform, Meta = (AllowPrivateAccess = true))
	float MaxHP = 0.f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Inform, Meta = (AllowPrivateAccess = true))
	bool IsDeath = false;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
