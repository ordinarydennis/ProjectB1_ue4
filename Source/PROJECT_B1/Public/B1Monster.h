// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "B1BaseCharacter.h"
#include "B1CharacterInfo.h"
#include "B1Monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class PROJECT_B1_API AB1Monster : public AB1BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AB1Monster();
	void CheckAttackHit();
	void EndOfAttack();
	void SetMonsterState(ERES_STATE_MONSTER state);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FOnAttackEndDelegate OnAttackEnd;
	UPROPERTY(EditAnywhere, Category = INFO)
	int MonsterType = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstiator, AActor* DamageCauser) override;

private:
	void Init(int32 monsterType);

private:
	UPROPERTY(VisibleAnywhere, Category = "B1PawnComponent")
	class USkeletalMeshComponent* SkelMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere)
	class UProgressBar* HPProgressBar;

	ERES_STATE_MONSTER MonsterState = ERES_STATE_MONSTER::IDLE;

	TArray<FSoftObjectPath> ResourcePathList;
	TSharedPtr<struct FStreamableHandle> ResourceStreamingHandle;
	
	//TSharedPtr<B1CharacterInfo> MonsterInfo;
	bool IsInit = false;
};
