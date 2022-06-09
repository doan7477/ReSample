// Fill out your copyright notice in the Description page of Project Settings.


#include "DZombie.h"
#include "DAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DZombieAnimInstance.h"

// Sets default values
ADZombie::ADZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//
	AIControllerClass = ADAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//Transform
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//CharacterMove
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;

	//Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_ZOMBIE(TEXT("/Game/Toon_Zombies/Meshes/Males/SK_M_Zombie_01.SK_M_Zombie_01"));
	if (SK_ZOMBIE.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_ZOMBIE.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance>ANIM_BP(TEXT("/Game/Sample/Enemy/Zombie/Animations/Male/AnimBP_Zombie_male.AnimBP_Zombie_male_C"));
	if (ANIM_BP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_BP.Class);
	}

	//State
	State = EZombieState::Idle;
	GenderType = EZombieGenderType::Male;
	CurMaxSpeed = 1.0f;
	HP = 100.0f;
}

// Called when the game starts or when spawned
void ADZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADZombie::Attack()
{
	auto AnimInstance = Cast<UDZombieAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr) return;
	//UE_LOG(LogTemp, Warning, TEXT("Zombie Attack!!!"));
	AnimInstance->PlayAttackMontage();
}

float ADZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//UE_LOG(LogTemp, Warning, TEXT("Zombie Take Damage : %f"), Damage);
	HitEvent(Damage);
	return Damage;
}

void ADZombie::HitEvent(float DamageAmount)
{
	auto AnimInstance = Cast<UDZombieAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance == nullptr) return;
	HP -= DamageAmount;
	if (HP <= 0.0f)
	{
		Die();
		return;
	}
	AnimInstance->PlayHitMontage();
}

void ADZombie::Die()
{
}

