// Fill out your copyright notice in the Description page of Project Settings.


#include "B1HPWidget.h"
#include "B1Monster.h"
#include "B1Character.h"
#include "Components/ProgressBar.h"

void UB1HPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
}
void UB1HPWidget::BindCharacterStat(APawn* pawn)
{
	//��� Ŭ������ ��� �Ҽ� �ֵ��� ����!
	//AB1Pawn�� �����
	auto monster = Cast<AB1Monster>(pawn);
	if (nullptr != monster)
	{
		monster->OnHPChanged.AddUObject(this, &UB1HPWidget::UpdateHPWidget);
	}
	auto character = Cast<AB1Character>(pawn);
	if (nullptr != character)
	{
		character->OnHPChanged.AddUObject(this, &UB1HPWidget::UpdateHPWidget);
	}
}
void UB1HPWidget::UpdateHPWidget()
{
	printf("UpdateHPWidget HPProgressBar %p", HPProgressBar);
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetPercent(0.5);
	}
}