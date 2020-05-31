// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Monster.h"
#include "B1MonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "B1HPWidget.h"

// Sets default values
AB1Monster::AB1Monster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
    BoxCollision->SetGenerateOverlapEvents(true);
    BoxCollision->SetBoxExtent(FVector(40.f, 40.f, 100.f));
    BoxCollision->SetCollisionProfileName(TEXT("B1Monster"));

    RootComponent = BoxCollision;

    // Rendering - SkeletalMeshComponent
    SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("B1MonsterSM"));
    SkelMesh->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -90.f),
        FRotator(0.f, -90.f, 0.f)    // Roll
    );

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Monster(*RES_SK_MONSTER1);
    SkelMesh->SetSkeletalMesh(SK_Monster.Object);
    // Attacth to RootComponent
    SkelMesh->SetupAttachment(BoxCollision);

    static ConstructorHelpers::FClassFinder<UAnimInstance> ResAnimInst(*RES_ANIM_INST_MONSTER);
    if (ResAnimInst.Succeeded()) {
        SkelMesh->SetAnimInstanceClass(ResAnimInst.Class);
    }


    HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
    HPBarWidget->SetupAttachment(SkelMesh);
    HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
    HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
    static ConstructorHelpers::FClassFinder<UUserWidget> ResWidgetHP(*RES_WIDGET_HP);
    if (ResWidgetHP.Succeeded())
    {
        HPBarWidget->SetWidgetClass(ResWidgetHP.Class);
        HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
        HUDWidgetClass = ResWidgetHP.Class;
    }
}

// Called when the game starts or when spawned
void AB1Monster::BeginPlay()
{
	Super::BeginPlay();

    if (HUDWidgetClass != nullptr) {
        //BeginPlay() 함수에서  SetWidgetClass 해야 한다. 
        //내부적으로 BeginPlay 인지 확인하고 세팅하기 때문
        auto CharacterWidget = Cast<UB1HPWidget>(HPBarWidget->GetUserWidgetObject());
        if (nullptr != CharacterWidget)
        {
            CharacterWidget->BindCharacterStat(this);
        }
    }

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

    auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    AnimInst->OnAttackHitCheck.AddUObject(this, &AB1Monster::CheckAttack);

}
float AB1Monster::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    //printf("Actor %s took Damage %f", *GetName(), FinalDamage);

    //auto AnimInst = Cast<UB1MonsterAnimInstance>(SkelMesh->GetAnimInstance());
    //AnimInst->SetDeadAnim();

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
        HitResult.Actor->TakeDamage(100, DamageEvent, this->GetController(), this);
    }
}