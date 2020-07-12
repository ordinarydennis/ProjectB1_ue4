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

	//������ ��ų�� ���⿡�� �ε� �ϵ��� �Ѵ�.
	//������ ��ų�� ��� �����´�.
	//��ų �迭 �����. ���´�.
	//���� ������ �ε��� �ʿ�
	//��ų ť���� �պ��� 
	//��ư �ʿ� ��ų ť �պ��� �ִ´�.
	//��񿡼� ������ ��ų ��ȣ ����Ʈ�� �����´�. 
	TArray<ERES_ANIM_NUM> skillNums;
	skillNums.Add(ERES_ANIM_NUM::_1000);
	skillNums.Add(ERES_ANIM_NUM::_1001);
	skillNums.Add(ERES_ANIM_NUM::_1002);
	skillNums.Add(ERES_ANIM_NUM::_1003);
	skillNums.Add(ERES_ANIM_NUM::_1004);
	skillNums.Add(ERES_ANIM_NUM::_1005);

	//��ų �ʱ�ȭ
	//�ʱ�ȭ ������ ť�� �ִ� ������ �޶�� �Ѵ�.
	Skills.Reserve(6);
	for (const auto& skillNum : skillNums) {
		auto skill = USkillFactory::GetInstance()->CreateSkill(skillNum, B1Character);
		//skill->init(B1Character);
		Skills.Add(skill);
		SkillQueue.Enqueue(skill.Get());
	}

	//��ư�� �������� ������� �ְ� SkillQueue ���⼭ ��ȯ���� ��ư�� �ִ´�.
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

	//���� �ҽ��ڵ� �ѹ� �����ϱ�
	//�̹� ���� ���õǾ� �ִٸ� �������� �ʱ�
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

	//��ų ��ü �Լ��� ���� �����
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