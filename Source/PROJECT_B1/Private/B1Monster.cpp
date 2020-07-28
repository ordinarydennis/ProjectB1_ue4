// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Monster.h"
#include "B1MonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "B1HPWidget.h"
#include "B1MonsterAIController.h"
#include "B1CharacterInfo.h"
#include "B1GameInstance.h"
#include "B1CustomStructs.h"
#include "B1DebugPrint.h"

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
}
// Called when the game starts or when spawned
void AB1Monster::BeginPlay()
{
	Super::BeginPlay();

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
    const FB1MonaterTableRow* MonsterTableRow = B1GameInstance->GetMonsterData(monsterType);

    if(nullptr == MonsterTableRow){
        printf("MonsterTableRow null");
        return;
    }

    FSoftObjectPath mesh = MonsterTableRow->ResSKMesh;
    TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(mesh);
    if (LoadedAssetPath.IsValid()) {
        SkelMesh->SetSkeletalMesh(LoadedAssetPath.Get());
    }

    FSoftObjectPath anim = MonsterTableRow->ResAnimInst;
    TSoftClassPtr<UAnimInstance> LoadedAssetPath2(anim);
    if (LoadedAssetPath2.IsValid()) {
        SkelMesh->SetAnimInstanceClass(LoadedAssetPath2.Get());
    }

    GetCapsuleComponent()->SetCapsuleSize(MonsterTableRow->CapsuleSizeX, MonsterTableRow->CapsuleSizeY);

    SkelMesh->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -90.f),
        FRotator(0.f, -90.f, 0.f)    // Roll
    );

    //출력 로그창에서 버그 나오는거 리소스 로딩 때문인 것 같다.
    HPBarWidget->SetupAttachment(SkelMesh);
    HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));

    MaxHP = HP = MonsterTableRow->HP;
    GetCharacterMovement()->MaxWalkSpeed = MonsterTableRow->Speed;
    Damage = MonsterTableRow->Damage;

    auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    AnimInst->OnCheckAttackHit.AddUObject(this, &AB1Monster::CheckAttackHit);
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

}
float AB1Monster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    HP -= DamageAmount;
    if (0.0f >= HP)
    {
        HP = 0.0f;
        IsDeath = true;
        auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
        AnimInst->SetIsDeath(IsDeath);
        SetActorEnableCollision(false);
        GetMesh()->SetHiddenInGame(false);
        HPBarWidget->SetHiddenInGame(true);

        AController* CurrentController = GetController();
        if (CurrentController) {
            // Stop movement so the death animation plays immediately
            CurrentController->StopMovement();
            // Unpossess to stop AI
            CurrentController->UnPossess();
            // Destroy the controller, since it's not part of the enemy anymore
            CurrentController->Destroy();
        }
    }
    OnHPChanged.Broadcast();

    return FinalDamage;
}
void AB1Monster::CheckAttackHit()
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