// Fill out your copyright notice in the Description page of Project Settings.


#include "B1BaseCharacter.h"

// Sets default values
AB1BaseCharacter::AB1BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
float AB1BaseCharacter::GetHP()
{
	return HP;
}
float AB1BaseCharacter::GetMaxHP()
{
	return MaxHP;
}
// Called when the game starts or when spawned
void AB1BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AB1BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AB1BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

