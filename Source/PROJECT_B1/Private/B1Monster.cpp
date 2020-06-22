// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Monster.h"
#include "B1MonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "B1HPWidget.h"
#include "B1MonsterAIController.h"
#include "B1CharacterInfo.h"
#include "B1GameInstance.h"

// Sets default values
AB1Monster::AB1Monster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = GetCapsuleComponent();
    GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Monster"));
    // Rendering - SkeletalMeshComponent
    SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("B1MonsterSM"));

    B1CharacterInfo MonsterInfo = getResourceInfo(MonsterType);

    float NewRadius = MonsterInfo.GetCapsuleSize().X;
    float NewHalfHeight = MonsterInfo.GetCapsuleSize().Y;
    GetCapsuleComponent()->SetCapsuleSize(NewRadius, NewHalfHeight);
    
    SkelMesh->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -90.f),
        FRotator(0.f, -90.f, 0.f)    // Roll
    );

    //static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Monster(*MonsterInfo.GetResSkMesh());

    //SkelMesh->SetSkeletalMesh(SK_Monster.Object);

    // Attacth to RootComponent
    SkelMesh->SetupAttachment(RootComponent);

    //static ConstructorHelpers::FClassFinder<UAnimInstance> ResAnimInst(*MonsterInfo.GetResAnimInst());
    //if (ResAnimInst.Succeeded()) {
        //SkelMesh->SetAnimInstanceClass(ResAnimInst.Class);
    //}

    HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
    HPBarWidget->SetupAttachment(SkelMesh);
    //HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
    //SetPivot is better than SetRelativeLocation to adjust widget.
    HPBarWidget->SetPivot(FVector2D(0.5f, 3.f));
    HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
    
    static ConstructorHelpers::FClassFinder<UUserWidget> ResWidgetHP(*RES_WIDGET_HP);
    if (ResWidgetHP.Succeeded()){
        HPBarWidget->SetWidgetClass(ResWidgetHP.Class);
        HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
        HUDWidgetClass = ResWidgetHP.Class;
    }

    MaxHP = HP = 100.0f;
    Damage = 50;

    AIControllerClass = AB1MonsterAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
B1CharacterInfo AB1Monster::getResourceInfo(int monsterType)
{
    B1CharacterInfo MonsterInfo;
    switch (monsterType) {
    case 0:
        MonsterInfo.SetResSkMesh(RES_SK_MONSTER1);
        MonsterInfo.SetResAnimInst(RES_ANIM_INST_MONSTER);
        MonsterInfo.SetCapsuleSize(FVector2D(50.f, 100.f));
        break;
    case 1:
        MonsterInfo.SetResSkMesh(RES_SK_MONSTER_1);
        MonsterInfo.SetResAnimInst(RES_ANIM_INST_MONSTER_1);
        MonsterInfo.SetCapsuleSize(FVector2D(50.f, 100.f));
        break;
    default:
        break;
    }

    return MonsterInfo;
}
// Called when the game starts or when spawned
void AB1Monster::BeginPlay()
{
	Super::BeginPlay();

    auto B1GameInstance = Cast<UB1GameInstance>(GetGameInstance());
    if (nullptr != B1GameInstance) {

        B1CharacterInfo MonsterInfo = getResourceInfo(MonsterType);
       
        AssetList.AddUnique(MonsterInfo.GetResSkMesh());
        AssetList.AddUnique(MonsterInfo.GetResAnimInst());
        
        AssetStreamingHandle = B1GameInstance->StreamableManager.RequestAsyncLoad(
            AssetList, FStreamableDelegate::CreateUObject(this, &AB1Monster::OnAssetLoadCompleted));

    }

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
void AB1Monster::OnAssetLoadCompleted()
{
    AssetStreamingHandle->ReleaseHandle();

    TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(AssetList[0]);
    if (LoadedAssetPath.IsValid()) {
        SkelMesh->SetSkeletalMesh(LoadedAssetPath.Get());
    }

    TSoftClassPtr<UAnimInstance> LoadedAssetPath2(AssetList[1]);
    if (LoadedAssetPath2.IsValid()) {
        printf("LoadedAssetPath2.IsValid() true");
        SkelMesh->SetAnimInstanceClass(LoadedAssetPath2.Get());
    }
    else {
        printf("LoadedAssetPath2.IsValid() false");
    }

    //SetCharacterState(ECharacterState::READY);
}
void AB1Monster::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}
// Called every frame
void AB1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called to bind functionality to input
void AB1Monster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void AB1Monster::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    //printf("MonsterType %d", MonsterType);
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