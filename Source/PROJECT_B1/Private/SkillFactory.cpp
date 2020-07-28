// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillFactory.h"
#include "B1Character.h"
#include "B1Resources.h"
#include "Skill/1000/B1Skill1000.h"
#include "Skill/1000/B1Skill1001.h"
#include "Skill/1000/B1Skill1002.h"
#include "Skill/1000/B1Skill1003.h"
#include "Skill/1000/B1Skill1004.h"
#include "Skill/1000/B1Skill1005.h"

USkillFactory* USkillFactory::Instance = nullptr;

USkillFactory::USkillFactory()
{

}
USkillFactory* USkillFactory::GetInstance()
{
	if (nullptr == Instance) {
		Instance = NewObject<USkillFactory>();
	}
	return Instance;
}
TSharedPtr<IB1Skill> USkillFactory::CreateSkill(ERES_ANIM_NUM SkillNum, AB1Character* character)
{
	TSharedPtr<IB1Skill> skill = nullptr;
	switch (SkillNum)
	{
	case ERES_ANIM_NUM::_1000:
		skill = MakeShareable(new B1Skill1000(character));
		break;
	case ERES_ANIM_NUM::_1001:
		skill = MakeShareable(new B1Skill1001(character));
		break;
	case ERES_ANIM_NUM::_1002:
		skill = MakeShareable(new B1Skill1002(character));
		break;
	case ERES_ANIM_NUM::_1003:
		skill = MakeShareable(new B1Skill1003(character));
		break;
	case ERES_ANIM_NUM::_1004:
		skill = MakeShareable(new B1Skill1004(character));
		break;
	case ERES_ANIM_NUM::_1005:
		skill = MakeShareable(new B1Skill1005(character));
		break;
	}
	return skill;
}