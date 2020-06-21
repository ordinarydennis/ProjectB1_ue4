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

	void SetResSkMesh(FString resSkMesh);
	void SetResAnimInst(FString resAnimInst);
	void SetCapsuleSize(FVector2D capsuleSize);
	
private:
	FString ResSkMesh;
	FString ResAnimInst;
	FVector2D CapsuleSize;
};
