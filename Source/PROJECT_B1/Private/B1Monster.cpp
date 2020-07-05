// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Monster.h"
#include "B1MonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "B1HPWidget.h"
#include "B1MonsterAIController.h"
#include "B1CharacterInfo.h"
#include "B1GameInstance.h"
#include "B1CustomStructs.h"

// Sets default values
AB1Monster::AB1Monster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = GetCapsuleComponent();
    GetCapsuleComponent()->SetVisibleFlag(1);
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Monster"));
    // Rendering - SkeletalMeshComponent
    SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("B1MonsterSM"));
    
    //SkelMesh->SetRelativeLocationAndRotation(
    //    FVector(0.f, 0.f, -90.f),
    //    FRotator(0.f, -90.f, 0.f)    // Roll
    //);

    //static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Monster(*MonsterInfo.GetResSkMesh());

    //SkelMesh->SetSkeletalMesh(SK_Monster.Object);

    // Attacth to RootComponent
    SkelMesh->SetupAttachment(RootComponent);

    //static ConstructorHelpers::FClassFinder<UAnimInstance> ResAnimInst(*MonsterInfo.GetResAnimInst());
    //if (ResAnimInst.Succeeded()) {
        //SkelMesh->SetAnimInstanceClass(ResAnimInst.Class);
    //}

    HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
    
    //SetPivot is better than SetRelativeLocation to adjust widget.
    //HPBarWidget->SetPivot(FVector2D(0.5f, 3.f));
    HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

    static ConstructorHelpers::FClassFinder<UUserWidget> ResWidgetHP(*RES_WIDGET_HP);
    if (ResWidgetHP.Succeeded()){
        HPBarWidget->SetWidgetClass(ResWidgetHP.Class);
        HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
        HUDWidgetClass = ResWidgetHP.Class;
    }

    AIControllerClass = AB1MonsterAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    //MonsterInfo = MakeShareable(new B1CharacterInfo);
}
B1CharacterInfo AB1Monster::GetCharacterInfo(int monsterType)
{
    TSharedPtr<B1CharacterInfo> MonsterInfo = MakeShareable(new B1CharacterInfo);
    switch (monsterType) {
    case 0:
        MonsterInfo->SetResSkMesh(RES_SK_MONSTER1);
        MonsterInfo->SetResAnimInst(RES_ANIM_INST_MONSTER);
        MonsterInfo->SetCapsuleSize(FVector2D(50.f, 100.f));
        MonsterInfo->SetMaxHP(100.f);
        MonsterInfo->SetDamage(50.f);
        MonsterInfo->SetMaxWalkSpeed(300.f);
        break;
    case 1:
        MonsterInfo->SetResSkMesh(RES_SK_MONSTER_1);
        MonsterInfo->SetResAnimInst(RES_ANIM_INST_MONSTER_1);
        MonsterInfo->SetCapsuleSize(FVector2D(50.f, 100.f));
        MonsterInfo->SetMaxHP(100.f);
        MonsterInfo->SetDamage(50.f);
        MonsterInfo->SetMaxWalkSpeed(200.f);
        break;
    default:
        break;
    }

    //MonsterInfo->ReimportDT();
    return *MonsterInfo;
}
// Called when the game starts or when spawned
void AB1Monster::BeginPlay()
{
	Super::BeginPlay();
    //printf("BeginPlay");
    //Init(MonsterType);
    //LoadResource();

    if (HUDWidgetClass != nullptr) {
        //BeginPlay() 함수에서  SetWidgetClass 해야 한다. 
        //내부적으로 BeginPlay 인지 확인하고 세팅하기 때문
        auto CharacterWidget = Cast<UB1HPWidget>(HPBarWidget->GetUserWidgetObject());
        if (nullptr != CharacterWidget){
            CharacterWidget->BindCharacterStat(this);
        }
    }

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
}
void AB1Monster::Init(int32 monsterType)
{
    auto B1GameInstance = Cast<UB1GameInstance>(GetGameInstance());
    printf("monsterType %d", monsterType);
    FB1MonaterTableRow* MonsterTableRow = B1GameInstance->GetMonsterData(monsterType);

    if(nullptr == MonsterTableRow){
        printf("MonsterTableRow null");
        return;
    }

    //printf("monsterType %d, health: %f, Damage %f, Speed: %f", monsterType, MonsterTableRow->HP, MonsterTableRow->Speed, MonsterTableRow->Damage);
    FSoftObjectPath mesh = MonsterTableRow->ResSKMesh;
    TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(mesh);
    if (LoadedAssetPath.IsValid()) {
        //printf("LoadedAssetPath %s", *LoadedAssetPath.ToString());
        SkelMesh->SetSkeletalMesh(LoadedAssetPath.Get());
    }

    FSoftObjectPath anim = MonsterTableRow->ResAnimInst;
    TSoftClassPtr<UAnimInstance> LoadedAssetPath2(anim);
    if (LoadedAssetPath2.IsValid()) {
        //printf("LoadedAssetPath2 %s", *LoadedAssetPath2.ToString());
        SkelMesh->SetAnimInstanceClass(LoadedAssetPath2.Get());
    }

    B1CharacterInfo MonsterInfo = GetCharacterInfo(MonsterType);
    GetCapsuleComponent()->SetCapsuleSize(
        MonsterInfo.GetCapsuleSize().X,
        MonsterInfo.GetCapsuleSize().Y
    );

    SkelMesh->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -90.f),
        FRotator(0.f, -90.f, 0.f)    // Roll
    );

    HPBarWidget->SetupAttachment(SkelMesh);
    HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));

    MaxHP = HP = MonsterTableRow->HP;
    GetCharacterMovement()->MaxWalkSpeed = MonsterTableRow->Speed;
    Damage = MonsterTableRow->Damage;

    auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    AnimInst->OnAttackHitCheck.AddUObject(this, &AB1Monster::CheckAttack);
    AnimInst->OnEndOfAttack.AddUObject(this, &AB1Monster::EndOfAttack);
}
void AB1Monster::LoadResource()
{
    //여기 다 수정 해야 함
    auto B1GameInstance = Cast<UB1GameInstance>(GetGameInstance());
    if (nullptr != B1GameInstance) {
        printf("LoadResource");
        //B1CharacterInfo MonsterInfo = GetCharacterInfo(MonsterType);

        //ResourcePathList.AddUnique(MonsterInfo.GetResSkMesh());
        //ResourcePathList.AddUnique(MonsterInfo.GetResAnimInst());

        //auto B1GameInstance2 = Cast<UB1GameInstance>(GetGameInstance());

        //B1GameInstance2

        //UDataTable* DT_B1MonsterInfo = B1GameInstance->GetMonsterInfo();

        //if (DT_B1MonsterInfo != nullptr) {
        //    int32 num = DT_B1MonsterInfo->GetRowMap().Num();
        //    printf("num %d", num);
        //    for (int32 Index = 1; Index <= num; ++Index)
        //    {
        //        FB1CharacterData* a = DT_B1MonsterInfo->FindRow<FB1CharacterData>(*FString::FromInt(Index), TEXT(""));
        //        printf("Dagame %f Health %f Speed %f", a->Damage, a->Health, a->Speed);
        //    }
        //}

       // ResourceStreamingHandle = B1GameInstance2->StreamableManager.RequestAsyncLoad(
       //     ResourcePathList, FStreamableDelegate::CreateUObject(this, &AB1Monster::CompletedResourceLoad));
    }
}
void AB1Monster::CompletedResourceLoad()
{
    printf("CompletedResourceLoad type %d", MonsterType);
    ResourceStreamingHandle->ReleaseHandle();

    TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(ResourcePathList[0]);
    if (LoadedAssetPath.IsValid()) {
        SkelMesh->SetSkeletalMesh(LoadedAssetPath.Get());
    }

    SkelMesh->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -90.f),
        FRotator(0.f, -90.f, 0.f)    // Roll
    );

    HPBarWidget->SetupAttachment(SkelMesh);
    HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));

    TSoftClassPtr<UAnimInstance> LoadedAssetPath2(ResourcePathList[1]);
    if (LoadedAssetPath2.IsValid()) {
        SkelMesh->SetAnimInstanceClass(LoadedAssetPath2.Get());
    }

    //FB1CharacterData* MonsterData = DT_B1MonsterInfo->FindRow<FB1CharacterData>(*FString::FromInt(MonsterType), TEXT(""));
    ////printf("MonsterData %p", MonsterData);

    //if (MonsterData != nullptr) {
    //    //printf("MonsterType %d, health: %f, Damage %f, Speed: %f", MonsterType, MonsterData->Health, MonsterData->Damage, MonsterData->Speed);
    //    MaxHP = HP = MonsterData->Health;
    //    Damage = MonsterData->Damage;
    //    GetCharacterMovement()->MaxWalkSpeed = MonsterData->Speed;
    //}


    auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    AnimInst->OnAttackHitCheck.AddUObject(this, &AB1Monster::CheckAttack);
    AnimInst->OnEndOfAttack.AddUObject(this, &AB1Monster::EndOfAttack);

    //SetCharacterState(ECharacterState::READY);
}
void AB1Monster::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
}
// Called every frame
void AB1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    auto B1GameInstance = Cast<UB1GameInstance>(GetGameInstance());
    if (B1GameInstance->IsMonsterTableLoad && IsInit == false) {
        //printf("B1GameInstance->IsMonsterTableLoad %d", B1GameInstance->IsMonsterTableLoad);
        Init(MonsterType);
        IsInit = true;
    }

}
// Called to bind functionality to input
void AB1Monster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void AB1Monster::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    //auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    //AnimInst->OnAttackHitCheck.AddUObject(this, &AB1Monster::CheckAttack);
    //AnimInst->OnEndOfAttack.AddUObject(this, &AB1Monster::EndOfAttack);
}
float AB1Monster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    //printf("Actor %s took Damage %f", *GetName(), FinalDamage);

    HP -= DamageAmount;
    if (0.0f > HP)
    {
        HP = 0.0f;
    }
    OnHPChanged.Broadcast();

    return FinalDamage;
}
void AB1Monster::CheckAttack()
{
    float FinalAttackRange = 150.f;
    FHitResult HitResult;
    FCollisionQueryParams Params(NAME_None, false, this);
    
    bool bResult = this->GetWorld()->SweepSingleByChannel(
        HitResult,
        this->GetActorLocation(),
        this->GetActorLocation() + this->GetActorForwardVector() * FinalAttackRange,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel4,
        FCollisionShape::MakeSphere(50.0f),
        Params);

#if ENABLE_DRAW_DEBUG
    FVector TraceVec = this->GetActorForwardVector() * FinalAttackRange;
    FVector Center = this->GetActorLocation() + TraceVec * 0.5f;
    float AttackRadius = 50.f;
    float HalfHeight = FinalAttackRange * 0.5f + AttackRadius;
    FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
    FColor DrawColor = bResult ? FColor::Green : FColor::Red;
    float DebugLifeTime = 0.5f;

    DrawDebugCapsule(this->GetWorld(),
        Center,
        HalfHeight,
        AttackRadius,
        CapsuleRot,
        DrawColor,
        false,
        DebugLifeTime);


#endif
    
    if (HitResult.Actor.IsValid())
    {
        FDamageEvent DamageEvent;
        HitResult.Actor->TakeDamage(Damage, DamageEvent, this->GetController(), this);
    }
}
void AB1Monster::EndOfAttack()
{
    OnAttackEnd.Broadcast();
}
void AB1Monster::SetMonsterState(ERES_STATE_MONSTER state)
{
    auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    AnimInst->SetMonsterState(state);
}