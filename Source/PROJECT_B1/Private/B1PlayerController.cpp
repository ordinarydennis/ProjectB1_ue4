// Fill out your copyright notice in the Description page of Project Settings.


#include "B1PlayerController.h"
#include "B1InGameWidget.h"

AB1PlayerController::AB1PlayerController()
{
	bShowMouseCursor = true;
	static ConstructorHelpers::FClassFinder<UB1InGameWidget> ResWidInGameC(*RES_WID_INGAME_C);

	if (ResWidInGameC.Succeeded()) {
		WidInGameClass = ResWidInGameC.Class;
	}
}
void AB1PlayerController::BeginPlay()
{
	WidInGame = CreateWidget<UB1InGameWidget>(this, WidInGameClass);
	WidInGame->AddToViewport();
}