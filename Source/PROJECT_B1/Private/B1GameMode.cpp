// Fill out your copyright notice in the Description page of Project Settings.


#include "B1GameMode.h"
#include "B1Character.h"
#include "B1PlayerController.h"

AB1GameMode::AB1GameMode()
{
	PlayerControllerClass = AB1PlayerController::StaticClass();
	//DefaultPawnClass = AB1Character::StaticClass();

    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/B1CharacterBP.B1CharacterBP_C"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}