// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Weapon.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AB1Weapon::AB1Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WEAPON(TEXT("/Game/Resources/Market/ModularRPGHeroesPolyart/Meshes/Weapons/Axe01SM.Axe01SM"));
	if (SM_WEAPON.Succeeded()) {
		Weapon->SetStaticMesh(SM_WEAPON.Object);
	}
	else {
		printf("SM_WEAPON fail");
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AB1Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AB1Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

