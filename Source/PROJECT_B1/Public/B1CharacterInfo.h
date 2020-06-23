// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_B1_API B1CharacterInfo
{
public:
	B1CharacterInfo();
	~B1CharacterInfo();

	FString GetResSkMesh();
	FString GetResAnimInst();
	FVector2D GetCapsuleSize();
	float GetMaxHP();
	float GetDamage();
	float GetMaxWalkSpeed();

	void SetResSkMesh(FString resSkMesh);
	void SetResAnimInst(FString resAnimInst);
	void SetCapsuleSize(FVector2D capsuleSize);
	void SetMaxHP(float maxHP);
	void SetDamage(float damage);
	void SetMaxWalkSpeed(float maxWalkSpeed);
	
private:
	FString ResSkMesh;
	FString ResAnimInst;
	FVector2D CapsuleSize;
	float MaxHP = 0.f;
	float Damage = 0.f;
	float MaxWalkSpeed = 0.f;
};
