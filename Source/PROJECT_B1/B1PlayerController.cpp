// Fill out your copyright notice in the Description page of Project Settings.


#include "B1PlayerController.h"
#include "B1InGameWidget.h"

AB1PlayerController::AB1PlayerController()
{
	bShowMouseCursor = true;
	static ConstructorHelpers::FClassFinder<UB1InGameWidget> INGAME_WIDGET(
		TEXT("/Game/UI/InGameWidget.InGameWidget_C"));

	if (INGAME_WIDGET.Succeeded()) {
		InGameWidgetClass = INGAME_WIDGET.Class;
	}
}
void AB1PlayerController::BeginPlay()
{
	InGameWidget = CreateWidget<UB1InGameWidget>(this, InGameWidgetClass);
	InGameWidget->AddToViewport();
}