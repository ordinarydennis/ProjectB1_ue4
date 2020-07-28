// Fill out your copyright notice in the Description page of Project Settings.


#include "B1GameInstance.h"
#include "B1CustomStructs.h"
#include "B1MonsterAnimInstance.h"
#include "Misc/FileHelper.h"
#include "B1DebugPrint.h"
//#include "Engine/DataTable.h"
//#include "UObject/ConstructorHelpers.h"


UB1GameInstance::UB1GameInstance()
{
	//게임 씬 전환 전에 리소스 로드 함수를 호출하고
	//리소스 로드가 완료 되면 관련 클래스들에게 브로드 캐스팅 한다.
	LoadMonsterTable();
}
void UB1GameInstance::Init()
{
	Super::Init();
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UB1GameInstance::Tick));
}
bool UB1GameInstance::Tick(float DeltaSeconds)
{

	return true;
}
void UB1GameInstance::Shutdown()
{
	Super::Shutdown();
	// Unregister ticker delegate
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}
void UB1GameInstance::LoadMonsterTable()
{
	MonsterTablePath = TEXT("/Game/Data/MonsterTable.MonsterTable");

	ResourceStreamingHandle = StreamableManager.RequestAsyncLoad(
		MonsterTablePath, FStreamableDelegate::CreateUObject(this, &UB1GameInstance::CompletedResourceLoad));
}
void UB1GameInstance::CompletedResourceLoad()
{
	//printf("UB1GameInstance::CompletedResourceLoad");
	ResourceStreamingHandle->ReleaseHandle();

	TSoftObjectPtr<UDataTable> LoadedAssetPath(MonsterTablePath);
	if (LoadedAssetPath.IsValid()) {
		B1MonsterTable = LoadedAssetPath.Get();
		
		int32 num = B1MonsterTable->GetRowMap().Num();
		for (int32 Index = 0; Index < num; ++Index){
			const FB1MonaterTableRow* Row = B1MonsterTable->FindRow<FB1MonaterTableRow>(*FString::FromInt(Index), TEXT(""));
			if (Row == nullptr) {
				continue;
			}

			MonsterResMeshPath.AddUnique(Row->ResSKMesh);
			MonsterResAnimPath.AddUnique(Row->ResAnimInst);
			MonsterResPath.AddUnique(Row->ResSKMesh);
			MonsterResPath.AddUnique(Row->ResAnimInst);
		}

		//MonsterResPath.Append(MonsterResMeshPath, ARRAY_COUNT(MonsterResMeshPath));
		//MonsterResPath.Append(MonsterResAnimPath, ARRAY_COUNT(MonsterResAnimPath));

		ResourceStreamingHandle = StreamableManager.RequestAsyncLoad(
			MonsterResPath, FStreamableDelegate::CreateUObject(this, &UB1GameInstance::CompletedResourceLoad2));

	}
}
void UB1GameInstance::CompletedResourceLoad2()
{
	ResourceStreamingHandle->ReleaseHandle();

	for (auto mesh : MonsterResMeshPath) {
		TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(mesh);
		if (!LoadedAssetPath.IsValid()) {
			printf("Mesh Load Fail %s", *LoadedAssetPath.ToString());
		}
	}

	for (auto anim : MonsterResAnimPath) {
		TSoftClassPtr<UAnimInstance> LoadedAssetPath(anim);
		if (!LoadedAssetPath.IsValid()) {
			printf("Anim Load Fail %s", *LoadedAssetPath.ToString());
		}
	}

	IsMonsterTableLoad = true;
}
const FB1MonaterTableRow* UB1GameInstance::GetMonsterData(int32 monsterType)
{
	return B1MonsterTable->FindRow<FB1MonaterTableRow>(*FString::FromInt(monsterType), TEXT(""));
}
void UB1GameInstance::ReloadDTFromCSVFile(UDataTable* dataTable, FString csvFileName)
{
	FString DataPath = FPaths::ProjectDir() + "/Content/Data";
	FString csvFile = DataPath + "/" + csvFileName;
	if (FPaths::FileExists(csvFile))
	{
		FString FileContent;
		FFileHelper::LoadFileToString(FileContent, *csvFile);

		TArray<FString> problems = dataTable->CreateTableFromCSVString(FileContent);
		if (0 < problems.Num()) {
			printf("error!! UB1GameInstance::ReloadDT problems.Num %d", problems.Num());
		}
	
		//int32 num = B1CharacterTable->GetRowMap().Num();
		//for (int32 Index = 1; Index != num; ++Index)
		//{
		//	FB1CharacterData* a = B1CharacterTable->FindRow<FB1CharacterData>(*FString::FromInt(Index), TEXT(""));
		//	printf("Dagame %f Health %f Speed %f", a->Damage, a->Health, a->Speed);
		//}
	}
}