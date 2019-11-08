// Fill out your copyright notice in the Description page of Project Settings.


#include "B1InGameWidget.h"
#include "B1Character.h"
#include "Components/Button.h"
#include "Skill/1000/B1Skill1000.h"
#include "Skill/1000/B1Skill1001.h"
#include "Skill/1000/B1Skill1002.h"
#include "Skill/1000/B1Skill1003.h"
#include "Skill/1000/B1Skill1004.h"
#include "Skill/1000/B1Skill1005.h"


UB1InGameWidget::UB1InGameWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	if (nullptr == B1Character) {
		B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	if (nullptr == B1Character) {
		return;
	}

	//printf("B1Character GetMesh %p", B1Character->GetMesh());
	//printf("B1Character GetAnimInstance %p", B1Character->GetMesh()->GetAnimInstance());

	//유저의 스킬을 여기에서 로딩 하도록 한다.
	//유저의 스킬을 모두 가져온다.
	//스킬 배열 만든다. 섞는다.
	//다음 가져올 인덱스 필요
	//스킬 큐에서 앞부터 
	//버튼 맵에 스킬 큐 앞부터 넣는다.
	//디비에서 유저의 스킬 번호 리스트를 가져온다. 
	TArray<ERES_ANIM_NUM> skillNums;
	skillNums.Add(ERES_ANIM_NUM::_1000);
	skillNums.Add(ERES_ANIM_NUM::_1001);
	skillNums.Add(ERES_ANIM_NUM::_1002);
	skillNums.Add(ERES_ANIM_NUM::_1003);
	skillNums.Add(ERES_ANIM_NUM::_1004);
	skillNums.Add(ERES_ANIM_NUM::_1005);

	//스킬 초기화
	//초기화 시점과 큐에 넣는 시점이 달라야 한다.
	InGameSkills2.Reserve(6);
	for (const auto& skillNum : skillNums) {
		auto skill = Factory(skillNum);
		skill->init(B1Character);
		InGameSkills2.Add(skill);
		SkillQueue.Enqueue(skill.Get());
	}

	//버튼에 넣을때는 순서대로 넣고 SkillQueue 여기서 순환에서 버튼에 넣는다.
	BTN_SKILL_INDEX a = BTN_SKILL_INDEX::INDEX_NONE;
	for (int i = 0; i < NUM_OF_INGAME_SKILL_BTN; i++) {
		IB1Skill* Skill;
		SkillQueue.Dequeue(Skill);
		InGameSkills.Add(++a, Skill);
	}
}
void UB1InGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BtnArr.Reserve(NUM_OF_INGAME_SKILL_BTN);

	auto BtnIndex2 = BTN_SKILL_INDEX::INDEX_NONE;
	UButton* btnSkill1 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill1")));
	//auto SkillonBtn = InGameSkills.Find(BTN_SKILL_INDEX::INDEX_1);
	if (nullptr != btnSkill1) {
		//(*SkillonBtn)->SetBtnImage(btnSkill1);
		btnSkill1->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill1Clicked);
		BtnArr.Add(++BtnIndex2, btnSkill1);
	}

	UButton* btnSkill2 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill2")));
	if (nullptr != btnSkill2) {
		//(*SkillonBtn)->SetBtnImage(btnSkill2);
		btnSkill2->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill2Clicked);
		BtnArr.Add(++BtnIndex2, btnSkill2);
	}

	UButton* btnSkill3 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill3")));
	if (nullptr != btnSkill3) {
		btnSkill3->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill3Clicked);
		BtnArr.Add(++BtnIndex2, btnSkill3);
	}

	UButton* btnSkill4 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill4")));
	if (nullptr != btnSkill4) {
		btnSkill4->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill4Clicked);
		BtnArr.Add(++BtnIndex2, btnSkill4);
	}

	LoadImage();

	auto AnimationInst = Cast<UB1AnimInstance>(B1Character->GetMesh()->GetAnimInstance());
	AnimationInst->OnEndofAnim.AddUObject(this, &UB1InGameWidget::StopSkill);
}
void UB1InGameWidget::LoadImage()
{
	UButton* btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill1")));
	auto btn = InGameSkills.Find(BTN_SKILL_INDEX::INDEX_1);
	if (nullptr != btn) {
		(*btn)->SetBtnImage(btnSkill);
	}

	btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill2")));
	btn = InGameSkills.Find(BTN_SKILL_INDEX::INDEX_2);
	if (nullptr != btn) {
		(*btn)->SetBtnImage(btnSkill);
	}

	btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill3")));
	btn = InGameSkills.Find(BTN_SKILL_INDEX::INDEX_3);
	if (nullptr != btn) {
		(*btn)->SetBtnImage(btnSkill);
	}

	btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill4")));
	btn = InGameSkills.Find(BTN_SKILL_INDEX::INDEX_4);
	if (nullptr != btn) {
		(*btn)->SetBtnImage(btnSkill);
	}
}
void UB1InGameWidget::onSkill1Clicked()
{
	if (nullptr == B1Character || nullptr != Skill) {
		//printf("Skill is running");
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_1);
	if (nullptr == SkillonBtn) {
		//printf("0 Cool Time");
		return;
	}
	BtnIndex = BTN_SKILL_INDEX::INDEX_1;
	Skill = SkillonBtn;
	B1Character->RunSkill(Skill);
}
void UB1InGameWidget::onSkill2Clicked()
{
	if (nullptr == B1Character || nullptr != Skill) {
		//printf("Skill is running");
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_2);
	if (nullptr == SkillonBtn) {
		//printf("1 Cool Time");
		return;
	}
	BtnIndex = BTN_SKILL_INDEX::INDEX_2;
	Skill = SkillonBtn;
	B1Character->RunSkill(Skill);
}
void UB1InGameWidget::onSkill3Clicked()
{
	if (nullptr == B1Character || nullptr != Skill) {
		//printf("Skill is running");
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_3);
	if (nullptr == SkillonBtn) {
		//printf("3 Cool Time");
		return;
	}
	BtnIndex = BTN_SKILL_INDEX::INDEX_3;
	Skill = SkillonBtn;
	B1Character->RunSkill(Skill);
}
void UB1InGameWidget::onSkill4Clicked()
{
	if (nullptr == B1Character || nullptr != Skill) {
		//printf("Skill is running");
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_4);
	if (nullptr == SkillonBtn) {
		//printf("4 Cool Time");
		return;
	}
	BtnIndex = BTN_SKILL_INDEX::INDEX_4;
	Skill = SkillonBtn;
	B1Character->RunSkill(Skill);
}
void UB1InGameWidget::ChangeSkillBtn()
{
	auto skill = InGameSkills.Find(BtnIndex);
	if (nullptr != skill) {
		(*skill)->SetBtnImage(BtnArr[BtnIndex]);
	}
}
TSharedPtr<IB1Skill> UB1InGameWidget::Factory(ERES_ANIM_NUM SkillNum)
{
	TSharedPtr<IB1Skill> skill = nullptr;
	switch (SkillNum)
	{
	case ERES_ANIM_NUM::_1000 :
		skill = MakeShareable(new B1Skill1000());
		break;
	case ERES_ANIM_NUM::_1001 :
		skill = MakeShareable(new B1Skill1001());
		break;
	case ERES_ANIM_NUM::_1002 :
		skill = MakeShareable(new B1Skill1002());
		break;
	case ERES_ANIM_NUM::_1003 :
		skill = MakeShareable(new B1Skill1003());
		break;
	case ERES_ANIM_NUM::_1004 :
		skill = MakeShareable(new B1Skill1004());
		break;
	case ERES_ANIM_NUM::_1005 :
		skill = MakeShareable(new B1Skill1005());
		break;
	}
	return skill;
}
IB1Skill* UB1InGameWidget::GetSkill(BTN_SKILL_INDEX SkillBtnIndex)
{
	auto skill = InGameSkills.Find(SkillBtnIndex);
	if (nullptr == skill || (*skill)->IsCoolTime()) {
		return nullptr;
	}
	return *skill;
}
void UB1InGameWidget::StopSkill()
{
	//printf("Enqueue %s", *Skill->GetName());
	SkillQueue.Enqueue(Skill);
	IB1Skill* Skill2;
	SkillQueue.Dequeue(Skill2);
	//printf("Dequeue %s", *Skill2->GetName());
	InGameSkills.Add(BtnIndex, Skill2);

	auto Btn = BtnArr.Find(BtnIndex);
	Skill2->SetBtnImage(*Btn);
	
	Skill = nullptr;
	BtnIndex = BTN_SKILL_INDEX::INDEX_NONE;

	B1Character->StopSkill();
}