// Fill out your copyright notice in the Description page of Project Settings.

#include "DCharacter_Base.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "../Weapons/DWeapon.h"
#include "DAnimInstance.h"

// Sets default values
ADCharacter_Base::ADCharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	AimingCamScene = CreateDefaultSubobject<USceneComponent>(TEXT("AIMINGCAMSCENE"));
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FORWARDARROW"));
	Legs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LEGS"));
	Head = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HEAD"));
	Backpack = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BACKPACK"));
	ExtraEquipment = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EXTRAEQUIPMENT"));
	WeaponScene = CreateDefaultSubobject<USceneComponent>(TEXT("WEAPONSCENE"));
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	//Attach
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	AimingCamScene->SetupAttachment(SpringArm);
	ForwardArrow->SetupAttachment(GetCapsuleComponent());
	Head->SetupAttachment(GetMesh());
	Legs->SetupAttachment(GetMesh());
	Backpack->SetupAttachment(GetMesh());
	ExtraEquipment->SetupAttachment(GetMesh());
	WeaponScene->SetupAttachment(GetMesh(), "WeaponSocket_R");
	Weapon->SetupAttachment(WeaponScene);
	//Timeline
	SmoothCamCurveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CAMTIMELINE"));
	SmoothCamInterpFunction.BindUFunction(this, FName("SmoothCamInterpReturn"));
	SmoothCamTimelineFinish.BindUFunction(this, FName("SmoothCamOnFinish"));
	static ConstructorHelpers::FObjectFinder<UCurveFloat>CAM_CURVE(TEXT("/Game/Sample/Curve/CamChangeCurve.CamChangeCurve"));
	if (CAM_CURVE.Succeeded())
	{
		SmoothCamCurveFloat = CAM_CURVE.Object;
	}
	//Transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 180.0f;
	SpringArm->SocketOffset = FVector(0.0f, 77.0f, 25.0f);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 45.0f));
	AimingCamScene->SetRelativeLocation(FVector(38.8f, -24.5f, 0.0f));

	Camera->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	Camera->SetRelativeRotation(FRotator::ZeroRotator);

	//Mesh Setting
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_SOLDIER(TEXT("/Game/Toon_Soldiers_Armies/Meshes/Characters_Parts/Bodies/TSA_Body_G.TSA_Body_G"));
	if (SK_SOLDIER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_SOLDIER.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM_BP(TEXT("/Game/Sample/Character/Animations/AnimBP_Soldier.AnimBP_Soldier_C"));
	if (ANIM_BP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_BP.Class);
	}
	//Body
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_HEAD(TEXT("/Game/Toon_Soldiers_Armies/Meshes/Characters_Parts/Heads/TSA_Head_A1.TSA_Head_A1"));
	if (SK_HEAD.Succeeded()) Head->SetSkeletalMesh(SK_HEAD.Object);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_LEGS(TEXT("/Game/Toon_Soldiers_Armies/Meshes/Characters_Parts/Legs/TSA_Legs_A.TSA_Legs_A"));
	if (SK_LEGS.Succeeded()) Legs->SetSkeletalMesh(SK_LEGS.Object);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_BACKPACK(TEXT("/Game/Toon_Soldiers_Armies/Meshes/Characters_Parts/Equipment/TSA_backpack.TSA_backpack"));
	if (SK_BACKPACK.Succeeded()) Backpack->SetSkeletalMesh(SK_BACKPACK.Object);

	//Camera Setting
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = false;

	//Setting
	AttackType = EWeaponType::None;
	FireState = EFireState::Idle;
	MoveState = EMovementState::Walking;
	bEquipWeapon = false;
	bFiring = false;
	bAttacking = false;
	bAiming = false;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	TargetWalkSpeed = 500.0f;
	//
	CameraSensitivity = 6.0f;
	YawAngleMax = 100.0f;
	YawAngleMin = -100.0f;
}

// Called when the game starts or when spawned
void ADCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
	SmoothCamTimelineSetting();
}

void ADCharacter_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Legs->SetMasterPoseComponent(GetMesh());
	Head->SetMasterPoseComponent(GetMesh());
	Backpack->SetMasterPoseComponent(GetMesh());
	ExtraEquipment->SetMasterPoseComponent(GetMesh());
}

// Called every frame
void ADCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LerpSpeed();
}

// Called to bind functionality to input
void ADCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Axis
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ADCharacter_Base::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ADCharacter_Base::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ADCharacter_Base::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADCharacter_Base::Turn);

	//Action
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ADCharacter_Base::Attack);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Released, this, &ADCharacter_Base::AttackFinish);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &ADCharacter_Base::RunOn);
	PlayerInputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &ADCharacter_Base::RunOff);
	PlayerInputComponent->BindAction(TEXT("FreeView"), EInputEvent::IE_Pressed, this, &ADCharacter_Base::FreeViewOn);
	PlayerInputComponent->BindAction(TEXT("FreeView"), EInputEvent::IE_Released, this, &ADCharacter_Base::FreeViewOff);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &ADCharacter_Base::AimingOn);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &ADCharacter_Base::AimingOff);
}

bool ADCharacter_Base::IsEquipWeapon()
{
	return bEquipWeapon;
}

void ADCharacter_Base::MovementMode(EMovementState state)
{
	switch (state)
	{
		case EMovementState::Walking:
			MoveState = EMovementState::Walking;
			//GetCharacterMovement()->MaxWalkSpeed = 350.0f;
			TargetWalkSpeed = 500.0f;
		break;

		case EMovementState::Running:
			MoveState = EMovementState::Running;
			//GetCharacterMovement()->MaxWalkSpeed = 600.0f;
			TargetWalkSpeed = 600.0f;
		break;

		case EMovementState::Sprinting:
			MoveState = EMovementState::Sprinting;
			//GetCharacterMovement()->MaxWalkSpeed = 700.0f;
			TargetWalkSpeed = 700.0f;
		break;
	
		case EMovementState::Crouching:
			MoveState = EMovementState::Crouching;
			//GetCharacterMovement()->MaxWalkSpeed = 300.0f;
			TargetWalkSpeed = 300.0f;
		break;
	
		case EMovementState::Proning:
			MoveState = EMovementState::Proning;
			//GetCharacterMovement()->MaxWalkSpeed = 200.0f;
			TargetWalkSpeed = 200.0f;
		break;
	
		default:
			MoveState = EMovementState::Walking;
			//GetCharacterMovement()->MaxWalkSpeed = 350.0f;
			TargetWalkSpeed = 500.0f;
		break;
	}
}

void ADCharacter_Base::AnimBPUpdateAimPitchAndYaw(float PitchValue, float YawValue, bool IsPitch, bool IsYaw, float YawMin, float YawMax)
{
	auto AnimInstance = Cast<UDAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->UpdateAimPitchAndYaw_Implementation(PitchValue, YawValue, IsPitch, IsYaw, YawMin, YawMax);
}

void ADCharacter_Base::ResetRotation()
{
}

void ADCharacter_Base::MoveForward(float NewAxisValue)
{
	FVector ForwardVec = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(ForwardVec, NewAxisValue);
}

void ADCharacter_Base::MoveRight(float NewAxisValue)
{
	FVector RightVec = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(RightVec, NewAxisValue);
}

void ADCharacter_Base::LookUp(float NewAxisValue)
{
	float value = NewAxisValue * 0.2 * CameraSensitivity;
	AddControllerPitchInput(value);
	float AngleDegrees = (CameraSensitivity * 0.2f) * (UKismetMathLibrary::NormalizeAxis(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetControlRotation().Pitch));
	float PitchValue = UKismetMathLibrary::ClampAngle(AngleDegrees, -90.0f, 90.0f);
	AnimBPUpdateAimPitchAndYaw(PitchValue, 0.0f, true, false, 0.0f, 0.0f);
}

void ADCharacter_Base::Turn(float NewAxisValue)
{
	float value = NewAxisValue * 0.2 * CameraSensitivity;
	AddControllerYawInput(value);
	AnimBPUpdateAimPitchAndYaw(0.0f, CalculateAimOffsetYaw(), false, true, YawAngleMin, YawAngleMax);
}

void ADCharacter_Base::Attack()
{
	
	if (::IsValid(HasWeapon) == true)
	{
		if (bFiring == false)
		{
			bAttacking = true;
			//GetCharacterMovement()->bOrientRotationToMovement = true;
			GetWorld()->GetTimerManager().SetTimer(AutoAttackHandle,
				FTimerDelegate::CreateLambda([&]()
				{
					AutoAttackEvent();
				}), 0.05f, true);
		}
	}
}

void ADCharacter_Base::AttackFinish()
{
	AutoAttackFinish();
	bAttacking = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;

}

void ADCharacter_Base::RunOn()
{
	switch (MoveState)
	{
		case EMovementState::Walking:
			MovementMode(EMovementState::Running);
		break;
	
		case EMovementState::Running:
			
		break;
	
		case EMovementState::Sprinting:
			
		break;
	
		case EMovementState::Crouching:
			
		break;
	
		case EMovementState::Proning:
			
		break;
	
		default:
			
		break;
	}
}

void ADCharacter_Base::RunOff()
{
	switch (MoveState)
	{
	case EMovementState::Walking:
		
		break;

	case EMovementState::Running:
		MovementMode(EMovementState::Walking);
		break;

	case EMovementState::Sprinting:

		break;

	case EMovementState::Crouching:

		break;

	case EMovementState::Proning:

		break;

	default:

		break;
	}
}

void ADCharacter_Base::FreeViewOn()
{
	if (bEquipWeapon)
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}
}

void ADCharacter_Base::FreeViewOff()
{
	if (bEquipWeapon)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		bUseControllerRotationYaw = true;
	}
}

void ADCharacter_Base::LerpSpeed()
{
	//float CurMaxSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::Lerp(GetCharacterMovement()->MaxWalkSpeed, TargetWalkSpeed, 0.2f);
}

void ADCharacter_Base::AimingOn()
{
	if (bEquipWeapon == false) return;
	bAiming = true;
	SmoothCamCurveTimeline->Play();
}

void ADCharacter_Base::AimingOff()
{
	if (bEquipWeapon == false) return;
	bAiming = false;
	SmoothCamCurveTimeline->Reverse();
}

float ADCharacter_Base::CalculateAimOffsetYaw()
{
	FVector CameraVecNormal = UKismetMathLibrary::Normal(FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0.0f));
	FVector ForwardNormal = UKismetMathLibrary::Normal(FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0.0f));
	FVector RightNormal = UKismetMathLibrary::Normal(FVector(GetActorRightVector().X, GetActorRightVector().Y, 0.0f));
	float CamForwardAngle = UKismetMathLibrary::Dot_VectorVector(CameraVecNormal, ForwardNormal);
	float CamRightAngle = UKismetMathLibrary::Dot_VectorVector(CameraVecNormal, RightNormal);
	float YawAngle = UKismetMathLibrary::DegAcos(CamForwardAngle) * UKismetMathLibrary::SignOfFloat(CamRightAngle);
	return YawAngle;
}

void ADCharacter_Base::TimeDuringAiming()
{
	bool bYawAngleMin = CalculateAimOffsetYaw() < -100.0f;
	bool bYawAngleMax = CalculateAimOffsetYaw() > 100.0f;

	if (bYawAngleMax || bYawAngleMin)
	{
		ResetRotation();
	}
}

void ADCharacter_Base::SmoothCamTimelineSetting()
{
	if (SmoothCamCurveFloat)
	{
		SmoothCamCurveTimeline->AddInterpFloat(SmoothCamCurveFloat, SmoothCamInterpFunction);
		SmoothCamCurveTimeline->SetTimelineFinishedFunc(SmoothCamTimelineFinish);
		SmoothCamCurveTimeline->SetLooping(false);
	}
}

void ADCharacter_Base::SmoothCamInterpReturn(float value)
{
	FTransform ZeroTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	FTransform AimingCamTransform = AimingCamScene->GetRelativeTransform();
	FTransform CurTransform = UKismetMathLibrary::TLerp(ZeroTransform, AimingCamTransform, value);
	Camera->SetRelativeTransform(CurTransform);
	float TargetArmLength = UKismetMathLibrary::Lerp(180.0f, 150.0f, value);
	SpringArm->TargetArmLength = TargetArmLength;
}

void ADCharacter_Base::SmoothCamOnFinish()
{
	//
}

void ADCharacter_Base::EquipWeapon(ADWeapon* weapon)
{
	if (::IsValid(weapon) == false) return;
	if (::IsValid(HasWeapon) == true)
	{
		HasWeapon->Destroy();
		AttackType = EWeaponType::None;
	}
	bEquipWeapon = true;
	HasWeapon = weapon;
	HasWeapon->SetPlayer(this);
	HasWeapon->AttachToComponent(WeaponScene, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//HasWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("WeaponSocket_R"));
	HasWeapon->SetOwner(this);
	AttackType = HasWeapon->WeaponData.WeaponType;
	//UE_LOG(LogTemp, Warning, TEXT("Equip Weapon!!!"));
	//View Setting
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	//MaxSpeedSetting
}

void ADCharacter_Base::AutoAttackEvent()
{
	auto AnimInstance = Cast<UDAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr) return;
	if (bFiring == true) return;
	AnimInstance->PlayAttackMontage(HasWeapon->WeaponData.AttackMontage);
	bFiring = true;
	HasWeapon->AttackEvent();
	HasWeapon->FireProjectile();
	UE_LOG(LogTemp, Warning, TEXT("Attack!!!"));
}

void ADCharacter_Base::AutoAttackFinish()
{
	UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this, AutoAttackHandle);
	UE_LOG(LogTemp, Warning, TEXT("AttackFinish"));
}

