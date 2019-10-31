// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Character.h"
#include "Skill/1000/B1Skill1000.h"
#include "Skill/1000/B1Skill1001.h"
#include "Skill/1000/B1Skill1002.h"
#include "Skill/1000/B1Skill1003.h"
#include "Skill/1000/B1Skill1004.h"
#include "Skill/1000/B1Skill1005.h"

#include "B1InGameWidget.h"
#include "Misc/DateTime.h"

// Sets default values
AB1Character::AB1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, -90.0f, 0.0f));

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	//시작 위치
	SetActorLocation(FVector(-2560.0f, 0.0f, 0.0f), false);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Character"));

	//유저가 선택한 캐릭터에따라 로딩
	//메인UI에서 입력 받은 값을 가져온다. 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_COMMONER(
		TEXT("/Game/Resources/Market/ModularRPGHeroesPolyart/Meshes/OneMeshCharacters/CommonerSK.CommonerSK"));
	if (SK_COMMONER.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_COMMONER.Object);
		GetMesh()->AddLocalRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->AddRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> PLAYER_ANIM(
		TEXT("/Game/Blueprints/PlayerAnimBlueprint.PlayerAnimBlueprint_C"));
	if (PLAYER_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(PLAYER_ANIM.Class);
	}

	//유저의 스킬을 모두 가져온다.
	//스킬 배열 만든다. 섞는다.
	//다음 가져올 인덱스 필요
	//스킬 큐에서 앞부터 
	//버튼 맵에 스킬 큐 앞부터 넣는다.

	//디비에서 유저의 스킬 번호 리스트를 가져온다. 
	TArray<uint32> skillNums;
	skillNums.Add(1000);
	skillNums.Add(1001);
	skillNums.Add(1002);
	skillNums.Add(1003);
	skillNums.Add(1004);
	skillNums.Add(1005);

	//팩토리 패턴으로 유저의 스킬 객체를 반환 받고 스킬 맵에 넣는다.
	InGameSkills2.Reserve(6);
	for (const auto& skilNum : skillNums){
		//랜덤으로 넣기
		InGameSkills2.Add(Factory(skilNum));
	}


	//버튼에 넣을때는 순서대로 넣고 InGameSkills2 여기서 순환에서 버튼에 넣는다.
	InGameSkills.Add(BTN_SKILL_INDEX::INDEX_1, InGameSkills2[0]);
	InGameSkills.Add(BTN_SKILL_INDEX::INDEX_2, InGameSkills2[1]);
	InGameSkills.Add(BTN_SKILL_INDEX::INDEX_3, InGameSkills2[2]);
	InGameSkills.Add(BTN_SKILL_INDEX::INDEX_4, InGameSkills2[3]);
}
void AB1Character::RunSkill(BTN_SKILL_INDEX BtnSkillIdx)
{
	auto CheckedSkill = InGameSkills.Find(BtnSkillIdx);
	if (nullptr == CheckedSkill || (*CheckedSkill)->IsCoolTime()) {
		return;
	}

	Skill = CheckedSkill;
}

void AB1Character::StopSkill()
{
	Skill = nullptr;
}
void AB1Character::CheckAttack()
{
	if (nullptr != Skill) {
		(*Skill)->CheckAttack();
	}
}
TMap<BTN_SKILL_INDEX, TSharedPtr<IB1Skill>>* AB1Character::GetSkillBtnList()
{
	return &InGameSkills;
}
// Called when the game starts or when spawned
void AB1Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AB1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DirectionToMove.SizeSquared() > 0.0f) {
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove);
	}

	if (nullptr != Skill) {
		(*Skill)->Run();
	}
}

void AB1Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	for(const auto& element:InGameSkills){
		(element.Value)->init(this);
	}

	auto AnimationInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
	AnimationInst->OnAttackHitCheck.AddUObject(this, &AB1Character::CheckAttack);
}

float AB1Character::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//printf("Actor %s Damage %f", *GetName(), FinalDamage);
	return FinalDamage;
}

// Called to bind functionality to input
void AB1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AB1Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AB1Character::LeftRight);
}

void AB1Character::UpDown(float NewAxisValue)
{
	DirectionToMove.Y = NewAxisValue * MovingSpeed;
}
void AB1Character::LeftRight(float NewAxisValue)
{
	DirectionToMove.X = NewAxisValue * MovingSpeed;
}

TSharedPtr<IB1Skill> AB1Character::Factory(uint32 SkillNum)
{
	TSharedPtr<IB1Skill> skill = nullptr;
	switch (SkillNum)
	{
	case 1000:
		skill = MakeShareable(new B1Skill1000());
		break;
	case 1001:
		skill = MakeShareable(new B1Skill1001());
		break;
	case 1002:
		skill = MakeShareable(new B1Skill1002());
		break;
	case 1003:
		skill = MakeShareable(new B1Skill1003());
		break;
	case 1004:
		skill = MakeShareable(new B1Skill1004());
		break;
	case 1005:
		skill = MakeShareable(new B1Skill1005());
		break;
	}
	return skill;
}
