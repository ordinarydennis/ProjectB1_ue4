// Fill out your copyright notice in the Description page of Project Settings.


#include "B1InGameWidget.h"
#include "B1Character.h"
#include "Components/Button.h"

void UB1InGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UButton* btnSkill1 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill1")));
	if (nullptr != btnSkill1) {
		btnSkill1->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill1Clicked);
	}

	UButton* btnSkill2 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill2")));
	if (nullptr != btnSkill2) {
		btnSkill2->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill2Clicked);
	}

	UButton* btnSkill3 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill3")));
	if (nullptr != btnSkill3) {
		btnSkill3->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill3Clicked);
	}

	UButton* btnSkill4 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill4")));
	if (nullptr != btnSkill4) {
		btnSkill4->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill4Clicked);
	}
}

void UB1InGameWidget::onSkill1Clicked()
{
	//캐릭터에 세팅 
	auto B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	B1Character->RunSkill(BTN_SKILL_INDEX::INDEX_1);
}

void UB1InGameWidget::onSkill2Clicked()
{
	auto B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	B1Character->RunSkill(BTN_SKILL_INDEX::INDEX_2);
}

void UB1InGameWidget::onSkill3Clicked()
{
	auto B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	B1Character->RunSkill(BTN_SKILL_INDEX::INDEX_3);
}

void UB1InGameWidget::onSkill4Clicked()
{
	auto B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	B1Character->RunSkill(BTN_SKILL_INDEX::INDEX_4);
}