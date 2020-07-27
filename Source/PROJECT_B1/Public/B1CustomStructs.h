// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "B1CustomStructs.generated.h"

UCLASS()
class PROJECT_B1_API AB1CustomStructs : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AB1CustomStructs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(BlueprintType)
struct FB1MonaterTableRow : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FB1MonaterTableRow()
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Speed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Damage = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CapsuleSizeX = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CapsuleSizeY = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ResSKMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ResAnimInst;
};
