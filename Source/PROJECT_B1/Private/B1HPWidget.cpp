// Fill out your copyright notice in the Description page of Project Settings.


#include "B1HPWidget.h"
#include "B1Monster.h"
#include "Components/ProgressBar.h"

void UB1HPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
}
void UB1HPWidget::BindCharacterStat(AB1Monster* monster)
{
	//모든 클래스가 사용 할수 있도록 수정!
	monster->OnHPChanged.AddUObject(this, &UB1HPWidget::UpdateHPWidget);
}
void UB1HPWidget::UpdateHPWidget()
{
	printf("UpdateHPWidget HPProgressBar %p", HPProgressBar);
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetPercent(0.5);
	}
}