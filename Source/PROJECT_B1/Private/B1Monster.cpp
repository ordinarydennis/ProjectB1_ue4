// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Monster.h"

// Sets default values
AB1Monster::AB1Monster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Rendering - SkeletalMeshComponent
    SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("B1MonsterSM"));

    SkelMesh->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, 10.f),
        FRotator(0.f, -90.f, 0.f)    // Roll
    );

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Warrior(*RES_SK_MONSTER1);
    SkelMesh->SetSkeletalMesh(SK_Warrior.Object);
    // Attacth to RootComponent
    SkelMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FClassFinder<UAnimInstance> ResAnimInst(*RES_ANIM_INST_MONSTER);
    if (ResAnimInst.Succeeded()) {
        SkelMesh->SetAnimInstanceClass(ResAnimInst.Class);
    }
}

// Called when the game starts or when spawned
void AB1Monster::BeginPlay()
{
	Super::BeginPlay();
	
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

