// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Character.h"
#include "B1AIController.h"
#include "Misc/DateTime.h"
#include "Components/WidgetComponent.h"
#include "B1HPWidget.h"

// Sets default values
AB1Character::AB1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-75.0f, -90.0f, 0.0f));


	//���� ��ġ
	//SetActorLocation(FVector(-2560.0f, 0.0f, 0.0f), false);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("B1Character"));
	
	//������ ������ ĳ���Ϳ����� �ε�
	//����UI���� �Է� ���� ���� �����´�. 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ResSkCommoner(*RES_SK_COMMONER);
	if (ResSkCommoner.Succeeded()) {
		GetMesh()->SetSkeletalMesh(ResSkCommoner.Object);
		GetMesh()->AddLocalRotation(FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->AddRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ResAnimInstPlayer(*RES_ANIM_INST_PLAYER);
	if (ResAnimInstPlayer.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(ResAnimInstPlayer.Class);
	}

	AIControllerClass = AB1AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> ResWidgetHP(*RES_WIDGET_HP);
	if (ResWidgetHP.Succeeded())
	{
		HPBarWidget->SetWidgetClass(ResWidgetHP.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
		HUDWidgetClass = ResWidgetHP.Class;
	}

	MaxHP = HP = 100.0f;
}
void AB1Character::RunSkill(IB1Skill* skill)
{
	Skill = skill;
}
void AB1Character::StopSkill()
{
	Skill = nullptr;
}
void AB1Character::CheckAttack()
{
	if (nullptr != Skill) {
		Skill->CheckAttack();
	}
}
// Called when the game starts or when spawned
void AB1Character::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr) {
		//BeginPlay() �Լ�����  SetWidgetClass �ؾ� �Ѵ�. 
		//���������� BeginPlay ���� Ȯ���ϰ� �����ϱ� ����
		auto CharacterWidget = Cast<UB1HPWidget>(HPBarWidget->GetUserWidgetObject());
		if (nullptr != CharacterWidget)
		{
			CharacterWidget->BindCharacterStat(this);
		}
	}

}
void AB1Character::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode) {
	case EControlMode::QUARTER_VIEW:
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritYaw = false;
		SpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

		break;
	case EControlMode::NPC:
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
		break;
	}
}
// Called every frame
void AB1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDeath){
		return;
	}

	if (DirectionToMove.SizeSquared() > 0.0f) {
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove);
	}

	if (nullptr != Skill) {
		Skill->Run();
	}
}
void AB1Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto AnimInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
	AnimInst->OnAttackHitCheck.AddUObject(this, &AB1Character::CheckAttack);
}
float AB1Character::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	//auto AnimInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInst->SetIsDeath(true);
	//IsDeath = true;
	//SetActorEnableCollision(false);

	OnHPChanged.Broadcast();
	
	return FinalDamage;
}
// Called to bind functionality to input
void AB1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AB1Character::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AB1Character::LeftRight);
}
void AB1Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (IsPlayerControlled()) {
		SetControlMode(EControlMode::QUARTER_VIEW);
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	else {
		SetControlMode(EControlMode::NPC);
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}
void AB1Character::UpDown(float NewAxisValue)
{
	DirectionToMove.Y = NewAxisValue * MovingSpeed;
}
void AB1Character::LeftRight(float NewAxisValue)
{
	DirectionToMove.X = NewAxisValue * MovingSpeed;
}

