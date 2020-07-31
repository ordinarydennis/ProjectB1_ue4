// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECT_B1.h"
#include "Blueprint/UserWidget.h"
#include "Skill/B1Skill.h"
#include "B1InGameWidget.generated.h"

UENUM()
enum class BTN_SKILL_INDEX : uint8
{
	INDEX_NONE,
	INDEX_1,
	INDEX_2,
	INDEX_3,
	INDEX_4
};

inline //이게 없으면 정의는 cpp 파일에 있어야 한다. 없으면 중복 정의 오류 발생함.
BTN_SKILL_INDEX& operator++(BTN_SKILL_INDEX& BtnSkillIndex)
{
	switch (BtnSkillIndex)
	{
	case BTN_SKILL_INDEX::INDEX_NONE: return BtnSkillIndex = BTN_SKILL_INDEX::INDEX_1;
	case BTN_SKILL_INDEX::INDEX_1: return BtnSkillIndex = BTN_SKILL_INDEX::INDEX_2;
	case BTN_SKILL_INDEX::INDEX_2: return BtnSkillIndex = BTN_SKILL_INDEX::INDEX_3;
	case BTN_SKILL_INDEX::INDEX_3: return BtnSkillIndex = BTN_SKILL_INDEX::INDEX_4;
	case BTN_SKILL_INDEX::INDEX_4: return BtnSkillIndex = BTN_SKILL_INDEX::INDEX_1;
	default: return BtnSkillIndex = BTN_SKILL_INDEX::INDEX_1;
	}
}

UCLASS()
class PROJECT_B1_API UB1InGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UB1InGameWidget(const FObjectInitializer& ObjectInitializer);
	void LoadImage();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION()
	void onClickedAttack();
	//TODO: onClickedSkill1 이하 모두 수정하기
	UFUNCTION()
	void onSkill1Clicked();
	UFUNCTION()
	void onSkill2Clicked();
	UFUNCTION()
	void onSkill3Clicked();
	UFUNCTION()
	void onSkill4Clicked();

private:
	IB1Skill* GetSkill(BTN_SKILL_INDEX SkillBtnIndex);
	void StopSkill();
	void SetNextSkillImg();

private:
	//IB1Skill* Skill = nullptr;
	BTN_SKILL_INDEX BtnIndex = BTN_SKILL_INDEX::INDEX_NONE;
	TArray<TSharedPtr<IB1Skill>> Skills;
	TMap<BTN_SKILL_INDEX, UButton*> Btns;
	TMap<BTN_SKILL_INDEX, IB1Skill*> SkillsOfBtn;
	TQueue<IB1Skill*> SkillQueue;
	AB1Character* B1Character = nullptr;
};

