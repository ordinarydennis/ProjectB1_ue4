// Fill out your copyright notice in the Description page of Project Settings.


#include "B1SkillEffect.h"
#include "B1BaseCharacter.h"

B1SkillEffect::B1SkillEffect()
{
}
B1SkillEffect::~B1SkillEffect()
{
}
void B1SkillEffect::ApplyEffect(AB1BaseCharacter* baseCharacter)
{
	StartTimestamp = FDateTime::Now().ToUnixTimestamp();
	if(0 == Type){
		Duration = 5;
		baseCharacter->SetDamage(baseCharacter->GetDamage() * 2.f);
	}
}
bool B1SkillEffect::IsEnd()
{
	int64 CurrentTimestamp = FDateTime::Now().ToUnixTimestamp();
	return (Duration <= CurrentTimestamp - StartTimestamp);
}
int32 B1SkillEffect::GetType()
{
	return Type;
}
