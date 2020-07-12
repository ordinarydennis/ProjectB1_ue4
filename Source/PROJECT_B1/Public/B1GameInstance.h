// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "PROJECT_B1.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "B1GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_B1_API UB1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UB1GameInstance();
	virtual void Init() override;
	void Shutdown() override;

public:
	bool Tick(float DeltaSeconds);
	const struct FB1MonaterTableRow* GetMonsterData(int32 monsterType);
	void ReloadDTFromCSVFile(UDataTable* dataTable, FString csvFileName);

public:
	FStreamableManager StreamableManager;
	bool IsMonsterTableLoad = false;

private:
	void LoadMonsterTable();
	void CompletedResourceLoad();
	void CompletedResourceLoad2();

private:
	FSoftObjectPath MonsterTablePath = FSoftObjectPath(nullptr);
	
	TArray<FSoftObjectPath> MonsterResMeshPath;
	TArray<FSoftObjectPath> MonsterResAnimPath;

	TArray<FSoftObjectPath> MonsterResPath;
	

	TSharedPtr<struct FStreamableHandle> ResourceStreamingHandle;

	UPROPERTY()
	class UDataTable* B1MonsterTable = nullptr;
	FDelegateHandle TickDelegateHandle;
};
