// Fill out your copyright notice in the Description page of Project Settings.


#include "B1InGameWidget.h"
#include "B1Character.h"
#include "Components/Button.h"
#include "Components/Image.h"
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
		auto skill = SkillFactory(skillNum, B1Character);
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

	static ConstructorHelpers::FObjectFinder<UTexture2D> NextSkillIcon(TEXT("/Game/Resources/Market/CraftResourcesIcons/Textures/Tex_stone_11_b.Tex_stone_11_b"));
	if (NextSkillIcon.Succeeded()) {
		NextSkillIconTexture = NextSkillIcon.Object;
	}
}
void UB1InGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

	auto AnimationInst = Cast<UB1AnimInstance>(B1Character->GetMesh()->GetAnimInstance());
	AnimationInst->OnEndofAnim.AddUObject(this, &UB1InGameWidget::StopSkill);
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
TSharedPtr<IB1Skill> UB1InGameWidget::SkillFactory(ERES_ANIM_NUM SkillNum, AB1Character* character)
{
	TSharedPtr<IB1Skill> skill = nullptr;
	switch (SkillNum)
	{
	case ERES_ANIM_NUM::_1000 :
		skill = MakeShareable(new B1Skill1000(character));
		break;
	case ERES_ANIM_NUM::_1001 :
		skill = MakeShareable(new B1Skill1001(character));
		break;
	case ERES_ANIM_NUM::_1002 :
		skill = MakeShareable(new B1Skill1002(character));
		break;
	case ERES_ANIM_NUM::_1003 :
		skill = MakeShareable(new B1Skill1003(character));
		break;
	case ERES_ANIM_NUM::_1004 :
		skill = MakeShareable(new B1Skill1004(character));
		break;
	case ERES_ANIM_NUM::_1005 :
		skill = MakeShareable(new B1Skill1005(character));
		break;
	}
	return skill;
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