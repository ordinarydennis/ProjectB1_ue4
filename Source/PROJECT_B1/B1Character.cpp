// Fill out your copyright notice in the Description page of Project Settings.


#include "B1Character.h"
#include "B1InGameWidget.h"

// Sets default values
AB1Character::AB1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength = 350.0f;
	SpringArm->SetRelativeRotation(FRotator(-75.0f, 0.0f, 0.0f));

	//ArmLengthTo = 350.0f;
	//ArmRotationTo = FRotator(-70.0f, 0.0f, 0.0f);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

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
}
void AB1Character::RunSkill(BTN_SKILL_INDEX BtnSkillIdx)
{
	//printf("RunSkill BtnSkillIdx: %d", BtnSkillIdx);
	//현재 스킬 세팅 
	//CurrentSkillAnimNum = (int32)BtnSkillIdx;
}
//ERES_ANIM_NUM AB1Character::GetCurrentSkillAnimNum()
//{
//	return CurrentSkillAnimNum;
//}
//void AB1Character::SetCurrentSkillAnimNum(int32 SkillAnimNum)
//{
//	CurrentSkillAnimNum = (RES_ANIM_NUM)(SkillAnimNum + 1000);
//}
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
	DirectionToMove.X = NewAxisValue * MovingSpeed;
}
void AB1Character::LeftRight(float NewAxisValue)
{
	DirectionToMove.Y = NewAxisValue * MovingSpeed;
}

