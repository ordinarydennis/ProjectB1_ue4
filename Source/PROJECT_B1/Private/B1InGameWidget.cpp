// Fill out your copyright notice in the Description page of Project Settings.


#include "B1InGameWidget.h"
#include "B1Character.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "SkillFactory.h"

UB1InGameWidget::UB1InGameWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	if (nullptr == B1Character) {
		B1Character = Cast<AB1Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	if (nullptr == B1Character) {
		return;
	}

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
	Skills.Reserve(6);
	for (const auto& skillNum : skillNums) {
		auto skill = USkillFactory::GetInstance()->CreateSkill(skillNum, B1Character);
		//skill->init(B1Character);
		Skills.Add(skill);
		SkillQueue.Enqueue(skill.Get());
	}

	//버튼에 넣을때는 순서대로 넣고 SkillQueue 여기서 순환에서 버튼에 넣는다.
	BTN_SKILL_INDEX a = BTN_SKILL_INDEX::INDEX_NONE;
	for (int i = 0; i < NUM_OF_INGAME_SKILL_BTN; i++) {
		IB1Skill* Skill;
		SkillQueue.Dequeue(Skill);
		SkillsOfBtn.Add(++a, Skill);
	}
}
void UB1InGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UButton* btnAttack = Cast<UButton>(GetWidgetFromName(TEXT("btnAttack")));
	if (nullptr != btnAttack) {
		btnAttack->OnClicked.AddDynamic(this, &UB1InGameWidget::onClickedAttack);
	}

	Btns.Reserve(NUM_OF_INGAME_SKILL_BTN);

	auto BtnIndex2 = BTN_SKILL_INDEX::INDEX_NONE;
	UButton* btnSkill1 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill1")));
	if (nullptr != btnSkill1) {
		btnSkill1->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill1Clicked);
		Btns.Add(++BtnIndex2, btnSkill1);
	}

	UButton* btnSkill2 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill2")));
	if (nullptr != btnSkill2) {
		btnSkill2->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill2Clicked);
		Btns.Add(++BtnIndex2, btnSkill2);
	}

	UButton* btnSkill3 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill3")));
	if (nullptr != btnSkill3) {
		btnSkill3->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill3Clicked);
		Btns.Add(++BtnIndex2, btnSkill3);
	}

	UButton* btnSkill4 = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill4")));
	if (nullptr != btnSkill4) {
		btnSkill4->OnClicked.AddDynamic(this, &UB1InGameWidget::onSkill4Clicked);
		Btns.Add(++BtnIndex2, btnSkill4);
	}

	LoadImage();

	auto AnimInst = Cast<UB1AnimInstance>(B1Character->GetMesh()->GetAnimInstance());
	AnimInst->OnEndofAnim.AddUObject(this, &UB1InGameWidget::StopSkill);
}
void UB1InGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//여기 소스코드 한번 정리하기
	//이미 색이 세팅되어 있다면 세팅하지 않기
	BTN_SKILL_INDEX a = BTN_SKILL_INDEX::INDEX_NONE;
	for (int i = 0; i < NUM_OF_INGAME_SKILL_BTN; i++) {
		auto Skill = SkillsOfBtn.Find(++a);
		if (nullptr == Skill) {
			continue;
		}
		UButton** Btn = Btns.Find(a);
		if (nullptr == Btn) {
			continue;
		}

		if (false == (*Skill)->IsCoolTime()) {
			(*Btn)->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			//(*Btn)->SetIsEnabled(true);
		}
		else {
			(*Btn)->SetBackgroundColor(FLinearColor(0.05f, 0.05f, 0.05f, 1.0f));
			//(*Btn)->SetIsEnabled(false);
		}
	}

	IB1Skill* NextSkill;
	SkillQueue.Peek(NextSkill);
	auto imgSkill = Cast<UImage>(GetWidgetFromName(TEXT("imgNextSkill")));
	if (NextSkill->IsCoolTime()) {
		imgSkill->SetBrushTintColor(FSlateColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.0f)));
	}
	else {
		imgSkill->SetBrushTintColor(FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
	}
}
void UB1InGameWidget::LoadImage()
{
	UButton* btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill1")));
	auto SkillOfBtn = SkillsOfBtn.Find(BTN_SKILL_INDEX::INDEX_1);
	if (nullptr != SkillOfBtn) {
		(*SkillOfBtn)->SetBtnImage(btnSkill);
	}

	btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill2")));
	SkillOfBtn = SkillsOfBtn.Find(BTN_SKILL_INDEX::INDEX_2);
	if (nullptr != SkillOfBtn) {
		(*SkillOfBtn)->SetBtnImage(btnSkill);
	}

	btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill3")));
	SkillOfBtn = SkillsOfBtn.Find(BTN_SKILL_INDEX::INDEX_3);
	if (nullptr != SkillOfBtn) {
		(*SkillOfBtn)->SetBtnImage(btnSkill);
	}

	btnSkill = Cast<UButton>(GetWidgetFromName(TEXT("btnSkill4")));
	SkillOfBtn = SkillsOfBtn.Find(BTN_SKILL_INDEX::INDEX_4);
	if (nullptr != SkillOfBtn) {
		(*SkillOfBtn)->SetBtnImage(btnSkill);
	}	

	SetNextSkillImg();
}
void UB1InGameWidget::onClickedAttack()
{
	if (nullptr == B1Character) {
		return;
	}

	B1Character->RunAttack();
}
void UB1InGameWidget::onSkill1Clicked()
{
	if (nullptr == B1Character || BTN_SKILL_INDEX::INDEX_NONE != BtnIndex) {
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_1);
	if (nullptr == SkillonBtn) {
		printf("Cool Time 4");
		return;
	}

	BtnIndex = BTN_SKILL_INDEX::INDEX_1;
	B1Character->RunSkill(SkillonBtn);
}
void UB1InGameWidget::onSkill2Clicked()
{
	if (nullptr == B1Character || BTN_SKILL_INDEX::INDEX_NONE != BtnIndex) {
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_2);
	if (nullptr == SkillonBtn) {
		printf("Cool Time 4");
		return;
	}

	BtnIndex = BTN_SKILL_INDEX::INDEX_2;
	B1Character->RunSkill(SkillonBtn);
}
void UB1InGameWidget::onSkill3Clicked()
{
	if (nullptr == B1Character || BTN_SKILL_INDEX::INDEX_NONE != BtnIndex) {
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_3);
	if (nullptr == SkillonBtn) {
		printf("Cool Time 4");
		return;
	}

	BtnIndex = BTN_SKILL_INDEX::INDEX_3;
	B1Character->RunSkill(SkillonBtn);
}
void UB1InGameWidget::onSkill4Clicked()
{
	if (nullptr == B1Character || BTN_SKILL_INDEX::INDEX_NONE != BtnIndex) {
		return;
	}

	auto SkillonBtn = GetSkill(BTN_SKILL_INDEX::INDEX_4);
	if (nullptr == SkillonBtn) {
		printf("Cool Time 4");
		return;
	}

	BtnIndex = BTN_SKILL_INDEX::INDEX_4;
	B1Character->RunSkill(SkillonBtn);
}
IB1Skill* UB1InGameWidget::GetSkill(BTN_SKILL_INDEX SkillBtnIndex)
{
	auto skill = SkillsOfBtn.Find(SkillBtnIndex);
	if (nullptr == skill || (*skill)->IsCoolTime()) {
		return nullptr;
	}
	return *skill;
}
void UB1InGameWidget::StopSkill()
{
	if (BTN_SKILL_INDEX::INDEX_NONE == BtnIndex) {
		printf("StopSkill() BTN_SKILL_INDEX::INDEX_NONE ");
		return;
	}

	//스킬 교체 함수로 따로 만들기
	auto Skill = SkillsOfBtn.Find(BtnIndex);
	auto Btn = Btns.Find(BtnIndex);

	SkillQueue.Enqueue(*Skill);
	IB1Skill* NextSkill = nullptr;
	SkillQueue.Dequeue(NextSkill);
	NextSkill->SetBtnImage(*Btn);
	SkillsOfBtn.Add(BtnIndex, NextSkill);
	
	BtnIndex = BTN_SKILL_INDEX::INDEX_NONE;
	B1Character->StopSkill();
	SetNextSkillImg();
}
void UB1InGameWidget::SetNextSkillImg()
{
	IB1Skill* NextSkill;
	SkillQueue.Peek(NextSkill);
	auto imgSkill = Cast<UImage>(GetWidgetFromName(TEXT("imgNextSkill")));
	imgSkill->Brush.SetResourceObject(Cast<UObject>(NextSkill->GetBtnImage()));
	imgSkill->Brush.SetImageSize(FVector2D(130.f, 130.f));
	imgSkill->Brush.DrawAs = ESlateBrushDrawType::Image;
}