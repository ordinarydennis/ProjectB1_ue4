// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Character.h"
#include "B1AIController.h"
#include "B1PlayerController.h"
#include "Misc/DateTime.h"
#include "Components/WidgetComponent.h"
#include "B1HPWidget.h"
#include "B1Weapon.h"

// Sets default values
AB1Character::AB1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetRelativeRotation(FRotator(-50.0f, -90.0f, 0.0f));

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
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> ResWidgetHP(*RES_WIDGET_HP);
	if (ResWidgetHP.Succeeded())
	{
		HPBarWidget->SetWidgetClass(ResWidgetHP.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
		HUDWidgetClass = ResWidgetHP.Class;
	}

	MaxHP = HP = 100.0f;
	AttackEndComboState();
}
void AB1Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
	//ABCHECK(nullptr != ABAnim);
	AnimInst->OnCheckAttackHit.AddUObject(this, &AB1Character::CheckAttackHit);
	//AnimInst->OnCheckSkillHit.AddUObject(this, &AB1Character::CheckSkillHit);

	AnimInst->OnMontageEnded.AddDynamic(this, &AB1Character::OnAttackMontageEnded);

	AnimInst->OnCheckNextAttack.AddLambda([this]() -> void {
			CanNextCombo = false;
			if (IsComboInputOn)
			{
				AttackStartComboState();
				AnimInst->JumpToAttackMontageSection(CurrentCombo);
			}
		}
	);
}
void AB1Character::RunAttack()
{
	//auto AnimInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInst->PlayAttack();
	//AnimInst->SetIsAttack(true);

	if (IsAttacking)
	{
		//ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (CanNextCombo)
		{
			IsComboInputOn = true;
		}
	}
	else
	{
		AttackStartComboState();
		AnimInst->PlayAttack();
		AnimInst->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	}

}
void AB1Character::RunSkill(IB1Skill* skill)
{
	Skill = skill;
}

void AB1Character::StopSkill()
{
	Skill = nullptr;
}
void AB1Character::CheckAttackHit()
{
	float FinalAttackRange = 150.f;
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = this->GetWorld()->SweepSingleByChannel(
		HitResult,
		this->GetActorLocation(),
		this->GetActorLocation() + this->GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

#if ENABLE_DRAW_DEBUG
	FVector TraceVec = this->GetActorForwardVector() * FinalAttackRange;
	FVector Center = this->GetActorLocation() + TraceVec * 0.5f;
	float AttackRadius = 50.f;
	float HalfHeight = FinalAttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 2.0f;

	DrawDebugCapsule(this->GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult) {
		if (HitResult.Actor.IsValid())
		{
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(5, DamageEvent, this->GetController(), this);
		}
	}
}
void AB1Character::CheckSkillHit()
{
	//if (nullptr != Skill) {
	//	Skill->CheckAttack();
	//}
}
void AB1Character::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	//printf("OnAttackMontageEnded");
	IsAttacking = false;
	AttackEndComboState();
	//OnAttackEnd.Broadcast();
}
// Called when the game starts or when spawned
void AB1Character::BeginPlay()
{
	Super::BeginPlay();
	
	B1PlayerController = Cast<AB1PlayerController>(GetController());

	if (HUDWidgetClass != nullptr) {
		//BeginPlay() �Լ�����  SetWidgetClass �ؾ� �Ѵ�. 
		//���������� BeginPlay ���� Ȯ���ϰ� �����ϱ� ����
		auto CharacterWidget = Cast<UB1HPWidget>(HPBarWidget->GetUserWidgetObject());
		if (nullptr != CharacterWidget)
		{
			CharacterWidget->BindCharacterStat(this);
		}
	}

	FName WeaponSocket(TEXT("hand_lSocket"));
	if (GetMesh()->DoesSocketExist(WeaponSocket)) {
		auto Weapon = GetWorld()->SpawnActor<AB1Weapon>(FVector::ZeroVector, FRotator::ZeroRotator);
		if (nullptr != Weapon) {
			Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
	}
	else {
		printf("WeaponSocket fail");
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
void AB1Character::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}
void AB1Character::AttackEndComboState()
{
	CanNextCombo = false;
	IsComboInputOn = false;
	CurrentCombo = 0;
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
float AB1Character::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	//auto AnimInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInst->SetIsDeath(true);
	//IsDeath = true;
	//SetActorEnableCollision(false);

	HP -= DamageAmount;
	if (KINDA_SMALL_NUMBER > HP) {
		//auto AnimInst = Cast<UB1AnimInstance>(GetMesh()->GetAnimInstance());
		AnimInst->SetIsDeath(true);
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		HPBarWidget->SetHiddenInGame(true);
		DisableInput(B1PlayerController);
		IsDeath = true;
	}

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

