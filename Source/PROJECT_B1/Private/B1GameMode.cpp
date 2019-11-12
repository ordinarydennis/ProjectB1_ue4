// Fill out your copyright notice in the Description page of Project Settings.


#include "B1GameMode.h"
#include "B1Character.h"
#include "B1PlayerController.h"

AB1GameMode::AB1GameMode()
{
	PlayerControllerClass = AB1PlayerController::StaticClass();
	DefaultPawnClass = AB1Character::StaticClass();
}