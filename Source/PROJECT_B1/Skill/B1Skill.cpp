// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Skill.h"
#include "Components/Button.h"

// Add default functionality here for any IB1Skill functions that are not pure virtual.

bool IB1Skill::IsCoolTime()
{
	bool ret = false;
	if (FDateTime::Now().ToUnixTimestamp() - SkillStartTimestamp <= CoolTime) {
		ret = true;
	}
	else {
		SkillStartTimestamp = 0;
	}
	return ret;
}
void IB1Skill::SetBtnImage(UButton* btn)
{
	if (nullptr == btn || nullptr == SkillIconTexture) {
		return;
	}

	btn->WidgetStyle.Normal.SetResourceObject(Cast<UObject>(SkillIconTexture));
	btn->WidgetStyle.Normal.SetImageSize(FVector2D(400.f, 400.f));
	btn->WidgetStyle.Normal.DrawAs = ESlateBrushDrawType::Image;

	btn->WidgetStyle.Hovered.SetResourceObject(Cast<UObject>(SkillIconTexture));
	btn->WidgetStyle.Hovered.SetImageSize(FVector2D(300.f, 300.f));
	btn->WidgetStyle.Hovered.DrawAs = ESlateBrushDrawType::Image;

	btn->WidgetStyle.Pressed.SetResourceObject(Cast<UObject>(SkillIconTexture));
	btn->WidgetStyle.Pressed.SetImageSize(FVector2D(100.f, 100.f));
	btn->WidgetStyle.Pressed.DrawAs = ESlateBrushDrawType::Image;

	btn->WidgetStyle.Disabled.SetResourceObject(Cast<UObject>(SkillIconTexture));
	btn->WidgetStyle.Disabled.SetImageSize(FVector2D(100.f, 100.f));
	btn->WidgetStyle.Disabled.DrawAs = ESlateBrushDrawType::Image;

	//btn->SetIsEnabled(false);

}
FString IB1Skill::GetName()
{	
	return ClassName;
}