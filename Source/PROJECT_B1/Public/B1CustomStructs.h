// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "B1CustomStructs.generated.h"


USTRUCT(BlueprintType)
struct FB1MonaterTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FB1MonaterTableRow()
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ResSKMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ResAnimInst;
};


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
